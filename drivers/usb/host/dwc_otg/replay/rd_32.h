#include"common.h"
static void rd_32(void *base)
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
	udelay(10);
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
	/* 0,&dwc_otg_hcd->core_if->host_if->host_global_regs->hfnum,408,15f9200c : 46 */
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
	/* 0,&dwc_otg_hcd->core_if->host_if->host_global_regs->hfnum,408,16ad200f : 91 */
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
	cmd = prepare_read_10(32);
	udelay(10);
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
	/* 0,&dwc_otg_hcd->core_if->host_if->host_global_regs->hfnum,408,12a8206a : 140 */
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
	} while (val < 0x00080100);
	/* 0,&global_regs->gnptxsts,2c,00080100 : 162 */
	read(base, 0x2c, 0x00080100);
	/* 1,&hc_regs->hctsiz,510,40401000 : 163 */
	write(base, 0x510, 0x40401000);
	/* 1,&hc_regs->hcdma,514,da358000 : 168 */
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
	poll_for_irq(base);
	/* 0,&core_if->core_global_regs->gpwrdn,58,00000000 : 177 */
	read(base, 0x58, 0x00000000);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 178 */
	read(base, 0x14, 0x06400029);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 179 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 : 180 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 : 181 */
	read(base, 0x18, 0xf3000806);
	/* 0,&core_if->core_global_regs->gahbcfg,8,00000031 : 182 */
	read(base, 0x8, 0x00000031);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 183 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 : 184 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 : 185 */
	read(base, 0x18, 0xf3000806);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 186 */
	read(base, 0x14, 0x06400029);
	/* 0,&dwc_otg_hcd->core_if->host_if->host_global_regs->hfnum,408,006f206c : 187 */
	read(base, 0x408, IGNORE);
	/* 0,&_core_if->host_if->host_global_regs->haint,414,00000001 : 188 */
	read(base, 0x414, 0x00000001);
	/* 0,&hc_regs->hcint,508,00000023 : 189 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 : 190 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hcint,508,00000023 : 191 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 : 192 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hctsiz,510,c0000000 : 193 */
	read(base, 0x510, 0xc0000000);
	/* 0,&hc_regs->hctsiz,510,c0000000 : 194 */
	read(base, 0x510, 0xc0000000);
	/* 0,&hc_regs->hcint,508,00000023 : 195 */
	read(base, 0x508, 0x00000023);
	/* 1,&hc_regs->hcintmsk,50c,00000000 : 196 */
	write(base, 0x50c, 0x00000000);
	/* 1,&hc_regs->hcint,508,ffffffff : 197 */
	write(base, 0x508, 0xffffffff);
	/* 1,&hc_regs->hcint,508,00003fff : 198 */
	write(base, 0x508, 0x00003fff);
	/* 1,&hc_regs->hcintmsk,50c,00000006 : 199 */
	write(base, 0x50c, 0x00000006);
	/* 1,&host_if->hc_regs[hc_num]->hcchar,500,01089200 : 200 */
	write(base, 0x500, 0x01089200);
	/* 1,&host_if->hc_regs[hc_num]->hcsplt,504,00000000 : 201 */
	write(base, 0x504, 0x00000000);
	/* 0,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 : 202 */
	read(base, 0x418, 0x00000001);
	/* 1,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 : 203 */
	write(base, 0x418, 0x00000001);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 204 */
	read(base, 0x18, 0xf3000806);
	/* 1,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 205 */
	write(base, 0x18, 0xf3000806);
	do {
		val = readl(base + 0x2c);
	} while (val < 0x00080100);
	/* 0,&global_regs->gnptxsts,2c,00080100 : 206 */
	read(base, 0x2c, 0x00080100);
	/* 1,&hc_regs->hctsiz,510,40401000 : 207 */
	write(base, 0x510, 0x40401000);
	/* 1,&hc_regs->hcdma,514,ee31e000 : 212 */
	write(base, 0x514, data);
	/* 0,&hc_regs->hcchar,500,01089200 : 213 */
	read(base, 0x500, 0x01089200);
	/* 1,&hc_regs->hcchar,500,81189200 : 214 */
	write(base, 0x500, 0x81189200);
	/* 0,&(hc_regs)->hcintmsk,50c,00000006 : 215 */
	read(base, 0x50c, 0x00000006);
	/* 1,&(hc_regs)->hcintmsk,50c,00000006 : 216 */
	write(base, 0x50c, 0x00000006);
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
	/* 0,&dwc_otg_hcd->core_if->host_if->host_global_regs->hfnum,408,136e206e : 227 */
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
	/* 0,&hc_regs->hctsiz,510,c0000000 : 233 */
	read(base, 0x510, 0xc0000000);
	/* 0,&hc_regs->hctsiz,510,c0000000 : 234 */
	read(base, 0x510, 0xc0000000);
	/* 0,&hc_regs->hcint,508,00000023 : 235 */
	read(base, 0x508, 0x00000023);
	/* 1,&hc_regs->hcintmsk,50c,00000000 : 236 */
	write(base, 0x50c, 0x00000000);
	/* 1,&hc_regs->hcint,508,ffffffff : 237 */
	write(base, 0x508, 0xffffffff);
	/* 1,&hc_regs->hcint,508,00003fff : 238 */
	write(base, 0x508, 0x00003fff);
	/* 1,&hc_regs->hcintmsk,50c,00000006 : 239 */
	write(base, 0x50c, 0x00000006);
	/* 1,&host_if->hc_regs[hc_num]->hcchar,500,01089200 : 240 */
	write(base, 0x500, 0x01089200);
	/* 1,&host_if->hc_regs[hc_num]->hcsplt,504,00000000 : 241 */
	write(base, 0x504, 0x00000000);
	/* 0,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 : 242 */
	read(base, 0x418, 0x00000001);
	/* 1,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 : 243 */
	write(base, 0x418, 0x00000001);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 244 */
	read(base, 0x18, 0xf3000806);
	/* 1,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 245 */
	write(base, 0x18, 0xf3000806);
	do {
		val = readl(base + 0x2c);
	} while (val < 0x00080100);
	/* 0,&global_regs->gnptxsts,2c,00080100 : 246 */
	read(base, 0x2c, 0x00080100);
	/* 1,&hc_regs->hctsiz,510,40401000 : 247 */
	write(base, 0x510, 0x40401000);
	/* 1,&hc_regs->hcdma,514,dc1a0000 : 252 */
	write(base, 0x514, data);
	/* 0,&hc_regs->hcchar,500,01089200 : 253 */
	read(base, 0x500, 0x01089200);
	/* 1,&hc_regs->hcchar,500,81189200 : 254 */
	write(base, 0x500, 0x81189200);
	/* 0,&(hc_regs)->hcintmsk,50c,00000006 : 255 */
	read(base, 0x50c, 0x00000006);
	/* 1,&(hc_regs)->hcintmsk,50c,00000006 : 256 */
	write(base, 0x50c, 0x00000006);
	poll_for_irq(base);
	/* 0,&core_if->core_global_regs->gpwrdn,58,00000000 : 257 */
	read(base, 0x58, 0x00000000);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 258 */
	read(base, 0x14, 0x06400029);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 259 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 : 260 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 : 261 */
	read(base, 0x18, 0xf3000806);
	/* 0,&core_if->core_global_regs->gahbcfg,8,00000031 : 262 */
	read(base, 0x8, 0x00000031);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 263 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 : 264 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 : 265 */
	read(base, 0x18, 0xf3000806);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 266 */
	read(base, 0x14, 0x06400029);
	/* 0,&dwc_otg_hcd->core_if->host_if->host_global_regs->hfnum,408,0b3d206f : 267 */
	read(base, 0x408, IGNORE);
	/* 0,&_core_if->host_if->host_global_regs->haint,414,00000001 : 268 */
	read(base, 0x414, 0x00000001);
	/* 0,&hc_regs->hcint,508,00000023 : 269 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 : 270 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hcint,508,00000023 : 271 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 : 272 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hctsiz,510,c0000000 : 273 */
	read(base, 0x510, 0xc0000000);
	/* 0,&hc_regs->hctsiz,510,c0000000 : 274 */
	read(base, 0x510, 0xc0000000);
	/* 0,&hc_regs->hcint,508,00000023 : 275 */
	read(base, 0x508, 0x00000023);
	/* 1,&hc_regs->hcintmsk,50c,00000000 : 276 */
	write(base, 0x50c, 0x00000000);
	/* 1,&hc_regs->hcint,508,ffffffff : 277 */
	write(base, 0x508, 0xffffffff);
	/* 1,&hc_regs->hcint,508,00003fff : 278 */
	write(base, 0x508, 0x00003fff);
	/* 1,&hc_regs->hcintmsk,50c,00000006 : 279 */
	write(base, 0x50c, 0x00000006);
	/* 1,&host_if->hc_regs[hc_num]->hcchar,500,01089200 : 280 */
	write(base, 0x500, 0x01089200);
	/* 1,&host_if->hc_regs[hc_num]->hcsplt,504,00000000 : 281 */
	write(base, 0x504, 0x00000000);
	/* 0,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 : 282 */
	read(base, 0x418, 0x00000001);
	/* 1,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 : 283 */
	write(base, 0x418, 0x00000001);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 284 */
	read(base, 0x18, 0xf3000806);
	/* 1,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 285 */
	write(base, 0x18, 0xf3000806);
	do {
		val = readl(base + 0x2c);
	} while (val < 0x00080100);
	/* 0,&global_regs->gnptxsts,2c,00080100 : 286 */
	read(base, 0x2c, 0x00080100);
	/* 1,&hc_regs->hctsiz,510,40401000 : 287 */
	write(base, 0x510, 0x40401000);
	/* 1,&hc_regs->hcdma,514,da837000 : 292 */
	write(base, 0x514, data);
	/* 0,&hc_regs->hcchar,500,01089200 : 293 */
	read(base, 0x500, 0x01089200);
	/* 1,&hc_regs->hcchar,500,81189200 : 294 */
	write(base, 0x500, 0x81189200);
	/* 0,&(hc_regs)->hcintmsk,50c,00000006 : 295 */
	read(base, 0x50c, 0x00000006);
	/* 1,&(hc_regs)->hcintmsk,50c,00000006 : 296 */
	write(base, 0x50c, 0x00000006);
	poll_for_irq(base);
	/* 0,&core_if->core_global_regs->gpwrdn,58,00000000 : 297 */
	read(base, 0x58, 0x00000000);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 298 */
	read(base, 0x14, 0x06400029);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 299 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 : 300 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 : 301 */
	read(base, 0x18, 0xf3000806);
	/* 0,&core_if->core_global_regs->gahbcfg,8,00000031 : 302 */
	read(base, 0x8, 0x00000031);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 303 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 : 304 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 : 305 */
	read(base, 0x18, 0xf3000806);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 306 */
	read(base, 0x14, 0x06400029);
	/* 0,&dwc_otg_hcd->core_if->host_if->host_global_regs->hfnum,408,054c2070 : 307 */
	read(base, 0x408, IGNORE);
	/* 0,&_core_if->host_if->host_global_regs->haint,414,00000001 : 308 */
	read(base, 0x414, 0x00000001);
	/* 0,&hc_regs->hcint,508,00000023 : 309 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 : 310 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hcint,508,00000023 : 311 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 : 312 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hctsiz,510,c0000000 : 313 */
	read(base, 0x510, 0xc0000000);
	/* 0,&hc_regs->hctsiz,510,c0000000 : 314 */
	read(base, 0x510, 0xc0000000);
	/* 0,&hc_regs->hcint,508,00000023 : 315 */
	read(base, 0x508, 0x00000023);
	/* 1,&hc_regs->hcintmsk,50c,00000000 : 316 */
	write(base, 0x50c, 0x00000000);
	/* 1,&hc_regs->hcint,508,ffffffff : 317 */
	write(base, 0x508, 0xffffffff);
	/* 0,&(hc_regs)->hcintmsk,50c,00000000 : 318 */
	read(base, 0x50c, 0x00000000);
	/* 1,&(hc_regs)->hcintmsk,50c,00000000 : 319 */
	write(base, 0x50c, 0x00000000);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 325 */
	read(base, 0x18, 0xf3000806);
	/* 1,&hc_regs->hcint,508,00003fff : 326 */
	write(base, 0x508, 0x00003fff);
	/* 1,&hc_regs->hcintmsk,50c,00000006 : 327 */
	write(base, 0x50c, 0x00000006);
	/* 1,&host_if->hc_regs[hc_num]->hcchar,500,01089200 : 328 */
	write(base, 0x500, 0x01089200);
	/* 1,&host_if->hc_regs[hc_num]->hcsplt,504,00000000 : 329 */
	write(base, 0x504, 0x00000000);
	/* 0,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 : 330 */
	read(base, 0x418, 0x00000001);
	/* 1,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 : 331 */
	write(base, 0x418, 0x00000001);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 332 */
	read(base, 0x18, 0xf3000806);
	/* 1,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 333 */
	write(base, 0x18, 0xf3000806);
	udelay(10);
	/* 0,&global_regs->gnptxsts,2c,00080100 : 334 */
	read(base, 0x2c, 0x00080100);
	/* 1,&hc_regs->hctsiz,510,40080200 : 335 */
	write(base, 0x510, 0x40080200);
	/* 1,&hc_regs->hcdma,514,f7053000 : 340 */
	write(base, 0x514, cmd);
	/* 0,&hc_regs->hcchar,500,01089200 : 341 */
	read(base, 0x500, 0x01089200);
	/* 1,&hc_regs->hcchar,500,81189200 : 342 */
	write(base, 0x500, 0x81189200);
	poll_for_irq(base);
	/* 0,&core_if->core_global_regs->gpwrdn,58,00000000 : 343 */
	read(base, 0x58, 0x00000000);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 344 */
	read(base, 0x14, 0x06400029);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 345 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 : 346 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 : 347 */
	read(base, 0x18, 0xf3000806);
	/* 0,&core_if->core_global_regs->gahbcfg,8,00000031 : 348 */
	read(base, 0x8, 0x00000031);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 349 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 : 350 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 : 351 */
	read(base, 0x18, 0xf3000806);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 352 */
	read(base, 0x14, 0x06400029);
	/* 0,&dwc_otg_hcd->core_if->host_if->host_global_regs->hfnum,408,06422071 : 353 */
	read(base, 0x408, IGNORE);
	/* 0,&_core_if->host_if->host_global_regs->haint,414,00000001 : 354 */
	read(base, 0x414, 0x00000001);
	/* 0,&hc_regs->hcint,508,00000023 : 355 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 : 356 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hcint,508,00000023 : 357 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 : 358 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hctsiz,510,800001f3 : 359 */
	read(base, 0x510, 0x800001f3);
	/* 0,&hc_regs->hctsiz,510,800001f3 : 360 */
	read(base, 0x510, 0x800001f3);
	/* 0,&hc_regs->hcint,508,00000023 : 361 */
	read(base, 0x508, 0x00000023);
	/* 1,&hc_regs->hcintmsk,50c,00000000 : 362 */
	write(base, 0x50c, 0x00000000);
	/* 1,&hc_regs->hcint,508,ffffffff : 363 */
	write(base, 0x508, 0xffffffff);
	/* 0,&(hc_regs)->hcintmsk,50c,00000000 : 364 */
	read(base, 0x50c, 0x00000000);
	/* 1,&(hc_regs)->hcintmsk,50c,00000000 : 365 */
	write(base, 0x50c, 0x00000000);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 374 */
	read(base, 0x18, 0xf3000806);
	/* 1,&hc_regs->hcint,508,00003fff : 375 */
	write(base, 0x508, 0x00003fff);
	/* 1,&hc_regs->hcintmsk,50c,00000006 : 376 */
	write(base, 0x50c, 0x00000006);
	/* 1,&host_if->hc_regs[hc_num]->hcchar,500,01081200 : 377 */
	write(base, 0x500, 0x01081200);
	/* 1,&host_if->hc_regs[hc_num]->hcsplt,504,00000000 : 378 */
	write(base, 0x504, 0x00000000);
	/* 0,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 : 379 */
	read(base, 0x418, 0x00000001);
	/* 1,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 : 380 */
	write(base, 0x418, 0x00000001);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 381 */
	read(base, 0x18, 0xf3000806);
	/* 1,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 382 */
	write(base, 0x18, 0xf3000806);
	cmd = prepare_allow_medium_removal(0);
	udelay(10);
	/* 0,&global_regs->gnptxsts,2c,00080100 : 383 */
	read(base, 0x2c, 0x00080100);
	/* 1,&hc_regs->hctsiz,510,0008001f : 384 */
	write(base, 0x510, 0x0008001f);
	/* 1,&hc_regs->hcdma,514,f7053000 : 389 */
	write(base, 0x514, cmd);
	/* 0,&hc_regs->hcchar,500,01081200 : 390 */
	read(base, 0x500, 0x01081200);
	/* 1,&hc_regs->hcchar,500,81181200 : 391 */
	write(base, 0x500, 0x81181200);
	poll_for_irq(base);
	/* 0,&core_if->core_global_regs->gpwrdn,58,00000000 : 392 */
	read(base, 0x58, 0x00000000);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 393 */
	read(base, 0x14, 0x06400029);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 394 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 : 395 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 : 396 */
	read(base, 0x18, 0xf3000806);
	/* 0,&core_if->core_global_regs->gahbcfg,8,00000031 : 397 */
	read(base, 0x8, 0x00000031);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 398 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 : 399 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 : 400 */
	read(base, 0x18, 0xf3000806);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 401 */
	read(base, 0x14, 0x06400029);
	/* 0,&dwc_otg_hcd->core_if->host_if->host_global_regs->hfnum,408,0c9920be : 402 */
	read(base, 0x408, IGNORE);
	/* 0,&_core_if->host_if->host_global_regs->haint,414,00000001 : 403 */
	read(base, 0x414, 0x00000001);
	/* 0,&hc_regs->hcint,508,00000023 : 404 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 : 405 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hcint,508,00000023 : 406 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 : 407 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hctsiz,510,4000001f : 408 */
	read(base, 0x510, 0x4000001f);
	/* 0,&hc_regs->hctsiz,510,4000001f : 409 */
	read(base, 0x510, 0x4000001f);
	/* 0,&hc_regs->hcint,508,00000023 : 410 */
	read(base, 0x508, 0x00000023);
	/* 1,&hc_regs->hcintmsk,50c,00000000 : 411 */
	write(base, 0x50c, 0x00000000);
	/* 1,&hc_regs->hcint,508,ffffffff : 412 */
	write(base, 0x508, 0xffffffff);
	/* 0,&(hc_regs)->hcintmsk,50c,00000000 : 413 */
	read(base, 0x50c, 0x00000000);
	/* 1,&(hc_regs)->hcintmsk,50c,00000000 : 414 */
	write(base, 0x50c, 0x00000000);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 419 */
	read(base, 0x18, 0xf3000806);
	/* 1,&hc_regs->hcint,508,00003fff : 420 */
	write(base, 0x508, 0x00003fff);
	/* 1,&hc_regs->hcintmsk,50c,00000006 : 421 */
	write(base, 0x50c, 0x00000006);
	/* 1,&host_if->hc_regs[hc_num]->hcchar,500,01089200 : 422 */
	write(base, 0x500, 0x01089200);
	/* 1,&host_if->hc_regs[hc_num]->hcsplt,504,00000000 : 423 */
	write(base, 0x504, 0x00000000);
	/* 0,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 : 424 */
	read(base, 0x418, 0x00000001);
	/* 1,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 : 425 */
	write(base, 0x418, 0x00000001);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 426 */
	read(base, 0x18, 0xf3000806);
	/* 1,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 427 */
	write(base, 0x18, 0xf3000806);
	udelay(10);
	/* 0,&global_regs->gnptxsts,2c,00080100 : 428 */
	read(base, 0x2c, 0x00080100);
	/* 1,&hc_regs->hctsiz,510,00080200 : 429 */
	write(base, 0x510, 0x00080200);
	/* 1,&hc_regs->hcdma,514,f7053000 : 434 */
	write(base, 0x514, cmd);
	/* 0,&hc_regs->hcchar,500,01089200 : 435 */
	read(base, 0x500, 0x01089200);
	/* 1,&hc_regs->hcchar,500,81189200 : 436 */
	write(base, 0x500, 0x81189200);
	poll_for_irq(base);
	/* 0,&core_if->core_global_regs->gpwrdn,58,00000000 : 437 */
	read(base, 0x58, 0x00000000);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 438 */
	read(base, 0x14, 0x06400029);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 439 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 : 440 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 : 441 */
	read(base, 0x18, 0xf3000806);
	/* 0,&core_if->core_global_regs->gahbcfg,8,00000031 : 442 */
	read(base, 0x8, 0x00000031);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 443 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 : 444 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 : 445 */
	read(base, 0x18, 0xf3000806);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 446 */
	read(base, 0x14, 0x06400029);
	/* 0,&dwc_otg_hcd->core_if->host_if->host_global_regs->hfnum,408,0b8b20c0 : 447 */
	read(base, 0x408, IGNORE);
	/* 0,&_core_if->host_if->host_global_regs->haint,414,00000001 : 448 */
	read(base, 0x414, 0x00000001);
	/* 0,&hc_regs->hcint,508,00000023 : 449 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 : 450 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hcint,508,00000023 : 451 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 : 452 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hctsiz,510,c00001f3 : 453 */
	read(base, 0x510, 0xc00001f3);
	/* 0,&hc_regs->hctsiz,510,c00001f3 : 454 */
	read(base, 0x510, 0xc00001f3);
	/* 0,&hc_regs->hcint,508,00000023 : 455 */
	read(base, 0x508, 0x00000023);
	/* 1,&hc_regs->hcintmsk,50c,00000000 : 456 */
	write(base, 0x50c, 0x00000000);
	/* 1,&hc_regs->hcint,508,ffffffff : 457 */
	write(base, 0x508, 0xffffffff);
	/* 0,&(hc_regs)->hcintmsk,50c,00000000 : 458 */
	read(base, 0x50c, 0x00000000);
	/* 1,&(hc_regs)->hcintmsk,50c,00000000 : 459 */
	write(base, 0x50c, 0x00000000);
}
