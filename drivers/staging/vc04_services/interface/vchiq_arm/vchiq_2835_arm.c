/**
 * Copyright (c) 2010-2012 Broadcom. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions, and the following disclaimer,
 *    without modification.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. The names of the above-listed copyright holders may not be used
 *    to endorse or promote products derived from this software without
 *    specific prior written permission.
 *
 * ALTERNATIVELY, this software may be distributed under the terms of the
 * GNU General Public License ("GPL") version 2, as published by the Free
 * Software Foundation.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
 * IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/errno.h>
#include <linux/interrupt.h>
#include <linux/pagemap.h>
#include <linux/dma-mapping.h>
#include <linux/io.h>
#include <linux/platform_device.h>
#include <linux/uaccess.h>
#include <linux/mm.h>
#include <linux/of.h>
#include <soc/bcm2835/raspberrypi-firmware.h>
/* lwg: dump memory */
#include <linux/binfmts.h>
#include <linux/coredump.h>
#include <linux/elf.h>
#include <linux/proc_fs.h>

#define TOTAL_SLOTS (VCHIQ_SLOT_ZERO_SLOTS + 2 * 32)

#include "vchiq_arm.h"
#include "vchiq_connected.h"
#include "vchiq_killable.h"
#include "vchiq_pagelist.h"

#define MAX_FRAGMENTS (VCHIQ_NUM_CURRENT_BULKS * 2)

#define VCHIQ_PLATFORM_FRAGMENTS_OFFSET_IDX 0
#define VCHIQ_PLATFORM_FRAGMENTS_COUNT_IDX  1

#define BELL0	0x00
#define BELL2	0x08

#define MAX_SEGS 200
struct dump_cb {
	struct coredump_params *cprm;
	void *slot_virt;
	int seg_bytes;
	int segs;
	/* stores temporary snapshot */
	void *stash[MAX_SEGS];
};

void *slot_virt;
int slot_dump_size;
struct dump_cb* cb;

static struct file* file_open(const char *path, int flags, int rights) {
	struct file *filp = NULL;
	mm_segment_t oldfs;
	int err = 0;

	oldfs = get_fs();
	// set_fs(get_ds());
	set_fs(KERNEL_DS);
	filp = filp_open(path, flags, rights);
	set_fs(oldfs);
	if (IS_ERR(filp)) {
		err = PTR_ERR(filp);
		return NULL;
	}
	return filp;
}



static void fill_elf_header(struct elfhdr *elf, int segs,
			    u16 machine, u32 flags)
{
	memset(elf, 0, sizeof(*elf));

	memcpy(elf->e_ident, ELFMAG, SELFMAG);
	elf->e_ident[EI_CLASS] = ELF_CLASS;
	elf->e_ident[EI_DATA] = ELF_DATA;
	elf->e_ident[EI_VERSION] = EV_CURRENT;
	elf->e_ident[EI_OSABI] = ELF_OSABI;

	elf->e_type = ET_CORE;
	elf->e_machine = machine;
	elf->e_version = EV_CURRENT;
	elf->e_phoff = sizeof(struct elfhdr);
	elf->e_flags = flags;
	elf->e_ehsize = sizeof(struct elfhdr);
	elf->e_phentsize = sizeof(struct elf_phdr);
	elf->e_phnum = segs;
}



