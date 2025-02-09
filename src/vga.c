#include "vga.h"

#include <i86.h>
#include <conio.h>

// VGA CRT controller
#define VGA_CRTC_INDEX	0x3D4
#define VGA_CRTC_DATA 	0x3D5

#define	VGA_SC_INDEX	0x3C4
#define	VGA_SC_DATA		0x3C5
#define	VGA_MISC_OUTPUT	0x3C2

#define	VGA_AC_INDEX	0x03C0
#define	VGA_AC_DATA		0x03C0

#define	VGA_GC_INDEX	0x03CE
#define	VGA_GC_DATA		0x03CF

#define VGA_PAL_INDEX	0x03C8
#define VGA_PAL_DATA	0x03C9

// Index/data pairs for CRT Controller registers that differ between
// mode 13h and mode X.
const uint16_t CRTParms[] = {
	0x0d06,	// vertical total
	0x3e07,	// overflow (bit 8 of vertical counts)
	0x4109,	// cell height (2 to double-scan)
	0xea10,	// v sync start
	0xac11,	// v sync end and protect cr0-cr7
	0xdf12,	// vertical displayed
	0x0014,	// turn off dword mode
	0xe715,	// v blank start
	0x0616,	// v blank end
	0xe317,	// turn on byte mode
};

void VGA_SetVideoMode(uint8_t mode)
{
#if defined(M_I386)
	union REGS regs;
	
	regs.w.ax = mode;
	int386(0x10, &regs, &regs);
#else	
	union REGPACK regs;

	regs.x.ax = mode;
	intr(0x10, &regs);
#endif
}

void VGA_SetVideoMode_320x240(void)
{
	uint8_t val;
	int i;
	
	// let the BIOS set standard 256-color
	// mode (320x200 linear)
	VGA_SetVideoMode(0x13);
	
	// disable chain4 mode
	outpw(VGA_SC_INDEX, 0x0604);
	
	// synchronous reset while setting Misc Output
	// for safety, even though clock unchanged
	outpw(VGA_SC_INDEX, 0x0100);
	
	// select 25 MHz dot clock & 60 Hz scanning rate
	outp(VGA_MISC_OUTPUT, 0xe3);

	// undo reset (restart sequencer)
	outpw(VGA_SC_INDEX, 0x0300);
	
	// reprogram the CRT Controller
	// VSync End reg contains register write
	// protect bit
	outp(VGA_CRTC_INDEX, 0x11);
	
	// get current VSync End register setting
	val = inp(VGA_CRTC_DATA);
	
	// remove write protect on various
	val &= 0x7f;
	outp(VGA_CRTC_DATA, val);
	
	// Set all parameters from table
	for (i = 0; i < sizeof(CRTParms)/sizeof(CRTParms[0]); i++)
	{
		outpw(VGA_CRTC_INDEX, CRTParms[i]);
	}
	
	// enable writes to all four planes
	outpw(VGA_SC_INDEX, 0x0f02);
}
