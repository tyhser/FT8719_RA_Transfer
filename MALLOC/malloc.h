#ifndef _USR_MALLOC_H
#define _USR_MALLOC_H
 
  
#ifndef NULL
#define NULL 0
#endif


//内存参数设定.
#define MEM_BLOCK_SIZE			32  	  						//内存块大小为32字节
#define MEM_MAX_SIZE			32*40  						//最大管理内存 35K
#define MEM_ALLOC_TABLE_SIZE	MEM_MAX_SIZE/MEM_BLOCK_SIZE 	//内存表大小
 
		 


void usr_memset(void *buf,unsigned char c,unsigned int count);	//设置内存
void usr_memcpy(void *des,void *src,unsigned int n);//复制内存     
void mem_init(void);					 //内存管理初始化函数(外/内部调用)

unsigned char mem_perused(void);					//得内存使用率(外/内部调用) 
////////////////////////////////////////////////////////////////////////////////
//用户调用函数
void usr_free(void *ptr);  				//内存释放(外部调用)
void *usr_malloc(unsigned int size);				//内存分配(外部调用)
void *usr_realloc(void *ptr,unsigned int size);	//重新分配内存(外部调用)
#endif













