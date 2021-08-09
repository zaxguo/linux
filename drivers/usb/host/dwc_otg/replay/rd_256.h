#include"common.h"
static void rd_256(void *base)
{
	dma_addr_t cmd, data;
	u32 val;
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
	poll_less_than_with_max_tries(base + 0x2c, 0x00080100, 200);
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
	/* 0,&dwc_otg_hcd->core_if->host_if->host_global_regs->hfnum,408,12ed028d : 46 */
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
	poll_less_than_with_max_tries(base + 0x2c, 0x00080100, 200);
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
	/* 0,&dwc_otg_hcd->core_if->host_if->host_global_regs->hfnum,408,0da7028e : 91 */
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
	poll_less_than_with_max_tries(base + 0x2c, 0x00080100, 200);
	/* 0,&global_regs->gnptxsts,2c,00080100 : 121 */
	read(base, 0x2c, 0x00080100);
	cmd = prepare_read_10(240);
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
	/* 0,&dwc_otg_hcd->core_if->host_if->host_global_regs->hfnum,408,022502df : 140 */
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
	poll_less_than_with_max_tries(base + 0x2c, 0x00080100, 200);
	/* 0,&global_regs->gnptxsts,2c,00080100 : 162 */
	read(base, 0x2c, 0x00080100);
	/* 1,&hc_regs->hctsiz,510,40401000 : 163 */
	write(base, 0x510, 0x40401000);
	/* 1,&hc_regs->hcdma,514,d9435000 : 168 */
	write(base, 0x514, data);
	/* 0,&hc_regs->hcchar,500,01089200 : 169 */
	read(base, 0x500, 0x01089200);
	/* 1,&hc_regs->hcchar,500,81189200 : 170 */
	write(base, 0x500, 0x81189200);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 171 */
	read(base, 0x18, 0xf3000806);
	/* 0,&global_regs->gnptxsts,2c,00000100 : 172 */
	read(base, 0x2c, 0x00000100);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 173 */
	read(base, 0x18, 0xf3000806);
	/* 0,&global_regs->gnptxsts,2c,00000100 : 174 */
	read(base, 0x2c, 0x00000100);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 175 */
	read(base, 0x18, 0xf3000806);
	/* 0,&global_regs->gnptxsts,2c,00000100 : 176 */
	read(base, 0x2c, 0x00000100);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 177 */
	read(base, 0x18, 0xf3000806);
	/* 0,&global_regs->gnptxsts,2c,00000100 : 178 */
	read(base, 0x2c, 0x00000100);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 179 */
	read(base, 0x18, 0xf3000806);
	/* 0,&global_regs->gnptxsts,2c,00000100 : 180 */
	read(base, 0x2c, 0x00000100);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 181 */
	read(base, 0x18, 0xf3000806);
	/* 0,&global_regs->gnptxsts,2c,00080100 : 182 */
	read(base, 0x2c, 0x00080100);
	poll_for_irq(base);
	/* 0,&core_if->core_global_regs->gpwrdn,58,00000000 : 183 */
	read(base, 0x58, 0x00000000);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 184 */
	read(base, 0x14, 0x06400029);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 185 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 : 186 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 : 187 */
	read(base, 0x18, 0xf3000806);
	/* 0,&core_if->core_global_regs->gahbcfg,8,00000031 : 188 */
	read(base, 0x8, 0x00000031);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 189 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 : 190 */
	read(base, 0x14, 0x06400029);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 191 */
	read(base, 0x18, 0xf3000806);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 : 192 */
	read(base, 0x18, 0xf3000806);
	/* 0,&global_regs->gnptxsts,2c,00080100 : 193 */
	read(base, 0x2c, 0x00080100);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 194 */
	read(base, 0x14, 0x06400029);
	/* 0,&dwc_otg_hcd->core_if->host_if->host_global_regs->hfnum,408,091202e2 : 195 */
	read(base, 0x408, IGNORE);
	/* 0,&_core_if->host_if->host_global_regs->haint,414,00000001 : 196 */
	read(base, 0x414, 0x00000001);
	/* 0,&hc_regs->hcint,508,00000023 : 197 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 : 198 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hcint,508,00000023 : 199 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 : 200 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hctsiz,510,c0000000 : 201 */
	read(base, 0x510, 0xc0000000);
	/* 0,&hc_regs->hctsiz,510,c0000000 : 202 */
	read(base, 0x510, 0xc0000000);
	/* 0,&hc_regs->hcint,508,00000023 : 203 */
	read(base, 0x508, 0x00000023);
	/* 1,&hc_regs->hcintmsk,50c,00000000 : 204 */
	write(base, 0x50c, 0x00000000);
	/* 1,&hc_regs->hcint,508,ffffffff : 205 */
	write(base, 0x508, 0xffffffff);
	/* 1,&hc_regs->hcint,508,00003fff : 206 */
	write(base, 0x508, 0x00003fff);
	/* 1,&hc_regs->hcintmsk,50c,00000006 : 207 */
	write(base, 0x50c, 0x00000006);
	/* 1,&host_if->hc_regs[hc_num]->hcchar,500,01089200 : 208 */
	write(base, 0x500, 0x01089200);
	/* 1,&host_if->hc_regs[hc_num]->hcsplt,504,00000000 : 209 */
	write(base, 0x504, 0x00000000);
	/* 0,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 : 210 */
	read(base, 0x418, 0x00000001);
	/* 1,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 : 211 */
	write(base, 0x418, 0x00000001);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 212 */
	read(base, 0x18, 0xf3000806);
	/* 1,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 213 */
	write(base, 0x18, 0xf3000806);
	poll_less_than_with_max_tries(base + 0x2c, 0x00080100, 200);
	/* 0,&global_regs->gnptxsts,2c,00080100 : 214 */
	read(base, 0x2c, 0x00080100);
	/* 1,&hc_regs->hctsiz,510,40401000 : 215 */
	write(base, 0x510, 0x40401000);
	/* 1,&hc_regs->hcdma,514,d8700000 : 220 */
	write(base, 0x514, data);
	/* 0,&hc_regs->hcchar,500,01089200 : 221 */
	read(base, 0x500, 0x01089200);
	/* 1,&hc_regs->hcchar,500,81189200 : 222 */
	write(base, 0x500, 0x81189200);
	/* 0,&(hc_regs)->hcintmsk,50c,00000006 : 223 */
	read(base, 0x50c, 0x00000006);
	/* 1,&(hc_regs)->hcintmsk,50c,00000006 : 224 */
	write(base, 0x50c, 0x00000006);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 225 */
	read(base, 0x18, 0xf3000806);
	/* 0,&global_regs->gnptxsts,2c,00000100 : 226 */
	read(base, 0x2c, 0x00000100);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 227 */
	read(base, 0x18, 0xf3000806);
	/* 0,&global_regs->gnptxsts,2c,00000100 : 228 */
	read(base, 0x2c, 0x00000100);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 229 */
	read(base, 0x18, 0xf3000806);
	/* 0,&global_regs->gnptxsts,2c,00000100 : 230 */
	read(base, 0x2c, 0x00000100);
	poll_for_irq(base);
	/* 0,&core_if->core_global_regs->gpwrdn,58,00000000 : 231 */
	read(base, 0x58, 0x00000000);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 232 */
	read(base, 0x14, 0x06400029);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 233 */
	read(base, 0x18, 0xf3000806);
	/* 0,&global_regs->gnptxsts,2c,00080100 : 234 */
	read(base, 0x2c, 0x00080100);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 235 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 : 236 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 : 237 */
	read(base, 0x18, 0xf3000806);
	/* 0,&core_if->core_global_regs->gahbcfg,8,00000031 : 238 */
	read(base, 0x8, 0x00000031);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 239 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 : 240 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 : 241 */
	read(base, 0x18, 0xf3000806);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 242 */
	read(base, 0x14, 0x06400029);
	/* 0,&dwc_otg_hcd->core_if->host_if->host_global_regs->hfnum,408,1c1d02e4 : 243 */
	read(base, 0x408, IGNORE);
	/* 0,&_core_if->host_if->host_global_regs->haint,414,00000001 : 244 */
	read(base, 0x414, 0x00000001);
	/* 0,&hc_regs->hcint,508,00000023 : 245 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 : 246 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hcint,508,00000023 : 247 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 : 248 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hctsiz,510,c0000000 : 249 */
	read(base, 0x510, 0xc0000000);
	/* 0,&hc_regs->hctsiz,510,c0000000 : 250 */
	read(base, 0x510, 0xc0000000);
	/* 0,&hc_regs->hcint,508,00000023 : 251 */
	read(base, 0x508, 0x00000023);
	/* 1,&hc_regs->hcintmsk,50c,00000000 : 252 */
	write(base, 0x50c, 0x00000000);
	/* 1,&hc_regs->hcint,508,ffffffff : 253 */
	write(base, 0x508, 0xffffffff);
	/* 1,&hc_regs->hcint,508,00003fff : 254 */
	write(base, 0x508, 0x00003fff);
	/* 1,&hc_regs->hcintmsk,50c,00000006 : 255 */
	write(base, 0x50c, 0x00000006);
	/* 1,&host_if->hc_regs[hc_num]->hcchar,500,01089200 : 256 */
	write(base, 0x500, 0x01089200);
	/* 1,&host_if->hc_regs[hc_num]->hcsplt,504,00000000 : 257 */
	write(base, 0x504, 0x00000000);
	/* 0,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 : 258 */
	read(base, 0x418, 0x00000001);
	/* 1,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 : 259 */
	write(base, 0x418, 0x00000001);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 260 */
	read(base, 0x18, 0xf3000806);
	/* 1,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 261 */
	write(base, 0x18, 0xf3000806);
	poll_less_than_with_max_tries(base + 0x2c, 0x00080100, 200);
	/* 0,&global_regs->gnptxsts,2c,00080100 : 262 */
	read(base, 0x2c, 0x00080100);
	/* 1,&hc_regs->hctsiz,510,40401000 : 263 */
	write(base, 0x510, 0x40401000);
	/* 1,&hc_regs->hcdma,514,db99e000 : 268 */
	write(base, 0x514, data);
	/* 0,&hc_regs->hcchar,500,01089200 : 269 */
	read(base, 0x500, 0x01089200);
	/* 1,&hc_regs->hcchar,500,81189200 : 270 */
	write(base, 0x500, 0x81189200);
	/* 0,&(hc_regs)->hcintmsk,50c,00000006 : 271 */
	read(base, 0x50c, 0x00000006);
	/* 1,&(hc_regs)->hcintmsk,50c,00000006 : 272 */
	write(base, 0x50c, 0x00000006);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 273 */
	read(base, 0x18, 0xf3000806);
	/* 0,&global_regs->gnptxsts,2c,00000100 : 274 */
	read(base, 0x2c, 0x00000100);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 275 */
	read(base, 0x18, 0xf3000806);
	/* 0,&global_regs->gnptxsts,2c,00000100 : 276 */
	read(base, 0x2c, 0x00000100);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 277 */
	read(base, 0x18, 0xf3000806);
	/* 0,&global_regs->gnptxsts,2c,00000100 : 278 */
	read(base, 0x2c, 0x00000100);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 279 */
	read(base, 0x18, 0xf3000806);
	/* 0,&global_regs->gnptxsts,2c,00080100 : 280 */
	read(base, 0x2c, 0x00080100);
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
	/* 0,&dwc_otg_hcd->core_if->host_if->host_global_regs->hfnum,408,130e02e5 : 291 */
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
	/* 0,&global_regs->gnptxsts,2c,00080100 : 310 */
	read(base, 0x2c, 0x00080100);
	/* 1,&hc_regs->hctsiz,510,40401000 : 311 */
	write(base, 0x510, 0x40401000);
	/* 0,&hc_regs->hcchar,500,01089200 : 317 */
	read(base, 0x500, 0x01089200);
	/* 1,&hc_regs->hcchar,500,81189200 : 318 */
	write(base, 0x500, 0x81189200);
	/* 0,&(hc_regs)->hcintmsk,50c,00000006 : 319 */
	read(base, 0x50c, 0x00000006);
	/* 1,&(hc_regs)->hcintmsk,50c,00000006 : 320 */
	write(base, 0x50c, 0x00000006);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 321 */
	read(base, 0x18, 0xf3000806);
	/* 0,&global_regs->gnptxsts,2c,00000100 : 322 */
	read(base, 0x2c, 0x00000100);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 323 */
	read(base, 0x18, 0xf3000806);
	/* 0,&global_regs->gnptxsts,2c,00000100 : 324 */
	read(base, 0x2c, 0x00000100);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 325 */
	read(base, 0x18, 0xf3000806);
	/* 0,&global_regs->gnptxsts,2c,00000100 : 326 */
	read(base, 0x2c, 0x00000100);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 327 */
	read(base, 0x18, 0xf3000806);
	/* 0,&global_regs->gnptxsts,2c,00000100 : 328 */
	read(base, 0x2c, 0x00000100);
	poll_for_irq(base);
	/* 0,&core_if->core_global_regs->gpwrdn,58,00000000 : 329 */
	read(base, 0x58, 0x00000000);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 330 */
	read(base, 0x14, 0x06400029);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 331 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 : 332 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 : 333 */
	read(base, 0x18, 0xf3000806);
	/* 0,&core_if->core_global_regs->gahbcfg,8,00000031 : 334 */
	read(base, 0x8, 0x00000031);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 335 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 : 336 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 : 337 */
	read(base, 0x18, 0xf3000806);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 338 */
	read(base, 0x14, 0x06400029);
	/* 0,&dwc_otg_hcd->core_if->host_if->host_global_regs->hfnum,408,070b02e6 : 339 */
	read(base, 0x408, IGNORE);
	/* 0,&_core_if->host_if->host_global_regs->haint,414,00000001 : 340 */
	read(base, 0x414, 0x00000001);
	/* 0,&hc_regs->hcint,508,00000023 : 341 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 : 342 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hcint,508,00000023 : 343 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 : 344 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hctsiz,510,c0000000 : 345 */
	read(base, 0x510, 0xc0000000);
	/* 0,&hc_regs->hctsiz,510,c0000000 : 346 */
	read(base, 0x510, 0xc0000000);
	/* 0,&hc_regs->hcint,508,00000023 : 347 */
	read(base, 0x508, 0x00000023);
	/* 1,&hc_regs->hcintmsk,50c,00000000 : 348 */
	write(base, 0x50c, 0x00000000);
	/* 1,&hc_regs->hcint,508,ffffffff : 349 */
	write(base, 0x508, 0xffffffff);
	/* 1,&hc_regs->hcint,508,00003fff : 350 */
	write(base, 0x508, 0x00003fff);
	/* 1,&hc_regs->hcintmsk,50c,00000006 : 351 */
	write(base, 0x50c, 0x00000006);
	/* 1,&host_if->hc_regs[hc_num]->hcchar,500,01089200 : 352 */
	write(base, 0x500, 0x01089200);
	/* 1,&host_if->hc_regs[hc_num]->hcsplt,504,00000000 : 353 */
	write(base, 0x504, 0x00000000);
	/* 0,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 : 354 */
	read(base, 0x418, 0x00000001);
	/* 1,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 : 355 */
	write(base, 0x418, 0x00000001);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 356 */
	read(base, 0x18, 0xf3000806);
	/* 1,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 357 */
	write(base, 0x18, 0xf3000806);
	poll_less_than_with_max_tries(base + 0x2c, 0x00080100, 200);
	/* 0,&global_regs->gnptxsts,2c,00080100 : 358 */
	read(base, 0x2c, 0x00080100);
	/* 1,&hc_regs->hctsiz,510,40401000 : 359 */
	write(base, 0x510, 0x40401000);
	/* 1,&hc_regs->hcdma,514,dc80d000 : 364 */
	write(base, 0x514, data);
	/* 0,&hc_regs->hcchar,500,01089200 : 365 */
	read(base, 0x500, 0x01089200);
	/* 1,&hc_regs->hcchar,500,81189200 : 366 */
	write(base, 0x500, 0x81189200);
	/* 0,&(hc_regs)->hcintmsk,50c,00000006 : 367 */
	read(base, 0x50c, 0x00000006);
	/* 1,&(hc_regs)->hcintmsk,50c,00000006 : 368 */
	write(base, 0x50c, 0x00000006);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 369 */
	read(base, 0x18, 0xf3000806);
	/* 0,&global_regs->gnptxsts,2c,00000100 : 370 */
	read(base, 0x2c, 0x00000100);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 371 */
	read(base, 0x18, 0xf3000806);
	/* 0,&global_regs->gnptxsts,2c,00000100 : 372 */
	read(base, 0x2c, 0x00000100);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 373 */
	read(base, 0x18, 0xf3000806);
	/* 0,&global_regs->gnptxsts,2c,00000100 : 374 */
	read(base, 0x2c, 0x00000100);
	poll_for_irq(base);
	/* 0,&core_if->core_global_regs->gpwrdn,58,00000000 : 375 */
	read(base, 0x58, 0x00000000);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 376 */
	read(base, 0x14, 0x06400029);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 377 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 : 378 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 : 379 */
	read(base, 0x18, 0xf3000806);
	/* 0,&core_if->core_global_regs->gahbcfg,8,00000031 : 380 */
	read(base, 0x8, 0x00000031);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 381 */
	read(base, 0x14, 0x06400029);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 382 */
	read(base, 0x18, 0xf3000806);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 : 383 */
	read(base, 0x14, 0x06400029);
	/* 0,&global_regs->gnptxsts,2c,00080100 : 384 */
	read(base, 0x2c, 0x00080100);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 : 385 */
	read(base, 0x18, 0xf3000806);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 386 */
	read(base, 0x14, 0x06400029);
	/* 0,&dwc_otg_hcd->core_if->host_if->host_global_regs->hfnum,408,01b902e7 : 387 */
	read(base, 0x408, IGNORE);
	/* 0,&_core_if->host_if->host_global_regs->haint,414,00000001 : 388 */
	read(base, 0x414, 0x00000001);
	/* 0,&hc_regs->hcint,508,00000023 : 389 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 : 390 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hcint,508,00000023 : 391 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 : 392 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hctsiz,510,c0000000 : 393 */
	read(base, 0x510, 0xc0000000);
	/* 0,&hc_regs->hctsiz,510,c0000000 : 394 */
	read(base, 0x510, 0xc0000000);
	/* 0,&hc_regs->hcint,508,00000023 : 395 */
	read(base, 0x508, 0x00000023);
	/* 1,&hc_regs->hcintmsk,50c,00000000 : 396 */
	write(base, 0x50c, 0x00000000);
	/* 1,&hc_regs->hcint,508,ffffffff : 397 */
	write(base, 0x508, 0xffffffff);
	/* 1,&hc_regs->hcint,508,00003fff : 398 */
	write(base, 0x508, 0x00003fff);
	/* 1,&hc_regs->hcintmsk,50c,00000006 : 399 */
	write(base, 0x50c, 0x00000006);
	/* 1,&host_if->hc_regs[hc_num]->hcchar,500,01089200 : 400 */
	write(base, 0x500, 0x01089200);
	/* 1,&host_if->hc_regs[hc_num]->hcsplt,504,00000000 : 401 */
	write(base, 0x504, 0x00000000);
	/* 0,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 : 402 */
	read(base, 0x418, 0x00000001);
	/* 1,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 : 403 */
	write(base, 0x418, 0x00000001);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 404 */
	read(base, 0x18, 0xf3000806);
	/* 1,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 405 */
	write(base, 0x18, 0xf3000806);
	poll_less_than_with_max_tries(base + 0x2c, 0x00080100, 200);
	/* 0,&global_regs->gnptxsts,2c,00080100 : 406 */
	read(base, 0x2c, 0x00080100);
	/* 1,&hc_regs->hctsiz,510,40401000 : 407 */
	write(base, 0x510, 0x40401000);
	/* 1,&hc_regs->hcdma,514,dffe5000 : 412 */
	write(base, 0x514, data);
	/* 0,&hc_regs->hcchar,500,01089200 : 413 */
	read(base, 0x500, 0x01089200);
	/* 1,&hc_regs->hcchar,500,81189200 : 414 */
	write(base, 0x500, 0x81189200);
	/* 0,&(hc_regs)->hcintmsk,50c,00000006 : 415 */
	read(base, 0x50c, 0x00000006);
	/* 1,&(hc_regs)->hcintmsk,50c,00000006 : 416 */
	write(base, 0x50c, 0x00000006);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 417 */
	read(base, 0x18, 0xf3000806);
	/* 0,&global_regs->gnptxsts,2c,00000100 : 418 */
	read(base, 0x2c, 0x00000100);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 419 */
	read(base, 0x18, 0xf3000806);
	/* 0,&global_regs->gnptxsts,2c,00000100 : 420 */
	read(base, 0x2c, 0x00000100);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 421 */
	read(base, 0x18, 0xf3000806);
	/* 0,&global_regs->gnptxsts,2c,00000100 : 422 */
	read(base, 0x2c, 0x00000100);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 423 */
	read(base, 0x18, 0xf3000806);
	/* 0,&global_regs->gnptxsts,2c,00080100 : 424 */
	read(base, 0x2c, 0x00080100);
	poll_for_irq(base);
	/* 0,&core_if->core_global_regs->gpwrdn,58,00000000 : 425 */
	read(base, 0x58, 0x00000000);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 426 */
	read(base, 0x14, 0x06400029);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 427 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 : 428 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 : 429 */
	read(base, 0x18, 0xf3000806);
	/* 0,&core_if->core_global_regs->gahbcfg,8,00000031 : 430 */
	read(base, 0x8, 0x00000031);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 431 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 : 432 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 : 433 */
	read(base, 0x18, 0xf3000806);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 434 */
	read(base, 0x14, 0x06400029);
	/* 0,&dwc_otg_hcd->core_if->host_if->host_global_regs->hfnum,408,193502e9 : 435 */
	read(base, 0x408, IGNORE);
	/* 0,&_core_if->host_if->host_global_regs->haint,414,00000001 : 436 */
	read(base, 0x414, 0x00000001);
	/* 0,&hc_regs->hcint,508,00000023 : 437 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 : 438 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hcint,508,00000023 : 439 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 : 440 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hctsiz,510,c0000000 : 441 */
	read(base, 0x510, 0xc0000000);
	/* 0,&hc_regs->hctsiz,510,c0000000 : 442 */
	read(base, 0x510, 0xc0000000);
	/* 0,&hc_regs->hcint,508,00000023 : 443 */
	read(base, 0x508, 0x00000023);
	/* 1,&hc_regs->hcintmsk,50c,00000000 : 444 */
	write(base, 0x50c, 0x00000000);
	/* 1,&hc_regs->hcint,508,ffffffff : 445 */
	write(base, 0x508, 0xffffffff);
	/* 1,&hc_regs->hcint,508,00003fff : 446 */
	write(base, 0x508, 0x00003fff);
	/* 1,&hc_regs->hcintmsk,50c,00000006 : 447 */
	write(base, 0x50c, 0x00000006);
	/* 1,&host_if->hc_regs[hc_num]->hcchar,500,01089200 : 448 */
	write(base, 0x500, 0x01089200);
	/* 1,&host_if->hc_regs[hc_num]->hcsplt,504,00000000 : 449 */
	write(base, 0x504, 0x00000000);
	/* 0,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 : 450 */
	read(base, 0x418, 0x00000001);
	/* 1,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 : 451 */
	write(base, 0x418, 0x00000001);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 452 */
	read(base, 0x18, 0xf3000806);
	/* 1,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 453 */
	write(base, 0x18, 0xf3000806);
	poll_less_than_with_max_tries(base + 0x2c, 0x00080100, 200);
	/* 0,&global_regs->gnptxsts,2c,00080100 : 454 */
	read(base, 0x2c, 0x00080100);
	/* 1,&hc_regs->hctsiz,510,40401000 : 455 */
	write(base, 0x510, 0x40401000);
	/* 1,&hc_regs->hcdma,514,da34d000 : 460 */
	write(base, 0x514, data);
	/* 0,&hc_regs->hcchar,500,01089200 : 461 */
	read(base, 0x500, 0x01089200);
	/* 1,&hc_regs->hcchar,500,81189200 : 462 */
	write(base, 0x500, 0x81189200);
	/* 0,&(hc_regs)->hcintmsk,50c,00000006 : 463 */
	read(base, 0x50c, 0x00000006);
	/* 1,&(hc_regs)->hcintmsk,50c,00000006 : 464 */
	write(base, 0x50c, 0x00000006);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 465 */
	read(base, 0x18, 0xf3000806);
	/* 0,&global_regs->gnptxsts,2c,00000100 : 466 */
	read(base, 0x2c, 0x00000100);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 467 */
	read(base, 0x18, 0xf3000806);
	/* 0,&global_regs->gnptxsts,2c,00000100 : 468 */
	read(base, 0x2c, 0x00000100);
	poll_for_irq(base);
	/* 0,&core_if->core_global_regs->gpwrdn,58,00000000 : 469 */
	read(base, 0x58, 0x00000000);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 470 */
	read(base, 0x14, 0x06400029);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 471 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 : 472 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 : 473 */
	read(base, 0x18, 0xf3000806);
	/* 0,&core_if->core_global_regs->gahbcfg,8,00000031 : 474 */
	read(base, 0x8, 0x00000031);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 475 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 : 476 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 : 477 */
	read(base, 0x18, 0xf3000806);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 478 */
	read(base, 0x14, 0x06400029);
	/* 0,&dwc_otg_hcd->core_if->host_if->host_global_regs->hfnum,408,110a02ea : 479 */
	read(base, 0x408, IGNORE);
	/* 0,&_core_if->host_if->host_global_regs->haint,414,00000001 : 480 */
	read(base, 0x414, 0x00000001);
	/* 0,&hc_regs->hcint,508,00000023 : 481 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 : 482 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hcint,508,00000023 : 483 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 : 484 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hctsiz,510,c0000000 : 485 */
	read(base, 0x510, 0xc0000000);
	/* 0,&hc_regs->hctsiz,510,c0000000 : 486 */
	read(base, 0x510, 0xc0000000);
	/* 0,&hc_regs->hcint,508,00000023 : 487 */
	read(base, 0x508, 0x00000023);
	/* 1,&hc_regs->hcintmsk,50c,00000000 : 488 */
	write(base, 0x50c, 0x00000000);
	/* 1,&hc_regs->hcint,508,ffffffff : 489 */
	write(base, 0x508, 0xffffffff);
	/* 1,&hc_regs->hcint,508,00003fff : 490 */
	write(base, 0x508, 0x00003fff);
	/* 1,&hc_regs->hcintmsk,50c,00000006 : 491 */
	write(base, 0x50c, 0x00000006);
	/* 1,&host_if->hc_regs[hc_num]->hcchar,500,01089200 : 492 */
	write(base, 0x500, 0x01089200);
	/* 1,&host_if->hc_regs[hc_num]->hcsplt,504,00000000 : 493 */
	write(base, 0x504, 0x00000000);
	/* 0,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 : 494 */
	read(base, 0x418, 0x00000001);
	/* 1,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 : 495 */
	write(base, 0x418, 0x00000001);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 496 */
	read(base, 0x18, 0xf3000806);
	/* 1,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 497 */
	write(base, 0x18, 0xf3000806);
	poll_less_than_with_max_tries(base + 0x2c, 0x00080100, 200);
	/* 0,&global_regs->gnptxsts,2c,00080100 : 498 */
	read(base, 0x2c, 0x00080100);
	/* 1,&hc_regs->hctsiz,510,40401000 : 499 */
	write(base, 0x510, 0x40401000);
	/* 1,&hc_regs->hcdma,514,e05b1000 : 504 */
	write(base, 0x514, data);
	/* 0,&hc_regs->hcchar,500,01089200 : 505 */
	read(base, 0x500, 0x01089200);
	/* 1,&hc_regs->hcchar,500,81189200 : 506 */
	write(base, 0x500, 0x81189200);
	/* 0,&(hc_regs)->hcintmsk,50c,00000006 : 507 */
	read(base, 0x50c, 0x00000006);
	/* 1,&(hc_regs)->hcintmsk,50c,00000006 : 508 */
	write(base, 0x50c, 0x00000006);
	poll_for_irq(base);
	/* 0,&core_if->core_global_regs->gpwrdn,58,00000000 : 509 */
	read(base, 0x58, 0x00000000);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 510 */
	read(base, 0x14, 0x06400029);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 511 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 : 512 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 : 513 */
	read(base, 0x18, 0xf3000806);
	/* 0,&core_if->core_global_regs->gahbcfg,8,00000031 : 514 */
	read(base, 0x8, 0x00000031);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 515 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 : 516 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 : 517 */
	read(base, 0x18, 0xf3000806);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 518 */
	read(base, 0x14, 0x06400029);
	/* 0,&dwc_otg_hcd->core_if->host_if->host_global_regs->hfnum,408,099602eb : 519 */
	read(base, 0x408, IGNORE);
	/* 0,&_core_if->host_if->host_global_regs->haint,414,00000001 : 520 */
	read(base, 0x414, 0x00000001);
	/* 0,&hc_regs->hcint,508,00000023 : 521 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 : 522 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hcint,508,00000023 : 523 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 : 524 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hctsiz,510,c0000000 : 525 */
	read(base, 0x510, 0xc0000000);
	/* 0,&hc_regs->hctsiz,510,c0000000 : 526 */
	read(base, 0x510, 0xc0000000);
	/* 0,&hc_regs->hcint,508,00000023 : 527 */
	read(base, 0x508, 0x00000023);
	/* 1,&hc_regs->hcintmsk,50c,00000000 : 528 */
	write(base, 0x50c, 0x00000000);
	/* 1,&hc_regs->hcint,508,ffffffff : 529 */
	write(base, 0x508, 0xffffffff);
	/* 1,&hc_regs->hcint,508,00003fff : 530 */
	write(base, 0x508, 0x00003fff);
	/* 1,&hc_regs->hcintmsk,50c,00000006 : 531 */
	write(base, 0x50c, 0x00000006);
	/* 1,&host_if->hc_regs[hc_num]->hcchar,500,01089200 : 532 */
	write(base, 0x500, 0x01089200);
	/* 1,&host_if->hc_regs[hc_num]->hcsplt,504,00000000 : 533 */
	write(base, 0x504, 0x00000000);
	/* 0,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 : 534 */
	read(base, 0x418, 0x00000001);
	/* 1,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 : 535 */
	write(base, 0x418, 0x00000001);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 536 */
	read(base, 0x18, 0xf3000806);
	/* 1,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 537 */
	write(base, 0x18, 0xf3000806);
	poll_less_than_with_max_tries(base + 0x2c, 0x00080100, 200);
	/* 0,&global_regs->gnptxsts,2c,00080100 : 538 */
	read(base, 0x2c, 0x00080100);
	/* 1,&hc_regs->hctsiz,510,40401000 : 539 */
	write(base, 0x510, 0x40401000);
	/* 1,&hc_regs->hcdma,514,debd0000 : 544 */
	write(base, 0x514, data);
	/* 0,&hc_regs->hcchar,500,01089200 : 545 */
	read(base, 0x500, 0x01089200);
	/* 1,&hc_regs->hcchar,500,81189200 : 546 */
	write(base, 0x500, 0x81189200);
	/* 0,&(hc_regs)->hcintmsk,50c,00000006 : 547 */
	read(base, 0x50c, 0x00000006);
	/* 1,&(hc_regs)->hcintmsk,50c,00000006 : 548 */
	write(base, 0x50c, 0x00000006);
	poll_for_irq(base);
	/* 0,&core_if->core_global_regs->gpwrdn,58,00000000 : 549 */
	read(base, 0x58, 0x00000000);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 550 */
	read(base, 0x14, 0x06400029);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 551 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 : 552 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 : 553 */
	read(base, 0x18, 0xf3000806);
	/* 0,&core_if->core_global_regs->gahbcfg,8,00000031 : 554 */
	read(base, 0x8, 0x00000031);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 555 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 : 556 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 : 557 */
	read(base, 0x18, 0xf3000806);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 558 */
	read(base, 0x14, 0x06400029);
	/* 0,&dwc_otg_hcd->core_if->host_if->host_global_regs->hfnum,408,042002ec : 559 */
	read(base, 0x408, IGNORE);
	/* 0,&_core_if->host_if->host_global_regs->haint,414,00000001 : 560 */
	read(base, 0x414, 0x00000001);
	/* 0,&hc_regs->hcint,508,00000023 : 561 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 : 562 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hcint,508,00000023 : 563 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 : 564 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hctsiz,510,c0000000 : 565 */
	read(base, 0x510, 0xc0000000);
	/* 0,&hc_regs->hctsiz,510,c0000000 : 566 */
	read(base, 0x510, 0xc0000000);
	/* 0,&hc_regs->hcint,508,00000023 : 567 */
	read(base, 0x508, 0x00000023);
	/* 1,&hc_regs->hcintmsk,50c,00000000 : 568 */
	write(base, 0x50c, 0x00000000);
	/* 1,&hc_regs->hcint,508,ffffffff : 569 */
	write(base, 0x508, 0xffffffff);
	/* 1,&hc_regs->hcint,508,00003fff : 570 */
	write(base, 0x508, 0x00003fff);
	/* 1,&hc_regs->hcintmsk,50c,00000006 : 571 */
	write(base, 0x50c, 0x00000006);
	/* 1,&host_if->hc_regs[hc_num]->hcchar,500,01089200 : 572 */
	write(base, 0x500, 0x01089200);
	/* 1,&host_if->hc_regs[hc_num]->hcsplt,504,00000000 : 573 */
	write(base, 0x504, 0x00000000);
	/* 0,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 : 574 */
	read(base, 0x418, 0x00000001);
	/* 1,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 : 575 */
	write(base, 0x418, 0x00000001);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 576 */
	read(base, 0x18, 0xf3000806);
	/* 1,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 577 */
	write(base, 0x18, 0xf3000806);
	poll_less_than_with_max_tries(base + 0x2c, 0x00080100, 200);
	/* 0,&global_regs->gnptxsts,2c,00080100 : 578 */
	read(base, 0x2c, 0x00080100);
	/* 1,&hc_regs->hctsiz,510,40401000 : 579 */
	write(base, 0x510, 0x40401000);
	/* 1,&hc_regs->hcdma,514,db6b9000 : 584 */
	write(base, 0x514, data);
	/* 0,&hc_regs->hcchar,500,01089200 : 585 */
	read(base, 0x500, 0x01089200);
	/* 1,&hc_regs->hcchar,500,81189200 : 586 */
	write(base, 0x500, 0x81189200);
	/* 0,&(hc_regs)->hcintmsk,50c,00000006 : 587 */
	read(base, 0x50c, 0x00000006);
	/* 1,&(hc_regs)->hcintmsk,50c,00000006 : 588 */
	write(base, 0x50c, 0x00000006);
	poll_for_irq(base);
	/* 0,&core_if->core_global_regs->gpwrdn,58,00000000 : 589 */
	read(base, 0x58, 0x00000000);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 590 */
	read(base, 0x14, 0x06400029);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 591 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 : 592 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 : 593 */
	read(base, 0x18, 0xf3000806);
	/* 0,&core_if->core_global_regs->gahbcfg,8,00000031 : 594 */
	read(base, 0x8, 0x00000031);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 595 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 : 596 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 : 597 */
	read(base, 0x18, 0xf3000806);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 598 */
	read(base, 0x14, 0x06400029);
	/* 0,&dwc_otg_hcd->core_if->host_if->host_global_regs->hfnum,408,1c3802ee : 599 */
	read(base, 0x408, IGNORE);
	/* 0,&_core_if->host_if->host_global_regs->haint,414,00000001 : 600 */
	read(base, 0x414, 0x00000001);
	/* 0,&hc_regs->hcint,508,00000023 : 601 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 : 602 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hcint,508,00000023 : 603 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 : 604 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hctsiz,510,c0000000 : 605 */
	read(base, 0x510, 0xc0000000);
	/* 0,&hc_regs->hctsiz,510,c0000000 : 606 */
	read(base, 0x510, 0xc0000000);
	/* 0,&hc_regs->hcint,508,00000023 : 607 */
	read(base, 0x508, 0x00000023);
	/* 1,&hc_regs->hcintmsk,50c,00000000 : 608 */
	write(base, 0x50c, 0x00000000);
	/* 1,&hc_regs->hcint,508,ffffffff : 609 */
	write(base, 0x508, 0xffffffff);
	/* 1,&hc_regs->hcint,508,00003fff : 610 */
	write(base, 0x508, 0x00003fff);
	/* 1,&hc_regs->hcintmsk,50c,00000006 : 611 */
	write(base, 0x50c, 0x00000006);
	/* 1,&host_if->hc_regs[hc_num]->hcchar,500,01089200 : 612 */
	write(base, 0x500, 0x01089200);
	/* 1,&host_if->hc_regs[hc_num]->hcsplt,504,00000000 : 613 */
	write(base, 0x504, 0x00000000);
	/* 0,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 : 614 */
	read(base, 0x418, 0x00000001);
	/* 1,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 : 615 */
	write(base, 0x418, 0x00000001);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 616 */
	read(base, 0x18, 0xf3000806);
	/* 1,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 617 */
	write(base, 0x18, 0xf3000806);
	poll_less_than_with_max_tries(base + 0x2c, 0x00080100, 200);
	/* 0,&global_regs->gnptxsts,2c,00080100 : 618 */
	read(base, 0x2c, 0x00080100);
	/* 1,&hc_regs->hctsiz,510,40401000 : 619 */
	write(base, 0x510, 0x40401000);
	/* 1,&hc_regs->hcdma,514,db6b6000 : 624 */
	write(base, 0x514, data);
	/* 0,&hc_regs->hcchar,500,01089200 : 625 */
	read(base, 0x500, 0x01089200);
	/* 1,&hc_regs->hcchar,500,81189200 : 626 */
	write(base, 0x500, 0x81189200);
	/* 0,&(hc_regs)->hcintmsk,50c,00000006 : 627 */
	read(base, 0x50c, 0x00000006);
	/* 1,&(hc_regs)->hcintmsk,50c,00000006 : 628 */
	write(base, 0x50c, 0x00000006);
	poll_for_irq(base);
	/* 0,&core_if->core_global_regs->gpwrdn,58,00000000 : 629 */
	read(base, 0x58, 0x00000000);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 630 */
	read(base, 0x14, 0x06400029);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 631 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 : 632 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 : 633 */
	read(base, 0x18, 0xf3000806);
	/* 0,&core_if->core_global_regs->gahbcfg,8,00000031 : 634 */
	read(base, 0x8, 0x00000031);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 635 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 : 636 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 : 637 */
	read(base, 0x18, 0xf3000806);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 638 */
	read(base, 0x14, 0x06400029);
	/* 0,&dwc_otg_hcd->core_if->host_if->host_global_regs->hfnum,408,15e402ef : 639 */
	read(base, 0x408, IGNORE);
	/* 0,&_core_if->host_if->host_global_regs->haint,414,00000001 : 640 */
	read(base, 0x414, 0x00000001);
	/* 0,&hc_regs->hcint,508,00000023 : 641 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 : 642 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hcint,508,00000023 : 643 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 : 644 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hctsiz,510,c0000000 : 645 */
	read(base, 0x510, 0xc0000000);
	/* 0,&hc_regs->hctsiz,510,c0000000 : 646 */
	read(base, 0x510, 0xc0000000);
	/* 0,&hc_regs->hcint,508,00000023 : 647 */
	read(base, 0x508, 0x00000023);
	/* 1,&hc_regs->hcintmsk,50c,00000000 : 648 */
	write(base, 0x50c, 0x00000000);
	/* 1,&hc_regs->hcint,508,ffffffff : 649 */
	write(base, 0x508, 0xffffffff);
	/* 1,&hc_regs->hcint,508,00003fff : 650 */
	write(base, 0x508, 0x00003fff);
	/* 1,&hc_regs->hcintmsk,50c,00000006 : 651 */
	write(base, 0x50c, 0x00000006);
	/* 1,&host_if->hc_regs[hc_num]->hcchar,500,01089200 : 652 */
	write(base, 0x500, 0x01089200);
	/* 1,&host_if->hc_regs[hc_num]->hcsplt,504,00000000 : 653 */
	write(base, 0x504, 0x00000000);
	/* 0,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 : 654 */
	read(base, 0x418, 0x00000001);
	/* 1,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 : 655 */
	write(base, 0x418, 0x00000001);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 656 */
	read(base, 0x18, 0xf3000806);
	/* 1,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 657 */
	write(base, 0x18, 0xf3000806);
	poll_less_than_with_max_tries(base + 0x2c, 0x00080100, 200);
	/* 0,&global_regs->gnptxsts,2c,00080100 : 658 */
	read(base, 0x2c, 0x00080100);
	/* 1,&hc_regs->hctsiz,510,40401000 : 659 */
	write(base, 0x510, 0x40401000);
	/* 1,&hc_regs->hcdma,514,d7591000 : 664 */
	write(base, 0x514, data);
	/* 0,&hc_regs->hcchar,500,01089200 : 665 */
	read(base, 0x500, 0x01089200);
	/* 1,&hc_regs->hcchar,500,81189200 : 666 */
	write(base, 0x500, 0x81189200);
	/* 0,&(hc_regs)->hcintmsk,50c,00000006 : 667 */
	read(base, 0x50c, 0x00000006);
	/* 1,&(hc_regs)->hcintmsk,50c,00000006 : 668 */
	write(base, 0x50c, 0x00000006);
	poll_for_irq(base);
	/* 0,&core_if->core_global_regs->gpwrdn,58,00000000 : 669 */
	read(base, 0x58, 0x00000000);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 670 */
	read(base, 0x14, 0x06400029);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 671 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 : 672 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 : 673 */
	read(base, 0x18, 0xf3000806);
	/* 0,&core_if->core_global_regs->gahbcfg,8,00000031 : 674 */
	read(base, 0x8, 0x00000031);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 675 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 : 676 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 : 677 */
	read(base, 0x18, 0xf3000806);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 678 */
	read(base, 0x14, 0x06400029);
	/* 0,&dwc_otg_hcd->core_if->host_if->host_global_regs->hfnum,408,0f2a02f0 : 679 */
	read(base, 0x408, IGNORE);
	/* 0,&_core_if->host_if->host_global_regs->haint,414,00000001 : 680 */
	read(base, 0x414, 0x00000001);
	/* 0,&hc_regs->hcint,508,00000023 : 681 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 : 682 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hcint,508,00000023 : 683 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 : 684 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hctsiz,510,c0000000 : 685 */
	read(base, 0x510, 0xc0000000);
	/* 0,&hc_regs->hctsiz,510,c0000000 : 686 */
	read(base, 0x510, 0xc0000000);
	/* 0,&hc_regs->hcint,508,00000023 : 687 */
	read(base, 0x508, 0x00000023);
	/* 1,&hc_regs->hcintmsk,50c,00000000 : 688 */
	write(base, 0x50c, 0x00000000);
	/* 1,&hc_regs->hcint,508,ffffffff : 689 */
	write(base, 0x508, 0xffffffff);
	/* 1,&hc_regs->hcint,508,00003fff : 690 */
	write(base, 0x508, 0x00003fff);
	/* 1,&hc_regs->hcintmsk,50c,00000006 : 691 */
	write(base, 0x50c, 0x00000006);
	/* 1,&host_if->hc_regs[hc_num]->hcchar,500,01089200 : 692 */
	write(base, 0x500, 0x01089200);
	/* 1,&host_if->hc_regs[hc_num]->hcsplt,504,00000000 : 693 */
	write(base, 0x504, 0x00000000);
	/* 0,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 : 694 */
	read(base, 0x418, 0x00000001);
	/* 1,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 : 695 */
	write(base, 0x418, 0x00000001);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 696 */
	read(base, 0x18, 0xf3000806);
	/* 1,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 697 */
	write(base, 0x18, 0xf3000806);
	poll_less_than_with_max_tries(base + 0x2c, 0x00080100, 200);
	/* 0,&global_regs->gnptxsts,2c,00080100 : 698 */
	read(base, 0x2c, 0x00080100);
	/* 1,&hc_regs->hctsiz,510,40401000 : 699 */
	write(base, 0x510, 0x40401000);
	/* 1,&hc_regs->hcdma,514,d7111000 : 704 */
	write(base, 0x514, data);
	/* 0,&hc_regs->hcchar,500,01089200 : 705 */
	read(base, 0x500, 0x01089200);
	/* 1,&hc_regs->hcchar,500,81189200 : 706 */
	write(base, 0x500, 0x81189200);
	/* 0,&(hc_regs)->hcintmsk,50c,00000006 : 707 */
	read(base, 0x50c, 0x00000006);
	/* 1,&(hc_regs)->hcintmsk,50c,00000006 : 708 */
	write(base, 0x50c, 0x00000006);
	poll_for_irq(base);
	/* 0,&core_if->core_global_regs->gpwrdn,58,00000000 : 709 */
	read(base, 0x58, 0x00000000);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 710 */
	read(base, 0x14, 0x06400029);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 711 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 : 712 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 : 713 */
	read(base, 0x18, 0xf3000806);
	/* 0,&core_if->core_global_regs->gahbcfg,8,00000031 : 714 */
	read(base, 0x8, 0x00000031);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 715 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 : 716 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 : 717 */
	read(base, 0x18, 0xf3000806);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 718 */
	read(base, 0x14, 0x06400029);
	/* 0,&dwc_otg_hcd->core_if->host_if->host_global_regs->hfnum,408,083102f1 : 719 */
	read(base, 0x408, IGNORE);
	/* 0,&_core_if->host_if->host_global_regs->haint,414,00000001 : 720 */
	read(base, 0x414, 0x00000001);
	/* 0,&hc_regs->hcint,508,00000023 : 721 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 : 722 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hcint,508,00000023 : 723 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 : 724 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hctsiz,510,c0000000 : 725 */
	read(base, 0x510, 0xc0000000);
	/* 0,&hc_regs->hctsiz,510,c0000000 : 726 */
	read(base, 0x510, 0xc0000000);
	/* 0,&hc_regs->hcint,508,00000023 : 727 */
	read(base, 0x508, 0x00000023);
	/* 1,&hc_regs->hcintmsk,50c,00000000 : 728 */
	write(base, 0x50c, 0x00000000);
	/* 1,&hc_regs->hcint,508,ffffffff : 729 */
	write(base, 0x508, 0xffffffff);
	/* 1,&hc_regs->hcint,508,00003fff : 730 */
	write(base, 0x508, 0x00003fff);
	/* 1,&hc_regs->hcintmsk,50c,00000006 : 731 */
	write(base, 0x50c, 0x00000006);
	/* 1,&host_if->hc_regs[hc_num]->hcchar,500,01089200 : 732 */
	write(base, 0x500, 0x01089200);
	/* 1,&host_if->hc_regs[hc_num]->hcsplt,504,00000000 : 733 */
	write(base, 0x504, 0x00000000);
	/* 0,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 : 734 */
	read(base, 0x418, 0x00000001);
	/* 1,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 : 735 */
	write(base, 0x418, 0x00000001);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 736 */
	read(base, 0x18, 0xf3000806);
	/* 1,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 737 */
	write(base, 0x18, 0xf3000806);
	poll_less_than_with_max_tries(base + 0x2c, 0x00080100, 200);
	/* 0,&global_regs->gnptxsts,2c,00080100 : 738 */
	read(base, 0x2c, 0x00080100);
	/* 1,&hc_regs->hctsiz,510,40401000 : 739 */
	write(base, 0x510, 0x40401000);
	/* 1,&hc_regs->hcdma,514,db910000 : 744 */
	write(base, 0x514, data);
	/* 0,&hc_regs->hcchar,500,01089200 : 745 */
	read(base, 0x500, 0x01089200);
	/* 1,&hc_regs->hcchar,500,81189200 : 746 */
	write(base, 0x500, 0x81189200);
	/* 0,&(hc_regs)->hcintmsk,50c,00000006 : 747 */
	read(base, 0x50c, 0x00000006);
	/* 1,&(hc_regs)->hcintmsk,50c,00000006 : 748 */
	write(base, 0x50c, 0x00000006);
	poll_for_irq(base);
	/* 0,&core_if->core_global_regs->gpwrdn,58,00000000 : 749 */
	read(base, 0x58, 0x00000000);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 750 */
	read(base, 0x14, 0x06400029);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 751 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 : 752 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 : 753 */
	read(base, 0x18, 0xf3000806);
	/* 0,&core_if->core_global_regs->gahbcfg,8,00000031 : 754 */
	read(base, 0x8, 0x00000031);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 755 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 : 756 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 : 757 */
	read(base, 0x18, 0xf3000806);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 758 */
	read(base, 0x14, 0x06400029);
	/* 0,&dwc_otg_hcd->core_if->host_if->host_global_regs->hfnum,408,02ac02f2 : 759 */
	read(base, 0x408, IGNORE);
	/* 0,&_core_if->host_if->host_global_regs->haint,414,00000001 : 760 */
	read(base, 0x414, 0x00000001);
	/* 0,&hc_regs->hcint,508,00000023 : 761 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 : 762 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hcint,508,00000023 : 763 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 : 764 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hctsiz,510,c0000000 : 765 */
	read(base, 0x510, 0xc0000000);
	/* 0,&hc_regs->hctsiz,510,c0000000 : 766 */
	read(base, 0x510, 0xc0000000);
	/* 0,&hc_regs->hcint,508,00000023 : 767 */
	read(base, 0x508, 0x00000023);
	/* 1,&hc_regs->hcintmsk,50c,00000000 : 768 */
	write(base, 0x50c, 0x00000000);
	/* 1,&hc_regs->hcint,508,ffffffff : 769 */
	write(base, 0x508, 0xffffffff);
	/* 1,&hc_regs->hcint,508,00003fff : 770 */
	write(base, 0x508, 0x00003fff);
	/* 1,&hc_regs->hcintmsk,50c,00000006 : 771 */
	write(base, 0x50c, 0x00000006);
	/* 1,&host_if->hc_regs[hc_num]->hcchar,500,01089200 : 772 */
	write(base, 0x500, 0x01089200);
	/* 1,&host_if->hc_regs[hc_num]->hcsplt,504,00000000 : 773 */
	write(base, 0x504, 0x00000000);
	/* 0,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 : 774 */
	read(base, 0x418, 0x00000001);
	/* 1,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 : 775 */
	write(base, 0x418, 0x00000001);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 776 */
	read(base, 0x18, 0xf3000806);
	/* 1,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 777 */
	write(base, 0x18, 0xf3000806);
	poll_less_than_with_max_tries(base + 0x2c, 0x00080100, 200);
	/* 0,&global_regs->gnptxsts,2c,00080100 : 778 */
	read(base, 0x2c, 0x00080100);
	/* 1,&hc_regs->hctsiz,510,40401000 : 779 */
	write(base, 0x510, 0x40401000);
	/* 1,&hc_regs->hcdma,514,d710a000 : 784 */
	write(base, 0x514, data);
	/* 0,&hc_regs->hcchar,500,01089200 : 785 */
	read(base, 0x500, 0x01089200);
	/* 1,&hc_regs->hcchar,500,81189200 : 786 */
	write(base, 0x500, 0x81189200);
	/* 0,&(hc_regs)->hcintmsk,50c,00000006 : 787 */
	read(base, 0x50c, 0x00000006);
	/* 1,&(hc_regs)->hcintmsk,50c,00000006 : 788 */
	write(base, 0x50c, 0x00000006);
	poll_for_irq(base);
	/* 0,&core_if->core_global_regs->gpwrdn,58,00000000 : 789 */
	read(base, 0x58, 0x00000000);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 790 */
	read(base, 0x14, 0x06400029);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 791 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 : 792 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 : 793 */
	read(base, 0x18, 0xf3000806);
	/* 0,&core_if->core_global_regs->gahbcfg,8,00000031 : 794 */
	read(base, 0x8, 0x00000031);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 795 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 : 796 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 : 797 */
	read(base, 0x18, 0xf3000806);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 798 */
	read(base, 0x14, 0x06400029);
	/* 0,&dwc_otg_hcd->core_if->host_if->host_global_regs->hfnum,408,1b9002f4 : 799 */
	read(base, 0x408, IGNORE);
	/* 0,&_core_if->host_if->host_global_regs->haint,414,00000001 : 800 */
	read(base, 0x414, 0x00000001);
	/* 0,&hc_regs->hcint,508,00000023 : 801 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 : 802 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hcint,508,00000023 : 803 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 : 804 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hctsiz,510,c0000000 : 805 */
	read(base, 0x510, 0xc0000000);
	/* 0,&hc_regs->hctsiz,510,c0000000 : 806 */
	read(base, 0x510, 0xc0000000);
	/* 0,&hc_regs->hcint,508,00000023 : 807 */
	read(base, 0x508, 0x00000023);
	/* 1,&hc_regs->hcintmsk,50c,00000000 : 808 */
	write(base, 0x50c, 0x00000000);
	/* 1,&hc_regs->hcint,508,ffffffff : 809 */
	write(base, 0x508, 0xffffffff);
	/* 1,&hc_regs->hcint,508,00003fff : 810 */
	write(base, 0x508, 0x00003fff);
	/* 1,&hc_regs->hcintmsk,50c,00000006 : 811 */
	write(base, 0x50c, 0x00000006);
	/* 1,&host_if->hc_regs[hc_num]->hcchar,500,01089200 : 812 */
	write(base, 0x500, 0x01089200);
	/* 1,&host_if->hc_regs[hc_num]->hcsplt,504,00000000 : 813 */
	write(base, 0x504, 0x00000000);
	/* 0,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 : 814 */
	read(base, 0x418, 0x00000001);
	/* 1,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 : 815 */
	write(base, 0x418, 0x00000001);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 816 */
	read(base, 0x18, 0xf3000806);
	/* 1,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 817 */
	write(base, 0x18, 0xf3000806);
	poll_less_than_with_max_tries(base + 0x2c, 0x00080100, 200);
	/* 0,&global_regs->gnptxsts,2c,00080100 : 818 */
	read(base, 0x2c, 0x00080100);
	/* 1,&hc_regs->hctsiz,510,40401000 : 819 */
	write(base, 0x510, 0x40401000);
	/* 1,&hc_regs->hcdma,514,d9b56000 : 824 */
	write(base, 0x514, data);
	/* 0,&hc_regs->hcchar,500,01089200 : 825 */
	read(base, 0x500, 0x01089200);
	/* 1,&hc_regs->hcchar,500,81189200 : 826 */
	write(base, 0x500, 0x81189200);
	/* 0,&(hc_regs)->hcintmsk,50c,00000006 : 827 */
	read(base, 0x50c, 0x00000006);
	/* 1,&(hc_regs)->hcintmsk,50c,00000006 : 828 */
	write(base, 0x50c, 0x00000006);
	poll_for_irq(base);
	/* 0,&core_if->core_global_regs->gpwrdn,58,00000000 : 829 */
	read(base, 0x58, 0x00000000);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 830 */
	read(base, 0x14, 0x06400029);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 831 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 : 832 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 : 833 */
	read(base, 0x18, 0xf3000806);
	/* 0,&core_if->core_global_regs->gahbcfg,8,00000031 : 834 */
	read(base, 0x8, 0x00000031);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 835 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 : 836 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 : 837 */
	read(base, 0x18, 0xf3000806);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 838 */
	read(base, 0x14, 0x06400029);
	/* 0,&dwc_otg_hcd->core_if->host_if->host_global_regs->hfnum,408,13da02f5 : 839 */
	read(base, 0x408, IGNORE);
	/* 0,&_core_if->host_if->host_global_regs->haint,414,00000001 : 840 */
	read(base, 0x414, 0x00000001);
	/* 0,&hc_regs->hcint,508,00000023 : 841 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 : 842 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hcint,508,00000023 : 843 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 : 844 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hctsiz,510,c0000000 : 845 */
	read(base, 0x510, 0xc0000000);
	/* 0,&hc_regs->hctsiz,510,c0000000 : 846 */
	read(base, 0x510, 0xc0000000);
	/* 0,&hc_regs->hcint,508,00000023 : 847 */
	read(base, 0x508, 0x00000023);
	/* 1,&hc_regs->hcintmsk,50c,00000000 : 848 */
	write(base, 0x50c, 0x00000000);
	/* 1,&hc_regs->hcint,508,ffffffff : 849 */
	write(base, 0x508, 0xffffffff);
	/* 1,&hc_regs->hcint,508,00003fff : 850 */
	write(base, 0x508, 0x00003fff);
	/* 1,&hc_regs->hcintmsk,50c,00000006 : 851 */
	write(base, 0x50c, 0x00000006);
	/* 1,&host_if->hc_regs[hc_num]->hcchar,500,01089200 : 852 */
	write(base, 0x500, 0x01089200);
	/* 1,&host_if->hc_regs[hc_num]->hcsplt,504,00000000 : 853 */
	write(base, 0x504, 0x00000000);
	/* 0,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 : 854 */
	read(base, 0x418, 0x00000001);
	/* 1,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 : 855 */
	write(base, 0x418, 0x00000001);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 856 */
	read(base, 0x18, 0xf3000806);
	/* 1,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 857 */
	write(base, 0x18, 0xf3000806);
	poll_less_than_with_max_tries(base + 0x2c, 0x00080100, 200);
	/* 0,&global_regs->gnptxsts,2c,00080100 : 858 */
	read(base, 0x2c, 0x00080100);
	/* 1,&hc_regs->hctsiz,510,40401000 : 859 */
	write(base, 0x510, 0x40401000);
	/* 1,&hc_regs->hcdma,514,db001000 : 864 */
	write(base, 0x514, data);
	/* 0,&hc_regs->hcchar,500,01089200 : 865 */
	read(base, 0x500, 0x01089200);
	/* 1,&hc_regs->hcchar,500,81189200 : 866 */
	write(base, 0x500, 0x81189200);
	/* 0,&(hc_regs)->hcintmsk,50c,00000006 : 867 */
	read(base, 0x50c, 0x00000006);
	/* 1,&(hc_regs)->hcintmsk,50c,00000006 : 868 */
	write(base, 0x50c, 0x00000006);
	poll_for_irq(base);
	/* 0,&core_if->core_global_regs->gpwrdn,58,00000000 : 869 */
	read(base, 0x58, 0x00000000);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 870 */
	read(base, 0x14, 0x06400029);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 871 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 : 872 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 : 873 */
	read(base, 0x18, 0xf3000806);
	/* 0,&core_if->core_global_regs->gahbcfg,8,00000031 : 874 */
	read(base, 0x8, 0x00000031);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 875 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 : 876 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 : 877 */
	read(base, 0x18, 0xf3000806);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 878 */
	read(base, 0x14, 0x06400029);
	/* 0,&dwc_otg_hcd->core_if->host_if->host_global_regs->hfnum,408,0cdb02f6 : 879 */
	read(base, 0x408, IGNORE);
	/* 0,&_core_if->host_if->host_global_regs->haint,414,00000001 : 880 */
	read(base, 0x414, 0x00000001);
	/* 0,&hc_regs->hcint,508,00000023 : 881 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 : 882 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hcint,508,00000023 : 883 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 : 884 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hctsiz,510,c0000000 : 885 */
	read(base, 0x510, 0xc0000000);
	/* 0,&hc_regs->hctsiz,510,c0000000 : 886 */
	read(base, 0x510, 0xc0000000);
	/* 0,&hc_regs->hcint,508,00000023 : 887 */
	read(base, 0x508, 0x00000023);
	/* 1,&hc_regs->hcintmsk,50c,00000000 : 888 */
	write(base, 0x50c, 0x00000000);
	/* 1,&hc_regs->hcint,508,ffffffff : 889 */
	write(base, 0x508, 0xffffffff);
	/* 1,&hc_regs->hcint,508,00003fff : 890 */
	write(base, 0x508, 0x00003fff);
	/* 1,&hc_regs->hcintmsk,50c,00000006 : 891 */
	write(base, 0x50c, 0x00000006);
	/* 1,&host_if->hc_regs[hc_num]->hcchar,500,01089200 : 892 */
	write(base, 0x500, 0x01089200);
	/* 1,&host_if->hc_regs[hc_num]->hcsplt,504,00000000 : 893 */
	write(base, 0x504, 0x00000000);
	/* 0,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 : 894 */
	read(base, 0x418, 0x00000001);
	/* 1,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 : 895 */
	write(base, 0x418, 0x00000001);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 896 */
	read(base, 0x18, 0xf3000806);
	/* 1,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 897 */
	write(base, 0x18, 0xf3000806);
	poll_less_than_with_max_tries(base + 0x2c, 0x00080100, 200);
	/* 0,&global_regs->gnptxsts,2c,00080100 : 898 */
	read(base, 0x2c, 0x00080100);
	/* 1,&hc_regs->hctsiz,510,40401000 : 899 */
	write(base, 0x510, 0x40401000);
	/* 1,&hc_regs->hcdma,514,d90fb000 : 904 */
	write(base, 0x514, data);
	/* 0,&hc_regs->hcchar,500,01089200 : 905 */
	read(base, 0x500, 0x01089200);
	/* 1,&hc_regs->hcchar,500,81189200 : 906 */
	write(base, 0x500, 0x81189200);
	/* 0,&(hc_regs)->hcintmsk,50c,00000006 : 907 */
	read(base, 0x50c, 0x00000006);
	/* 1,&(hc_regs)->hcintmsk,50c,00000006 : 908 */
	write(base, 0x50c, 0x00000006);
	poll_for_irq(base);
	/* 0,&core_if->core_global_regs->gpwrdn,58,00000000 : 909 */
	read(base, 0x58, 0x00000000);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 910 */
	read(base, 0x14, 0x06400029);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 911 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 : 912 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 : 913 */
	read(base, 0x18, 0xf3000806);
	/* 0,&core_if->core_global_regs->gahbcfg,8,00000031 : 914 */
	read(base, 0x8, 0x00000031);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 915 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 : 916 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 : 917 */
	read(base, 0x18, 0xf3000806);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 918 */
	read(base, 0x14, 0x06400029);
	/* 0,&dwc_otg_hcd->core_if->host_if->host_global_regs->hfnum,408,055e02f7 : 919 */
	read(base, 0x408, IGNORE);
	/* 0,&_core_if->host_if->host_global_regs->haint,414,00000001 : 920 */
	read(base, 0x414, 0x00000001);
	/* 0,&hc_regs->hcint,508,00000023 : 921 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 : 922 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hcint,508,00000023 : 923 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 : 924 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hctsiz,510,c0000000 : 925 */
	read(base, 0x510, 0xc0000000);
	/* 0,&hc_regs->hctsiz,510,c0000000 : 926 */
	read(base, 0x510, 0xc0000000);
	/* 0,&hc_regs->hcint,508,00000023 : 927 */
	read(base, 0x508, 0x00000023);
	/* 1,&hc_regs->hcintmsk,50c,00000000 : 928 */
	write(base, 0x50c, 0x00000000);
	/* 1,&hc_regs->hcint,508,ffffffff : 929 */
	write(base, 0x508, 0xffffffff);
	/* 1,&hc_regs->hcint,508,00003fff : 930 */
	write(base, 0x508, 0x00003fff);
	/* 1,&hc_regs->hcintmsk,50c,00000006 : 931 */
	write(base, 0x50c, 0x00000006);
	/* 1,&host_if->hc_regs[hc_num]->hcchar,500,01089200 : 932 */
	write(base, 0x500, 0x01089200);
	/* 1,&host_if->hc_regs[hc_num]->hcsplt,504,00000000 : 933 */
	write(base, 0x504, 0x00000000);
	/* 0,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 : 934 */
	read(base, 0x418, 0x00000001);
	/* 1,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 : 935 */
	write(base, 0x418, 0x00000001);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 936 */
	read(base, 0x18, 0xf3000806);
	/* 1,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 937 */
	write(base, 0x18, 0xf3000806);
	poll_less_than_with_max_tries(base + 0x2c, 0x00080100, 200);
	/* 0,&global_regs->gnptxsts,2c,00080100 : 938 */
	read(base, 0x2c, 0x00080100);
	/* 1,&hc_regs->hctsiz,510,40401000 : 939 */
	write(base, 0x510, 0x40401000);
	/* 1,&hc_regs->hcdma,514,d8c8e000 : 944 */
	write(base, 0x514, data);
	/* 0,&hc_regs->hcchar,500,01089200 : 945 */
	read(base, 0x500, 0x01089200);
	/* 1,&hc_regs->hcchar,500,81189200 : 946 */
	write(base, 0x500, 0x81189200);
	/* 0,&(hc_regs)->hcintmsk,50c,00000006 : 947 */
	read(base, 0x50c, 0x00000006);
	/* 1,&(hc_regs)->hcintmsk,50c,00000006 : 948 */
	write(base, 0x50c, 0x00000006);
	poll_for_irq(base);
	/* 0,&core_if->core_global_regs->gpwrdn,58,00000000 : 949 */
	read(base, 0x58, 0x00000000);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 950 */
	read(base, 0x14, 0x06400029);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 951 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 : 952 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 : 953 */
	read(base, 0x18, 0xf3000806);
	/* 0,&core_if->core_global_regs->gahbcfg,8,00000031 : 954 */
	read(base, 0x8, 0x00000031);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 955 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 : 956 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 : 957 */
	read(base, 0x18, 0xf3000806);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 958 */
	read(base, 0x14, 0x06400029);
	/* 0,&dwc_otg_hcd->core_if->host_if->host_global_regs->hfnum,408,007e02f8 : 959 */
	read(base, 0x408, IGNORE);
	/* 0,&_core_if->host_if->host_global_regs->haint,414,00000001 : 960 */
	read(base, 0x414, 0x00000001);
	/* 0,&hc_regs->hcint,508,00000023 : 961 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 : 962 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hcint,508,00000023 : 963 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 : 964 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hctsiz,510,c0000000 : 965 */
	read(base, 0x510, 0xc0000000);
	/* 0,&hc_regs->hctsiz,510,c0000000 : 966 */
	read(base, 0x510, 0xc0000000);
	/* 0,&hc_regs->hcint,508,00000023 : 967 */
	read(base, 0x508, 0x00000023);
	/* 1,&hc_regs->hcintmsk,50c,00000000 : 968 */
	write(base, 0x50c, 0x00000000);
	/* 1,&hc_regs->hcint,508,ffffffff : 969 */
	write(base, 0x508, 0xffffffff);
	/* 1,&hc_regs->hcint,508,00003fff : 970 */
	write(base, 0x508, 0x00003fff);
	/* 1,&hc_regs->hcintmsk,50c,00000006 : 971 */
	write(base, 0x50c, 0x00000006);
	/* 1,&host_if->hc_regs[hc_num]->hcchar,500,01089200 : 972 */
	write(base, 0x500, 0x01089200);
	/* 1,&host_if->hc_regs[hc_num]->hcsplt,504,00000000 : 973 */
	write(base, 0x504, 0x00000000);
	/* 0,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 : 974 */
	read(base, 0x418, 0x00000001);
	/* 1,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 : 975 */
	write(base, 0x418, 0x00000001);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 976 */
	read(base, 0x18, 0xf3000806);
	/* 1,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 977 */
	write(base, 0x18, 0xf3000806);
	poll_less_than_with_max_tries(base + 0x2c, 0x00080100, 200);
	/* 0,&global_regs->gnptxsts,2c,00080100 : 978 */
	read(base, 0x2c, 0x00080100);
	/* 1,&hc_regs->hctsiz,510,40401000 : 979 */
	write(base, 0x510, 0x40401000);
	/* 1,&hc_regs->hcdma,514,df5e3000 : 984 */
	write(base, 0x514, data);
	/* 0,&hc_regs->hcchar,500,01089200 : 985 */
	read(base, 0x500, 0x01089200);
	/* 1,&hc_regs->hcchar,500,81189200 : 986 */
	write(base, 0x500, 0x81189200);
	/* 0,&(hc_regs)->hcintmsk,50c,00000006 : 987 */
	read(base, 0x50c, 0x00000006);
	/* 1,&(hc_regs)->hcintmsk,50c,00000006 : 988 */
	write(base, 0x50c, 0x00000006);
	poll_for_irq(base);
	/* 0,&core_if->core_global_regs->gpwrdn,58,00000000 : 989 */
	read(base, 0x58, 0x00000000);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 990 */
	read(base, 0x14, 0x06400029);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 991 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 : 992 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 : 993 */
	read(base, 0x18, 0xf3000806);
	/* 0,&core_if->core_global_regs->gahbcfg,8,00000031 : 994 */
	read(base, 0x8, 0x00000031);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 995 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 : 996 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 : 997 */
	read(base, 0x18, 0xf3000806);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 998 */
	read(base, 0x14, 0x06400029);
	/* 0,&dwc_otg_hcd->core_if->host_if->host_global_regs->hfnum,408,164402fa : 999 */
	read(base, 0x408, IGNORE);
	/* 0,&_core_if->host_if->host_global_regs->haint,414,00000001 : 1000 */
	read(base, 0x414, 0x00000001);
	/* 0,&hc_regs->hcint,508,00000023 : 1001 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 : 1002 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hcint,508,00000023 : 1003 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 : 1004 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hctsiz,510,c0000000 : 1005 */
	read(base, 0x510, 0xc0000000);
	/* 0,&hc_regs->hctsiz,510,c0000000 : 1006 */
	read(base, 0x510, 0xc0000000);
	/* 0,&hc_regs->hcint,508,00000023 : 1007 */
	read(base, 0x508, 0x00000023);
	/* 1,&hc_regs->hcintmsk,50c,00000000 : 1008 */
	write(base, 0x50c, 0x00000000);
	/* 1,&hc_regs->hcint,508,ffffffff : 1009 */
	write(base, 0x508, 0xffffffff);
	/* 1,&hc_regs->hcint,508,00003fff : 1010 */
	write(base, 0x508, 0x00003fff);
	/* 1,&hc_regs->hcintmsk,50c,00000006 : 1011 */
	write(base, 0x50c, 0x00000006);
	/* 1,&host_if->hc_regs[hc_num]->hcchar,500,01089200 : 1012 */
	write(base, 0x500, 0x01089200);
	/* 1,&host_if->hc_regs[hc_num]->hcsplt,504,00000000 : 1013 */
	write(base, 0x504, 0x00000000);
	/* 0,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 : 1014 */
	read(base, 0x418, 0x00000001);
	/* 1,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 : 1015 */
	write(base, 0x418, 0x00000001);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 1016 */
	read(base, 0x18, 0xf3000806);
	/* 1,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 1017 */
	write(base, 0x18, 0xf3000806);
	poll_less_than_with_max_tries(base + 0x2c, 0x00080100, 200);
	/* 0,&global_regs->gnptxsts,2c,00080100 : 1018 */
	read(base, 0x2c, 0x00080100);
	/* 1,&hc_regs->hctsiz,510,40401000 : 1019 */
	write(base, 0x510, 0x40401000);
	/* 1,&hc_regs->hcdma,514,d717a000 : 1024 */
	write(base, 0x514, data);
	/* 0,&hc_regs->hcchar,500,01089200 : 1025 */
	read(base, 0x500, 0x01089200);
	/* 1,&hc_regs->hcchar,500,81189200 : 1026 */
	write(base, 0x500, 0x81189200);
	/* 0,&(hc_regs)->hcintmsk,50c,00000006 : 1027 */
	read(base, 0x50c, 0x00000006);
	/* 1,&(hc_regs)->hcintmsk,50c,00000006 : 1028 */
	write(base, 0x50c, 0x00000006);
	poll_for_irq(base);
	/* 0,&core_if->core_global_regs->gpwrdn,58,00000000 : 1029 */
	read(base, 0x58, 0x00000000);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 1030 */
	read(base, 0x14, 0x06400029);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 1031 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 : 1032 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 : 1033 */
	read(base, 0x18, 0xf3000806);
	/* 0,&core_if->core_global_regs->gahbcfg,8,00000031 : 1034 */
	read(base, 0x8, 0x00000031);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 1035 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 : 1036 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 : 1037 */
	read(base, 0x18, 0xf3000806);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 1038 */
	read(base, 0x14, 0x06400029);
	/* 0,&dwc_otg_hcd->core_if->host_if->host_global_regs->hfnum,408,0f0002fb : 1039 */
	read(base, 0x408, IGNORE);
	/* 0,&_core_if->host_if->host_global_regs->haint,414,00000001 : 1040 */
	read(base, 0x414, 0x00000001);
	/* 0,&hc_regs->hcint,508,00000023 : 1041 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 : 1042 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hcint,508,00000023 : 1043 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 : 1044 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hctsiz,510,c0000000 : 1045 */
	read(base, 0x510, 0xc0000000);
	/* 0,&hc_regs->hctsiz,510,c0000000 : 1046 */
	read(base, 0x510, 0xc0000000);
	/* 0,&hc_regs->hcint,508,00000023 : 1047 */
	read(base, 0x508, 0x00000023);
	/* 1,&hc_regs->hcintmsk,50c,00000000 : 1048 */
	write(base, 0x50c, 0x00000000);
	/* 1,&hc_regs->hcint,508,ffffffff : 1049 */
	write(base, 0x508, 0xffffffff);
	/* 1,&hc_regs->hcint,508,00003fff : 1050 */
	write(base, 0x508, 0x00003fff);
	/* 1,&hc_regs->hcintmsk,50c,00000006 : 1051 */
	write(base, 0x50c, 0x00000006);
	/* 1,&host_if->hc_regs[hc_num]->hcchar,500,01089200 : 1052 */
	write(base, 0x500, 0x01089200);
	/* 1,&host_if->hc_regs[hc_num]->hcsplt,504,00000000 : 1053 */
	write(base, 0x504, 0x00000000);
	/* 0,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 : 1054 */
	read(base, 0x418, 0x00000001);
	/* 1,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 : 1055 */
	write(base, 0x418, 0x00000001);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 1056 */
	read(base, 0x18, 0xf3000806);
	/* 1,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 1057 */
	write(base, 0x18, 0xf3000806);
	poll_less_than_with_max_tries(base + 0x2c, 0x00080100, 200);
	/* 0,&global_regs->gnptxsts,2c,00080100 : 1058 */
	read(base, 0x2c, 0x00080100);
	/* 1,&hc_regs->hctsiz,510,40401000 : 1059 */
	write(base, 0x510, 0x40401000);
	/* 1,&hc_regs->hcdma,514,db902000 : 1064 */
	write(base, 0x514, data);
	/* 0,&hc_regs->hcchar,500,01089200 : 1065 */
	read(base, 0x500, 0x01089200);
	/* 1,&hc_regs->hcchar,500,81189200 : 1066 */
	write(base, 0x500, 0x81189200);
	/* 0,&(hc_regs)->hcintmsk,50c,00000006 : 1067 */
	read(base, 0x50c, 0x00000006);
	/* 1,&(hc_regs)->hcintmsk,50c,00000006 : 1068 */
	write(base, 0x50c, 0x00000006);
	poll_for_irq(base);
	/* 0,&core_if->core_global_regs->gpwrdn,58,00000000 : 1069 */
	read(base, 0x58, 0x00000000);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 1070 */
	read(base, 0x14, 0x06400029);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 1071 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 : 1072 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 : 1073 */
	read(base, 0x18, 0xf3000806);
	/* 0,&core_if->core_global_regs->gahbcfg,8,00000031 : 1074 */
	read(base, 0x8, 0x00000031);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 1075 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 : 1076 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 : 1077 */
	read(base, 0x18, 0xf3000806);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 1078 */
	read(base, 0x14, 0x06400029);
	/* 0,&dwc_otg_hcd->core_if->host_if->host_global_regs->hfnum,408,07bc02fc : 1079 */
	read(base, 0x408, IGNORE);
	/* 0,&_core_if->host_if->host_global_regs->haint,414,00000001 : 1080 */
	read(base, 0x414, 0x00000001);
	/* 0,&hc_regs->hcint,508,00000023 : 1081 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 : 1082 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hcint,508,00000023 : 1083 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 : 1084 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hctsiz,510,c0000000 : 1085 */
	read(base, 0x510, 0xc0000000);
	/* 0,&hc_regs->hctsiz,510,c0000000 : 1086 */
	read(base, 0x510, 0xc0000000);
	/* 0,&hc_regs->hcint,508,00000023 : 1087 */
	read(base, 0x508, 0x00000023);
	/* 1,&hc_regs->hcintmsk,50c,00000000 : 1088 */
	write(base, 0x50c, 0x00000000);
	/* 1,&hc_regs->hcint,508,ffffffff : 1089 */
	write(base, 0x508, 0xffffffff);
	/* 1,&hc_regs->hcint,508,00003fff : 1090 */
	write(base, 0x508, 0x00003fff);
	/* 1,&hc_regs->hcintmsk,50c,00000006 : 1091 */
	write(base, 0x50c, 0x00000006);
	/* 1,&host_if->hc_regs[hc_num]->hcchar,500,01089200 : 1092 */
	write(base, 0x500, 0x01089200);
	/* 1,&host_if->hc_regs[hc_num]->hcsplt,504,00000000 : 1093 */
	write(base, 0x504, 0x00000000);
	/* 0,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 : 1094 */
	read(base, 0x418, 0x00000001);
	/* 1,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 : 1095 */
	write(base, 0x418, 0x00000001);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 1096 */
	read(base, 0x18, 0xf3000806);
	/* 1,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 1097 */
	write(base, 0x18, 0xf3000806);
	poll_less_than_with_max_tries(base + 0x2c, 0x00080100, 200);
	/* 0,&global_regs->gnptxsts,2c,00080100 : 1098 */
	read(base, 0x2c, 0x00080100);
	/* 1,&hc_regs->hctsiz,510,40401000 : 1099 */
	write(base, 0x510, 0x40401000);
	/* 1,&hc_regs->hcdma,514,db901000 : 1104 */
	write(base, 0x514, data);
	/* 0,&hc_regs->hcchar,500,01089200 : 1105 */
	read(base, 0x500, 0x01089200);
	/* 1,&hc_regs->hcchar,500,81189200 : 1106 */
	write(base, 0x500, 0x81189200);
	/* 0,&(hc_regs)->hcintmsk,50c,00000006 : 1107 */
	read(base, 0x50c, 0x00000006);
	/* 1,&(hc_regs)->hcintmsk,50c,00000006 : 1108 */
	write(base, 0x50c, 0x00000006);
	poll_for_irq(base);
	/* 0,&core_if->core_global_regs->gpwrdn,58,00000000 : 1109 */
	read(base, 0x58, 0x00000000);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 1110 */
	read(base, 0x14, 0x06400029);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 1111 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 : 1112 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 : 1113 */
	read(base, 0x18, 0xf3000806);
	/* 0,&core_if->core_global_regs->gahbcfg,8,00000031 : 1114 */
	read(base, 0x8, 0x00000031);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 1115 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 : 1116 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 : 1117 */
	read(base, 0x18, 0xf3000806);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 1118 */
	read(base, 0x14, 0x06400029);
	/* 0,&dwc_otg_hcd->core_if->host_if->host_global_regs->hfnum,408,034e02fd : 1119 */
	read(base, 0x408, IGNORE);
	/* 0,&_core_if->host_if->host_global_regs->haint,414,00000001 : 1120 */
	read(base, 0x414, 0x00000001);
	/* 0,&hc_regs->hcint,508,00000023 : 1121 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 : 1122 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hcint,508,00000023 : 1123 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 : 1124 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hctsiz,510,c0000000 : 1125 */
	read(base, 0x510, 0xc0000000);
	/* 0,&hc_regs->hctsiz,510,c0000000 : 1126 */
	read(base, 0x510, 0xc0000000);
	/* 0,&hc_regs->hcint,508,00000023 : 1127 */
	read(base, 0x508, 0x00000023);
	/* 1,&hc_regs->hcintmsk,50c,00000000 : 1128 */
	write(base, 0x50c, 0x00000000);
	/* 1,&hc_regs->hcint,508,ffffffff : 1129 */
	write(base, 0x508, 0xffffffff);
	/* 1,&hc_regs->hcint,508,00003fff : 1130 */
	write(base, 0x508, 0x00003fff);
	/* 1,&hc_regs->hcintmsk,50c,00000006 : 1131 */
	write(base, 0x50c, 0x00000006);
	/* 1,&host_if->hc_regs[hc_num]->hcchar,500,01089200 : 1132 */
	write(base, 0x500, 0x01089200);
	/* 1,&host_if->hc_regs[hc_num]->hcsplt,504,00000000 : 1133 */
	write(base, 0x504, 0x00000000);
	/* 0,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 : 1134 */
	read(base, 0x418, 0x00000001);
	/* 1,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 : 1135 */
	write(base, 0x418, 0x00000001);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 1136 */
	read(base, 0x18, 0xf3000806);
	/* 1,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 1137 */
	write(base, 0x18, 0xf3000806);
	poll_less_than_with_max_tries(base + 0x2c, 0x00080100, 200);
	/* 0,&global_regs->gnptxsts,2c,00080100 : 1138 */
	read(base, 0x2c, 0x00080100);
	/* 1,&hc_regs->hctsiz,510,40401000 : 1139 */
	write(base, 0x510, 0x40401000);
	/* 1,&hc_regs->hcdma,514,d9b6e000 : 1144 */
	write(base, 0x514, data);
	/* 0,&hc_regs->hcchar,500,01089200 : 1145 */
	read(base, 0x500, 0x01089200);
	/* 1,&hc_regs->hcchar,500,81189200 : 1146 */
	write(base, 0x500, 0x81189200);
	/* 0,&(hc_regs)->hcintmsk,50c,00000006 : 1147 */
	read(base, 0x50c, 0x00000006);
	/* 1,&(hc_regs)->hcintmsk,50c,00000006 : 1148 */
	write(base, 0x50c, 0x00000006);
	poll_for_irq(base);
	/* 0,&core_if->core_global_regs->gpwrdn,58,00000000 : 1149 */
	read(base, 0x58, 0x00000000);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 1150 */
	read(base, 0x14, 0x06400029);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 1151 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 : 1152 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 : 1153 */
	read(base, 0x18, 0xf3000806);
	/* 0,&core_if->core_global_regs->gahbcfg,8,00000031 : 1154 */
	read(base, 0x8, 0x00000031);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 1155 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 : 1156 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 : 1157 */
	read(base, 0x18, 0xf3000806);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 1158 */
	read(base, 0x14, 0x06400029);
	/* 0,&dwc_otg_hcd->core_if->host_if->host_global_regs->hfnum,408,1b0302ff : 1159 */
	read(base, 0x408, IGNORE);
	/* 0,&_core_if->host_if->host_global_regs->haint,414,00000001 : 1160 */
	read(base, 0x414, 0x00000001);
	/* 0,&hc_regs->hcint,508,00000023 : 1161 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 : 1162 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hcint,508,00000023 : 1163 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 : 1164 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hctsiz,510,c0000000 : 1165 */
	read(base, 0x510, 0xc0000000);
	/* 0,&hc_regs->hctsiz,510,c0000000 : 1166 */
	read(base, 0x510, 0xc0000000);
	/* 0,&hc_regs->hcint,508,00000023 : 1167 */
	read(base, 0x508, 0x00000023);
	/* 1,&hc_regs->hcintmsk,50c,00000000 : 1168 */
	write(base, 0x50c, 0x00000000);
	/* 1,&hc_regs->hcint,508,ffffffff : 1169 */
	write(base, 0x508, 0xffffffff);
	/* 1,&hc_regs->hcint,508,00003fff : 1170 */
	write(base, 0x508, 0x00003fff);
	/* 1,&hc_regs->hcintmsk,50c,00000006 : 1171 */
	write(base, 0x50c, 0x00000006);
	/* 1,&host_if->hc_regs[hc_num]->hcchar,500,01089200 : 1172 */
	write(base, 0x500, 0x01089200);
	/* 1,&host_if->hc_regs[hc_num]->hcsplt,504,00000000 : 1173 */
	write(base, 0x504, 0x00000000);
	/* 0,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 : 1174 */
	read(base, 0x418, 0x00000001);
	/* 1,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 : 1175 */
	write(base, 0x418, 0x00000001);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 1176 */
	read(base, 0x18, 0xf3000806);
	/* 1,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 1177 */
	write(base, 0x18, 0xf3000806);
	poll_less_than_with_max_tries(base + 0x2c, 0x00080100, 200);
	/* 0,&global_regs->gnptxsts,2c,00080100 : 1178 */
	read(base, 0x2c, 0x00080100);
	/* 1,&hc_regs->hctsiz,510,40401000 : 1179 */
	write(base, 0x510, 0x40401000);
	/* 1,&hc_regs->hcdma,514,dabb8000 : 1184 */
	write(base, 0x514, data);
	/* 0,&hc_regs->hcchar,500,01089200 : 1185 */
	read(base, 0x500, 0x01089200);
	/* 1,&hc_regs->hcchar,500,81189200 : 1186 */
	write(base, 0x500, 0x81189200);
	/* 0,&(hc_regs)->hcintmsk,50c,00000006 : 1187 */
	read(base, 0x50c, 0x00000006);
	/* 1,&(hc_regs)->hcintmsk,50c,00000006 : 1188 */
	write(base, 0x50c, 0x00000006);
	poll_for_irq(base);
	/* 0,&core_if->core_global_regs->gpwrdn,58,00000000 : 1189 */
	read(base, 0x58, 0x00000000);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 1190 */
	read(base, 0x14, 0x06400029);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 1191 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 : 1192 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 : 1193 */
	read(base, 0x18, 0xf3000806);
	/* 0,&core_if->core_global_regs->gahbcfg,8,00000031 : 1194 */
	read(base, 0x8, 0x00000031);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 1195 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 : 1196 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 : 1197 */
	read(base, 0x18, 0xf3000806);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 1198 */
	read(base, 0x14, 0x06400029);
	/* 0,&dwc_otg_hcd->core_if->host_if->host_global_regs->hfnum,408,13ce0300 : 1199 */
	read(base, 0x408, IGNORE);
	/* 0,&_core_if->host_if->host_global_regs->haint,414,00000001 : 1200 */
	read(base, 0x414, 0x00000001);
	/* 0,&hc_regs->hcint,508,00000023 : 1201 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 : 1202 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hcint,508,00000023 : 1203 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 : 1204 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hctsiz,510,c0000000 : 1205 */
	read(base, 0x510, 0xc0000000);
	/* 0,&hc_regs->hctsiz,510,c0000000 : 1206 */
	read(base, 0x510, 0xc0000000);
	/* 0,&hc_regs->hcint,508,00000023 : 1207 */
	read(base, 0x508, 0x00000023);
	/* 1,&hc_regs->hcintmsk,50c,00000000 : 1208 */
	write(base, 0x50c, 0x00000000);
	/* 1,&hc_regs->hcint,508,ffffffff : 1209 */
	write(base, 0x508, 0xffffffff);
	/* 1,&hc_regs->hcint,508,00003fff : 1210 */
	write(base, 0x508, 0x00003fff);
	/* 1,&hc_regs->hcintmsk,50c,00000006 : 1211 */
	write(base, 0x50c, 0x00000006);
	/* 1,&host_if->hc_regs[hc_num]->hcchar,500,01089200 : 1212 */
	write(base, 0x500, 0x01089200);
	/* 1,&host_if->hc_regs[hc_num]->hcsplt,504,00000000 : 1213 */
	write(base, 0x504, 0x00000000);
	/* 0,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 : 1214 */
	read(base, 0x418, 0x00000001);
	/* 1,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 : 1215 */
	write(base, 0x418, 0x00000001);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 1216 */
	read(base, 0x18, 0xf3000806);
	/* 1,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 1217 */
	write(base, 0x18, 0xf3000806);
	poll_less_than_with_max_tries(base + 0x2c, 0x00080100, 200);
	/* 0,&global_regs->gnptxsts,2c,00080100 : 1218 */
	read(base, 0x2c, 0x00080100);
	/* 1,&hc_regs->hctsiz,510,40401000 : 1219 */
	write(base, 0x510, 0x40401000);
	/* 1,&hc_regs->hcdma,514,d8b9e000 : 1224 */
	write(base, 0x514, data);
	/* 0,&hc_regs->hcchar,500,01089200 : 1225 */
	read(base, 0x500, 0x01089200);
	/* 1,&hc_regs->hcchar,500,81189200 : 1226 */
	write(base, 0x500, 0x81189200);
	/* 0,&(hc_regs)->hcintmsk,50c,00000006 : 1227 */
	read(base, 0x50c, 0x00000006);
	/* 1,&(hc_regs)->hcintmsk,50c,00000006 : 1228 */
	write(base, 0x50c, 0x00000006);
	poll_for_irq(base);
	/* 0,&core_if->core_global_regs->gpwrdn,58,00000000 : 1229 */
	read(base, 0x58, 0x00000000);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 1230 */
	read(base, 0x14, 0x06400029);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 1231 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 : 1232 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 : 1233 */
	read(base, 0x18, 0xf3000806);
	/* 0,&core_if->core_global_regs->gahbcfg,8,00000031 : 1234 */
	read(base, 0x8, 0x00000031);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 1235 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 : 1236 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 : 1237 */
	read(base, 0x18, 0xf3000806);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 1238 */
	read(base, 0x14, 0x06400029);
	/* 0,&dwc_otg_hcd->core_if->host_if->host_global_regs->hfnum,408,0c120301 : 1239 */
	read(base, 0x408, IGNORE);
	/* 0,&_core_if->host_if->host_global_regs->haint,414,00000001 : 1240 */
	read(base, 0x414, 0x00000001);
	/* 0,&hc_regs->hcint,508,00000023 : 1241 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 : 1242 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hcint,508,00000023 : 1243 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 : 1244 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hctsiz,510,c0000000 : 1245 */
	read(base, 0x510, 0xc0000000);
	/* 0,&hc_regs->hctsiz,510,c0000000 : 1246 */
	read(base, 0x510, 0xc0000000);
	/* 0,&hc_regs->hcint,508,00000023 : 1247 */
	read(base, 0x508, 0x00000023);
	/* 1,&hc_regs->hcintmsk,50c,00000000 : 1248 */
	write(base, 0x50c, 0x00000000);
	/* 1,&hc_regs->hcint,508,ffffffff : 1249 */
	write(base, 0x508, 0xffffffff);
	/* 1,&hc_regs->hcint,508,00003fff : 1250 */
	write(base, 0x508, 0x00003fff);
	/* 1,&hc_regs->hcintmsk,50c,00000006 : 1251 */
	write(base, 0x50c, 0x00000006);
	/* 1,&host_if->hc_regs[hc_num]->hcchar,500,01089200 : 1252 */
	write(base, 0x500, 0x01089200);
	/* 1,&host_if->hc_regs[hc_num]->hcsplt,504,00000000 : 1253 */
	write(base, 0x504, 0x00000000);
	/* 0,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 : 1254 */
	read(base, 0x418, 0x00000001);
	/* 1,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 : 1255 */
	write(base, 0x418, 0x00000001);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 1256 */
	read(base, 0x18, 0xf3000806);
	/* 1,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 1257 */
	write(base, 0x18, 0xf3000806);
	poll_less_than_with_max_tries(base + 0x2c, 0x00080100, 200);
	/* 0,&global_regs->gnptxsts,2c,00080100 : 1258 */
	read(base, 0x2c, 0x00080100);
	/* 1,&hc_regs->hctsiz,510,40401000 : 1259 */
	write(base, 0x510, 0x40401000);
	/* 1,&hc_regs->hcdma,514,daa5b000 : 1264 */
	write(base, 0x514, data);
	/* 0,&hc_regs->hcchar,500,01089200 : 1265 */
	read(base, 0x500, 0x01089200);
	/* 1,&hc_regs->hcchar,500,81189200 : 1266 */
	write(base, 0x500, 0x81189200);
	/* 0,&(hc_regs)->hcintmsk,50c,00000006 : 1267 */
	read(base, 0x50c, 0x00000006);
	/* 1,&(hc_regs)->hcintmsk,50c,00000006 : 1268 */
	write(base, 0x50c, 0x00000006);
	poll_for_irq(base);
	/* 0,&core_if->core_global_regs->gpwrdn,58,00000000 : 1269 */
	read(base, 0x58, 0x00000000);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 1270 */
	read(base, 0x14, 0x06400029);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 1271 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 : 1272 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 : 1273 */
	read(base, 0x18, 0xf3000806);
	/* 0,&core_if->core_global_regs->gahbcfg,8,00000031 : 1274 */
	read(base, 0x8, 0x00000031);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 1275 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 : 1276 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 : 1277 */
	read(base, 0x18, 0xf3000806);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 1278 */
	read(base, 0x14, 0x06400029);
	/* 0,&dwc_otg_hcd->core_if->host_if->host_global_regs->hfnum,408,05f40302 : 1279 */
	read(base, 0x408, IGNORE);
	/* 0,&_core_if->host_if->host_global_regs->haint,414,00000001 : 1280 */
	read(base, 0x414, 0x00000001);
	/* 0,&hc_regs->hcint,508,00000023 : 1281 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 : 1282 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hcint,508,00000023 : 1283 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 : 1284 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hctsiz,510,c0000000 : 1285 */
	read(base, 0x510, 0xc0000000);
	/* 0,&hc_regs->hctsiz,510,c0000000 : 1286 */
	read(base, 0x510, 0xc0000000);
	/* 0,&hc_regs->hcint,508,00000023 : 1287 */
	read(base, 0x508, 0x00000023);
	/* 1,&hc_regs->hcintmsk,50c,00000000 : 1288 */
	write(base, 0x50c, 0x00000000);
	/* 1,&hc_regs->hcint,508,ffffffff : 1289 */
	write(base, 0x508, 0xffffffff);
	/* 1,&hc_regs->hcint,508,00003fff : 1290 */
	write(base, 0x508, 0x00003fff);
	/* 1,&hc_regs->hcintmsk,50c,00000006 : 1291 */
	write(base, 0x50c, 0x00000006);
	/* 1,&host_if->hc_regs[hc_num]->hcchar,500,01089200 : 1292 */
	write(base, 0x500, 0x01089200);
	/* 1,&host_if->hc_regs[hc_num]->hcsplt,504,00000000 : 1293 */
	write(base, 0x504, 0x00000000);
	/* 0,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 : 1294 */
	read(base, 0x418, 0x00000001);
	/* 1,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 : 1295 */
	write(base, 0x418, 0x00000001);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 1296 */
	read(base, 0x18, 0xf3000806);
	/* 1,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 1297 */
	write(base, 0x18, 0xf3000806);
	poll_less_than_with_max_tries(base + 0x2c, 0x00080100, 200);
	/* 0,&global_regs->gnptxsts,2c,00080100 : 1298 */
	read(base, 0x2c, 0x00080100);
	/* 1,&hc_regs->hctsiz,510,40401000 : 1299 */
	write(base, 0x510, 0x40401000);
	/* 1,&hc_regs->hcdma,514,e51ef000 : 1304 */
	write(base, 0x514, data);
	/* 0,&hc_regs->hcchar,500,01089200 : 1305 */
	read(base, 0x500, 0x01089200);
	/* 1,&hc_regs->hcchar,500,81189200 : 1306 */
	write(base, 0x500, 0x81189200);
	/* 0,&(hc_regs)->hcintmsk,50c,00000006 : 1307 */
	read(base, 0x50c, 0x00000006);
	/* 1,&(hc_regs)->hcintmsk,50c,00000006 : 1308 */
	write(base, 0x50c, 0x00000006);
	poll_for_irq(base);
	/* 0,&core_if->core_global_regs->gpwrdn,58,00000000 : 1309 */
	read(base, 0x58, 0x00000000);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 1310 */
	read(base, 0x14, 0x06400029);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 1311 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 : 1312 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 : 1313 */
	read(base, 0x18, 0xf3000806);
	/* 0,&core_if->core_global_regs->gahbcfg,8,00000031 : 1314 */
	read(base, 0x8, 0x00000031);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 1315 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 : 1316 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 : 1317 */
	read(base, 0x18, 0xf3000806);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 1318 */
	read(base, 0x14, 0x06400029);
	/* 0,&dwc_otg_hcd->core_if->host_if->host_global_regs->hfnum,408,01a40303 : 1319 */
	read(base, 0x408, IGNORE);
	/* 0,&_core_if->host_if->host_global_regs->haint,414,00000001 : 1320 */
	read(base, 0x414, 0x00000001);
	/* 0,&hc_regs->hcint,508,00000023 : 1321 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 : 1322 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hcint,508,00000023 : 1323 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 : 1324 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hctsiz,510,c0000000 : 1325 */
	read(base, 0x510, 0xc0000000);
	/* 0,&hc_regs->hctsiz,510,c0000000 : 1326 */
	read(base, 0x510, 0xc0000000);
	/* 0,&hc_regs->hcint,508,00000023 : 1327 */
	read(base, 0x508, 0x00000023);
	/* 1,&hc_regs->hcintmsk,50c,00000000 : 1328 */
	write(base, 0x50c, 0x00000000);
	/* 1,&hc_regs->hcint,508,ffffffff : 1329 */
	write(base, 0x508, 0xffffffff);
	/* 1,&hc_regs->hcint,508,00003fff : 1330 */
	write(base, 0x508, 0x00003fff);
	/* 1,&hc_regs->hcintmsk,50c,00000006 : 1331 */
	write(base, 0x50c, 0x00000006);
	/* 1,&host_if->hc_regs[hc_num]->hcchar,500,01089200 : 1332 */
	write(base, 0x500, 0x01089200);
	/* 1,&host_if->hc_regs[hc_num]->hcsplt,504,00000000 : 1333 */
	write(base, 0x504, 0x00000000);
	/* 0,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 : 1334 */
	read(base, 0x418, 0x00000001);
	/* 1,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 : 1335 */
	write(base, 0x418, 0x00000001);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 1336 */
	read(base, 0x18, 0xf3000806);
	/* 1,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 1337 */
	write(base, 0x18, 0xf3000806);
	poll_less_than_with_max_tries(base + 0x2c, 0x00080100, 200);
	/* 0,&global_regs->gnptxsts,2c,00080100 : 1338 */
	read(base, 0x2c, 0x00080100);
	/* 1,&hc_regs->hctsiz,510,40401000 : 1339 */
	write(base, 0x510, 0x40401000);
	/* 1,&hc_regs->hcdma,514,d7593000 : 1344 */
	write(base, 0x514, data);
	/* 0,&hc_regs->hcchar,500,01089200 : 1345 */
	read(base, 0x500, 0x01089200);
	/* 1,&hc_regs->hcchar,500,81189200 : 1346 */
	write(base, 0x500, 0x81189200);
	/* 0,&(hc_regs)->hcintmsk,50c,00000006 : 1347 */
	read(base, 0x50c, 0x00000006);
	/* 1,&(hc_regs)->hcintmsk,50c,00000006 : 1348 */
	write(base, 0x50c, 0x00000006);
	poll_for_irq(base);
	/* 0,&core_if->core_global_regs->gpwrdn,58,00000000 : 1349 */
	read(base, 0x58, 0x00000000);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 1350 */
	read(base, 0x14, 0x06400029);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 1351 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 : 1352 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 : 1353 */
	read(base, 0x18, 0xf3000806);
	/* 0,&core_if->core_global_regs->gahbcfg,8,00000031 : 1354 */
	read(base, 0x8, 0x00000031);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 1355 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 : 1356 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 : 1357 */
	read(base, 0x18, 0xf3000806);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 1358 */
	read(base, 0x14, 0x06400029);
	/* 0,&dwc_otg_hcd->core_if->host_if->host_global_regs->hfnum,408,1a1f0305 : 1359 */
	read(base, 0x408, IGNORE);
	/* 0,&_core_if->host_if->host_global_regs->haint,414,00000001 : 1360 */
	read(base, 0x414, 0x00000001);
	/* 0,&hc_regs->hcint,508,00000023 : 1361 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 : 1362 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hcint,508,00000023 : 1363 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 : 1364 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hctsiz,510,c0000000 : 1365 */
	read(base, 0x510, 0xc0000000);
	/* 0,&hc_regs->hctsiz,510,c0000000 : 1366 */
	read(base, 0x510, 0xc0000000);
	/* 0,&hc_regs->hcint,508,00000023 : 1367 */
	read(base, 0x508, 0x00000023);
	/* 1,&hc_regs->hcintmsk,50c,00000000 : 1368 */
	write(base, 0x50c, 0x00000000);
	/* 1,&hc_regs->hcint,508,ffffffff : 1369 */
	write(base, 0x508, 0xffffffff);
	/* 1,&hc_regs->hcint,508,00003fff : 1370 */
	write(base, 0x508, 0x00003fff);
	/* 1,&hc_regs->hcintmsk,50c,00000006 : 1371 */
	write(base, 0x50c, 0x00000006);
	/* 1,&host_if->hc_regs[hc_num]->hcchar,500,01089200 : 1372 */
	write(base, 0x500, 0x01089200);
	/* 1,&host_if->hc_regs[hc_num]->hcsplt,504,00000000 : 1373 */
	write(base, 0x504, 0x00000000);
	/* 0,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 : 1374 */
	read(base, 0x418, 0x00000001);
	/* 1,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 : 1375 */
	write(base, 0x418, 0x00000001);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 1376 */
	read(base, 0x18, 0xf3000806);
	/* 1,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 1377 */
	write(base, 0x18, 0xf3000806);
	poll_less_than_with_max_tries(base + 0x2c, 0x00080100, 200);
	/* 0,&global_regs->gnptxsts,2c,00080100 : 1378 */
	read(base, 0x2c, 0x00080100);
	/* 1,&hc_regs->hctsiz,510,40401000 : 1379 */
	write(base, 0x510, 0x40401000);
	/* 1,&hc_regs->hcdma,514,dfadf000 : 1384 */
	write(base, 0x514, data);
	/* 0,&hc_regs->hcchar,500,01089200 : 1385 */
	read(base, 0x500, 0x01089200);
	/* 1,&hc_regs->hcchar,500,81189200 : 1386 */
	write(base, 0x500, 0x81189200);
	/* 0,&(hc_regs)->hcintmsk,50c,00000006 : 1387 */
	read(base, 0x50c, 0x00000006);
	/* 1,&(hc_regs)->hcintmsk,50c,00000006 : 1388 */
	write(base, 0x50c, 0x00000006);
	poll_for_irq(base);
	/* 0,&core_if->core_global_regs->gpwrdn,58,00000000 : 1389 */
	read(base, 0x58, 0x00000000);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 1390 */
	read(base, 0x14, 0x06400029);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 1391 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 : 1392 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 : 1393 */
	read(base, 0x18, 0xf3000806);
	/* 0,&core_if->core_global_regs->gahbcfg,8,00000031 : 1394 */
	read(base, 0x8, 0x00000031);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 1395 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 : 1396 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 : 1397 */
	read(base, 0x18, 0xf3000806);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 1398 */
	read(base, 0x14, 0x06400029);
	/* 0,&dwc_otg_hcd->core_if->host_if->host_global_regs->hfnum,408,13b60306 : 1399 */
	read(base, 0x408, IGNORE);
	/* 0,&_core_if->host_if->host_global_regs->haint,414,00000001 : 1400 */
	read(base, 0x414, 0x00000001);
	/* 0,&hc_regs->hcint,508,00000023 : 1401 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 : 1402 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hcint,508,00000023 : 1403 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 : 1404 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hctsiz,510,c0000000 : 1405 */
	read(base, 0x510, 0xc0000000);
	/* 0,&hc_regs->hctsiz,510,c0000000 : 1406 */
	read(base, 0x510, 0xc0000000);
	/* 0,&hc_regs->hcint,508,00000023 : 1407 */
	read(base, 0x508, 0x00000023);
	/* 1,&hc_regs->hcintmsk,50c,00000000 : 1408 */
	write(base, 0x50c, 0x00000000);
	/* 1,&hc_regs->hcint,508,ffffffff : 1409 */
	write(base, 0x508, 0xffffffff);
	/* 0,&(hc_regs)->hcintmsk,50c,00000000 : 1410 */
	read(base, 0x50c, 0x00000000);
	/* 1,&(hc_regs)->hcintmsk,50c,00000000 : 1411 */
	write(base, 0x50c, 0x00000000);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 1417 */
	read(base, 0x18, 0xf3000806);
	/* 1,&hc_regs->hcint,508,00003fff : 1418 */
	write(base, 0x508, 0x00003fff);
	/* 1,&hc_regs->hcintmsk,50c,00000006 : 1419 */
	write(base, 0x50c, 0x00000006);
	/* 1,&host_if->hc_regs[hc_num]->hcchar,500,01089200 : 1420 */
	write(base, 0x500, 0x01089200);
	/* 1,&host_if->hc_regs[hc_num]->hcsplt,504,00000000 : 1421 */
	write(base, 0x504, 0x00000000);
	/* 0,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 : 1422 */
	read(base, 0x418, 0x00000001);
	/* 1,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 : 1423 */
	write(base, 0x418, 0x00000001);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 1424 */
	read(base, 0x18, 0xf3000806);
	/* 1,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 1425 */
	write(base, 0x18, 0xf3000806);
	poll_less_than_with_max_tries(base + 0x2c, 0x00080100, 200);
	/* 0,&global_regs->gnptxsts,2c,00080100 : 1426 */
	read(base, 0x2c, 0x00080100);
	/* 1,&hc_regs->hctsiz,510,40080200 : 1427 */
	write(base, 0x510, 0x40080200);
	/* 1,&hc_regs->hcdma,514,f7053000 : 1432 */
	write(base, 0x514, cmd);
	/* 0,&hc_regs->hcchar,500,01089200 : 1433 */
	read(base, 0x500, 0x01089200);
	/* 1,&hc_regs->hcchar,500,81189200 : 1434 */
	write(base, 0x500, 0x81189200);
	poll_for_irq(base);
	/* 0,&core_if->core_global_regs->gpwrdn,58,00000000 : 1435 */
	read(base, 0x58, 0x00000000);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 1436 */
	read(base, 0x14, 0x06400029);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 1437 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 : 1438 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 : 1439 */
	read(base, 0x18, 0xf3000806);
	/* 0,&core_if->core_global_regs->gahbcfg,8,00000031 : 1440 */
	read(base, 0x8, 0x00000031);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 1441 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 : 1442 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 : 1443 */
	read(base, 0x18, 0xf3000806);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 1444 */
	read(base, 0x14, 0x06400029);
	/* 0,&dwc_otg_hcd->core_if->host_if->host_global_regs->hfnum,408,12660307 : 1445 */
	read(base, 0x408, IGNORE);
	/* 0,&_core_if->host_if->host_global_regs->haint,414,00000001 : 1446 */
	read(base, 0x414, 0x00000001);
	/* 0,&hc_regs->hcint,508,00000023 : 1447 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 : 1448 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hcint,508,00000023 : 1449 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 : 1450 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hctsiz,510,800001f3 : 1451 */
	read(base, 0x510, 0x800001f3);
	/* 0,&hc_regs->hctsiz,510,800001f3 : 1452 */
	read(base, 0x510, 0x800001f3);
	/* 0,&hc_regs->hcint,508,00000023 : 1453 */
	read(base, 0x508, 0x00000023);
	/* 1,&hc_regs->hcintmsk,50c,00000000 : 1454 */
	write(base, 0x50c, 0x00000000);
	/* 1,&hc_regs->hcint,508,ffffffff : 1455 */
	write(base, 0x508, 0xffffffff);
	/* 0,&(hc_regs)->hcintmsk,50c,00000000 : 1456 */
	read(base, 0x50c, 0x00000000);
	/* 1,&(hc_regs)->hcintmsk,50c,00000000 : 1457 */
	write(base, 0x50c, 0x00000000);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 1466 */
	read(base, 0x18, 0xf3000806);
	/* 1,&hc_regs->hcint,508,00003fff : 1467 */
	write(base, 0x508, 0x00003fff);
	/* 1,&hc_regs->hcintmsk,50c,00000006 : 1468 */
	write(base, 0x50c, 0x00000006);
	/* 1,&host_if->hc_regs[hc_num]->hcchar,500,01081200 : 1469 */
	write(base, 0x500, 0x01081200);
	/* 1,&host_if->hc_regs[hc_num]->hcsplt,504,00000000 : 1470 */
	write(base, 0x504, 0x00000000);
	/* 0,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 : 1471 */
	read(base, 0x418, 0x00000001);
	/* 1,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 : 1472 */
	write(base, 0x418, 0x00000001);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 1473 */
	read(base, 0x18, 0xf3000806);
	/* 1,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 1474 */
	write(base, 0x18, 0xf3000806);
	poll_less_than_with_max_tries(base + 0x2c, 0x00080100, 200);
	/* 0,&global_regs->gnptxsts,2c,00080100 : 1475 */
	read(base, 0x2c, 0x00080100);
	cmd = prepare_read_10(16);
	/* 1,&hc_regs->hctsiz,510,0008001f : 1476 */
	write(base, 0x510, 0x0008001f);
	/* 1,&hc_regs->hcdma,514,f7053000 : 1481 */
	write(base, 0x514, cmd);
	/* 0,&hc_regs->hcchar,500,01081200 : 1482 */
	read(base, 0x500, 0x01081200);
	/* 1,&hc_regs->hcchar,500,81181200 : 1483 */
	write(base, 0x500, 0x81181200);
	poll_for_irq(base);
	/* 0,&core_if->core_global_regs->gpwrdn,58,00000000 : 1484 */
	read(base, 0x58, 0x00000000);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 1485 */
	read(base, 0x14, 0x06400029);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 1486 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 : 1487 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 : 1488 */
	read(base, 0x18, 0xf3000806);
	/* 0,&core_if->core_global_regs->gahbcfg,8,00000031 : 1489 */
	read(base, 0x8, 0x00000031);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 1490 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 : 1491 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 : 1492 */
	read(base, 0x18, 0xf3000806);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 1493 */
	read(base, 0x14, 0x06400029);
	/* 0,&dwc_otg_hcd->core_if->host_if->host_global_regs->hfnum,408,09870355 : 1494 */
	read(base, 0x408, IGNORE);
	/* 0,&_core_if->host_if->host_global_regs->haint,414,00000001 : 1495 */
	read(base, 0x414, 0x00000001);
	/* 0,&hc_regs->hcint,508,00000023 : 1496 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 : 1497 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hcint,508,00000023 : 1498 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 : 1499 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hctsiz,510,4000001f : 1500 */
	read(base, 0x510, 0x4000001f);
	/* 0,&hc_regs->hctsiz,510,4000001f : 1501 */
	read(base, 0x510, 0x4000001f);
	/* 0,&hc_regs->hcint,508,00000023 : 1502 */
	read(base, 0x508, 0x00000023);
	/* 1,&hc_regs->hcintmsk,50c,00000000 : 1503 */
	write(base, 0x50c, 0x00000000);
	/* 1,&hc_regs->hcint,508,ffffffff : 1504 */
	write(base, 0x508, 0xffffffff);
	/* 0,&(hc_regs)->hcintmsk,50c,00000000 : 1505 */
	read(base, 0x50c, 0x00000000);
	/* 1,&(hc_regs)->hcintmsk,50c,00000000 : 1506 */
	write(base, 0x50c, 0x00000000);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 1507 */
	read(base, 0x18, 0xf3000806);
	/* 1,&hc_regs->hcint,508,00003fff : 1508 */
	write(base, 0x508, 0x00003fff);
	/* 1,&hc_regs->hcintmsk,50c,00000006 : 1509 */
	write(base, 0x50c, 0x00000006);
	/* 1,&host_if->hc_regs[hc_num]->hcchar,500,01089200 : 1510 */
	write(base, 0x500, 0x01089200);
	/* 1,&host_if->hc_regs[hc_num]->hcsplt,504,00000000 : 1511 */
	write(base, 0x504, 0x00000000);
	/* 0,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 : 1512 */
	read(base, 0x418, 0x00000001);
	/* 1,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 : 1513 */
	write(base, 0x418, 0x00000001);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 1514 */
	read(base, 0x18, 0xf3000806);
	/* 1,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 1515 */
	write(base, 0x18, 0xf3000806);
	poll_less_than_with_max_tries(base + 0x2c, 0x00080100, 200);
	/* 0,&global_regs->gnptxsts,2c,00080100 : 1516 */
	read(base, 0x2c, 0x00080100);
	/* 1,&hc_regs->hctsiz,510,00401000 : 1517 */
	write(base, 0x510, 0x00401000);
	/* 1,&hc_regs->hcdma,514,d711f000 : 1522 */
	write(base, 0x514, data);
	/* 0,&hc_regs->hcchar,500,01089200 : 1523 */
	read(base, 0x500, 0x01089200);
	/* 1,&hc_regs->hcchar,500,81189200 : 1524 */
	write(base, 0x500, 0x81189200);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 1525 */
	read(base, 0x18, 0xf3000806);
	/* 0,&global_regs->gnptxsts,2c,00000100 : 1526 */
	read(base, 0x2c, 0x00000100);
	poll_for_irq(base);
	/* 0,&core_if->core_global_regs->gpwrdn,58,00000000 : 1527 */
	read(base, 0x58, 0x00000000);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 1528 */
	read(base, 0x14, 0x06400029);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 1529 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 : 1530 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 : 1531 */
	read(base, 0x18, 0xf3000806);
	/* 0,&core_if->core_global_regs->gahbcfg,8,00000031 : 1532 */
	read(base, 0x8, 0x00000031);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 1533 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 : 1534 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 : 1535 */
	read(base, 0x18, 0xf3000806);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 1536 */
	read(base, 0x14, 0x06400029);
	/* 0,&dwc_otg_hcd->core_if->host_if->host_global_regs->hfnum,408,11ac0358 : 1537 */
	read(base, 0x408, IGNORE);
	/* 0,&_core_if->host_if->host_global_regs->haint,414,00000001 : 1538 */
	read(base, 0x414, 0x00000001);
	/* 0,&hc_regs->hcint,508,00000023 : 1539 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 : 1540 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hcint,508,00000023 : 1541 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 : 1542 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hctsiz,510,80000000 : 1543 */
	read(base, 0x510, 0x80000000);
	/* 0,&hc_regs->hctsiz,510,80000000 : 1544 */
	read(base, 0x510, 0x80000000);
	/* 0,&hc_regs->hcint,508,00000023 : 1545 */
	read(base, 0x508, 0x00000023);
	/* 1,&hc_regs->hcintmsk,50c,00000000 : 1546 */
	write(base, 0x50c, 0x00000000);
	/* 1,&hc_regs->hcint,508,ffffffff : 1547 */
	write(base, 0x508, 0xffffffff);
	/* 1,&hc_regs->hcint,508,00003fff : 1548 */
	write(base, 0x508, 0x00003fff);
	/* 1,&hc_regs->hcintmsk,50c,00000006 : 1549 */
	write(base, 0x50c, 0x00000006);
	/* 1,&host_if->hc_regs[hc_num]->hcchar,500,01089200 : 1550 */
	write(base, 0x500, 0x01089200);
	/* 1,&host_if->hc_regs[hc_num]->hcsplt,504,00000000 : 1551 */
	write(base, 0x504, 0x00000000);
	/* 0,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 : 1552 */
	read(base, 0x418, 0x00000001);
	/* 1,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 : 1553 */
	write(base, 0x418, 0x00000001);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 1554 */
	read(base, 0x18, 0xf3000806);
	/* 1,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 1555 */
	write(base, 0x18, 0xf3000806);
	poll_less_than_with_max_tries(base + 0x2c, 0x00080100, 200);
	/* 0,&global_regs->gnptxsts,2c,00080100 : 1556 */
	read(base, 0x2c, 0x00080100);
	/* 1,&hc_regs->hctsiz,510,00401000 : 1557 */
	write(base, 0x510, 0x00401000);
	/* 1,&hc_regs->hcdma,514,d9844000 : 1562 */
	write(base, 0x514, data);
	/* 0,&hc_regs->hcchar,500,01089200 : 1563 */
	read(base, 0x500, 0x01089200);
	/* 1,&hc_regs->hcchar,500,81189200 : 1564 */
	write(base, 0x500, 0x81189200);
	/* 0,&(hc_regs)->hcintmsk,50c,00000006 : 1565 */
	read(base, 0x50c, 0x00000006);
	/* 1,&(hc_regs)->hcintmsk,50c,00000006 : 1566 */
	write(base, 0x50c, 0x00000006);
	poll_for_irq(base);
	/* 0,&core_if->core_global_regs->gpwrdn,58,00000000 : 1567 */
	read(base, 0x58, 0x00000000);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 1568 */
	read(base, 0x14, 0x06400029);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 1569 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 : 1570 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 : 1571 */
	read(base, 0x18, 0xf3000806);
	/* 0,&core_if->core_global_regs->gahbcfg,8,00000031 : 1572 */
	read(base, 0x8, 0x00000031);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 1573 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 : 1574 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 : 1575 */
	read(base, 0x18, 0xf3000806);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 1576 */
	read(base, 0x14, 0x06400029);
	/* 0,&dwc_otg_hcd->core_if->host_if->host_global_regs->hfnum,408,09a80359 : 1577 */
	read(base, 0x408, IGNORE);
	/* 0,&_core_if->host_if->host_global_regs->haint,414,00000001 : 1578 */
	read(base, 0x414, 0x00000001);
	/* 0,&hc_regs->hcint,508,00000023 : 1579 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 : 1580 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hcint,508,00000023 : 1581 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 : 1582 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hctsiz,510,80000000 : 1583 */
	read(base, 0x510, 0x80000000);
	/* 0,&hc_regs->hctsiz,510,80000000 : 1584 */
	read(base, 0x510, 0x80000000);
	/* 0,&hc_regs->hcint,508,00000023 : 1585 */
	read(base, 0x508, 0x00000023);
	/* 1,&hc_regs->hcintmsk,50c,00000000 : 1586 */
	write(base, 0x50c, 0x00000000);
	/* 1,&hc_regs->hcint,508,ffffffff : 1587 */
	write(base, 0x508, 0xffffffff);
	/* 0,&(hc_regs)->hcintmsk,50c,00000000 : 1588 */
	read(base, 0x50c, 0x00000000);
	/* 1,&(hc_regs)->hcintmsk,50c,00000000 : 1589 */
	write(base, 0x50c, 0x00000000);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 1595 */
	read(base, 0x18, 0xf3000806);
	/* 1,&hc_regs->hcint,508,00003fff : 1596 */
	write(base, 0x508, 0x00003fff);
	/* 1,&hc_regs->hcintmsk,50c,00000006 : 1597 */
	write(base, 0x50c, 0x00000006);
	/* 1,&host_if->hc_regs[hc_num]->hcchar,500,01089200 : 1598 */
	write(base, 0x500, 0x01089200);
	/* 1,&host_if->hc_regs[hc_num]->hcsplt,504,00000000 : 1599 */
	write(base, 0x504, 0x00000000);
	/* 0,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 : 1600 */
	read(base, 0x418, 0x00000001);
	/* 1,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 : 1601 */
	write(base, 0x418, 0x00000001);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 1602 */
	read(base, 0x18, 0xf3000806);
	/* 1,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 1603 */
	write(base, 0x18, 0xf3000806);
	/* 0,&global_regs->gnptxsts,2c,00080100 : 1604 */
	read(base, 0x2c, 0x00080100);
	/* 1,&hc_regs->hctsiz,510,00080200 : 1605 */
	write(base, 0x510, 0x00080200);
	/* 1,&hc_regs->hcdma,514,f7053000 : 1610 */
	write(base, 0x514, cmd);
	/* 0,&hc_regs->hcchar,500,01089200 : 1611 */
	read(base, 0x500, 0x01089200);
	/* 1,&hc_regs->hcchar,500,81189200 : 1612 */
	write(base, 0x500, 0x81189200);
	poll_for_irq(base);
	/* 0,&core_if->core_global_regs->gpwrdn,58,00000000 : 1613 */
	read(base, 0x58, 0x00000000);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 1614 */
	read(base, 0x14, 0x06400029);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 1615 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 : 1616 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 : 1617 */
	read(base, 0x18, 0xf3000806);
	/* 0,&core_if->core_global_regs->gahbcfg,8,00000031 : 1618 */
	read(base, 0x8, 0x00000031);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 1619 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 : 1620 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 : 1621 */
	read(base, 0x18, 0xf3000806);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 1622 */
	read(base, 0x14, 0x06400029);
	/* 0,&dwc_otg_hcd->core_if->host_if->host_global_regs->hfnum,408,0b28035a : 1623 */
	read(base, 0x408, IGNORE);
	/* 0,&_core_if->host_if->host_global_regs->haint,414,00000001 : 1624 */
	read(base, 0x414, 0x00000001);
	/* 0,&hc_regs->hcint,508,00000023 : 1625 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 : 1626 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hcint,508,00000023 : 1627 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 : 1628 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hctsiz,510,c00001f3 : 1629 */
	read(base, 0x510, 0xc00001f3);
	/* 0,&hc_regs->hctsiz,510,c00001f3 : 1630 */
	read(base, 0x510, 0xc00001f3);
	/* 0,&hc_regs->hcint,508,00000023 : 1631 */
	read(base, 0x508, 0x00000023);
	/* 1,&hc_regs->hcintmsk,50c,00000000 : 1632 */
	write(base, 0x50c, 0x00000000);
	/* 1,&hc_regs->hcint,508,ffffffff : 1633 */
	write(base, 0x508, 0xffffffff);
	/* 0,&(hc_regs)->hcintmsk,50c,00000000 : 1634 */
	read(base, 0x50c, 0x00000000);
	/* 1,&(hc_regs)->hcintmsk,50c,00000000 : 1635 */
	write(base, 0x50c, 0x00000000);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 1644 */
	read(base, 0x18, 0xf3000806);
	/* 1,&hc_regs->hcint,508,00003fff : 1645 */
	write(base, 0x508, 0x00003fff);
	/* 1,&hc_regs->hcintmsk,50c,00000006 : 1646 */
	write(base, 0x50c, 0x00000006);
	/* 1,&host_if->hc_regs[hc_num]->hcchar,500,01081200 : 1647 */
	write(base, 0x500, 0x01081200);
	/* 1,&host_if->hc_regs[hc_num]->hcsplt,504,00000000 : 1648 */
	write(base, 0x504, 0x00000000);
	/* 0,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 : 1649 */
	read(base, 0x418, 0x00000001);
	/* 1,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 : 1650 */
	write(base, 0x418, 0x00000001);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 1651 */
	read(base, 0x18, 0xf3000806);
	/* 1,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 1652 */
	write(base, 0x18, 0xf3000806);
	poll_less_than_with_max_tries(base + 0x2c, 0x00080100, 200);
	/* 0,&global_regs->gnptxsts,2c,00080100 : 1653 */
	read(base, 0x2c, 0x00080100);
	cmd = prepare_allow_medium_removal(0);
	/* 1,&hc_regs->hctsiz,510,4008001f : 1654 */
	write(base, 0x510, 0x4008001f);
	/* 1,&hc_regs->hcdma,514,f7053000 : 1659 */
	write(base, 0x514, cmd);
	/* 0,&hc_regs->hcchar,500,01081200 : 1660 */
	read(base, 0x500, 0x01081200);
	/* 1,&hc_regs->hcchar,500,81181200 : 1661 */
	write(base, 0x500, 0x81181200);
	poll_for_irq(base);
	/* 0,&core_if->core_global_regs->gpwrdn,58,00000000 : 1662 */
	read(base, 0x58, 0x00000000);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 1663 */
	read(base, 0x14, 0x06400029);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 1664 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 : 1665 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 : 1666 */
	read(base, 0x18, 0xf3000806);
	/* 0,&core_if->core_global_regs->gahbcfg,8,00000031 : 1667 */
	read(base, 0x8, 0x00000031);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 1668 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 : 1669 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 : 1670 */
	read(base, 0x18, 0xf3000806);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 1671 */
	read(base, 0x14, 0x06400029);
	/* 0,&dwc_otg_hcd->core_if->host_if->host_global_regs->hfnum,408,160b03a1 : 1672 */
	read(base, 0x408, IGNORE);
	/* 0,&_core_if->host_if->host_global_regs->haint,414,00000001 : 1673 */
	read(base, 0x414, 0x00000001);
	/* 0,&hc_regs->hcint,508,00000023 : 1674 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 : 1675 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hcint,508,00000023 : 1676 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 : 1677 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hctsiz,510,0000001f : 1678 */
	read(base, 0x510, 0x0000001f);
	/* 0,&hc_regs->hctsiz,510,0000001f : 1679 */
	read(base, 0x510, 0x0000001f);
	/* 0,&hc_regs->hcint,508,00000023 : 1680 */
	read(base, 0x508, 0x00000023);
	/* 1,&hc_regs->hcintmsk,50c,00000000 : 1681 */
	write(base, 0x50c, 0x00000000);
	/* 1,&hc_regs->hcint,508,ffffffff : 1682 */
	write(base, 0x508, 0xffffffff);
	/* 0,&(hc_regs)->hcintmsk,50c,00000000 : 1683 */
	read(base, 0x50c, 0x00000000);
	/* 1,&(hc_regs)->hcintmsk,50c,00000000 : 1684 */
	write(base, 0x50c, 0x00000000);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 1689 */
	read(base, 0x18, 0xf3000806);
	/* 1,&hc_regs->hcint,508,00003fff : 1690 */
	write(base, 0x508, 0x00003fff);
	/* 1,&hc_regs->hcintmsk,50c,00000006 : 1691 */
	write(base, 0x50c, 0x00000006);
	/* 1,&host_if->hc_regs[hc_num]->hcchar,500,01089200 : 1692 */
	write(base, 0x500, 0x01089200);
	/* 1,&host_if->hc_regs[hc_num]->hcsplt,504,00000000 : 1693 */
	write(base, 0x504, 0x00000000);
	/* 0,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 : 1694 */
	read(base, 0x418, 0x00000001);
	/* 1,&hcd->core_if->host_if->host_global_regs->haintmsk,418,00000001 : 1695 */
	write(base, 0x418, 0x00000001);
	/* 0,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 1696 */
	read(base, 0x18, 0xf3000806);
	/* 1,&hcd->core_if->core_global_regs->gintmsk,18,f3000806 : 1697 */
	write(base, 0x18, 0xf3000806);
	poll_less_than_with_max_tries(base + 0x2c, 0x00080100, 200);
	/* 0,&global_regs->gnptxsts,2c,00080100 : 1698 */
	read(base, 0x2c, 0x00080100);
	/* 1,&hc_regs->hctsiz,510,40080200 : 1699 */
	write(base, 0x510, 0x40080200);
	/* 1,&hc_regs->hcdma,514,f7053000 : 1704 */
	write(base, 0x514, cmd);
	/* 0,&hc_regs->hcchar,500,01089200 : 1705 */
	read(base, 0x500, 0x01089200);
	/* 1,&hc_regs->hcchar,500,81189200 : 1706 */
	write(base, 0x500, 0x81189200);
	poll_for_irq(base);
	/* 0,&core_if->core_global_regs->gpwrdn,58,00000000 : 1707 */
	read(base, 0x58, 0x00000000);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 1708 */
	read(base, 0x14, 0x06400029);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 1709 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 : 1710 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 : 1711 */
	read(base, 0x18, 0xf3000806);
	/* 0,&core_if->core_global_regs->gahbcfg,8,00000031 : 1712 */
	read(base, 0x8, 0x00000031);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 1713 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintsts,14,06400029 : 1714 */
	read(base, 0x14, 0x06400029);
	/* 0,&core_if->core_global_regs->gintmsk,18,f3000806 : 1715 */
	read(base, 0x18, 0xf3000806);
	/* 0,&_core_if->core_global_regs->gintsts,14,06400029 : 1716 */
	read(base, 0x14, 0x06400029);
	/* 0,&dwc_otg_hcd->core_if->host_if->host_global_regs->hfnum,408,0f2703a2 : 1717 */
	read(base, 0x408, IGNORE);
	/* 0,&_core_if->host_if->host_global_regs->haint,414,00000001 : 1718 */
	read(base, 0x414, 0x00000001);
	/* 0,&hc_regs->hcint,508,00000023 : 1719 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 : 1720 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hcint,508,00000023 : 1721 */
	read(base, 0x508, 0x00000023);
	/* 0,&hc_regs->hcintmsk,50c,00000006 : 1722 */
	read(base, 0x50c, 0x00000006);
	/* 0,&hc_regs->hctsiz,510,800001f3 : 1723 */
	read(base, 0x510, 0x800001f3);
	/* 0,&hc_regs->hctsiz,510,800001f3 : 1724 */
	read(base, 0x510, 0x800001f3);
	/* 0,&hc_regs->hcint,508,00000023 : 1725 */
	read(base, 0x508, 0x00000023);
	/* 1,&hc_regs->hcintmsk,50c,00000000 : 1726 */
	write(base, 0x50c, 0x00000000);
	/* 1,&hc_regs->hcint,508,ffffffff : 1727 */
	write(base, 0x508, 0xffffffff);
	/* 0,&(hc_regs)->hcintmsk,50c,00000000 : 1728 */
	read(base, 0x50c, 0x00000000);
	/* 1,&(hc_regs)->hcintmsk,50c,00000000 : 1729 */
	write(base, 0x50c, 0x00000000);
}