static int cam_replay_dump(struct seq_file *s, void *unused) {
	printk("start dumping..\n");
	struct coredump_params *cprm = cb->cprm;
	struct elfhdr elf;
	Elf_Half e_phnum;
	elf_addr_t e_shoff;
	int offset, dataoff, i;
	int segs = cb->segs;

	if (IS_ERR(cb->cprm->file)) {
		printk("prev file open failed! try again..\n");
		struct file *f = file_open("/tmp/msg_dump.elf", O_WRONLY | O_CREAT, 0644);
		if (!f) {
			printk("still cannot create! abort..\n");
		}
		cb->cprm->file = f;
		printk("successfully create dump file...\n");
	}

	e_phnum = (segs > PN_XNUM) ? PN_XNUM : segs;
	BUG_ON(e_phnum != segs);

	/* elfhdr */
	fill_elf_header(&elf, segs, ELF_ARCH, 0);
	offset += sizeof(elf);
	offset += segs * sizeof(struct elf_phdr);

	dataoff = offset = roundup(offset, ELF_EXEC_PAGESIZE);
	/* all segs */
	offset += (segs * cb->seg_bytes);
	e_shoff = offset;
	offset = dataoff;

	/* first dump elf header */
	if (!dump_emit(cprm, &elf, sizeof(elf))) {
		printk("cannot dump header!...\n");
	}

	/* then dump program header */
	for (i = 0; i < segs; i++) {
		struct elf_phdr phdr;
		phdr.p_type = PT_LOAD;
		phdr.p_offset = offset;
		phdr.p_vaddr = 0;
		phdr.p_paddr = 0;
		/* lwg: XXX page aligned? */
		phdr.p_memsz = cb->seg_bytes;
		phdr.p_filesz = cb->seg_bytes;
		phdr.p_flags = (PF_R|PF_W);
		phdr.p_align = ELF_EXEC_PAGESIZE;
		/* update offset */
		offset += phdr.p_filesz;

		if (!dump_emit(cprm, &phdr, sizeof(phdr))) {
			printk("failed to dump %d phdr\n", i);
		}
	}

	/* finally dump data */
	/* align to page */
	if (!dump_skip(cprm, dataoff - cprm->pos)) {
		printk("cannot align to page!\n");
	}

	for (i = 0; i < segs; i++) {
		if (!dump_emit(cprm, cb->stash[i], cb->seg_bytes)) {
			printk("fail to dump %d at stash! (size = %d)\n", i, cb->seg_bytes);
		}
	}

	printk("finished dumping..\n");
	return 0;
}


static int cam_replay_open(struct inode *inode, struct file *file) {
	return single_open(file, cam_replay_dump, NULL);
}

static const struct file_operations cam_replay_ops = {
	.open = cam_replay_open,
	.read = seq_read,
	.llseek = seq_lseek,
	.release = single_release,
};


/* reference impl in elf_core_dump */
static void init_dump_cb(void *addr, size_t size) {
	struct coredump_params *cparam;
	struct file *f;
	int i;
	cparam = kmalloc(sizeof(struct coredump_params), GFP_KERNEL);
	cb = kmalloc(sizeof(struct dump_cb), GFP_KERNEL);
	BUG_ON(!cparam);
	BUG_ON(!cb);

	/* lwg: compiled into kernel just directly use filp_open */
	/*f = file_open("/tmp/msg_dump.elf", O_WRONLY | O_CREAT, 0644);*/
	f = filp_open("/tmp/msg_dump.elf", O_WRONLY | O_CREAT, 0644);
	if (!f) {
		printk("cannot create dump file!\n");
		return;
	}
	printk("lwg:%s:dump file opened @ %p\n", __func__, f);

	cparam->siginfo= NULL;
	cparam->regs = NULL;
	cparam->limit = 0xffffffff;
	cparam->file = f;
	cparam->written = 0;
	cparam->pos = 0;


	cb->cprm = cparam;
	cb->slot_virt = addr;
	cb->segs = 0;
	cb->seg_bytes = size;
	for (i = 0; i < MAX_SEGS; i++) {
		cb->stash[i] = NULL;
	}
	proc_create("cam_replay", 0, NULL, &cam_replay_ops);
	printk("dump cb initialized...\n");
	return 0;
}

static void take_snapshot(struct dump_cb *cb) {
	BUG_ON(!cb);
	/* lwg: by now wmb has been issued */
	void *tmp = kvmalloc(cb->seg_bytes, GFP_KERNEL);
	memcpy(tmp, cb->slot_virt, cb->seg_bytes);
	cb->stash[cb->segs++] = tmp;
	printk("kacha! segs = %d\n", cb->segs);
	return;
}

typedef struct vchiq_2835_state_struct {
	int inited;
	VCHIQ_ARM_STATE_T arm_state;
} VCHIQ_2835_ARM_STATE_T;

