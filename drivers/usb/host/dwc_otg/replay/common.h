#ifndef __COMMON_REPLAY_H
#define __COMMON_REPLAY_H
extern void* dma_ctx;

static int tag_cnt = 0x43;
static int toggle = 0;

#define IGNORE	0xdeadbeef

static dma_addr_t prepare_allow_medium_removal(int flag) {
	dma_addr_t addr;
	void *virt = dma_zalloc_coherent(dma_ctx, 31, &addr, GFP_ATOMIC);
	int *word = (int *)virt;
	/* USBC signature */
	*word = 0x43425355;
	/* tag */
	*(word + 1) = tag_cnt++;
	*(word + 3) = 0x1e060000;
	if (flag == 1)
		*(uint8_t *)(virt + 0x13) = 0x01;
	print_hex_dump(KERN_WARNING, "urb:", DUMP_PREFIX_ADDRESS, 16, 4, virt, 31, 1);
	return addr;
}

static dma_addr_t prepare_csw(void) {
	dma_addr_t addr;
	void *virt = dma_zalloc_coherent(dma_ctx, 512, &addr, GFP_ATOMIC);
	int *word = (int *)virt;
	*word = 0x43425355;
	*(word + 1) = tag_cnt++;
	return addr;
}

static dma_addr_t prepare_data(void) {
	dma_addr_t addr;
	void *virt = dma_zalloc_coherent(dma_ctx, 4096, &addr, GFP_ATOMIC);
	memset(virt, toggle, 4096);
	return addr;
}

static dma_addr_t prepare_write_10(uint8_t len) {
	dma_addr_t addr;
	void *virt = dma_zalloc_coherent(dma_ctx, 31, &addr, GFP_ATOMIC);
	int *word = (int *)virt;
	/* USBC signature */
	*word = 0x43425355;
	/* tag */
	*(word + 1) = tag_cnt++;
	*(word + 2) = 0x00001000;
	if (len == 32)
		*(word + 2) = 0x00004000;
	*(word + 3) = 0x2a0a0000;
	/* # of sectors */
	*(uint8_t *)(virt + 0x17) = len;
	print_hex_dump(KERN_WARNING, "bcd:", DUMP_PREFIX_ADDRESS, 16, 4, virt, 31, 1);
	return addr;
}

static void poll_for_irq(void *host) {
	int tries = 0;
	u32 val = 0;
	do {
		/* gintsts */
		val = readl(host + 0x14);
		tries++;
		//printk("val = %08x!!!\n", val);
		if (tries > 100){
			printk("poll failed for IRQ!!!\n");
			break;
		}
		mdelay(1);
		/* hcintr bit */
	} while((val &= 0x02000000) == 0);
}

static inline void read(void *base, u32 off, u32 expect) {
	u32 val = readl(base + off);
	if (expect != IGNORE && val != expect) {
		printk("divergence!! %08x != %08x\n", val, expect);
	}
}

static inline void write(void *base, u32 off, u32 val) {
	printk("writing %08x to off %08x\n", val, off);
	writel(val, base + off);
}

#endif __COMMON_REPLAY_H


