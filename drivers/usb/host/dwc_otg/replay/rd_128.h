#include"common.h"
static void rd_128(void *base)
{
	dma_addr_t cmd, data;
	u32 val;
	data = prepare_data();
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
	cmd = prepare_allow_medium_removal(1);
	do {
		val = readl(base + 0x2c);
	} while(val < 0x00080100);
	/* 0,&global_regs->gnptxsts,2c,00080100 : 27 */
	read(base, 0x2c, 0x00080100);
	/* 1,&hc_regs->hctsiz,510,0008001f : 28 */
	write(base, 0x510, 0x0008001f);
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
	/* 0,&dwc_otg_hcd->core_if->host_if->host_global_regs->hfnum,408,08490c67 : 46 */
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
	do {
		val = readl(base + 0x2c);
	} while(val < 0x00080100);

	/* 0,&global_regs->gnptxsts,2c,00080100 : 72 */
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
	/* 0,&dwc_otg_hcd->core_if->host_if->host_global_regs->hfnum,408,02e80c68 : 91 */
	read(base, 0x408, IGNORE);
	/* 0,&_core_if->host_if->host_global_regs->haint,414,00000001 : 92 */
	read(base, 0x414, 0x00000001);
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
	cmd = prepare_read_10(128);
	do {
		val = readl(base + 0x2c);
	} while(val < 0x00080100);
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
	/* 0,&dwc_otg_hcd->core_if->host_if->host_global_regs->hfnum,408,0a4a0cbd : 140 */
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
	} while(val < 0x00080100);
	/* 0,&global_regs->gnptxsts,2c,00080100 : 162 */
	read(base, 0x2c, 0x00080100);
	/* 1,&hc_regs->hctsiz,510,40401000 : 163 */
	write(base, 0x510, 0x40401000);
	/* 1,&hc_regs->hcdma,514,da377000 : 168 */
	write(base, 0x514, data);
	/* 0,&hc_regs->hcchar,500,01089200 : 169 */
	read(base, 0x500, 0x01089200);
	/* 1,&hc_regs->hcchar,500,81189200 : 170 */
	write(base, 0x500, 0x81189200);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 171 */
	read(base, 0x18, 0xf3000806);
	udelay(10);
	/* 0,&global_regs->gnptxsts,2c,00000100 : 172 */
	read(base, 0x2c, 0x00000100);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 173 */
	read(base, 0x18, 0xf3000806);
	udelay(10);
	/* 0,&global_regs->gnptxsts,2c,00000100 : 174 */
	read(base, 0x2c, 0x00000100);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 175 */
	read(base, 0x18, 0xf3000806);
	udelay(10);
	/* 0,&global_regs->gnptxsts,2c,00000100 : 176 */
	read(base, 0x2c, 0x00000100);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 177 */
	read(base, 0x18, 0xf3000806);
	udelay(10);
	/* 0,&global_regs->gnptxsts,2c,00000100 : 178 */
	read(base, 0x2c, 0x00000100);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 179 */
	read(base, 0x18, 0xf3000806);
	udelay(10);
	/* 0,&global_regs->gnptxsts,2c,00000100 : 180 */
	read(base, 0x2c, 0x00000100);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 181 */
	read(base, 0x18, 0xf3000806);
	udelay(10);
	/* 0,&global_regs->gnptxsts,2c,00000100 : 182 */
	read(base, 0x2c, 0x00000100);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 183 */
	read(base, 0x18, 0xf3000806);
	udelay(10);
	/* 0,&global_regs->gnptxsts,2c,00000100 : 184 */
	read(base, 0x2c, 0x00000100);
	poll_for_irq(base);
	/* 0,&core_if->core_global_regs->gpwrdn,58,00000000 : 185 */
	read(base, 0x58, 0x00000000);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 186 */
	read(base, 0x14, 0x06400029);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 187 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 : 188 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 : 189 */
	read(base, 0x18, 0xf3000806);
	/* 0,&core_if->core_global_regs->gahbcfg,8,00000031 : 190 */
	read(base, 0x8, 0x00000031);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 191 */
	read(base, 0x14, 0x06400029);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 192 */
	read(base, 0x18, 0xf3000806);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 : 193 */
	read(base, 0x14, 0x06400029);
	udelay(10);
	do {
		val = readl(base + 0x2c);
	} while(val < 0x00080100);
	/* 0,&global_regs->gnptxsts,2c,00080100 : 194 */
	read(base, 0x2c, 0x00080100);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 : 195 */
	read(base, 0x18, 0xf3000806);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 196 */
	read(base, 0x14, 0x06400029);
	/* 0,&dwc_otg_hcd->core_if->host_if->host_global_regs->hfnum,408,15480cc0 : 197 */
	read(base, 0x408, IGNORE);
	/* 0,&_core_if->host_if->host_global_regs->haint,414,00000001 : 198 */
	read(base, 0x414, 0x00000001);
	/* 0,&hc_regs->hcint,508,00000023 : 199 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 : 200 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hcint,508,00000023 : 201 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 : 202 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hctsiz,510,c0000000 : 203 */
	read(base, 0x510, 0xc0000000);
	/* 0,&hc_regs->hctsiz,510,c0000000 : 204 */
	read(base, 0x510, 0xc0000000);
	/* 0,&hc_regs->hcint,508,00000023 : 205 */
	read(base, 0x508, 0x00000023);
	/* 1,&hc_regs->hcintmsk,50c,00000000 : 206 */
	write(base, 0x50c, 0x00000000);
	/* 1,&hc_regs->hcint,508,ffffffff : 207 */
	write(base, 0x508, 0xffffffff);
	/* 1,&hc_regs->hcint,508,00003fff : 208 */
	write(base, 0x508, 0x00003fff);
	/* 1,&hc_regs->hcintmsk,50c,00000006 : 209 */
	write(base, 0x50c, 0x00000006);
	/* 1,&host_if->hc_regs[hc_num]->hcchar,500,01089200 : 210 */
	write(base, 0x500, 0x01089200);
	/* 1,&host_if->hc_regs[hc_num]->hcsplt,504,00000000 : 211 */
	write(base, 0x504, 0x00000000);
	/* 0,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 : 212 */
	read(base, 0x418, 0x00000001);
	/* 1,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 : 213 */
	write(base, 0x418, 0x00000001);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 214 */
	read(base, 0x18, 0xf3000806);
	/* 1,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 215 */
	write(base, 0x18, 0xf3000806);
	udelay(10);
	/* 0,&global_regs->gnptxsts,2c,00080100 : 216 */
	read(base, 0x2c, 0x00080100);
	do {
		val = readl(base + 0x2c);
	} while(val < 0x00080100);
	/* 1,&hc_regs->hctsiz,510,40401000 : 217 */
	write(base, 0x510, 0x40401000);
	/* 1,&hc_regs->hcdma,514,d9b48000 : 222 */
	write(base, 0x514, data);
	/* 0,&hc_regs->hcchar,500,01089200 : 223 */
	read(base, 0x500, 0x01089200);
	/* 1,&hc_regs->hcchar,500,81189200 : 224 */
	write(base, 0x500, 0x81189200);
	/* 0,&(hc_regs)->hcintmsk,50c,00000006 : 225 */
	read(base, 0x50c, 0x00000006);
	/* 1,&(hc_regs)->hcintmsk,50c,00000006 : 226 */
	write(base, 0x50c, 0x00000006);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 227 */
	read(base, 0x18, 0xf3000806);
	udelay(10);
	/* 0,&global_regs->gnptxsts,2c,00000100 : 228 */
	read(base, 0x2c, 0x00000100);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 229 */
	read(base, 0x18, 0xf3000806);
	udelay(10);
	/* 0,&global_regs->gnptxsts,2c,00000100 : 230 */
	read(base, 0x2c, 0x00000100);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 231 */
	read(base, 0x18, 0xf3000806);
	udelay(10);
	/* 0,&global_regs->gnptxsts,2c,00000100 : 232 */
	read(base, 0x2c, 0x00000100);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 233 */
	read(base, 0x18, 0xf3000806);
	udelay(10);
	/* 0,&global_regs->gnptxsts,2c,00000100 : 234 */
	read(base, 0x2c, 0x00000100);
	poll_for_irq(base);
	/* 0,&core_if->core_global_regs->gpwrdn,58,00000000 : 235 */
	read(base, 0x58, 0x00000000);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 236 */
	read(base, 0x14, 0x06400029);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 237 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 : 238 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 : 239 */
	read(base, 0x18, 0xf3000806);
	/* 0,&core_if->core_global_regs->gahbcfg,8,00000031 : 240 */
	read(base, 0x8, 0x00000031);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 241 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 : 242 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 : 243 */
	read(base, 0x18, 0xf3000806);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 244 */
	read(base, 0x14, 0x06400029);
	/* 0,&dwc_otg_hcd->core_if->host_if->host_global_regs->hfnum,408,0d770cc1 : 245 */
	read(base, 0x408, IGNORE);
	/* 0,&_core_if->host_if->host_global_regs->haint,414,00000001 : 246 */
	read(base, 0x414, 0x00000001);
	/* 0,&hc_regs->hcint,508,00000023 : 247 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 : 248 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hcint,508,00000023 : 249 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 : 250 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hctsiz,510,c0000000 : 251 */
	read(base, 0x510, 0xc0000000);
	/* 0,&hc_regs->hctsiz,510,c0000000 : 252 */
	read(base, 0x510, 0xc0000000);
	/* 0,&hc_regs->hcint,508,00000023 : 253 */
	read(base, 0x508, 0x00000023);
	/* 1,&hc_regs->hcintmsk,50c,00000000 : 254 */
	write(base, 0x50c, 0x00000000);
	/* 1,&hc_regs->hcint,508,ffffffff : 255 */
	write(base, 0x508, 0xffffffff);
	/* 1,&hc_regs->hcint,508,00003fff : 256 */
	write(base, 0x508, 0x00003fff);
	/* 1,&hc_regs->hcintmsk,50c,00000006 : 257 */
	write(base, 0x50c, 0x00000006);
	/* 1,&host_if->hc_regs[hc_num]->hcchar,500,01089200 : 258 */
	write(base, 0x500, 0x01089200);
	/* 1,&host_if->hc_regs[hc_num]->hcsplt,504,00000000 : 259 */
	write(base, 0x504, 0x00000000);
	/* 0,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 : 260 */
	read(base, 0x418, 0x00000001);
	/* 1,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 : 261 */
	write(base, 0x418, 0x00000001);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 262 */
	read(base, 0x18, 0xf3000806);
	/* 1,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 263 */
	write(base, 0x18, 0xf3000806);
	udelay(10);
	do {
		val = readl(base + 0x2c);
	} while(val < 0x00080100);

	/* 0,&global_regs->gnptxsts,2c,00080100 : 264 */
	read(base, 0x2c, 0x00080100);
	/* 1,&hc_regs->hctsiz,510,40401000 : 265 */
	write(base, 0x510, 0x40401000);
	/* 1,&hc_regs->hcdma,514,efdf1000 : 270 */
	write(base, 0x514, data);
	/* 0,&hc_regs->hcchar,500,01089200 : 271 */
	read(base, 0x500, 0x01089200);
	/* 1,&hc_regs->hcchar,500,81189200 : 272 */
	write(base, 0x500, 0x81189200);
	/* 0,&(hc_regs)->hcintmsk,50c,00000006 : 273 */
	read(base, 0x50c, 0x00000006);
	/* 1,&(hc_regs)->hcintmsk,50c,00000006 : 274 */
	write(base, 0x50c, 0x00000006);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 275 */
	read(base, 0x18, 0xf3000806);
	udelay(10);
	/* 0,&global_regs->gnptxsts,2c,00000100 : 276 */
	read(base, 0x2c, 0x00000100);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 277 */
	read(base, 0x18, 0xf3000806);
	udelay(10);
	/* 0,&global_regs->gnptxsts,2c,00000100 : 278 */
	read(base, 0x2c, 0x00000100);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 279 */
	read(base, 0x18, 0xf3000806);
	udelay(10);
	/* 0,&global_regs->gnptxsts,2c,00000100 : 280 */
	read(base, 0x2c, 0x00000100);
	poll_for_irq(base);
	/* 0,&core_if->core_global_regs->gpwrdn,58,00000000 : 281 */
	read(base, 0x58, 0x00000000);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 282 */
	read(base, 0x14, 0x06400029);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 283 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 : 284 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 : 285 */
	read(base, 0x18, 0xf3000806);
	/* 0,&core_if->core_global_regs->gahbcfg,8,00000031 : 286 */
	read(base, 0x8, 0x00000031);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 287 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 : 288 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 : 289 */
	read(base, 0x18, 0xf3000806);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 290 */
	read(base, 0x14, 0x06400029);
	/* 0,&dwc_otg_hcd->core_if->host_if->host_global_regs->hfnum,408,05880cc2 : 291 */
	read(base, 0x408, IGNORE);
	/* 0,&_core_if->host_if->host_global_regs->haint,414,00000001 : 292 */
	read(base, 0x414, 0x00000001);
	/* 0,&hc_regs->hcint,508,00000023 : 293 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 : 294 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hcint,508,00000023 : 295 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 : 296 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hctsiz,510,c0000000 : 297 */
	read(base, 0x510, 0xc0000000);
	/* 0,&hc_regs->hctsiz,510,c0000000 : 298 */
	read(base, 0x510, 0xc0000000);
	/* 0,&hc_regs->hcint,508,00000023 : 299 */
	read(base, 0x508, 0x00000023);
	/* 1,&hc_regs->hcintmsk,50c,00000000 : 300 */
	write(base, 0x50c, 0x00000000);
	/* 1,&hc_regs->hcint,508,ffffffff : 301 */
	write(base, 0x508, 0xffffffff);
	/* 1,&hc_regs->hcint,508,00003fff : 302 */
	write(base, 0x508, 0x00003fff);
	/* 1,&hc_regs->hcintmsk,50c,00000006 : 303 */
	write(base, 0x50c, 0x00000006);
	/* 1,&host_if->hc_regs[hc_num]->hcchar,500,01089200 : 304 */
	write(base, 0x500, 0x01089200);
	/* 1,&host_if->hc_regs[hc_num]->hcsplt,504,00000000 : 305 */
	write(base, 0x504, 0x00000000);
	/* 0,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 : 306 */
	read(base, 0x418, 0x00000001);
	/* 1,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 : 307 */
	write(base, 0x418, 0x00000001);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 308 */
	read(base, 0x18, 0xf3000806);
	/* 1,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 309 */
	write(base, 0x18, 0xf3000806);
	do {
		val = readl(base + 0x2c);
	} while(val < 0x00080100);
	/* 0,&global_regs->gnptxsts,2c,00080100 : 310 */
	read(base, 0x2c, 0x00080100);
	/* 1,&hc_regs->hctsiz,510,40401000 : 311 */
	write(base, 0x510, 0x40401000);
	/* 1,&hc_regs->hcdma,514,db6d9000 : 316 */
	write(base, 0x514, data);
	/* 0,&hc_regs->hcchar,500,01089200 : 317 */
	read(base, 0x500, 0x01089200);
	/* 1,&hc_regs->hcchar,500,81189200 : 318 */
	write(base, 0x500, 0x81189200);
	/* 0,&(hc_regs)->hcintmsk,50c,00000006 : 319 */
	read(base, 0x50c, 0x00000006);
	/* 1,&(hc_regs)->hcintmsk,50c,00000006 : 320 */
	write(base, 0x50c, 0x00000006);
	poll_for_irq(base);
	/* 0,&core_if->core_global_regs->gpwrdn,58,00000000 : 321 */
	read(base, 0x58, 0x00000000);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 322 */
	read(base, 0x14, 0x06400029);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 323 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 : 324 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 : 325 */
	read(base, 0x18, 0xf3000806);
	/* 0,&core_if->core_global_regs->gahbcfg,8,00000031 : 326 */
	read(base, 0x8, 0x00000031);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 327 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 : 328 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 : 329 */
	read(base, 0x18, 0xf3000806);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 330 */
	read(base, 0x14, 0x06400029);
	/* 0,&dwc_otg_hcd->core_if->host_if->host_global_regs->hfnum,408,1bfc0cc4 : 331 */
	read(base, 0x408, IGNORE);
	/* 0,&_core_if->host_if->host_global_regs->haint,414,00000001 : 332 */
	read(base, 0x414, 0x00000001);
	/* 0,&hc_regs->hcint,508,00000023 : 333 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 : 334 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hcint,508,00000023 : 335 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 : 336 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hctsiz,510,c0000000 : 337 */
	read(base, 0x510, 0xc0000000);
	/* 0,&hc_regs->hctsiz,510,c0000000 : 338 */
	read(base, 0x510, 0xc0000000);
	/* 0,&hc_regs->hcint,508,00000023 : 339 */
	read(base, 0x508, 0x00000023);
	/* 1,&hc_regs->hcintmsk,50c,00000000 : 340 */
	write(base, 0x50c, 0x00000000);
	/* 1,&hc_regs->hcint,508,ffffffff : 341 */
	write(base, 0x508, 0xffffffff);
	/* 1,&hc_regs->hcint,508,00003fff : 342 */
	write(base, 0x508, 0x00003fff);
	/* 1,&hc_regs->hcintmsk,50c,00000006 : 343 */
	write(base, 0x50c, 0x00000006);
	/* 1,&host_if->hc_regs[hc_num]->hcchar,500,01089200 : 344 */
	write(base, 0x500, 0x01089200);
	/* 1,&host_if->hc_regs[hc_num]->hcsplt,504,00000000 : 345 */
	write(base, 0x504, 0x00000000);
	/* 0,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 : 346 */
	read(base, 0x418, 0x00000001);
	/* 1,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 : 347 */
	write(base, 0x418, 0x00000001);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 348 */
	read(base, 0x18, 0xf3000806);
	/* 1,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 349 */
	write(base, 0x18, 0xf3000806);
	do {
		val = readl(base + 0x2c);
	} while(val < 0x00080100);

	/* 0,&global_regs->gnptxsts,2c,00080100 : 350 */
	read(base, 0x2c, 0x00080100);
	/* 1,&hc_regs->hctsiz,510,40401000 : 351 */
	write(base, 0x510, 0x40401000);
	/* 1,&hc_regs->hcdma,514,d9952000 : 356 */
	write(base, 0x514, data);
	/* 0,&hc_regs->hcchar,500,01089200 : 357 */
	read(base, 0x500, 0x01089200);
	/* 1,&hc_regs->hcchar,500,81189200 : 358 */
	write(base, 0x500, 0x81189200);
	/* 0,&(hc_regs)->hcintmsk,50c,00000006 : 359 */
	read(base, 0x50c, 0x00000006);
	/* 1,&(hc_regs)->hcintmsk,50c,00000006 : 360 */
	write(base, 0x50c, 0x00000006);
	poll_for_irq(base);
	/* 0,&core_if->core_global_regs->gpwrdn,58,00000000 : 361 */
	read(base, 0x58, 0x00000000);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 362 */
	read(base, 0x14, 0x06400029);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 363 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 : 364 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 : 365 */
	read(base, 0x18, 0xf3000806);
	/* 0,&core_if->core_global_regs->gahbcfg,8,00000031 : 366 */
	read(base, 0x8, 0x00000031);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 367 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 : 368 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 : 369 */
	read(base, 0x18, 0xf3000806);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 370 */
	read(base, 0x14, 0x06400029);
	/* 0,&dwc_otg_hcd->core_if->host_if->host_global_regs->hfnum,408,13c20cc5 : 371 */
	read(base, 0x408, IGNORE);
	/* 0,&_core_if->host_if->host_global_regs->haint,414,00000001 : 372 */
	read(base, 0x414, 0x00000001);
	/* 0,&hc_regs->hcint,508,00000023 : 373 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 : 374 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hcint,508,00000023 : 375 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 : 376 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hctsiz,510,c0000000 : 377 */
	read(base, 0x510, 0xc0000000);
	/* 0,&hc_regs->hctsiz,510,c0000000 : 378 */
	read(base, 0x510, 0xc0000000);
	/* 0,&hc_regs->hcint,508,00000023 : 379 */
	read(base, 0x508, 0x00000023);
	/* 1,&hc_regs->hcintmsk,50c,00000000 : 380 */
	write(base, 0x50c, 0x00000000);
	/* 1,&hc_regs->hcint,508,ffffffff : 381 */
	write(base, 0x508, 0xffffffff);
	/* 1,&hc_regs->hcint,508,00003fff : 382 */
	write(base, 0x508, 0x00003fff);
	/* 1,&hc_regs->hcintmsk,50c,00000006 : 383 */
	write(base, 0x50c, 0x00000006);
	/* 1,&host_if->hc_regs[hc_num]->hcchar,500,01089200 : 384 */
	write(base, 0x500, 0x01089200);
	/* 1,&host_if->hc_regs[hc_num]->hcsplt,504,00000000 : 385 */
	write(base, 0x504, 0x00000000);
	/* 0,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 : 386 */
	read(base, 0x418, 0x00000001);
	/* 1,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 : 387 */
	write(base, 0x418, 0x00000001);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 388 */
	read(base, 0x18, 0xf3000806);
	/* 1,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 389 */
	write(base, 0x18, 0xf3000806);
	do {
		val = readl(base + 0x2c);
	} while(val < 0x00080100);

	/* 0,&global_regs->gnptxsts,2c,00080100 : 390 */
	read(base, 0x2c, 0x00080100);
	/* 1,&hc_regs->hctsiz,510,40401000 : 391 */
	write(base, 0x510, 0x40401000);
	/* 1,&hc_regs->hcdma,514,dabb8000 : 396 */
	write(base, 0x514, data);
	/* 0,&hc_regs->hcchar,500,01089200 : 397 */
	read(base, 0x500, 0x01089200);
	/* 1,&hc_regs->hcchar,500,81189200 : 398 */
	write(base, 0x500, 0x81189200);
	/* 0,&(hc_regs)->hcintmsk,50c,00000006 : 399 */
	read(base, 0x50c, 0x00000006);
	/* 1,&(hc_regs)->hcintmsk,50c,00000006 : 400 */
	write(base, 0x50c, 0x00000006);
	poll_for_irq(base);
	/* 0,&core_if->core_global_regs->gpwrdn,58,00000000 : 401 */
	read(base, 0x58, 0x00000000);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 402 */
	read(base, 0x14, 0x06400029);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 403 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 : 404 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 : 405 */
	read(base, 0x18, 0xf3000806);
	/* 0,&core_if->core_global_regs->gahbcfg,8,00000031 : 406 */
	read(base, 0x8, 0x00000031);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 407 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 : 408 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 : 409 */
	read(base, 0x18, 0xf3000806);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 410 */
	read(base, 0x14, 0x06400029);
	/* 0,&dwc_otg_hcd->core_if->host_if->host_global_regs->hfnum,408,0c4b0cc6 : 411 */
	read(base, 0x408, IGNORE);
	/* 0,&_core_if->host_if->host_global_regs->haint,414,00000001 : 412 */
	read(base, 0x414, 0x00000001);
	/* 0,&hc_regs->hcint,508,00000023 : 413 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 : 414 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hcint,508,00000023 : 415 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 : 416 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hctsiz,510,c0000000 : 417 */
	read(base, 0x510, 0xc0000000);
	/* 0,&hc_regs->hctsiz,510,c0000000 : 418 */
	read(base, 0x510, 0xc0000000);
	/* 0,&hc_regs->hcint,508,00000023 : 419 */
	read(base, 0x508, 0x00000023);
	/* 1,&hc_regs->hcintmsk,50c,00000000 : 420 */
	write(base, 0x50c, 0x00000000);
	/* 1,&hc_regs->hcint,508,ffffffff : 421 */
	write(base, 0x508, 0xffffffff);
	/* 1,&hc_regs->hcint,508,00003fff : 422 */
	write(base, 0x508, 0x00003fff);
	/* 1,&hc_regs->hcintmsk,50c,00000006 : 423 */
	write(base, 0x50c, 0x00000006);
	/* 1,&host_if->hc_regs[hc_num]->hcchar,500,01089200 : 424 */
	write(base, 0x500, 0x01089200);
	/* 1,&host_if->hc_regs[hc_num]->hcsplt,504,00000000 : 425 */
	write(base, 0x504, 0x00000000);
	/* 0,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 : 426 */
	read(base, 0x418, 0x00000001);
	/* 1,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 : 427 */
	write(base, 0x418, 0x00000001);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 428 */
	read(base, 0x18, 0xf3000806);
	/* 1,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 429 */
	write(base, 0x18, 0xf3000806);
	do {
		val = readl(base + 0x2c);
	} while(val < 0x00080100);
	/* 0,&global_regs->gnptxsts,2c,00080100 : 430 */
	read(base, 0x2c, 0x00080100);
	/* 1,&hc_regs->hctsiz,510,40401000 : 431 */
	write(base, 0x510, 0x40401000);
	/* 1,&hc_regs->hcdma,514,dabb4000 : 436 */
	write(base, 0x514, data);
	/* 0,&hc_regs->hcchar,500,01089200 : 437 */
	read(base, 0x500, 0x01089200);
	/* 1,&hc_regs->hcchar,500,81189200 : 438 */
	write(base, 0x500, 0x81189200);
	/* 0,&(hc_regs)->hcintmsk,50c,00000006 : 439 */
	read(base, 0x50c, 0x00000006);
	/* 1,&(hc_regs)->hcintmsk,50c,00000006 : 440 */
	write(base, 0x50c, 0x00000006);
	poll_for_irq(base);
	/* 0,&core_if->core_global_regs->gpwrdn,58,00000000 : 441 */
	read(base, 0x58, 0x00000000);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 442 */
	read(base, 0x14, 0x06400029);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 443 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 : 444 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 : 445 */
	read(base, 0x18, 0xf3000806);
	/* 0,&core_if->core_global_regs->gahbcfg,8,00000031 : 446 */
	read(base, 0x8, 0x00000031);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 447 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 : 448 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 : 449 */
	read(base, 0x18, 0xf3000806);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 450 */
	read(base, 0x14, 0x06400029);
	/* 0,&dwc_otg_hcd->core_if->host_if->host_global_regs->hfnum,408,054f0cc7 : 451 */
	read(base, 0x408, IGNORE);
	/* 0,&_core_if->host_if->host_global_regs->haint,414,00000001 : 452 */
	read(base, 0x414, 0x00000001);
	/* 0,&hc_regs->hcint,508,00000023 : 453 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 : 454 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hcint,508,00000023 : 455 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 : 456 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hctsiz,510,c0000000 : 457 */
	read(base, 0x510, 0xc0000000);
	/* 0,&hc_regs->hctsiz,510,c0000000 : 458 */
	read(base, 0x510, 0xc0000000);
	/* 0,&hc_regs->hcint,508,00000023 : 459 */
	read(base, 0x508, 0x00000023);
	/* 1,&hc_regs->hcintmsk,50c,00000000 : 460 */
	write(base, 0x50c, 0x00000000);
	/* 1,&hc_regs->hcint,508,ffffffff : 461 */
	write(base, 0x508, 0xffffffff);
	/* 1,&hc_regs->hcint,508,00003fff : 462 */
	write(base, 0x508, 0x00003fff);
	/* 1,&hc_regs->hcintmsk,50c,00000006 : 463 */
	write(base, 0x50c, 0x00000006);
	/* 1,&host_if->hc_regs[hc_num]->hcchar,500,01089200 : 464 */
	write(base, 0x500, 0x01089200);
	/* 1,&host_if->hc_regs[hc_num]->hcsplt,504,00000000 : 465 */
	write(base, 0x504, 0x00000000);
	/* 0,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 : 466 */
	read(base, 0x418, 0x00000001);
	/* 1,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 : 467 */
	write(base, 0x418, 0x00000001);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 468 */
	read(base, 0x18, 0xf3000806);
	/* 1,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 469 */
	write(base, 0x18, 0xf3000806);
	do {
		val = readl(base + 0x2c);
	} while(val < 0x00080100);
	/* 0,&global_regs->gnptxsts,2c,00080100 : 470 */
	read(base, 0x2c, 0x00080100);
	/* 1,&hc_regs->hctsiz,510,40401000 : 471 */
	write(base, 0x510, 0x40401000);
	/* 1,&hc_regs->hcdma,514,db88b000 : 476 */
	write(base, 0x514, data);
	/* 0,&hc_regs->hcchar,500,01089200 : 477 */
	read(base, 0x500, 0x01089200);
	/* 1,&hc_regs->hcchar,500,81189200 : 478 */
	write(base, 0x500, 0x81189200);
	/* 0,&(hc_regs)->hcintmsk,50c,00000006 : 479 */
	read(base, 0x50c, 0x00000006);
	/* 1,&(hc_regs)->hcintmsk,50c,00000006 : 480 */
	write(base, 0x50c, 0x00000006);
	poll_for_irq(base);
	/* 0,&core_if->core_global_regs->gpwrdn,58,00000000 : 481 */
	read(base, 0x58, 0x00000000);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 482 */
	read(base, 0x14, 0x06400029);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 483 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 : 484 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 : 485 */
	read(base, 0x18, 0xf3000806);
	/* 0,&core_if->core_global_regs->gahbcfg,8,00000031 : 486 */
	read(base, 0x8, 0x00000031);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 487 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 : 488 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 : 489 */
	read(base, 0x18, 0xf3000806);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 490 */
	read(base, 0x14, 0x06400029);
	/* 0,&dwc_otg_hcd->core_if->host_if->host_global_regs->hfnum,408,1cc80cc9 : 491 */
	read(base, 0x408, IGNORE);
	/* 0,&_core_if->host_if->host_global_regs->haint,414,00000001 : 492 */
	read(base, 0x414, 0x00000001);
	/* 0,&hc_regs->hcint,508,00000023 : 493 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 : 494 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hcint,508,00000023 : 495 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 : 496 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hctsiz,510,c0000000 : 497 */
	read(base, 0x510, 0xc0000000);
	/* 0,&hc_regs->hctsiz,510,c0000000 : 498 */
	read(base, 0x510, 0xc0000000);
	/* 0,&hc_regs->hcint,508,00000023 : 499 */
	read(base, 0x508, 0x00000023);
	/* 1,&hc_regs->hcintmsk,50c,00000000 : 500 */
	write(base, 0x50c, 0x00000000);
	/* 1,&hc_regs->hcint,508,ffffffff : 501 */
	write(base, 0x508, 0xffffffff);
	/* 1,&hc_regs->hcint,508,00003fff : 502 */
	write(base, 0x508, 0x00003fff);
	/* 1,&hc_regs->hcintmsk,50c,00000006 : 503 */
	write(base, 0x50c, 0x00000006);
	/* 1,&host_if->hc_regs[hc_num]->hcchar,500,01089200 : 504 */
	write(base, 0x500, 0x01089200);
	/* 1,&host_if->hc_regs[hc_num]->hcsplt,504,00000000 : 505 */
	write(base, 0x504, 0x00000000);
	/* 0,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 : 506 */
	read(base, 0x418, 0x00000001);
	/* 1,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 : 507 */
	write(base, 0x418, 0x00000001);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 508 */
	read(base, 0x18, 0xf3000806);
	/* 1,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 509 */
	write(base, 0x18, 0xf3000806);
	do {
		val = readl(base + 0x2c);
	} while(val < 0x00080100);

	/* 0,&global_regs->gnptxsts,2c,00080100 : 510 */
	read(base, 0x2c, 0x00080100);
	/* 1,&hc_regs->hctsiz,510,40401000 : 511 */
	write(base, 0x510, 0x40401000);
	/* 1,&hc_regs->hcdma,514,da832000 : 516 */
	write(base, 0x514, data);
	/* 0,&hc_regs->hcchar,500,01089200 : 517 */
	read(base, 0x500, 0x01089200);
	/* 1,&hc_regs->hcchar,500,81189200 : 518 */
	write(base, 0x500, 0x81189200);
	/* 0,&(hc_regs)->hcintmsk,50c,00000006 : 519 */
	read(base, 0x50c, 0x00000006);
	/* 1,&(hc_regs)->hcintmsk,50c,00000006 : 520 */
	write(base, 0x50c, 0x00000006);
	poll_for_irq(base);
	/* 0,&core_if->core_global_regs->gpwrdn,58,00000000 : 521 */
	read(base, 0x58, 0x00000000);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 522 */
	read(base, 0x14, 0x06400029);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 523 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 : 524 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 : 525 */
	read(base, 0x18, 0xf3000806);
	/* 0,&core_if->core_global_regs->gahbcfg,8,00000031 : 526 */
	read(base, 0x8, 0x00000031);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 527 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 : 528 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 : 529 */
	read(base, 0x18, 0xf3000806);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 530 */
	read(base, 0x14, 0x06400029);
	/* 0,&dwc_otg_hcd->core_if->host_if->host_global_regs->hfnum,408,15b70cca : 531 */
	read(base, 0x408, IGNORE);
	/* 0,&_core_if->host_if->host_global_regs->haint,414,00000001 : 532 */
	read(base, 0x414, 0x00000001);
	/* 0,&hc_regs->hcint,508,00000023 : 533 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 : 534 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hcint,508,00000023 : 535 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 : 536 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hctsiz,510,c0000000 : 537 */
	read(base, 0x510, 0xc0000000);
	/* 0,&hc_regs->hctsiz,510,c0000000 : 538 */
	read(base, 0x510, 0xc0000000);
	/* 0,&hc_regs->hcint,508,00000023 : 539 */
	read(base, 0x508, 0x00000023);
	/* 1,&hc_regs->hcintmsk,50c,00000000 : 540 */
	write(base, 0x50c, 0x00000000);
	/* 1,&hc_regs->hcint,508,ffffffff : 541 */
	write(base, 0x508, 0xffffffff);
	/* 1,&hc_regs->hcint,508,00003fff : 542 */
	write(base, 0x508, 0x00003fff);
	/* 1,&hc_regs->hcintmsk,50c,00000006 : 543 */
	write(base, 0x50c, 0x00000006);
	/* 1,&host_if->hc_regs[hc_num]->hcchar,500,01089200 : 544 */
	write(base, 0x500, 0x01089200);
	/* 1,&host_if->hc_regs[hc_num]->hcsplt,504,00000000 : 545 */
	write(base, 0x504, 0x00000000);
	/* 0,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 : 546 */
	read(base, 0x418, 0x00000001);
	/* 1,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 : 547 */
	write(base, 0x418, 0x00000001);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 548 */
	read(base, 0x18, 0xf3000806);
	/* 1,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 549 */
	write(base, 0x18, 0xf3000806);
	do {
		val = readl(base + 0x2c);
	} while(val < 0x00080100);

	/* 0,&global_regs->gnptxsts,2c,00080100 : 550 */
	read(base, 0x2c, 0x00080100);
	/* 1,&hc_regs->hctsiz,510,40401000 : 551 */
	write(base, 0x510, 0x40401000);
	/* 1,&hc_regs->hcdma,514,dc094000 : 556 */
	write(base, 0x514, data);
	/* 0,&hc_regs->hcchar,500,01089200 : 557 */
	read(base, 0x500, 0x01089200);
	/* 1,&hc_regs->hcchar,500,81189200 : 558 */
	write(base, 0x500, 0x81189200);
	/* 0,&(hc_regs)->hcintmsk,50c,00000006 : 559 */
	read(base, 0x50c, 0x00000006);
	/* 1,&(hc_regs)->hcintmsk,50c,00000006 : 560 */
	write(base, 0x50c, 0x00000006);
	poll_for_irq(base);
	/* 0,&core_if->core_global_regs->gpwrdn,58,00000000 : 561 */
	read(base, 0x58, 0x00000000);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 562 */
	read(base, 0x14, 0x06400029);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 563 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 : 564 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 : 565 */
	read(base, 0x18, 0xf3000806);
	/* 0,&core_if->core_global_regs->gahbcfg,8,00000031 : 566 */
	read(base, 0x8, 0x00000031);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 567 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 : 568 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 : 569 */
	read(base, 0x18, 0xf3000806);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 570 */
	read(base, 0x14, 0x06400029);
	/* 0,&dwc_otg_hcd->core_if->host_if->host_global_regs->hfnum,408,0ebe0ccb : 571 */
	read(base, 0x408, IGNORE);
	/* 0,&_core_if->host_if->host_global_regs->haint,414,00000001 : 572 */
	read(base, 0x414, 0x00000001);
	/* 0,&hc_regs->hcint,508,00000023 : 573 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 : 574 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hcint,508,00000023 : 575 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 : 576 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hctsiz,510,c0000000 : 577 */
	read(base, 0x510, 0xc0000000);
	/* 0,&hc_regs->hctsiz,510,c0000000 : 578 */
	read(base, 0x510, 0xc0000000);
	/* 0,&hc_regs->hcint,508,00000023 : 579 */
	read(base, 0x508, 0x00000023);
	/* 1,&hc_regs->hcintmsk,50c,00000000 : 580 */
	write(base, 0x50c, 0x00000000);
	/* 1,&hc_regs->hcint,508,ffffffff : 581 */
	write(base, 0x508, 0xffffffff);
	/* 1,&hc_regs->hcint,508,00003fff : 582 */
	write(base, 0x508, 0x00003fff);
	/* 1,&hc_regs->hcintmsk,50c,00000006 : 583 */
	write(base, 0x50c, 0x00000006);
	/* 1,&host_if->hc_regs[hc_num]->hcchar,500,01089200 : 584 */
	write(base, 0x500, 0x01089200);
	/* 1,&host_if->hc_regs[hc_num]->hcsplt,504,00000000 : 585 */
	write(base, 0x504, 0x00000000);
	/* 0,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 : 586 */
	read(base, 0x418, 0x00000001);
	/* 1,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 : 587 */
	write(base, 0x418, 0x00000001);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 588 */
	read(base, 0x18, 0xf3000806);
	/* 1,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 589 */
	write(base, 0x18, 0xf3000806);
	udelay(10);
	/* 0,&global_regs->gnptxsts,2c,00080100 : 590 */
	read(base, 0x2c, 0x00080100);
	/* 1,&hc_regs->hctsiz,510,40401000 : 591 */
	write(base, 0x510, 0x40401000);
	/* 1,&hc_regs->hcdma,514,dc1a1000 : 596 */
	write(base, 0x514, data);
	/* 0,&hc_regs->hcchar,500,01089200 : 597 */
	read(base, 0x500, 0x01089200);
	/* 1,&hc_regs->hcchar,500,81189200 : 598 */
	write(base, 0x500, 0x81189200);
	/* 0,&(hc_regs)->hcintmsk,50c,00000006 : 599 */
	read(base, 0x50c, 0x00000006);
	/* 1,&(hc_regs)->hcintmsk,50c,00000006 : 600 */
	write(base, 0x50c, 0x00000006);
	poll_for_irq(base);
	/* 0,&core_if->core_global_regs->gpwrdn,58,00000000 : 601 */
	read(base, 0x58, 0x00000000);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 602 */
	read(base, 0x14, 0x06400029);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 603 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 : 604 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 : 605 */
	read(base, 0x18, 0xf3000806);
	/* 0,&core_if->core_global_regs->gahbcfg,8,00000031 : 606 */
	read(base, 0x8, 0x00000031);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 607 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 : 608 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 : 609 */
	read(base, 0x18, 0xf3000806);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 610 */
	read(base, 0x14, 0x06400029);
	/* 0,&dwc_otg_hcd->core_if->host_if->host_global_regs->hfnum,408,07a10ccc : 611 */
	read(base, 0x408, IGNORE);
	/* 0,&_core_if->host_if->host_global_regs->haint,414,00000001 : 612 */
	read(base, 0x414, 0x00000001);
	/* 0,&hc_regs->hcint,508,00000023 : 613 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 : 614 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hcint,508,00000023 : 615 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 : 616 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hctsiz,510,c0000000 : 617 */
	read(base, 0x510, 0xc0000000);
	/* 0,&hc_regs->hctsiz,510,c0000000 : 618 */
	read(base, 0x510, 0xc0000000);
	/* 0,&hc_regs->hcint,508,00000023 : 619 */
	read(base, 0x508, 0x00000023);
	/* 1,&hc_regs->hcintmsk,50c,00000000 : 620 */
	write(base, 0x50c, 0x00000000);
	/* 1,&hc_regs->hcint,508,ffffffff : 621 */
	write(base, 0x508, 0xffffffff);
	/* 1,&hc_regs->hcint,508,00003fff : 622 */
	write(base, 0x508, 0x00003fff);
	/* 1,&hc_regs->hcintmsk,50c,00000006 : 623 */
	write(base, 0x50c, 0x00000006);
	/* 1,&host_if->hc_regs[hc_num]->hcchar,500,01089200 : 624 */
	write(base, 0x500, 0x01089200);
	/* 1,&host_if->hc_regs[hc_num]->hcsplt,504,00000000 : 625 */
	write(base, 0x504, 0x00000000);
	/* 0,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 : 626 */
	read(base, 0x418, 0x00000001);
	/* 1,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 : 627 */
	write(base, 0x418, 0x00000001);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 628 */
	read(base, 0x18, 0xf3000806);
	/* 1,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 629 */
	write(base, 0x18, 0xf3000806);
	udelay(10);
	/* 0,&global_regs->gnptxsts,2c,00080100 : 630 */
	read(base, 0x2c, 0x00080100);
	/* 1,&hc_regs->hctsiz,510,40401000 : 631 */
	write(base, 0x510, 0x40401000);
	/* 1,&hc_regs->hcdma,514,d9533000 : 636 */
	write(base, 0x514, data);
	/* 0,&hc_regs->hcchar,500,01089200 : 637 */
	read(base, 0x500, 0x01089200);
	/* 1,&hc_regs->hcchar,500,81189200 : 638 */
	write(base, 0x500, 0x81189200);
	/* 0,&(hc_regs)->hcintmsk,50c,00000006 : 639 */
	read(base, 0x50c, 0x00000006);
	/* 1,&(hc_regs)->hcintmsk,50c,00000006 : 640 */
	write(base, 0x50c, 0x00000006);
	poll_for_irq(base);
	/* 0,&core_if->core_global_regs->gpwrdn,58,00000000 : 641 */
	read(base, 0x58, 0x00000000);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 642 */
	read(base, 0x14, 0x06400029);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 643 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 : 644 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 : 645 */
	read(base, 0x18, 0xf3000806);
	/* 0,&core_if->core_global_regs->gahbcfg,8,00000031 : 646 */
	read(base, 0x8, 0x00000031);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 647 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 : 648 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 : 649 */
	read(base, 0x18, 0xf3000806);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 650 */
	read(base, 0x14, 0x06400029);
	/* 0,&dwc_otg_hcd->core_if->host_if->host_global_regs->hfnum,408,03720ccd : 651 */
	read(base, 0x408, IGNORE);
	/* 0,&_core_if->host_if->host_global_regs->haint,414,00000001 : 652 */
	read(base, 0x414, 0x00000001);
	/* 0,&hc_regs->hcint,508,00000023 : 653 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 : 654 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hcint,508,00000023 : 655 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 : 656 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hctsiz,510,c0000000 : 657 */
	read(base, 0x510, 0xc0000000);
	/* 0,&hc_regs->hctsiz,510,c0000000 : 658 */
	read(base, 0x510, 0xc0000000);
	/* 0,&hc_regs->hcint,508,00000023 : 659 */
	read(base, 0x508, 0x00000023);
	/* 1,&hc_regs->hcintmsk,50c,00000000 : 660 */
	write(base, 0x50c, 0x00000000);
	/* 1,&hc_regs->hcint,508,ffffffff : 661 */
	write(base, 0x508, 0xffffffff);
	/* 1,&hc_regs->hcint,508,00003fff : 662 */
	write(base, 0x508, 0x00003fff);
	/* 1,&hc_regs->hcintmsk,50c,00000006 : 663 */
	write(base, 0x50c, 0x00000006);
	/* 1,&host_if->hc_regs[hc_num]->hcchar,500,01089200 : 664 */
	write(base, 0x500, 0x01089200);
	/* 1,&host_if->hc_regs[hc_num]->hcsplt,504,00000000 : 665 */
	write(base, 0x504, 0x00000000);
	/* 0,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 : 666 */
	read(base, 0x418, 0x00000001);
	/* 1,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 : 667 */
	write(base, 0x418, 0x00000001);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 668 */
	read(base, 0x18, 0xf3000806);
	/* 1,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 669 */
	write(base, 0x18, 0xf3000806);
	udelay(10);
	/* 0,&global_regs->gnptxsts,2c,00080100 : 670 */
	read(base, 0x2c, 0x00080100);
	/* 1,&hc_regs->hctsiz,510,40401000 : 671 */
	write(base, 0x510, 0x40401000);
	/* 1,&hc_regs->hcdma,514,d9eae000 : 676 */
	write(base, 0x514, data);
	/* 0,&hc_regs->hcchar,500,01089200 : 677 */
	read(base, 0x500, 0x01089200);
	/* 1,&hc_regs->hcchar,500,81189200 : 678 */
	write(base, 0x500, 0x81189200);
	/* 0,&(hc_regs)->hcintmsk,50c,00000006 : 679 */
	read(base, 0x50c, 0x00000006);
	/* 1,&(hc_regs)->hcintmsk,50c,00000006 : 680 */
	write(base, 0x50c, 0x00000006);
	poll_for_irq(base);
	/* 0,&core_if->core_global_regs->gpwrdn,58,00000000 : 681 */
	read(base, 0x58, 0x00000000);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 682 */
	read(base, 0x14, 0x06400029);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 683 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 : 684 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 : 685 */
	read(base, 0x18, 0xf3000806);
	/* 0,&core_if->core_global_regs->gahbcfg,8,00000031 : 686 */
	read(base, 0x8, 0x00000031);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 687 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 : 688 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 : 689 */
	read(base, 0x18, 0xf3000806);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 690 */
	read(base, 0x14, 0x06400029);
	/* 0,&dwc_otg_hcd->core_if->host_if->host_global_regs->hfnum,408,1c350ccf : 691 */
	read(base, 0x408, IGNORE);
	/* 0,&_core_if->host_if->host_global_regs->haint,414,00000001 : 692 */
	read(base, 0x414, 0x00000001);
	/* 0,&hc_regs->hcint,508,00000023 : 693 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 : 694 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hcint,508,00000023 : 695 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 : 696 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hctsiz,510,c0000000 : 697 */
	read(base, 0x510, 0xc0000000);
	/* 0,&hc_regs->hctsiz,510,c0000000 : 698 */
	read(base, 0x510, 0xc0000000);
	/* 0,&hc_regs->hcint,508,00000023 : 699 */
	read(base, 0x508, 0x00000023);
	/* 1,&hc_regs->hcintmsk,50c,00000000 : 700 */
	write(base, 0x50c, 0x00000000);
	/* 1,&hc_regs->hcint,508,ffffffff : 701 */
	write(base, 0x508, 0xffffffff);
	/* 1,&hc_regs->hcint,508,00003fff : 702 */
	write(base, 0x508, 0x00003fff);
	/* 1,&hc_regs->hcintmsk,50c,00000006 : 703 */
	write(base, 0x50c, 0x00000006);
	/* 1,&host_if->hc_regs[hc_num]->hcchar,500,01089200 : 704 */
	write(base, 0x500, 0x01089200);
	/* 1,&host_if->hc_regs[hc_num]->hcsplt,504,00000000 : 705 */
	write(base, 0x504, 0x00000000);
	/* 0,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 : 706 */
	read(base, 0x418, 0x00000001);
	/* 1,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 : 707 */
	write(base, 0x418, 0x00000001);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 708 */
	read(base, 0x18, 0xf3000806);
	/* 1,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 709 */
	write(base, 0x18, 0xf3000806);
	udelay(10);
	/* 0,&global_regs->gnptxsts,2c,00080100 : 710 */
	read(base, 0x2c, 0x00080100);
	/* 1,&hc_regs->hctsiz,510,40401000 : 711 */
	write(base, 0x510, 0x40401000);
	/* 1,&hc_regs->hcdma,514,e519b000 : 716 */
	write(base, 0x514, data);
	/* 0,&hc_regs->hcchar,500,01089200 : 717 */
	read(base, 0x500, 0x01089200);
	/* 1,&hc_regs->hcchar,500,81189200 : 718 */
	write(base, 0x500, 0x81189200);
	/* 0,&(hc_regs)->hcintmsk,50c,00000006 : 719 */
	read(base, 0x50c, 0x00000006);
	/* 1,&(hc_regs)->hcintmsk,50c,00000006 : 720 */
	write(base, 0x50c, 0x00000006);
	poll_for_irq(base);
	/* 0,&core_if->core_global_regs->gpwrdn,58,00000000 : 721 */
	read(base, 0x58, 0x00000000);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 722 */
	read(base, 0x14, 0x06400029);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 723 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 : 724 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 : 725 */
	read(base, 0x18, 0xf3000806);
	/* 0,&core_if->core_global_regs->gahbcfg,8,00000031 : 726 */
	read(base, 0x8, 0x00000031);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 727 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 : 728 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 : 729 */
	read(base, 0x18, 0xf3000806);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 730 */
	read(base, 0x14, 0x06400029);
	/* 0,&dwc_otg_hcd->core_if->host_if->host_global_regs->hfnum,408,16410cd0 : 731 */
	read(base, 0x408, IGNORE);
	/* 0,&_core_if->host_if->host_global_regs->haint,414,00000001 : 732 */
	read(base, 0x414, 0x00000001);
	/* 0,&hc_regs->hcint,508,00000023 : 733 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 : 734 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hcint,508,00000023 : 735 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 : 736 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hctsiz,510,c0000000 : 737 */
	read(base, 0x510, 0xc0000000);
	/* 0,&hc_regs->hctsiz,510,c0000000 : 738 */
	read(base, 0x510, 0xc0000000);
	/* 0,&hc_regs->hcint,508,00000023 : 739 */
	read(base, 0x508, 0x00000023);
	/* 1,&hc_regs->hcintmsk,50c,00000000 : 740 */
	write(base, 0x50c, 0x00000000);
	/* 1,&hc_regs->hcint,508,ffffffff : 741 */
	write(base, 0x508, 0xffffffff);
	/* 1,&hc_regs->hcint,508,00003fff : 742 */
	write(base, 0x508, 0x00003fff);
	/* 1,&hc_regs->hcintmsk,50c,00000006 : 743 */
	write(base, 0x50c, 0x00000006);
	/* 1,&host_if->hc_regs[hc_num]->hcchar,500,01089200 : 744 */
	write(base, 0x500, 0x01089200);
	/* 1,&host_if->hc_regs[hc_num]->hcsplt,504,00000000 : 745 */
	write(base, 0x504, 0x00000000);
	/* 0,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 : 746 */
	read(base, 0x418, 0x00000001);
	/* 1,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 : 747 */
	write(base, 0x418, 0x00000001);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 748 */
	read(base, 0x18, 0xf3000806);
	/* 1,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 749 */
	write(base, 0x18, 0xf3000806);
	udelay(10);
	/* 0,&global_regs->gnptxsts,2c,00080100 : 750 */
	read(base, 0x2c, 0x00080100);
	/* 1,&hc_regs->hctsiz,510,40401000 : 751 */
	write(base, 0x510, 0x40401000);
	/* 1,&hc_regs->hcdma,514,def0e000 : 756 */
	write(base, 0x514, data);
	/* 0,&hc_regs->hcchar,500,01089200 : 757 */
	read(base, 0x500, 0x01089200);
	/* 1,&hc_regs->hcchar,500,81189200 : 758 */
	write(base, 0x500, 0x81189200);
	/* 0,&(hc_regs)->hcintmsk,50c,00000006 : 759 */
	read(base, 0x50c, 0x00000006);
	/* 1,&(hc_regs)->hcintmsk,50c,00000006 : 760 */
	write(base, 0x50c, 0x00000006);
	poll_for_irq(base);
	/* 0,&core_if->core_global_regs->gpwrdn,58,00000000 : 761 */
	read(base, 0x58, 0x00000000);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 762 */
	read(base, 0x14, 0x06400029);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 763 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 : 764 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 : 765 */
	read(base, 0x18, 0xf3000806);
	/* 0,&core_if->core_global_regs->gahbcfg,8,00000031 : 766 */
	read(base, 0x8, 0x00000031);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 767 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 : 768 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 : 769 */
	read(base, 0x18, 0xf3000806);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 770 */
	read(base, 0x14, 0x06400029);
	/* 0,&dwc_otg_hcd->core_if->host_if->host_global_regs->hfnum,408,0f3f0cd1 : 771 */
	read(base, 0x408, IGNORE);
	/* 0,&_core_if->host_if->host_global_regs->haint,414,00000001 : 772 */
	read(base, 0x414, 0x00000001);
	/* 0,&hc_regs->hcint,508,00000023 : 773 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 : 774 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hcint,508,00000023 : 775 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 : 776 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hctsiz,510,c0000000 : 777 */
	read(base, 0x510, 0xc0000000);
	/* 0,&hc_regs->hctsiz,510,c0000000 : 778 */
	read(base, 0x510, 0xc0000000);
	/* 0,&hc_regs->hcint,508,00000023 : 779 */
	read(base, 0x508, 0x00000023);
	/* 1,&hc_regs->hcintmsk,50c,00000000 : 780 */
	write(base, 0x50c, 0x00000000);
	/* 1,&hc_regs->hcint,508,ffffffff : 781 */
	write(base, 0x508, 0xffffffff);
	/* 1,&hc_regs->hcint,508,00003fff : 782 */
	write(base, 0x508, 0x00003fff);
	/* 1,&hc_regs->hcintmsk,50c,00000006 : 783 */
	write(base, 0x50c, 0x00000006);
	/* 1,&host_if->hc_regs[hc_num]->hcchar,500,01089200 : 784 */
	write(base, 0x500, 0x01089200);
	/* 1,&host_if->hc_regs[hc_num]->hcsplt,504,00000000 : 785 */
	write(base, 0x504, 0x00000000);
	/* 0,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 : 786 */
	read(base, 0x418, 0x00000001);
	/* 1,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 : 787 */
	write(base, 0x418, 0x00000001);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 788 */
	read(base, 0x18, 0xf3000806);
	/* 1,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 789 */
	write(base, 0x18, 0xf3000806);
	udelay(10);
	/* 0,&global_regs->gnptxsts,2c,00080100 : 790 */
	read(base, 0x2c, 0x00080100);
	/* 1,&hc_regs->hctsiz,510,40401000 : 791 */
	write(base, 0x510, 0x40401000);
	/* 1,&hc_regs->hcdma,514,e0596000 : 796 */
	write(base, 0x514, data);
	/* 0,&hc_regs->hcchar,500,01089200 : 797 */
	read(base, 0x500, 0x01089200);
	/* 1,&hc_regs->hcchar,500,81189200 : 798 */
	write(base, 0x500, 0x81189200);
	/* 0,&(hc_regs)->hcintmsk,50c,00000006 : 799 */
	read(base, 0x50c, 0x00000006);
	/* 1,&(hc_regs)->hcintmsk,50c,00000006 : 800 */
	write(base, 0x50c, 0x00000006);
	poll_for_irq(base);
	/* 0,&core_if->core_global_regs->gpwrdn,58,00000000 : 801 */
	read(base, 0x58, 0x00000000);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 802 */
	read(base, 0x14, 0x06400029);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 803 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 : 804 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 : 805 */
	read(base, 0x18, 0xf3000806);
	/* 0,&core_if->core_global_regs->gahbcfg,8,00000031 : 806 */
	read(base, 0x8, 0x00000031);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 807 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 : 808 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 : 809 */
	read(base, 0x18, 0xf3000806);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 810 */
	read(base, 0x14, 0x06400029);
	/* 0,&dwc_otg_hcd->core_if->host_if->host_global_regs->hfnum,408,07f80cd2 : 811 */
	read(base, 0x408, IGNORE);
	/* 0,&_core_if->host_if->host_global_regs->haint,414,00000001 : 812 */
	read(base, 0x414, 0x00000001);
	/* 0,&hc_regs->hcint,508,00000023 : 813 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 : 814 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hcint,508,00000023 : 815 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 : 816 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hctsiz,510,c0000000 : 817 */
	read(base, 0x510, 0xc0000000);
	/* 0,&hc_regs->hctsiz,510,c0000000 : 818 */
	read(base, 0x510, 0xc0000000);
	/* 0,&hc_regs->hcint,508,00000023 : 819 */
	read(base, 0x508, 0x00000023);
	/* 1,&hc_regs->hcintmsk,50c,00000000 : 820 */
	write(base, 0x50c, 0x00000000);
	/* 1,&hc_regs->hcint,508,ffffffff : 821 */
	write(base, 0x508, 0xffffffff);
	/* 0,&(hc_regs)->hcintmsk,50c,00000000 : 822 */
	read(base, 0x50c, 0x00000000);
	/* 1,&(hc_regs)->hcintmsk,50c,00000000 : 823 */
	write(base, 0x50c, 0x00000000);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 829 */
	read(base, 0x18, 0xf3000806);
	/* 1,&hc_regs->hcint,508,00003fff : 830 */
	write(base, 0x508, 0x00003fff);
	/* 1,&hc_regs->hcintmsk,50c,00000006 : 831 */
	write(base, 0x50c, 0x00000006);
	/* 1,&host_if->hc_regs[hc_num]->hcchar,500,01089200 : 832 */
	write(base, 0x500, 0x01089200);
	/* 1,&host_if->hc_regs[hc_num]->hcsplt,504,00000000 : 833 */
	write(base, 0x504, 0x00000000);
	/* 0,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 : 834 */
	read(base, 0x418, 0x00000001);
	/* 1,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 : 835 */
	write(base, 0x418, 0x00000001);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 836 */
	read(base, 0x18, 0xf3000806);
	/* 1,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 837 */
	write(base, 0x18, 0xf3000806);
	/* 0,&global_regs->gnptxsts,2c,00080100 : 838 */
	read(base, 0x2c, 0x00080100);
	/* 1,&hc_regs->hctsiz,510,40080200 : 839 */
	write(base, 0x510, 0x40080200);
	/* 1,&hc_regs->hcdma,514,f7053000 : 844 */
	write(base, 0x514, cmd);
	/* 0,&hc_regs->hcchar,500,01089200 : 845 */
	read(base, 0x500, 0x01089200);
	/* 1,&hc_regs->hcchar,500,81189200 : 846 */
	write(base, 0x500, 0x81189200);
	poll_for_irq(base);
	/* 0,&core_if->core_global_regs->gpwrdn,58,00000000 : 847 */
	read(base, 0x58, 0x00000000);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 848 */
	read(base, 0x14, 0x06400029);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 849 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 : 850 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 : 851 */
	read(base, 0x18, 0xf3000806);
	/* 0,&core_if->core_global_regs->gahbcfg,8,00000031 : 852 */
	read(base, 0x8, 0x00000031);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 853 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 : 854 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 : 855 */
	read(base, 0x18, 0xf3000806);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 856 */
	read(base, 0x14, 0x06400029);
	/* 0,&dwc_otg_hcd->core_if->host_if->host_global_regs->hfnum,408,08700cd3 : 857 */
	read(base, 0x408, IGNORE);
	/* 0,&_core_if->host_if->host_global_regs->haint,414,00000001 : 858 */
	read(base, 0x414, 0x00000001);
	/* 0,&hc_regs->hcint,508,00000023 : 859 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 : 860 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hcint,508,00000023 : 861 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 : 862 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hctsiz,510,800001f3 : 863 */
	read(base, 0x510, 0x800001f3);
	/* 0,&hc_regs->hctsiz,510,800001f3 : 864 */
	read(base, 0x510, 0x800001f3);
	/* 0,&hc_regs->hcint,508,00000023 : 865 */
	read(base, 0x508, 0x00000023);
	/* 1,&hc_regs->hcintmsk,50c,00000000 : 866 */
	write(base, 0x50c, 0x00000000);
	/* 1,&hc_regs->hcint,508,ffffffff : 867 */
	write(base, 0x508, 0xffffffff);
	/* 0,&(hc_regs)->hcintmsk,50c,00000000 : 868 */
	read(base, 0x50c, 0x00000000);
	/* 1,&(hc_regs)->hcintmsk,50c,00000000 : 869 */
	write(base, 0x50c, 0x00000000);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 878 */
	read(base, 0x18, 0xf3000806);
	/* 1,&hc_regs->hcint,508,00003fff : 879 */
	write(base, 0x508, 0x00003fff);
	/* 1,&hc_regs->hcintmsk,50c,00000006 : 880 */
	write(base, 0x50c, 0x00000006);
	/* 1,&host_if->hc_regs[hc_num]->hcchar,500,01081200 : 881 */
	write(base, 0x500, 0x01081200);
	/* 1,&host_if->hc_regs[hc_num]->hcsplt,504,00000000 : 882 */
	write(base, 0x504, 0x00000000);
	/* 0,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 : 883 */
	read(base, 0x418, 0x00000001);
	/* 1,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 : 884 */
	write(base, 0x418, 0x00000001);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 885 */
	read(base, 0x18, 0xf3000806);
	/* 1,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 886 */
	write(base, 0x18, 0xf3000806);
	cmd = prepare_allow_medium_removal(0);
	/* 0,&global_regs->gnptxsts,2c,00080100 : 887 */
	read(base, 0x2c, 0x00080100);
	/* 1,&hc_regs->hctsiz,510,0008001f : 888 */
	write(base, 0x510, 0x0008001f);
	/* 1,&hc_regs->hcdma,514,f7053000 : 893 */
	write(base, 0x514, cmd);
	/* 0,&hc_regs->hcchar,500,01081200 : 894 */
	read(base, 0x500, 0x01081200);
	/* 1,&hc_regs->hcchar,500,81181200 : 895 */
	write(base, 0x500, 0x81181200);
	poll_for_irq(base);
	/* 0,&core_if->core_global_regs->gpwrdn,58,00000000 : 896 */
	read(base, 0x58, 0x00000000);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 897 */
	read(base, 0x14, 0x06400029);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 898 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 : 899 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 : 900 */
	read(base, 0x18, 0xf3000806);
	/* 0,&core_if->core_global_regs->gahbcfg,8,00000031 : 901 */
	read(base, 0x8, 0x00000031);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 902 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 : 903 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 : 904 */
	read(base, 0x18, 0xf3000806);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 905 */
	read(base, 0x14, 0x06400029);
	/* 0,&dwc_otg_hcd->core_if->host_if->host_global_regs->hfnum,408,15750d22 : 906 */
	read(base, 0x408, IGNORE);
	/* 0,&_core_if->host_if->host_global_regs->haint,414,00000001 : 907 */
	read(base, 0x414, 0x00000001);
	/* 0,&hc_regs->hcint,508,00000023 : 908 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 : 909 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hcint,508,00000023 : 910 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 : 911 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hctsiz,510,4000001f : 912 */
	read(base, 0x510, 0x4000001f);
	/* 0,&hc_regs->hctsiz,510,4000001f : 913 */
	read(base, 0x510, 0x4000001f);
	/* 0,&hc_regs->hcint,508,00000023 : 914 */
	read(base, 0x508, 0x00000023);
	/* 1,&hc_regs->hcintmsk,50c,00000000 : 915 */
	write(base, 0x50c, 0x00000000);
	/* 1,&hc_regs->hcint,508,ffffffff : 916 */
	write(base, 0x508, 0xffffffff);
	/* 0,&(hc_regs)->hcintmsk,50c,00000000 : 917 */
	read(base, 0x50c, 0x00000000);
	/* 1,&(hc_regs)->hcintmsk,50c,00000000 : 918 */
	write(base, 0x50c, 0x00000000);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 923 */
	read(base, 0x18, 0xf3000806);
	/* 1,&hc_regs->hcint,508,00003fff : 924 */
	write(base, 0x508, 0x00003fff);
	/* 1,&hc_regs->hcintmsk,50c,00000006 : 925 */
	write(base, 0x50c, 0x00000006);
	/* 1,&host_if->hc_regs[hc_num]->hcchar,500,01089200 : 926 */
	write(base, 0x500, 0x01089200);
	/* 1,&host_if->hc_regs[hc_num]->hcsplt,504,00000000 : 927 */
	write(base, 0x504, 0x00000000);
	/* 0,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 : 928 */
	read(base, 0x418, 0x00000001);
	/* 1,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 : 929 */
	write(base, 0x418, 0x00000001);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 930 */
	read(base, 0x18, 0xf3000806);
	/* 1,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 931 */
	write(base, 0x18, 0xf3000806);
	udelay(10);
	/* 0,&global_regs->gnptxsts,2c,00080100 : 932 */
	read(base, 0x2c, 0x00080100);
	/* 1,&hc_regs->hctsiz,510,00080200 : 933 */
	write(base, 0x510, 0x00080200);
	/* 1,&hc_regs->hcdma,514,f7053000 : 938 */
	write(base, 0x514, cmd);
	/* 0,&hc_regs->hcchar,500,01089200 : 939 */
	read(base, 0x500, 0x01089200);
	/* 1,&hc_regs->hcchar,500,81189200 : 940 */
	write(base, 0x500, 0x81189200);
	poll_for_irq(base);
	/* 0,&core_if->core_global_regs->gpwrdn,58,00000000 : 941 */
	read(base, 0x58, 0x00000000);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 942 */
	read(base, 0x14, 0x06400029);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 943 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 : 944 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 : 945 */
	read(base, 0x18, 0xf3000806);
	/* 0,&core_if->core_global_regs->gahbcfg,8,00000031 : 946 */
	read(base, 0x8, 0x00000031);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 947 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 : 948 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 : 949 */
	read(base, 0x18, 0xf3000806);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 950 */
	read(base, 0x14, 0x06400029);
	/* 0,&dwc_otg_hcd->core_if->host_if->host_global_regs->hfnum,408,0e4c0d23 : 951 */
	read(base, 0x408, IGNORE);
	/* 0,&_core_if->host_if->host_global_regs->haint,414,00000001 : 952 */
	read(base, 0x414, 0x00000001);
	/* 0,&hc_regs->hcint,508,00000023 : 953 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 : 954 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hcint,508,00000023 : 955 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 : 956 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hctsiz,510,c00001f3 : 957 */
	read(base, 0x510, 0xc00001f3);
	/* 0,&hc_regs->hctsiz,510,c00001f3 : 958 */
	read(base, 0x510, 0xc00001f3);
	/* 0,&hc_regs->hcint,508,00000023 : 959 */
	read(base, 0x508, 0x00000023);
	/* 1,&hc_regs->hcintmsk,50c,00000000 : 960 */
	write(base, 0x50c, 0x00000000);
	/* 1,&hc_regs->hcint,508,ffffffff : 961 */
	write(base, 0x508, 0xffffffff);
	/* 0,&(hc_regs)->hcintmsk,50c,00000000 : 962 */
	read(base, 0x50c, 0x00000000);
	/* 1,&(hc_regs)->hcintmsk,50c,00000000 : 963 */
	write(base, 0x50c, 0x00000000);
}