struct vchiq_pagelist_info {
	PAGELIST_T *pagelist;
	size_t pagelist_buffer_size;
	dma_addr_t dma_addr;
	enum dma_data_direction dma_dir;
	unsigned int num_pages;
	unsigned int pages_need_release;
	struct page **pages;
	struct scatterlist *scatterlist;
	unsigned int scatterlist_mapped;
};

static void __iomem *g_regs;
static unsigned int g_cache_line_size = sizeof(CACHE_LINE_SIZE);
static unsigned int g_fragments_size;
static char *g_fragments_base;
static char *g_free_fragments;
static struct semaphore g_free_fragments_sema;
static struct device *g_dev;

extern int vchiq_arm_log_level;

static DEFINE_SEMAPHORE(g_free_fragments_mutex);

static irqreturn_t
vchiq_doorbell_irq(int irq, void *dev_id);

static struct vchiq_pagelist_info *
create_pagelist(char __user *buf, size_t count, unsigned short type,
		struct task_struct *task);

static void
free_pagelist(struct vchiq_pagelist_info *pagelistinfo,
	      int actual);

int vchiq_platform_init(struct platform_device *pdev, VCHIQ_STATE_T *state)
{
	struct device *dev = &pdev->dev;
	struct rpi_firmware *fw = platform_get_drvdata(pdev);
	VCHIQ_SLOT_ZERO_T *vchiq_slot_zero;
	struct resource *res;
	void *slot_mem;
	dma_addr_t slot_phys;
	u32 channelbase;
	int slot_mem_size, frag_mem_size;
	int err, irq, i;

	/*
	 * VCHI messages between the CPU and firmware use
	 * 32-bit bus addresses.
	 */
	err = dma_set_mask_and_coherent(dev, DMA_BIT_MASK(32));

	if (err < 0)
		return err;

	err = of_property_read_u32(dev->of_node, "cache-line-size",
				   &g_cache_line_size);

	if (err) {
		dev_err(dev, "Missing cache-line-size property\n");
		return -ENODEV;
	}

	g_fragments_size = 2 * g_cache_line_size;

	/* Allocate space for the channels in coherent memory */
	slot_mem_size = PAGE_ALIGN(TOTAL_SLOTS * VCHIQ_SLOT_SIZE);
	frag_mem_size = PAGE_ALIGN(g_fragments_size * MAX_FRAGMENTS);

	/* lwg: of course its DMA address */
	slot_mem = dmam_alloc_coherent(dev, slot_mem_size + frag_mem_size,
				       &slot_phys, GFP_KERNEL);
	if (!slot_mem) {
		dev_err(dev, "could not allocate DMA memory\n");
		return -ENOMEM;
	}

	WARN_ON(((unsigned long)slot_mem & (PAGE_SIZE - 1)) != 0);

	vchiq_slot_zero = vchiq_init_slots(slot_mem, slot_mem_size);
	if (!vchiq_slot_zero)
		return -EINVAL;

	vchiq_slot_zero->platform_data[VCHIQ_PLATFORM_FRAGMENTS_OFFSET_IDX] =
		(int)slot_phys + slot_mem_size;
	/* lwg: we have 64 fragments */
	vchiq_slot_zero->platform_data[VCHIQ_PLATFORM_FRAGMENTS_COUNT_IDX] =
		MAX_FRAGMENTS;

	g_fragments_base = (char *)slot_mem + slot_mem_size;

	g_free_fragments = g_fragments_base;
	/* lwg: linked fragments??  */
	for (i = 0; i < (MAX_FRAGMENTS - 1); i++) {
		*(char **)&g_fragments_base[i*g_fragments_size] =
			&g_fragments_base[(i + 1)*g_fragments_size];
	}
	/* lwg: last frag points to NULL */
	*(char **)&g_fragments_base[i * g_fragments_size] = NULL;
	sema_init(&g_free_fragments_sema, MAX_FRAGMENTS);

	if (vchiq_init_state(state, vchiq_slot_zero, 0) != VCHIQ_SUCCESS)
		return -EINVAL;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	g_regs = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(g_regs))
		return PTR_ERR(g_regs);

	irq = platform_get_irq(pdev, 0);
	if (irq <= 0) {
		dev_err(dev, "failed to get IRQ\n");
		return irq;
	}

	err = devm_request_irq(dev, irq, vchiq_doorbell_irq, IRQF_IRQPOLL,
			       "VCHIQ doorbell", state);
	if (err) {
		dev_err(dev, "failed to register irq=%d\n", irq);
		return err;
	}

	/* lwg: set up dump control block before first irq  */
	slot_virt = slot_mem;
	slot_dump_size = slot_mem_size;
	init_dump_cb(slot_mem, slot_mem_size + frag_mem_size);

	/* Send the base address of the slots to VideoCore
	 * lwg: ha! */
	channelbase = slot_phys;
	err = rpi_firmware_property(fw, RPI_FIRMWARE_VCHIQ_INIT,
				    &channelbase, sizeof(channelbase));


	if (err || channelbase) {
		dev_err(dev, "failed to set channelbase\n");
		return err ? : -ENXIO;
	}

	g_dev = dev;
	vchiq_log_info(vchiq_arm_log_level,
		"vchiq_init - done (slots %pK, phys %pad)",
		vchiq_slot_zero, &slot_phys);

	vchiq_call_connected_callbacks();


	return 0;
}

