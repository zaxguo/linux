#ifndef __COMMON_REPLAY_H
#define __COMMON_REPLAY_H
extern void* dma_ctx;

static int tag_cnt = 0xd8;
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
	print_hex_dump(KERN_WARNING, "urb:", DUMP_PREFIX_ADDRESS, 16, 4, virt, 31, 1);
	command_virt = virt;
	return addr;
}

/* lwg: csw is encoded as a response to the same DMA buffer as CMD */
static dma_addr_t prepare_csw(void) {
	dma_addr_t addr;
	void *virt = dma_zalloc_coherent(dma_ctx, 512, &addr, GFP_KERNEL);
	int *word = (int *)virt;
	/* USBS */
	*word = 0x53425355;
	*(word + 1) = tag_cnt++;
	//command_virt = virt;
	return addr;
}

static dma_addr_t prepare_data(void) {
	dma_addr_t addr;
	void *virt = dma_zalloc_coherent(dma_ctx, 4096, &addr, GFP_KERNEL);
	memset(virt, 0xee, 4096);
	//printk("setting data page to %02x\n", toggle);
	return addr;
}

static dma_addr_t prepare_read_10(uint8_t len) {
	dma_addr_t addr;
	void *virt = dma_zalloc_coherent(dma_ctx, 31, &addr, GFP_KERNEL);
	int *word = (int *)virt;
	*word = 0x43425355;
	*(word + 1) = tag_cnt++;
	*(word + 2) = len * 512;
	*(word + 3) = 0x280a0080;
	*(uint8_t *)(virt + 0x17) = len;
	command_virt = virt;
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
	*(word + 2) = len * 512;
#if 0
	if (len == 8) {
		*(word + 2) = 0x00001000;
	} else if(len == 16) {
		*(word + 2) = 0x00002000;
	} else if (len == 32) {
		*(word + 2) = 0x00004000;
	} else if(len == 128) {
		*(word + 2) = 0x00010000;
	} else if (len == 240) {
		*(word + 2) = 0x00020000;
	} else {
		printk("unsupported!!\n");
	}
#endif
	*(word + 3) = 0x2a0a0000;
	/* # of sectors */
	*(uint8_t *)(virt + 0x17) = len;
#if 0
	if (len == 240) {
		*(uint8_t *)(virt + 0x17) = 0x10;
		*(uint8_t *)(virt + 0x14) = 0xf0;
	}
#endif
	//print_hex_dump(KERN_WARNING, "bcd:", DUMP_PREFIX_ADDRESS, 16, 4, virt, 31, 1);
	command_virt = virt;
	return addr;
}

static void dump_csw(void) {
	print_hex_dump(KERN_WARNING, "csw:", DUMP_PREFIX_ADDRESS, 16, 4, command_virt, 32, 1);
}

static void _poll_for_irq(void *host, int line) {
	int tries = 0;
	u32 val = 0;
	do {
		/* gintsts */
		val = readl(host + 0x14);
		tries++;
		// taken value from device_hibernation_restore
		if (tries > 20000){
			printk("poll failed for IRQ[%d]!!! val = %08x\n", line, val);
			break;
		}
		udelay(1);
		/* hcintr bit */
	} while((val &= 0x02000000) == 0);
}

static void _poll_bit_with_max_tries(void *addr, int bit, int tries, int line) {
	int ret = 0;
	do {
		ret = readl(addr);
		udelay(1);
	} while((--tries) && ((ret &= (1 << bit)) == 0));
	if (tries == 0) {
		printk("timeout[%d]! ret = %08x\n", line, ret);
	}

}

static void _poll_value_with_max_tries(void *addr, int val, int tries, int line) {
	int ret;
	int i = tries;
	do {
		ret = readl(addr);
		udelay(10);
	} while ((--tries) && (ret != val));
	if (tries == 0) {
		printk("timeout[%d]! %08x != %08x\n", line, ret, val);
	}
}

static void _poll_less_than_with_max_tries(void *addr, int val, int tries, int line) {
	u32 ret;
	do {
		ret = readl(addr);
		udelay(1);
	} while ((--tries) && (ret < val));
	if (tries == 0) {
		printk("timeout[%d]! %08x != %08x\n", line, ret, val);
	}
}

/* assuming a fixed ep number 2 */
static void reset_ep(void) {

}

static inline void _read(void *base, u32 off, u32 expect, int line) {
	u32 val = readl(base + off);
	/* hcchar dev addr must be patched... */
	if (off == 0x500) {
		/* a dev addr bit has been incremented by 1 */
		expect |= 0x00400000;
	}
	if (expect != IGNORE && val != expect) {
		printk("divergence@off[0x%x:%d]!! %08x != %08x\n", off, line, val, expect);
#if 1
		/* gnptxsts */
		if (off == 0x2c) {
			trace_printk("divergence@off[0x%x:%d]!! %08x != %08x\n", off, line, val, expect);
		}
		/* only care about xsac error bit on */
		if (off == 0x508 && (val & (1 << 7))) {
			printk("divergence@off[0x%x:%d]!! %08x != %08x\n", off, line, val, expect);
		}
#endif
	}
}


static inline void write(void *base, u32 off, u32 val) {
	u32 _val = val;
	/* patch hcchar dev addr fields */
	if (off == 0x500) {
		_val |= 0x00400000;
	}
	printk("writing %08x to off %08x\n", _val, off);
	writel(_val, base + off);
}
#define read(b, o, v) _read((b), (o), (v), __LINE__)
#define poll_for_irq(b) _poll_for_irq((b), __LINE__)
#define poll_bit_with_max_tries(b, v, t) _poll_bit_with_max_tries((b), (v), (t), __LINE__)
#define poll_value_with_max_tries(b, v, t) _poll_value_with_max_tries((b), (v), (t), __LINE__)
#define poll_less_than_with_max_tries(b, v, t) _poll_value_with_max_tries((b), (v), (t), __LINE__)

#endif __COMMON_REPLAY_H


