#include"common.h"
static void rd_8(void *base)
{
	dma_addr_t cmd, data;
	int tries = 0;
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 18 */
	read(base, 0x18, 0xf3000806);
	/* 1,&hc_regs->hcint,508,00003fff : 19 */
	write(base, 0x508, 0x00003fff);
	/* 1,&hc_regs->hcintmsk,50c,00000006 : 20 */
	write(base, 0x50c, 0x00000006);
	/* 1,&host_if->hc_regs[hc_num]->hcchar,500,01081200 : 21 */
	write(base, 0x500, 0x01081200);
	/* 1,&host_if->hc_regs[hc_num]->hcsplt,504,00000000 : 22 */
	write(base, 0x504, 0x00000000);
	/* 0,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 : 23 */
	read(base, 0x418, 0x00000001);
	/* 1,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 : 24 */
	write(base, 0x418, 0x00000001);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 25 */
	read(base, 0x18, 0xf3000806);
	/* 1,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 26 */
	write(base, 0x18, 0xf3000806);
	u32 val;
	do {
		val = readl(base + 0x2c);
	} while (val < 0x00080100);
	cmd = prepare_allow_medium_removal(1);
	/* 0,&global_regs->gnptxsts,2c,00080100 : 27 */
	read(base, 0x2c, 0x00080100);
	/* 1,&hc_regs->hctsiz,510,0008001f : 28 */
	write(base, 0x510, 0x0008001f);
	// pid = 2
	//write(base, 0x510, 0x4008001f);
	/* 1,&hc_regs->hcdma,514,f7053000 : 33 */
	write(base, 0x514, cmd);
	/* 0,&hc_regs->hcchar,500,01081200 : 34 */
	read(base, 0x500, 0x01081200);
	/* 1,&hc_regs->hcchar,500,81181200 : 35 */
	write(base, 0x500, 0x81181200);
	poll_for_irq(base);
	/* 0,&core_if->core_global_regs->gpwrdn,58,00000000 : 36 */
	read(base, 0x58, 0x00000000);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 37 */
	read(base, 0x14, 0x06400029);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 38 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 : 39 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 : 40 */
	read(base, 0x18, 0xf3000806);
	/* 0,&core_if->core_global_regs->gahbcfg,8,00000031 : 41 */
	read(base, 0x8, 0x00000031);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 42 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 : 43 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 : 44 */
	read(base, 0x18, 0xf3000806);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 45 */
	read(base, 0x14, 0x06400029);
	/* 0,&dwc_otg_hcd->core_if->host_if->host_global_regs->hfnum,408,12693af9 : 46 */
	read(base, 0x408, IGNORE);
	/* 0,&_core_if->host_if->host_global_regs->haint,414,00000001 : 47 */
	read(base, 0x414, 0x00000001);
	/* 0,&hc_regs->hcint,508,00000023 : 48 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 : 49 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hcint,508,00000023 : 50 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 : 51 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hctsiz,510,4000001f : 52 */
	read(base, 0x510, 0x4000001f);
	/* 0,&hc_regs->hctsiz,510,4000001f : 53 */
	read(base, 0x510, 0x4000001f);
	/* 0,&hc_regs->hcint,508,00000023 : 54 */
	read(base, 0x508, 0x00000023);
	/* 1,&hc_regs->hcintmsk,50c,00000000 : 55 */
	write(base, 0x50c, 0x00000000);
	/* 1,&hc_regs->hcint,508,ffffffff : 56 */
	write(base, 0x508, 0xffffffff);
	/* 0,&(hc_regs)->hcintmsk,50c,00000000 : 57 */
	read(base, 0x50c, 0x00000000);
	/* 1,&(hc_regs)->hcintmsk,50c,00000000 : 58 */
	write(base, 0x50c, 0x00000000);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 63 */
	read(base, 0x18, 0xf3000806);
	/* 1,&hc_regs->hcint,508,00003fff : 64 */
	write(base, 0x508, 0x00003fff);
	/* 1,&hc_regs->hcintmsk,50c,00000006 : 65 */
	write(base, 0x50c, 0x00000006);
	/* 1,&host_if->hc_regs[hc_num]->hcchar,500,01089200 : 66 */
	write(base, 0x500, 0x01089200);
	/* 1,&host_if->hc_regs[hc_num]->hcsplt,504,00000000 : 67 */
	write(base, 0x504, 0x00000000);
	/* 0,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 : 68 */
	read(base, 0x418, 0x00000001);
	/* 1,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 : 69 */
	write(base, 0x418, 0x00000001);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 70 */
	read(base, 0x18, 0xf3000806);
	/* 1,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 71 */
	write(base, 0x18, 0xf3000806);
	udelay(10);
	/* 0,&global_regs->gnptxsts,2c,00080100 : 72 */
	do {
		val = readl(base + 0x2c);
	} while (val < 0x00080100 && (tries++ < 1000));
	tries = 0;
	read(base, 0x2c, 0x00080100);
	/* 1,&hc_regs->hctsiz,510,00080200 : 73 */
	write(base, 0x510, 0x00080200);
	/* 1,&hc_regs->hcdma,514,f7053000 : 78 */
	write(base, 0x514, cmd);
	/* 0,&hc_regs->hcchar,500,01089200 : 79 */
	read(base, 0x500, 0x01089200);
	/* 1,&hc_regs->hcchar,500,81189200 : 80 */
	write(base, 0x500, 0x81189200);
	poll_for_irq(base);
	/* 0,&core_if->core_global_regs->gpwrdn,58,00000000 : 81 */
	read(base, 0x58, 0x00000000);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 82 */
	read(base, 0x14, 0x06400029);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 83 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 : 84 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 : 85 */
	read(base, 0x18, 0xf3000806);
	/* 0,&core_if->core_global_regs->gahbcfg,8,00000031 : 86 */
	read(base, 0x8, 0x00000031);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 87 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 : 88 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 : 89 */
	read(base, 0x18, 0xf3000806);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 90 */
	read(base, 0x14, 0x06400029);
	/* 0,&dwc_otg_hcd->core_if->host_if->host_global_regs->hfnum,408,0d293afa : 91 */
	read(base, 0x408, IGNORE);
	/* 0,&_core_if->host_if->host_global_regs->haint,414,00000001 : 92 */
	read(base, 0x414, 0x00000001);
	dump_csw();
	/* 0,&hc_regs->hcint,508,00000023 : 93 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 : 94 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hcint,508,00000023 : 95 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 : 96 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hctsiz,510,c00001f3 : 97 */
	read(base, 0x510, 0xc00001f3);
	/* 0,&hc_regs->hctsiz,510,c00001f3 : 98 */
	read(base, 0x510, 0xc00001f3);
	/* 0,&hc_regs->hcint,508,00000023 : 99 */
	read(base, 0x508, 0x00000023);
	/* 1,&hc_regs->hcintmsk,50c,00000000 : 100 */
	write(base, 0x50c, 0x00000000);
	/* 1,&hc_regs->hcint,508,ffffffff : 101 */
	write(base, 0x508, 0xffffffff);
	/* 0,&(hc_regs)->hcintmsk,50c,00000000 : 102 */
	read(base, 0x50c, 0x00000000);
	/* 1,&(hc_regs)->hcintmsk,50c,00000000 : 103 */
	write(base, 0x50c, 0x00000000);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 112 */
	read(base, 0x18, 0xf3000806);
	/* 1,&hc_regs->hcint,508,00003fff : 113 */
	write(base, 0x508, 0x00003fff);
	/* 1,&hc_regs->hcintmsk,50c,00000006 : 114 */
	write(base, 0x50c, 0x00000006);
	/* 1,&host_if->hc_regs[hc_num]->hcchar,500,01081200 : 115 */
	write(base, 0x500, 0x01081200);
	/* 1,&host_if->hc_regs[hc_num]->hcsplt,504,00000000 : 116 */
	write(base, 0x504, 0x00000000);
	/* 0,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 : 117 */
	read(base, 0x418, 0x00000001);
	/* 1,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 : 118 */
	write(base, 0x418, 0x00000001);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 119 */
	read(base, 0x18, 0xf3000806);
	/* 1,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 120 */
	write(base, 0x18, 0xf3000806);
	cmd = prepare_read_10(8);
	do {
		val = readl(base + 0x2c);
		printk("val = %08x...\n", val);
	} while (val < 0x00080100 && tries++ < 1000);
	tries = 0;
	/* 0,&global_regs->gnptxsts,2c,00080100 : 121 */
	read(base, 0x2c, 0x00080100);
	/* 1,&hc_regs->hctsiz,510,4008001f : 122 */
	write(base, 0x510, 0x4008001f);
	/* 1,&hc_regs->hcdma,514,f7053000 : 127 */
	write(base, 0x514, cmd);
	/* 0,&hc_regs->hcchar,500,01081200 : 128 */
	read(base, 0x500, 0x01081200);
	/* 1,&hc_regs->hcchar,500,81181200 : 129 */
	write(base, 0x500, 0x81181200);
	poll_for_irq(base);
	/* 0,&core_if->core_global_regs->gpwrdn,58,00000000 : 130 */
	read(base, 0x58, 0x00000000);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 131 */
	read(base, 0x14, 0x06400029);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 132 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 : 133 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 : 134 */
	read(base, 0x18, 0xf3000806);
	/* 0,&core_if->core_global_regs->gahbcfg,8,00000031 : 135 */
	read(base, 0x8, 0x00000031);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 136 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 : 137 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 : 138 */
	read(base, 0x18, 0xf3000806);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 139 */
	read(base, 0x14, 0x06400029);
	/* 0,&dwc_otg_hcd->core_if->host_if->host_global_regs->hfnum,408,19a43b47 : 140 */
	read(base, 0x408, IGNORE);
	/* 0,&_core_if->host_if->host_global_regs->haint,414,00000001 : 141 */
	read(base, 0x414, 0x00000001);
	/* 0,&hc_regs->hcint,508,00000023 : 142 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 : 143 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hcint,508,00000023 : 144 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 : 145 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hctsiz,510,0000001f : 146 */
	read(base, 0x510, 0x0000001f);
	/* 0,&hc_regs->hctsiz,510,0000001f : 147 */
	read(base, 0x510, 0x0000001f);
	/* 0,&hc_regs->hcint,508,00000023 : 148 */
	read(base, 0x508, 0x00000023);
	/* 1,&hc_regs->hcintmsk,50c,00000000 : 149 */
	write(base, 0x50c, 0x00000000);
	/* 1,&hc_regs->hcint,508,ffffffff : 150 */
	write(base, 0x508, 0xffffffff);
	/* 0,&(hc_regs)->hcintmsk,50c,00000000 : 151 */
	read(base, 0x50c, 0x00000000);
	/* 1,&(hc_regs)->hcintmsk,50c,00000000 : 152 */
	write(base, 0x50c, 0x00000000);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 153 */
	read(base, 0x18, 0xf3000806);
	/* 1,&hc_regs->hcint,508,00003fff : 154 */
	write(base, 0x508, 0x00003fff);
	/* 1,&hc_regs->hcintmsk,50c,00000006 : 155 */
	write(base, 0x50c, 0x00000006);
	/* 1,&host_if->hc_regs[hc_num]->hcchar,500,01089200 : 156 */
	write(base, 0x500, 0x01089200);
	/* 1,&host_if->hc_regs[hc_num]->hcsplt,504,00000000 : 157 */
	write(base, 0x504, 0x00000000);
	/* 0,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 : 158 */
	read(base, 0x418, 0x00000001);
	/* 1,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 : 159 */
	write(base, 0x418, 0x00000001);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 160 */
	read(base, 0x18, 0xf3000806);
	/* 1,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 161 */
	write(base, 0x18, 0xf3000806);
	do {
		val = readl(base + 0x2c);
	} while (val < 0x00080100 && (tries++ < 1000));
	tries = 0;
	/* 0,&global_regs->gnptxsts,2c,00080100 : 162 */
	read(base, 0x2c, 0x00080100);
	/* 1,&hc_regs->hctsiz,510,40401000 : 163 */
	write(base, 0x510, 0x40401000);
	/* 1,&hc_regs->hcdma,514,db6c6000 : 168 */
	write(base, 0x514, data);
	/* 0,&hc_regs->hcchar,500,01089200 : 169 */
	read(base, 0x500, 0x01089200);
	/* 1,&hc_regs->hcchar,500,81189200 : 170 */
	write(base, 0x500, 0x81189200);
	poll_for_irq(base);
	/* 0,&core_if->core_global_regs->gpwrdn,58,00000000 : 171 */
	read(base, 0x58, 0x00000000);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 172 */
	read(base, 0x14, 0x06400029);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 173 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 : 174 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 : 175 */
	read(base, 0x18, 0xf3000806);
	/* 0,&core_if->core_global_regs->gahbcfg,8,00000031 : 176 */
	read(base, 0x8, 0x00000031);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 177 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 : 178 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 : 179 */
	read(base, 0x18, 0xf3000806);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 180 */
	read(base, 0x14, 0x06400029);
	/* 0,&dwc_otg_hcd->core_if->host_if->host_global_regs->hfnum,408,04d73b49 : 181 */
	read(base, 0x408, IGNORE);
	/* 0,&_core_if->host_if->host_global_regs->haint,414,00000001 : 182 */
	read(base, 0x414, 0x00000001);
	/* 0,&hc_regs->hcint,508,00000023 : 183 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 : 184 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hcint,508,00000023 : 185 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 : 186 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hctsiz,510,c0000000 : 187 */
	read(base, 0x510, 0xc0000000);
	/* 0,&hc_regs->hctsiz,510,c0000000 : 188 */
	read(base, 0x510, 0xc0000000);
	/* 0,&hc_regs->hcint,508,00000023 : 189 */
	read(base, 0x508, 0x00000023);
	/* 1,&hc_regs->hcintmsk,50c,00000000 : 190 */
	write(base, 0x50c, 0x00000000);
	/* 1,&hc_regs->hcint,508,ffffffff : 191 */
	write(base, 0x508, 0xffffffff);
	/* 0,&(hc_regs)->hcintmsk,50c,00000000 : 192 */
	read(base, 0x50c, 0x00000000);
	/* 1,&(hc_regs)->hcintmsk,50c,00000000 : 193 */
	write(base, 0x50c, 0x00000000);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 199 */
	read(base, 0x18, 0xf3000806);
	/* 1,&hc_regs->hcint,508,00003fff : 200 */
	write(base, 0x508, 0x00003fff);
	/* 1,&hc_regs->hcintmsk,50c,00000006 : 201 */
	write(base, 0x50c, 0x00000006);
	/* 1,&host_if->hc_regs[hc_num]->hcchar,500,01089200 : 202 */
	write(base, 0x500, 0x01089200);
	/* 1,&host_if->hc_regs[hc_num]->hcsplt,504,00000000 : 203 */
	write(base, 0x504, 0x00000000);
	/* 0,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 : 204 */
	read(base, 0x418, 0x00000001);
	/* 1,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 : 205 */
	write(base, 0x418, 0x00000001);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 206 */
	read(base, 0x18, 0xf3000806);
	/* 1,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 207 */
	write(base, 0x18, 0xf3000806);
	udelay(10);
	/* 0,&global_regs->gnptxsts,2c,00080100 : 208 */
	read(base, 0x2c, 0x00080100);
	/* 1,&hc_regs->hctsiz,510,40080200 : 209 */
	write(base, 0x510, 0x40080200);
	/* 1,&hc_regs->hcdma,514,f7053000 : 214 */
	write(base, 0x514, cmd);
	/* 0,&hc_regs->hcchar,500,01089200 : 215 */
	read(base, 0x500, 0x01089200);
	/* 1,&hc_regs->hcchar,500,81189200 : 216 */
	write(base, 0x500, 0x81189200);
	poll_for_irq(base);
	/* 0,&core_if->core_global_regs->gpwrdn,58,00000000 : 217 */
	read(base, 0x58, 0x00000000);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 218 */
	read(base, 0x14, 0x06400029);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 219 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 : 220 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 : 221 */
	read(base, 0x18, 0xf3000806);
	/* 0,&core_if->core_global_regs->gahbcfg,8,00000031 : 222 */
	read(base, 0x8, 0x00000031);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 223 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 : 224 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 : 225 */
	read(base, 0x18, 0xf3000806);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 226 */
	read(base, 0x14, 0x06400029);
	/* 0,&dwc_otg_hcd->core_if->host_if->host_global_regs->hfnum,408,06153b4a : 227 */
	read(base, 0x408, IGNORE);
	/* 0,&_core_if->host_if->host_global_regs->haint,414,00000001 : 228 */
	read(base, 0x414, 0x00000001);
	/* 0,&hc_regs->hcint,508,00000023 : 229 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 : 230 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hcint,508,00000023 : 231 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 : 232 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hctsiz,510,800001f3 : 233 */
	read(base, 0x510, 0x800001f3);
	/* 0,&hc_regs->hctsiz,510,800001f3 : 234 */
	read(base, 0x510, 0x800001f3);
	/* 0,&hc_regs->hcint,508,00000023 : 235 */
	read(base, 0x508, 0x00000023);
	/* 1,&hc_regs->hcintmsk,50c,00000000 : 236 */
	write(base, 0x50c, 0x00000000);
	/* 1,&hc_regs->hcint,508,ffffffff : 237 */
	write(base, 0x508, 0xffffffff);
	/* 0,&(hc_regs)->hcintmsk,50c,00000000 : 238 */
	read(base, 0x50c, 0x00000000);
	/* 1,&(hc_regs)->hcintmsk,50c,00000000 : 239 */
	write(base, 0x50c, 0x00000000);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 248 */
	read(base, 0x18, 0xf3000806);
	/* 1,&hc_regs->hcint,508,00003fff : 249 */
	write(base, 0x508, 0x00003fff);
	/* 1,&hc_regs->hcintmsk,50c,00000006 : 250 */
	write(base, 0x50c, 0x00000006);
	/* 1,&host_if->hc_regs[hc_num]->hcchar,500,01081200 : 251 */
	write(base, 0x500, 0x01081200);
	/* 1,&host_if->hc_regs[hc_num]->hcsplt,504,00000000 : 252 */
	write(base, 0x504, 0x00000000);
	/* 0,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 : 253 */
	read(base, 0x418, 0x00000001);
	/* 1,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 : 254 */
	write(base, 0x418, 0x00000001);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 255 */
	read(base, 0x18, 0xf3000806);
	/* 1,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 256 */
	write(base, 0x18, 0xf3000806);
	cmd = prepare_allow_medium_removal(0);
	udelay(10);
	/* 0,&global_regs->gnptxsts,2c,00080100 : 257 */
	read(base, 0x2c, 0x00080100);
	/* 1,&hc_regs->hctsiz,510,0008001f : 258 */
	write(base, 0x510, 0x0008001f);
	/* 1,&hc_regs->hcdma,514,f7053000 : 263 */
	write(base, 0x514, cmd);
	/* 0,&hc_regs->hcchar,500,01081200 : 264 */
	read(base, 0x500, 0x01081200);
	/* 1,&hc_regs->hcchar,500,81181200 : 265 */
	write(base, 0x500, 0x81181200);
	poll_for_irq(base);
	/* 0,&core_if->core_global_regs->gpwrdn,58,00000000 : 266 */
	read(base, 0x58, 0x00000000);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 267 */
	read(base, 0x14, 0x06400029);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 268 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 : 269 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 : 270 */
	read(base, 0x18, 0xf3000806);
	/* 0,&core_if->core_global_regs->gahbcfg,8,00000031 : 271 */
	read(base, 0x8, 0x00000031);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 272 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 : 273 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 : 274 */
	read(base, 0x18, 0xf3000806);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 275 */
	read(base, 0x14, 0x06400029);
	/* 0,&dwc_otg_hcd->core_if->host_if->host_global_regs->hfnum,408,0ff33b8d : 276 */
	read(base, 0x408, IGNORE);
	/* 0,&_core_if->host_if->host_global_regs->haint,414,00000001 : 277 */
	read(base, 0x414, 0x00000001);
	/* 0,&hc_regs->hcint,508,00000023 : 278 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 : 279 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hcint,508,00000023 : 280 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 : 281 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hctsiz,510,4000001f : 282 */
	read(base, 0x510, 0x4000001f);
	/* 0,&hc_regs->hctsiz,510,4000001f : 283 */
	read(base, 0x510, 0x4000001f);
	/* 0,&hc_regs->hcint,508,00000023 : 284 */
	read(base, 0x508, 0x00000023);
	/* 1,&hc_regs->hcintmsk,50c,00000000 : 285 */
	write(base, 0x50c, 0x00000000);
	/* 1,&hc_regs->hcint,508,ffffffff : 286 */
	write(base, 0x508, 0xffffffff);
	/* 0,&(hc_regs)->hcintmsk,50c,00000000 : 287 */
	read(base, 0x50c, 0x00000000);
	/* 1,&(hc_regs)->hcintmsk,50c,00000000 : 288 */
	write(base, 0x50c, 0x00000000);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 293 */
	read(base, 0x18, 0xf3000806);
	/* 1,&hc_regs->hcint,508,00003fff : 294 */
	write(base, 0x508, 0x00003fff);
	/* 1,&hc_regs->hcintmsk,50c,00000006 : 295 */
	write(base, 0x50c, 0x00000006);
	/* 1,&host_if->hc_regs[hc_num]->hcchar,500,01089200 : 296 */
	write(base, 0x500, 0x01089200);
	/* 1,&host_if->hc_regs[hc_num]->hcsplt,504,00000000 : 297 */
	write(base, 0x504, 0x00000000);
	/* 0,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 : 298 */
	read(base, 0x418, 0x00000001);
	/* 1,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 : 299 */
	write(base, 0x418, 0x00000001);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 300 */
	read(base, 0x18, 0xf3000806);
	/* 1,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 301 */
	write(base, 0x18, 0xf3000806);
	udelay(10);
	/* 0,&global_regs->gnptxsts,2c,00080100 : 302 */
	read(base, 0x2c, 0x00080100);
	/* 1,&hc_regs->hctsiz,510,00080200 : 303 */
	write(base, 0x510, 0x00080200);
	/* 1,&hc_regs->hcdma,514,f7053000 : 308 */
	write(base, 0x514, cmd);
	/* 0,&hc_regs->hcchar,500,01089200 : 309 */
	read(base, 0x500, 0x01089200);
	/* 1,&hc_regs->hcchar,500,81189200 : 310 */
	write(base, 0x500, 0x81189200);
	poll_for_irq(base);
	/* 0,&core_if->core_global_regs->gpwrdn,58,00000000 : 311 */
	read(base, 0x58, 0x00000000);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 312 */
	read(base, 0x14, 0x06400029);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 313 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 : 314 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 : 315 */
	read(base, 0x18, 0xf3000806);
	/* 0,&core_if->core_global_regs->gahbcfg,8,00000031 : 316 */
	read(base, 0x8, 0x00000031);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 317 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 : 318 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 : 319 */
	read(base, 0x18, 0xf3000806);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 320 */
	read(base, 0x14, 0x06400029);
	/* 0,&dwc_otg_hcd->core_if->host_if->host_global_regs->hfnum,408,098a3b8e : 321 */
	read(base, 0x408, IGNORE);
	/* 0,&_core_if->host_if->host_global_regs->haint,414,00000001 : 322 */
	read(base, 0x414, 0x00000001);
	/* 0,&hc_regs->hcint,508,00000023 : 323 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 : 324 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hcint,508,00000023 : 325 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 : 326 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hctsiz,510,c00001f3 : 327 */
	read(base, 0x510, 0xc00001f3);
	/* 0,&hc_regs->hctsiz,510,c00001f3 : 328 */
	read(base, 0x510, 0xc00001f3);
	/* 0,&hc_regs->hcint,508,00000023 : 329 */
	read(base, 0x508, 0x00000023);
	/* 1,&hc_regs->hcintmsk,50c,00000000 : 330 */
	write(base, 0x50c, 0x00000000);
	/* 1,&hc_regs->hcint,508,ffffffff : 331 */
	write(base, 0x508, 0xffffffff);
	/* 0,&(hc_regs)->hcintmsk,50c,00000000 : 332 */
	read(base, 0x50c, 0x00000000);
	/* 1,&(hc_regs)->hcintmsk,50c,00000000 : 333 */
	write(base, 0x50c, 0x00000000);
}