VCHIQ_STATUS_T
vchiq_platform_init_state(VCHIQ_STATE_T *state)
{
	VCHIQ_STATUS_T status = VCHIQ_SUCCESS;

	state->platform_state = kzalloc(sizeof(VCHIQ_2835_ARM_STATE_T), GFP_KERNEL);
	((VCHIQ_2835_ARM_STATE_T *)state->platform_state)->inited = 1;
	status = vchiq_arm_init_state(state, &((VCHIQ_2835_ARM_STATE_T *)state->platform_state)->arm_state);
	if (status != VCHIQ_SUCCESS)
	{
		((VCHIQ_2835_ARM_STATE_T *)state->platform_state)->inited = 0;
	}
	return status;
}

VCHIQ_ARM_STATE_T*
vchiq_platform_get_arm_state(VCHIQ_STATE_T *state)
{
	if (!((VCHIQ_2835_ARM_STATE_T *)state->platform_state)->inited)
	{
		BUG();
	}
	return &((VCHIQ_2835_ARM_STATE_T *)state->platform_state)->arm_state;
}

void
remote_event_signal(REMOTE_EVENT_T *event)
{
	wmb();

	event->fired = 1;

	dsb(sy);         /* data barrier operation */


	/* record into tmp memory first */
	take_snapshot(cb);

	if (event->armed) {
		writel(0, g_regs + BELL2); /* trigger vc interrupt */
		printk("lwg:%s:%d:write 0 to BELL2\n", __func__, __LINE__);
	}
}

VCHIQ_STATUS_T
vchiq_prepare_bulk_data(VCHIQ_BULK_T *bulk, VCHI_MEM_HANDLE_T memhandle,
	void *offset, int size, int dir)
{
	struct vchiq_pagelist_info *pagelistinfo;

	WARN_ON(memhandle != VCHI_MEM_HANDLE_INVALID);

	pagelistinfo = create_pagelist((char __user *)offset, size,
				       (dir == VCHIQ_BULK_RECEIVE)
				       ? PAGELIST_READ
				       : PAGELIST_WRITE,
				       current);

	if (!pagelistinfo)
		return VCHIQ_ERROR;

	bulk->handle = memhandle;
	bulk->data = (void *)(unsigned long)pagelistinfo->dma_addr;

	/*
	 * Store the pagelistinfo address in remote_data,
	 * which isn't used by the slave.
	 */
	bulk->remote_data = pagelistinfo;

	return VCHIQ_SUCCESS;
}

void
vchiq_complete_bulk(VCHIQ_BULK_T *bulk)
{
	if (bulk && bulk->remote_data && bulk->actual)
		free_pagelist((struct vchiq_pagelist_info *)bulk->remote_data,
			      bulk->actual);
}

