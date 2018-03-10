#ifndef __CRC_H
#define __CRC_H
#include "main.h"
#ifndef _getcrc16_state_
#define getcrc16_state extern
#else
#define getcrc16_state
#endif

#define TRUE 0
#define FALSE 1
// º¯ÊýÉùÃ÷
getcrc16_state u16 CalcCRC16(u16 crc,void *pBuff, u32 Length);
//getcrc16_state INT16U GetCRC16(INT8U *pBuff, INT32U Length);
getcrc16_state int CompareCrc16(u16 crc, u8* crcBuf);

//getcrc16_state INT8U PackCheck(stcBt304Frame *pPack);

#endif
