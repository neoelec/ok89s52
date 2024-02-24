#ifndef __AT89S52_H__
#define __AT89S52_H__

#include <at89x52.h>

__sfr __at 0x82 DP0L;
__sfr __at 0x83 DP0H;
__sfr __at 0x84 DP1L;
__sfr __at 0x85 DP1H;

__sfr __at 0x8E AUXR;

__sfr __at 0xA2 AUXR1;
__sfr __at 0xA6 WDTRST;

__sbit __at 0x95 MOSI;
__sbit __at 0x96 MISO;
__sbit __at 0x97 SCK;

#endif /* __AT89S52_H__ */