void
vchiq_transfer_bulk(VCHIQ_BULK_T *bulk)
{
	/*
	 * This should only be called on the master (VideoCore) side, but
	 * provide an implementation to avoid the need for ifdefery.
	 */
	BUG();
}

void
vchiq_dump_platform_state(void *dump_context)
{
	char buf[80];
	int len;

	len = snprintf(buf, sizeof(buf),
		"  Platform: 2835 (VC master)");
	vchiq_dump(dump_context, buf, len + 1);
}

VCHIQ_STATUS_T
vchiq_platform_suspend(VCHIQ_STATE_T *state)
{
	return VCHIQ_ERROR;
}

VCHIQ_STATUS_T
vchiq_platform_resume(VCHIQ_STATE_T *state)
{
	return VCHIQ_SUCCESS;
}

void
vchiq_platform_paused(VCHIQ_STATE_T *state)
{
}

void
vchiq_platform_resumed(VCHIQ_STATE_T *state)
{
}

int
vchiq_platform_videocore_wanted(VCHIQ_STATE_T *state)
{
	return 1; // autosuspend not supported - videocore always wanted
}

int
vchiq_platform_use_suspend_timer(void)
{
	return 0;
}
void
vchiq_dump_platform_use_state(VCHIQ_STATE_T *state)
{
	vchiq_log_info(vchiq_arm_log_level, "Suspend timer not in use");
}
void
vchiq_platform_handle_timeout(VCHIQ_STATE_T *state)
{
	(void)state;
}
/*
 * Local functions
 */

static irqreturn_t
vchiq_doorbell_irq(int irq, void *dev_id)
{
	VCHIQ_STATE_T *state = dev_id;
	irqreturn_t ret = IRQ_NONE;
	unsigned int status;

	/* Read (and clear) the doorbell */
	status = readl(g_regs + BELL0);
	printk("lwg:%s:%d:read %08x from BELL0\n", __func__, __LINE__, status);

	/* record upon irq */
	take_snapshot(cb);

	if (status & 0x4) {  /* Was the doorbell rung? */
		remote_event_pollall(state);
		ret = IRQ_HANDLED;
	}

	return ret;
}

static void
cleanup_pagelistinfo(struct vchiq_pagelist_info *pagelistinfo)
{
	if (pagelistinfo->scatterlist_mapped) {
		dma_unmap_sg(g_dev, pagelistinfo->scatterlist,
			     pagelistinfo->num_pages, pagelistinfo->dma_dir);
	}

	if (pagelistinfo->pages_need_release) {
		unsigned int i;

		for (i = 0; i < pagelistinfo->num_pages; i++)
			put_page(pagelistinfo->pages[i]);
	}

	dma_free_coherent(g_dev, pagelistinfo->pagelist_buffer_size,
			  pagelistinfo->pagelist, pagelistinfo->dma_addr);
}

/* There is a potential problem with partial cache lines (pages?)
** at the ends of the block when reading. If the CPU accessed anything in
** the same line (page?) then it may have pulled old data into the cache,
** obscuring the new data underneath. We can solve this by transferring the
** partial cache lines separately, and allowing the ARM to copy into the
** cached area.
*/

static struct vchiq_pagelist_info *
create_pagelist(char __user *buf, size_t count, unsigned short type,
		struct task_struct *task)
{
	PAGELIST_T *pagelist;
	struct vchiq_pagelist_info *pagelistinfo;
	struct page **pages;
	u32 *addrs;
	unsigned int num_pages, offset, i, k;
	int actual_pages;
	size_t pagelist_size;
	struct scatterlist *scatterlist, *sg;
	int dma_buffers;
	dma_addr_t dma_addr;

	offset = ((unsigned int)(unsigned long)buf & (PAGE_SIZE - 1));
	num_pages = DIV_ROUND_UP(count + offset, PAGE_SIZE);

	pagelist_size = sizeof(PAGELIST_T) +
			(num_pages * sizeof(u32)) +
			(num_pages * sizeof(pages[0]) +
			(num_pages * sizeof(struct scatterlist))) +
			sizeof(struct vchiq_pagelist_info);

