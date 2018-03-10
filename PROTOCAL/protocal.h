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

#define CCRC 0x00 //0x40Ϊ�������CRC
#define DCRC 0x00 //0x20Ϊ���ݰ���CRC

#define T 15
#define T3 3
#define T4 3
#define TREADY 3 //CS����ǰ�ȶ�ʱ��
#define HIGH 1
#define LOW 0
#endif
