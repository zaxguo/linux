#ifndef __COMMON_REPLAY_H
#define __COMMON_REPLAY_H
extern void* dma_ctx;

static int tag_cnt = 0xf00;
static int toggle = 0;

#define IGNORE	0xdeadbeef
void *command_virt;

static dma_addr_t prepare_allow_medium_removal(int flag) {
	dma_addr_t addr;
	void *virt = dma_zalloc_coherent(dma_ctx, 31, &addr, GFP_KERNEL);
	int *word = (int *)virt;
	/* USBC signature */
	*word = 0x43425355;
	/* tag */
	*(word + 1) = tag_cnt++;
	*(word + 3) = 0x1e060000;
	if (flag == 1)
		*(uint8_t *)(virt + 0x13) = 0x01;
	//print_hex_dump(KERN_WARNING, "urb:", DUMP_PREFIX_ADDRESS, 16, 4, virt, 31, 1);
	command_virt = virt;
	return addr;
}

static dma_addr_t prepare_csw(void) {
	dma_addr_t addr;
	void *virt = dma_zalloc_coherent(dma_ctx, 512, &addr, GFP_KERNEL);
	int *word = (int *)virt;
	/* USBS */
	*word = 0x53425355;
	*(word + 1) = tag_cnt++;
	return addr;
}

static dma_addr_t prepare_data(void) {
	dma_addr_t addr;
	void *virt = dma_zalloc_coherent(dma_ctx, 4096, &addr, GFP_KERNEL);
	memset(virt, toggle, 4096);
	//printk("setting data page to %02x\n", toggle);
	return addr;
}

static dma_addr_t prepare_write_10(uint8_t len) {
	dma_addr_t addr;
	void *virt = dma_zalloc_coherent(dma_ctx, 31, &addr, GFP_KERNEL);
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
	//print_hex_dump(KERN_WARNING, "bcd:", DUMP_PREFIX_ADDRESS, 16, 4, virt, 31, 1);
	command_virt = virt;
	return addr;
}

static void dump_csw(void) {
	//print_hex_dump(KERN_WARNING, "csw:", DUMP_PREFIX_ADDRESS, 16, 4, command_virt, 13, 1);
}

static void poll_for_irq(void *host) {
	int tries = 0;
	u32 val = 0;
	do {
		/* gintsts */
		val = readl(host + 0x14);
		tries++;
		// taken value from device_hibernation_restore
		if (tries > 20000){
			printk("poll failed for IRQ!!! val = %08x\n", val);
			break;
		}
		//udelay(1);
		/* hcintr bit */
	} while((val &= 0x02000000) == 0);
}

static void poll_with_max_tries(void *addr, int val, int tries) {
	int ret = 0;
	int i = tries;
	do {
		ret = readl(addr);
		udelay(1);
	} while((--tries) && (ret != val));
}

/* assuming a fixed ep number 2 */
static void reset_ep(void) {

}

static inline void read(void *base, u32 off, u32 expect) {
	u32 val = readl(base + off);
	if (expect != IGNORE && val != expect) {
		//printk("divergence@off[0x%x]!! %08x != %08x\n", off, val, expect);
#if 1
		/* only care about xsac error bit on */
		if (off == 0x508 && (val & (1 << 7))) {
			printk("divergence@off[0x%x]!! %08x != %08x\n", off, val, expect);
		}
#endif
	}
}

static inline void write(void *base, u32 off, u32 val) {
	//printk("writing %08x to off %08x\n", val, off);
	writel(val, base + off);
}

#endif __COMMON_REPLAY_H