	/* Allocate enough storage to hold the page pointers and the page
	** list
	*/
	pagelist = dma_zalloc_coherent(g_dev,
				       pagelist_size,
				       &dma_addr,
				       GFP_KERNEL);

	vchiq_log_trace(vchiq_arm_log_level, "create_pagelist - %pK",
			pagelist);
	if (!pagelist)
		return NULL;

	addrs		= pagelist->addrs;
	pages		= (struct page **)(addrs + num_pages);
	scatterlist	= (struct scatterlist *)(pages + num_pages);
	pagelistinfo	= (struct vchiq_pagelist_info *)
			  (scatterlist + num_pages);

	pagelist->length = count;
	pagelist->type = type;
	pagelist->offset = offset;

	/* Populate the fields of the pagelistinfo structure */
	pagelistinfo->pagelist = pagelist;
	pagelistinfo->pagelist_buffer_size = pagelist_size;
	pagelistinfo->dma_addr = dma_addr;
	pagelistinfo->dma_dir =  (type == PAGELIST_WRITE) ?
				  DMA_TO_DEVICE : DMA_FROM_DEVICE;
	pagelistinfo->num_pages = num_pages;
	pagelistinfo->pages_need_release = 0;
	pagelistinfo->pages = pages;
	pagelistinfo->scatterlist = scatterlist;
	pagelistinfo->scatterlist_mapped = 0;

	if (is_vmalloc_addr(buf)) {
		unsigned long length = count;
		unsigned int off = offset;

		for (actual_pages = 0; actual_pages < num_pages;
		     actual_pages++) {
			struct page *pg = vmalloc_to_page(buf + (actual_pages *
								 PAGE_SIZE));
			size_t bytes = PAGE_SIZE - off;

			if (!pg) {
				cleanup_pagelistinfo(pagelistinfo);
				return NULL;
			}

			if (bytes > length)
				bytes = length;
			pages[actual_pages] = pg;
			length -= bytes;
			off = 0;
		}
		/* do not try and release vmalloc pages */
	} else {
		down_read(&task->mm->mmap_sem);
		actual_pages = get_user_pages(
					  (unsigned long)buf & PAGE_MASK,
					  num_pages,
					  (type == PAGELIST_READ) ? FOLL_WRITE : 0,
					  pages,
					  NULL /*vmas */);
		up_read(&task->mm->mmap_sem);

		if (actual_pages != num_pages) {
			vchiq_log_info(vchiq_arm_log_level,
				       "create_pagelist - only %d/%d pages locked",
				       actual_pages,
				       num_pages);

			/* This is probably due to the process being killed */
			while (actual_pages > 0)
			{
				actual_pages--;
				put_page(pages[actual_pages]);
			}
			cleanup_pagelistinfo(pagelistinfo);
			return NULL;
		}
		 /* release user pages */
		pagelistinfo->pages_need_release = 1;
	}

	/*
	 * Initialize the scatterlist so that the magic cookie
	 *  is filled if debugging is enabled
	 */
	sg_init_table(scatterlist, num_pages);
	/* Now set the pages for each scatterlist */
	for (i = 0; i < num_pages; i++)	{
		unsigned int len = PAGE_SIZE - offset;

		if (len > count)
			len = count;
		sg_set_page(scatterlist + i, pages[i], len, offset);
		offset = 0;
		count -= len;
	}

	dma_buffers = dma_map_sg(g_dev,
				 scatterlist,
				 num_pages,
				 pagelistinfo->dma_dir);

	if (dma_buffers == 0) {
		cleanup_pagelistinfo(pagelistinfo);
		return NULL;
	}

	pagelistinfo->scatterlist_mapped = 1;

