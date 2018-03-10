#include "protocal.h"

void SPI0_PacketCmd_Wr(u8 *CmdLine, u8 n)
{
	u8 wrcl = 0x00;
	wrcl = wrcl | CCRC | DCRC | n;
	
}

void SPI0_PacketCmd_Rd(u8 *CmdLine, u8 n)
{
	u8 wrcl = 0x80;
	wrcl = wrcl | CCRC | DCRC | n;
	
}

