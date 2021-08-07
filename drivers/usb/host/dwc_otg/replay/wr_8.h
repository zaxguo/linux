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

static dma_addr_t prepare_write_10(void) {
	dma_addr_t addr;
	void *virt = dma_zalloc_coherent(dma_ctx, 31, &addr, GFP_ATOMIC);
	int *word = (int *)virt;
	/* USBC signature */
	*word = 0x43425355;
	/* tag */
	*(word + 1) = tag_cnt++;
	*(word + 2) = 0x00001000;
	*(word + 3) = 0x2a0a0000;
	/* # of sectors */
	*(uint8_t *)(virt + 0x17) = 0x08;
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

static void wr_8(void *base) {
	dma_addr_t addr;
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 */
	read(base, 0x18, 0xf3000806);
	/* 1,&hc_regs->hcint,508,00003fff */
	write(base, 0x508, 0x00003fff);
	/* 1,&hc_regs->hcintmsk,50c,00000006 */
	write(base, 0x50c, 0x00000006);
	/* 1,&host_if->hc_regs[hc_num]->hcchar,500,01081200 */
	write(base, 0x500, 0x01081200);
	/* 1,&host_if->hc_regs[hc_num]->hcsplt,504,00000000 */
	write(base, 0x504, 0x00000000);
	/* 0,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 */
	read(base, 0x418, 0x00000001);
	/* 1,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 */
	write(base, 0x418, 0x00000001);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 */
	read(base, 0x18, 0xf3000806);
	/* 1,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 */
	write(base, 0x18, 0xf3000806);
	/* 0,&global_regs->gnptxsts,2c,00080100 */
	read(base, 0x2c, 0x00080100);
	addr = prepare_allow_medium_removal(1);
	/* 1,&hc_regs->hctsiz,510,0008001f */
	write(base, 0x510, 0x0008001f | ((toggle & 1) << 30));
	/* 1,&hc_regs->hcdma,514,f7053000 */
	write(base, 0x514, addr);
	/* 0,&hc_regs->hcchar,500,01081200 */
	read(base, 0x500, 0x01081200);
	/* 1,&hc_regs->hcchar,500,81181200 */
	write(base, 0x500, 0x81181200);
	poll_for_irq(base);
	/* 0,&core_if->core_global_regs->gpwrdn,58,00000000 */
	read(base, 0x58, 0x00000000);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 */
	read(base, 0x14, 0x06400029);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 */
	read(base, 0x18, 0xf3000806);
	/* 0,&core_if->core_global_regs->gahbcfg,8,00000031 */
	read(base, 0x8, 0x00000031);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 */
	read(base, 0x18, 0xf3000806);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 */
	read(base, 0x14, 0x06400029);
	/* 0,&dwc_otg_hcd->core_if->host_if->host_global_regs->hfnum,408,00f60576 */
	read(base, 0x408, IGNORE);
	/* 0,&_core_if->host_if->host_global_regs->haint,414,00000001 */
	read(base, 0x414, 0x00000001);
	/* 0,&hc_regs->hcint,508,00000023 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hcint,508,00000023 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hctsiz,510,4000001f */
	read(base, 0x510, 0x4000001f);
	/* 0,&hc_regs->hctsiz,510,4000001f */
	read(base, 0x510, 0x4000001f);
	/* 0,&hc_regs->hcint,508,00000023 */
	read(base, 0x508, 0x00000023);
	/* 1,&hc_regs->hcintmsk,50c,00000000 */
	write(base, 0x50c, 0x00000000);
	/* 1,&hc_regs->hcint,508,ffffffff */
	write(base, 0x508, 0xffffffff);
	/* 0,&(hc_regs)->hcintmsk,50c,00000000 */
	read(base, 0x50c, 0x00000000);
	/* 1,&(hc_regs)->hcintmsk,50c,00000000 */
	write(base, 0x50c, 0x00000000);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 */
	read(base, 0x18, 0xf3000806);
	/* 1,&hc_regs->hcint,508,00003fff */
	write(base, 0x508, 0x00003fff);
	/* 1,&hc_regs->hcintmsk,50c,00000006 */
	write(base, 0x50c, 0x00000006);
	/* 1,&host_if->hc_regs[hc_num]->hcchar,500,01089200 */
	write(base, 0x500, 0x01089200);
	/* 1,&host_if->hc_regs[hc_num]->hcsplt,504,00000000 */
	write(base, 0x504, 0x00000000);
	/* 0,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 */
	read(base, 0x418, 0x00000001);
	/* 1,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 */
	write(base, 0x418, 0x00000001);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 */
	read(base, 0x18, 0xf3000806);
	/* 1,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 */
	write(base, 0x18, 0xf3000806);
	/* 0,&global_regs->gnptxsts,2c,00080100 */
	read(base, 0x2c, 0x00080100);
	/* 1,&hc_regs->hctsiz,510,00080200 */
	//write(base, 0x510, 0x00080200);
	write(base, 0x510, 0x00080200 | ((toggle & 1) << 30));
	addr = prepare_csw();
	/* 1,&hc_regs->hcdma,514,f7053000 */
	write(base, 0x514, addr);
	/* 0,&hc_regs->hcchar,500,01089200 */
	read(base, 0x500, 0x01089200);
	/* 1,&hc_regs->hcchar,500,81189200 */
	write(base, 0x500, 0x81189200);
	/* poll for irq */
	poll_for_irq(base);
	toggle++;
	/* 0,&core_if->core_global_regs->gpwrdn,58,00000000 */
	read(base, 0x58, 0x00000000);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 */
	read(base, 0x14, 0x06400029);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 */
	read(base, 0x18, 0xf3000806);
	/* 0,&core_if->core_global_regs->gahbcfg,8,00000031 */
	read(base, 0x8, 0x00000031);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 */
	read(base, 0x18, 0xf3000806);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 */
	read(base, 0x14, 0x06400029);
	/* 0,&dwc_otg_hcd->core_if->host_if->host_global_regs->hfnum,408,14d60579 */
	read(base, 0x408, IGNORE);
	/* 0,&_core_if->host_if->host_global_regs->haint,414,00000001 */
	read(base, 0x414, 0x00000001);
	/* 0,&hc_regs->hcint,508,00000023 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hcint,508,00000023 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hctsiz,510,c00001f3 */
	read(base, 0x510, 0xc00001f3);
	/* 0,&hc_regs->hctsiz,510,c00001f3 */
	read(base, 0x510, 0xc00001f3);
	/* 0,&hc_regs->hcint,508,00000023 */
	read(base, 0x508, 0x00000023);
	/* 1,&hc_regs->hcintmsk,50c,00000000 */
	write(base, 0x50c, 0x00000000);
	/* 1,&hc_regs->hcint,508,ffffffff */
	write(base, 0x508, 0xffffffff);
	/* 0,&(hc_regs)->hcintmsk,50c,00000000 */
	read(base, 0x50c, 0x00000000);
	/* 1,&(hc_regs)->hcintmsk,50c,00000000 */
	write(base, 0x50c, 0x00000000);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 */
	read(base, 0x18, 0xf3000806);
	/* 1,&hc_regs->hcint,508,00003fff */
	write(base, 0x508, 0x00003fff);
	/* 1,&hc_regs->hcintmsk,50c,00000006 */
	write(base, 0x50c, 0x00000006);
	/* 1,&host_if->hc_regs[hc_num]->hcchar,500,01081200 */
	write(base, 0x500, 0x01081200);
	/* 1,&host_if->hc_regs[hc_num]->hcsplt,504,00000000 */
	write(base, 0x504, 0x00000000);
	/* 0,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 */
	read(base, 0x418, 0x00000001);
	/* 1,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 */
	write(base, 0x418, 0x00000001);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 */
	read(base, 0x18, 0xf3000806);
	/* 1,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 */
	write(base, 0x18, 0xf3000806);
	/* 0,&global_regs->gnptxsts,2c,00080100 */
	read(base, 0x2c, 0x00080100);
	/* 1,&hc_regs->hctsiz,510,4008001f */
	addr = prepare_write_10();
	//write(base, 0x510, 0x4008001f);
	write(base, 0x510, 0x0008001f | ((toggle & 1) << 30));
	/* 1,&hc_regs->hcdma,514,f7053000 */
	write(base, 0x514, addr);
	/* 0,&hc_regs->hcchar,500,01081200 */
	read(base, 0x500, 0x01081200);
	/* 1,&hc_regs->hcchar,500,81181200 */
	write(base, 0x500, 0x81181200);
	poll_for_irq(base);
	toggle++;
	/* 0,&core_if->core_global_regs->gpwrdn,58,00000000 */
	read(base, 0x58, 0x00000000);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 */
	read(base, 0x14, 0x06400029);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 */
	read(base, 0x18, 0xf3000806);
	/* 0,&core_if->core_global_regs->gahbcfg,8,00000031 */
	read(base, 0x8, 0x00000031);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 */
	read(base, 0x18, 0xf3000806);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 */
	read(base, 0x14, 0x06400029);
	/* 0,&dwc_otg_hcd->core_if->host_if->host_global_regs->hfnum,408,0f9f05d5 */
	read(base, 0x408, IGNORE);
	/* 0,&_core_if->host_if->host_global_regs->haint,414,00000001 */
	read(base, 0x414, 0x00000001);
	/* 0,&hc_regs->hcint,508,00000023 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hcint,508,00000023 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hctsiz,510,0000001f */
	read(base, 0x510, 0x0000001f);
	/* 0,&hc_regs->hctsiz,510,0000001f */
	read(base, 0x510, 0x0000001f);
	/* 0,&hc_regs->hcint,508,00000023 */
	read(base, 0x508, 0x00000023);
	/* 1,&hc_regs->hcintmsk,50c,00000000 */
	write(base, 0x50c, 0x00000000);
	/* 1,&hc_regs->hcint,508,ffffffff */
	write(base, 0x508, 0xffffffff);
	/* 0,&(hc_regs)->hcintmsk,50c,00000000 */
	read(base, 0x50c, 0x00000000);
	/* 1,&(hc_regs)->hcintmsk,50c,00000000 */
	write(base, 0x50c, 0x00000000);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 */
	read(base, 0x18, 0xf3000806);
	/* 1,&hc_regs->hcint,508,00003fff */
	write(base, 0x508, 0x00003fff);
	/* 1,&hc_regs->hcintmsk,50c,00000006 */
	write(base, 0x50c, 0x00000006);
	/* 1,&host_if->hc_regs[hc_num]->hcchar,500,01081200 */
	write(base, 0x500, 0x01081200);
	/* 1,&host_if->hc_regs[hc_num]->hcsplt,504,00000000 */
	write(base, 0x504, 0x00000000);
	/* 0,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 */
	read(base, 0x418, 0x00000001);
	/* 1,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 */
	write(base, 0x418, 0x00000001);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 */
	read(base, 0x18, 0xf3000806);
	/* 1,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 */
	write(base, 0x18, 0xf3000806);
	/* 0,&global_regs->gnptxsts,2c,00080100 */
	read(base, 0x2c, 0x00080100);
	addr = prepare_data();
	/* 1,&hc_regs->hctsiz,510,00401000 */
	//write(base, 0x510, 0x00401000);
	write(base, 0x510, 0x00401000 | ((toggle & 1) << 30));
	/* 1,&hc_regs->hcdma,514,d7a0c000 */
	write(base, 0x514, addr);
	/* 0,&hc_regs->hcchar,500,01081200 */
	read(base, 0x500, 0x01081200);
	/* 1,&hc_regs->hcchar,500,81181200 */
	write(base, 0x500, 0x81181200);
	poll_for_irq(base);
	toggle++;
	/* 0,&core_if->core_global_regs->gpwrdn,58,00000000 */
	read(base, 0x58, 0x00000000);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 */
	read(base, 0x14, 0x06400029);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 */
	read(base, 0x18, 0xf3000806);
	/* 0,&core_if->core_global_regs->gahbcfg,8,00000031 */
	read(base, 0x8, 0x00000031);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 */
	read(base, 0x18, 0xf3000806);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 */
	read(base, 0x14, 0x06400029);
	/* 0,&dwc_otg_hcd->core_if->host_if->host_global_regs->hfnum,408,0ca805d9 */
	read(base, 0x408, IGNORE);
	/* 0,&_core_if->host_if->host_global_regs->haint,414,00000001 */
	read(base, 0x414, 0x00000001);
	/* 0,&hc_regs->hcint,508,00000023 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hcint,508,00000023 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hctsiz,510,00000200 */
	read(base, 0x510, 0x00000200);
	/* 0,&hc_regs->hctsiz,510,00000200 */
	read(base, 0x510, 0x00000200);
	/* 0,&hc_regs->hcint,508,00000023 */
	read(base, 0x508, 0x00000023);
	/* 1,&hc_regs->hcintmsk,50c,00000000 */
	write(base, 0x50c, 0x00000000);
	/* 1,&hc_regs->hcint,508,ffffffff */
	write(base, 0x508, 0xffffffff);
	/* 0,&(hc_regs)->hcintmsk,50c,00000000 */
	read(base, 0x50c, 0x00000000);
	/* 1,&(hc_regs)->hcintmsk,50c,00000000 */
	write(base, 0x50c, 0x00000000);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 */
	read(base, 0x18, 0xf3000806);
	/* 1,&hc_regs->hcint,508,00003fff */
	write(base, 0x508, 0x00003fff);
	/* 1,&hc_regs->hcintmsk,50c,00000006 */
	write(base, 0x50c, 0x00000006);
	/* 1,&host_if->hc_regs[hc_num]->hcchar,500,01089200 */
	write(base, 0x500, 0x01089200);
	/* 1,&host_if->hc_regs[hc_num]->hcsplt,504,00000000 */
	write(base, 0x504, 0x00000000);
	/* 0,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 */
	read(base, 0x418, 0x00000001);
	/* 1,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 */
	write(base, 0x418, 0x00000001);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 */
	read(base, 0x18, 0xf3000806);
	/* 1,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 */
	write(base, 0x18, 0xf3000806);
	/* 0,&global_regs->gnptxsts,2c,00080100 */
	read(base, 0x2c, 0x00080100);
	addr = prepare_csw();
	/* 1,&hc_regs->hctsiz,510,40080200 */
	//write(base, 0x510, 0x40080200);
	write(base, 0x510, 0x00080200 | ((toggle & 1) << 30));
	/* 1,&hc_regs->hcdma,514,f7053000 */
	write(base, 0x514, addr);
	/* 0,&hc_regs->hcchar,500,01089200 */
	read(base, 0x500, 0x01089200);
	/* 1,&hc_regs->hcchar,500,81189200 */
	write(base, 0x500, 0x81189200);
	poll_for_irq(base);
	toggle++;
	/* 0,&core_if->core_global_regs->gpwrdn,58,00000000 */
	read(base, 0x58, 0x00000000);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 */
	read(base, 0x14, 0x06400029);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 */
	read(base, 0x18, 0xf3000806);
	/* 0,&core_if->core_global_regs->gahbcfg,8,00000031 */
	read(base, 0x8, 0x00000031);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 */
	read(base, 0x18, 0xf3000806);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 */
	read(base, 0x14, 0x06400029);
	/* 0,&dwc_otg_hcd->core_if->host_if->host_global_regs->hfnum,408,083105df */
	read(base, 0x408, IGNORE);
	/* 0,&_core_if->host_if->host_global_regs->haint,414,00000001 */
	read(base, 0x414, 0x00000001);
	/* 0,&hc_regs->hcint,508,00000023 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hcint,508,00000023 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hctsiz,510,800001f3 */
	read(base, 0x510, 0x800001f3);
	/* 0,&hc_regs->hctsiz,510,800001f3 */
	read(base, 0x510, 0x800001f3);
	/* 0,&hc_regs->hcint,508,00000023 */
	read(base, 0x508, 0x00000023);
	/* 1,&hc_regs->hcintmsk,50c,00000000 */
	write(base, 0x50c, 0x00000000);
	/* 1,&hc_regs->hcint,508,ffffffff */
	write(base, 0x508, 0xffffffff);
	/* 0,&(hc_regs)->hcintmsk,50c,00000000 */
	read(base, 0x50c, 0x00000000);
	/* 1,&(hc_regs)->hcintmsk,50c,00000000 */
	write(base, 0x50c, 0x00000000);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 */
	read(base, 0x18, 0xf3000806);
	/* 1,&hc_regs->hcint,508,00003fff */
	write(base, 0x508, 0x00003fff);
	/* 1,&hc_regs->hcintmsk,50c,00000006 */
	write(base, 0x50c, 0x00000006);
	/* 1,&host_if->hc_regs[hc_num]->hcchar,500,01081200 */
	write(base, 0x500, 0x01081200);
	/* 1,&host_if->hc_regs[hc_num]->hcsplt,504,00000000 */
	write(base, 0x504, 0x00000000);
	/* 0,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 */
	read(base, 0x418, 0x00000001);
	/* 1,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 */
	write(base, 0x418, 0x00000001);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 */
	read(base, 0x18, 0xf3000806);
	/* 1,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 */
	write(base, 0x18, 0xf3000806);
	/* 0,&global_regs->gnptxsts,2c,00080100 */
	read(base, 0x2c, 0x00080100);
	addr = prepare_allow_medium_removal(0);
	/* 1,&hc_regs->hctsiz,510,0008001f */
	write(base, 0x510, 0x0008001f | ((toggle & 1) << 30));
	/* 1,&hc_regs->hcdma,514,f7053000 */
	write(base, 0x514, addr);
	/* 0,&hc_regs->hcchar,500,01081200 */
	read(base, 0x500, 0x01081200);
	/* 1,&hc_regs->hcchar,500,81181200 */
	write(base, 0x500, 0x81181200);
	poll_for_irq(base);
	/* 0,&core_if->core_global_regs->gpwrdn,58,00000000 */
	read(base, 0x58, 0x00000000);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 */
	read(base, 0x14, 0x06400029);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 */
	read(base, 0x18, 0xf3000806);
	/* 0,&core_if->core_global_regs->gahbcfg,8,00000031 */
	read(base, 0x8, 0x00000031);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 */
	read(base, 0x18, 0xf3000806);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 */
	read(base, 0x14, 0x06400029);
	/* 0,&dwc_otg_hcd->core_if->host_if->host_global_regs->hfnum,408,11880634 */
	read(base, 0x408, IGNORE);
	/* 0,&_core_if->host_if->host_global_regs->haint,414,00000001 */
	read(base, 0x414, 0x00000001);
	/* 0,&hc_regs->hcint,508,00000023 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hcint,508,00000023 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hctsiz,510,4000001f */
	read(base, 0x510, 0x4000001f);
	/* 0,&hc_regs->hctsiz,510,4000001f */
	read(base, 0x510, 0x4000001f);
	/* 0,&hc_regs->hcint,508,00000023 */
	read(base, 0x508, 0x00000023);
	/* 1,&hc_regs->hcintmsk,50c,00000000 */
	write(base, 0x50c, 0x00000000);
	/* 1,&hc_regs->hcint,508,ffffffff */
	write(base, 0x508, 0xffffffff);
	/* 0,&(hc_regs)->hcintmsk,50c,00000000 */
	read(base, 0x50c, 0x00000000);
	/* 1,&(hc_regs)->hcintmsk,50c,00000000 */
	write(base, 0x50c, 0x00000000);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 */
	read(base, 0x18, 0xf3000806);
	/* 1,&hc_regs->hcint,508,00003fff */
	write(base, 0x508, 0x00003fff);
	/* 1,&hc_regs->hcintmsk,50c,00000006 */
	write(base, 0x50c, 0x00000006);
	/* 1,&host_if->hc_regs[hc_num]->hcchar,500,01089200 */
	write(base, 0x500, 0x01089200);
	/* 1,&host_if->hc_regs[hc_num]->hcsplt,504,00000000 */
	write(base, 0x504, 0x00000000);
	/* 0,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 */
	read(base, 0x418, 0x00000001);
	/* 1,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 */
	write(base, 0x418, 0x00000001);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 */
	read(base, 0x18, 0xf3000806);
	/* 1,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 */
	write(base, 0x18, 0xf3000806);
	/* 0,&global_regs->gnptxsts,2c,00080100 */
	read(base, 0x2c, 0x00080100);
	/* 1,&hc_regs->hctsiz,510,00080200 */
	write(base, 0x510, 0x00080200 | ((toggle & 1) << 30));
	addr = prepare_csw();
	/* 1,&hc_regs->hcdma,514,f7053000 */
	write(base, 0x514, addr);
	/* 0,&hc_regs->hcchar,500,01089200 */
	read(base, 0x500, 0x01089200);
	/* 1,&hc_regs->hcchar,500,81189200 */
	write(base, 0x500, 0x81189200);
	poll_for_irq(base);
	/* 0,&core_if->core_global_regs->gpwrdn,58,00000000 */
	read(base, 0x58, 0x00000000);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 */
	read(base, 0x14, 0x06400029);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 */
	read(base, 0x18, 0xf3000806);
	/* 0,&core_if->core_global_regs->gahbcfg,8,00000031 */
	read(base, 0x8, 0x00000031);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 */
	read(base, 0x18, 0xf3000806);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 */
	read(base, 0x14, 0x06400029);
	/* 0,&dwc_otg_hcd->core_if->host_if->host_global_regs->hfnum,408,0a950636 */
	read(base, 0x408, IGNORE);
	/* 0,&_core_if->host_if->host_global_regs->haint,414,00000001 */
	read(base, 0x414, 0x00000001);
	/* 0,&hc_regs->hcint,508,00000023 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hcint,508,00000023 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hctsiz,510,c00001f3 */
	read(base, 0x510, 0xc00001f3);
	/* 0,&hc_regs->hctsiz,510,c00001f3 */
	read(base, 0x510, 0xc00001f3);
	/* 0,&hc_regs->hcint,508,00000023 */
	read(base, 0x508, 0x00000023);
	/* 1,&hc_regs->hcintmsk,50c,00000000 */
	write(base, 0x50c, 0x00000000);
	/* 1,&hc_regs->hcint,508,ffffffff */
	write(base, 0x508, 0xffffffff);
	/* 0,&(hc_regs)->hcintmsk,50c,00000000 */
	read(base, 0x50c, 0x00000000);
	/* 1,&(hc_regs)->hcintmsk,50c,00000000 */
	write(base, 0x50c, 0x00000000);
	toggle++;
}