	/* Combine adjacent blocks for performance */
	k = 0;
	for_each_sg(scatterlist, sg, dma_buffers, i) {
		u32 len = sg_dma_len(sg);
		u32 addr = sg_dma_address(sg);

		/* Note: addrs is the address + page_count - 1
		 * The firmware expects blocks after the first to be page-
		 * aligned and a multiple of the page size
		 */
		WARN_ON(len == 0);
		WARN_ON(i && (i != (dma_buffers - 1)) && (len & ~PAGE_MASK));
		WARN_ON(i && (addr & ~PAGE_MASK));
		if (k > 0 &&
		    ((addrs[k - 1] & PAGE_MASK) +
		     (((addrs[k - 1] & ~PAGE_MASK) + 1) << PAGE_SHIFT))
		    == (addr & PAGE_MASK))
			addrs[k - 1] += ((len + PAGE_SIZE - 1) >> PAGE_SHIFT);
		else
			addrs[k++] = (addr & PAGE_MASK) |
				(((len + PAGE_SIZE - 1) >> PAGE_SHIFT) - 1);
	}

	/* Partial cache lines (fragments) require special measures */
	if ((type == PAGELIST_READ) &&
		((pagelist->offset & (g_cache_line_size - 1)) ||
		((pagelist->offset + pagelist->length) &
		(g_cache_line_size - 1)))) {
		char *fragments;

		if (down_interruptible(&g_free_fragments_sema) != 0) {
			cleanup_pagelistinfo(pagelistinfo);
			return NULL;
		}

		WARN_ON(g_free_fragments == NULL);

		down(&g_free_fragments_mutex);
		fragments = g_free_fragments;
		WARN_ON(fragments == NULL);
		g_free_fragments = *(char **) g_free_fragments;
		up(&g_free_fragments_mutex);
		pagelist->type = PAGELIST_READ_WITH_FRAGMENTS +
			(fragments - g_fragments_base) / g_fragments_size;
	}

	return pagelistinfo;
}

static void
free_pagelist(struct vchiq_pagelist_info *pagelistinfo,
	      int actual)
{
	PAGELIST_T *pagelist   = pagelistinfo->pagelist;
	struct page **pages    = pagelistinfo->pages;
	unsigned int num_pages = pagelistinfo->num_pages;

	vchiq_log_trace(vchiq_arm_log_level, "free_pagelist - %pK, %d",
			pagelistinfo->pagelist, actual);

	/*
	 * NOTE: dma_unmap_sg must be called before the
	 * cpu can touch any of the data/pages.
	 */
	dma_unmap_sg(g_dev, pagelistinfo->scatterlist,
		     pagelistinfo->num_pages, pagelistinfo->dma_dir);
	pagelistinfo->scatterlist_mapped = 0;

	/* Deal with any partial cache lines (fragments) */
	if (pagelist->type >= PAGELIST_READ_WITH_FRAGMENTS) {
		char *fragments = g_fragments_base +
			(pagelist->type - PAGELIST_READ_WITH_FRAGMENTS) *
			g_fragments_size;
		int head_bytes, tail_bytes;

		head_bytes = (g_cache_line_size - pagelist->offset) &
			(g_cache_line_size - 1);
		tail_bytes = (pagelist->offset + actual) &
			(g_cache_line_size - 1);

		if ((actual >= 0) && (head_bytes != 0)) {
			if (head_bytes > actual)
				head_bytes = actual;

			memcpy((char *)kmap(pages[0]) +
				pagelist->offset,
				fragments,
				head_bytes);
			kunmap(pages[0]);
		}
		if ((actual >= 0) && (head_bytes < actual) &&
			(tail_bytes != 0)) {
			memcpy((char *)kmap(pages[num_pages - 1]) +
				((pagelist->offset + actual) &
				(PAGE_SIZE - 1) & ~(g_cache_line_size - 1)),
				fragments + g_cache_line_size,
				tail_bytes);
			kunmap(pages[num_pages - 1]);
		}

		down(&g_free_fragments_mutex);
		*(char **)fragments = g_free_fragments;
		g_free_fragments = fragments;
		up(&g_free_fragments_mutex);
		up(&g_free_fragments_sema);
	}

	/* Need to mark all the pages dirty. */
	if (pagelist->type != PAGELIST_WRITE &&
	    pagelistinfo->pages_need_release) {
		unsigned int i;

		for (i = 0; i < num_pages; i++)
			set_page_dirty(pages[i]);
	}

	cleanup_pagelistinfo(pagelistinfo);
}
