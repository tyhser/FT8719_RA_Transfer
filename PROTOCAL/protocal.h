#ifndef __PROTOCAL_H
#define __PROTOCAL_H
#include "spi.h"

typedef enum
{
	Slave0 = 0,
	Slave1 = 1,
	Slave2 = 2,
	Slave3 = 3
}Slavex_TypeDef;
	
#define CS(n) PBout(n)

#define CCRC 0x00 //0x40为命令包带CRC
#define DCRC 0x00 //0x20为数据包带CRC

#define T 15
#define T3 3
#define T4 3
#define TREADY 3 //CS拉低前稳定时间
#define HIGH 1
#define LOW 0
#endif
