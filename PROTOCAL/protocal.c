#include "protocal.h"
#include "spi.h"
#include "delay.h"

u8 cs = 0x00;
void SPI0_Init(void)
{	
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(	RCC_AHB1Periph_GPIOB, ENABLE );//PORTA时钟使能 

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;  // PB0,1,2,3
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;  //推挽输出
 	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
 	GPIO_Init(GPIOB, &GPIO_InitStructure);
 	GPIO_SetBits(GPIOB,GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3); //SPI从机全部不选中
	SPI1_Init(); //初始化MCU的SPI1
	SPI1_SetSpeed(SPI_BaudRatePrescaler_2);//设置为30M时钟,高速模式 
}  

s8 SPI0_ChangeSlave(Slavex_TypeDef slavex) //选择从机
{
	switch (slavex)
		{
			case Slave0:
				cs = Slave0;
				break;
			case Slave1:
				cs= Slave1;
				break;
			case Slave2:
				cs = Slave2;
				break;
			case Slave3:
				cs = Slave3;
			default:
				return -1;
				
		}

}

void SPI0_PacketCmd_Wr(u8 *CmdLine, u8 n)
{
	u8 wrcl = 0x00;
	u8 index = 0;
	wrcl = wrcl | CCRC | DCRC | n;
	CS(cs) = HIGH;
	delay_us(TREADY);
	CS(cs) = LOW;
	delay_us(T3); //t3>1us
	SPI1_ReadWriteByte(0xc0);
	delay_us(T); //T>10us
	SPI1_ReadWriteByte(wrcl);

	while (index < n)
		{
			SPI1_ReadWriteByte(*(CmdLine + index));
		}
	delay_us(T4); //t4>1us
	CS(cs) = HIGH;
}

void SPI0_PacketCmd_Rd(u8 *CmdLine, u8 n)
{
	u8 wrcl = 0x80;
	u8 index = 0;
	wrcl = wrcl | CCRC | DCRC | n;
	CS(cs) = HIGH;
	delay_us(TREADY);
	CS(cs) = LOW;
	delay_us(T3); //t3>1us
	SPI1_ReadWriteByte(0xc0);
	delay_us(T); //T>10us
	SPI1_ReadWriteByte(wrcl);

	while (index < n)
		{
			SPI1_ReadWriteByte(*(CmdLine + index));
		}
	delay_us(T4); //t4>1us
	CS(cs) = HIGH;
}

void SPI0_PacketData_Wr(u8 *data, u8 n)
{
	u8 index = 0;
	CS(cs) = HIGH;
	delay_us(TREADY);
	CS(cs) = LOW;
	delay_us(T3);
	SPI1_ReadWriteByte(0x3f);
	delay_us(T);
	while (index < n)
		{
			SPI1_ReadWriteByte(*(data + index));
		}
	delay_us(T4); //t4>1us
	CS(cs) = HIGH;
}

void SPI0_PacketData_Rd(u8 *targetadd,u8 n)
{
	
}

