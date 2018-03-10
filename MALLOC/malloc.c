#include "main.h"
//内存管理控制器
struct _m_mallco_dev
{
	void (*init)(void);				//初始化
	u8 (*perused)(void);		  	//内存使用率
	u8 	*membase;					//内存池 
	u16 *memmap; 					//内存管理状态表
	u8  memrdy; 					//内存管理是否就绪
};

//内存池(4字节对齐)
__align(4) u8 membase[MEM_MAX_SIZE];			//SRAM内存池
//内存管理表
static u16 memmapbase[MEM_ALLOC_TABLE_SIZE];			//SRAM内存池MAP
//内存管理参数	   
const u32 memtblsize=MEM_ALLOC_TABLE_SIZE;		//内存表大小
const u32 memblksize=MEM_BLOCK_SIZE;			//内存分块大小
const u32 memsize=MEM_MAX_SIZE;					//内存总大小


//内存管理控制器
struct _m_mallco_dev mallco_dev=
{
	mem_init,			//内存初始化
	mem_perused,		//内存使用率
	membase,			//内存池
	memmapbase,			//内存管理状态表
	0,  				//内存管理未就绪
};


void usr_memcpy(void *des,void *src,u32 n)  
{  
    u8 *xdes=des;
	u8 *xsrc=src; 
    while(n--)*xdes++=*xsrc++;  
}  
//设置内存
//*s:内存首地址
//c :要设置的值
//count:需要设置的内存大小(字节为单位)
void usr_memset(void *s,u8 c,u32 count)  
{  
    u8 *xs = s;  
    while(count--)*xs++=c;  
}	   
//内存管理初始化  
void mem_init(void)  
{  
    usr_memset(mallco_dev.memmap, 0,memtblsize*2);//内存状态表数据清零  
	usr_memset(mallco_dev.membase, 0,memsize);	//内存池所有数据清零  
	mallco_dev.memrdy=1;						//内存管理初始化OK  
}  


//获取内存使用率
//返回值:使用率(0~100)
u8 mem_perused(void)  
{  
    u32 used=0;  
    u32 i;  
    for(i=0;i<memtblsize;i++)  
    {  
        if(mallco_dev.memmap[i])used++; 
    } 
    return (used*100)/(memtblsize);  
}  



static u32 mem_malloc(u32 size)  
{  
    signed long offset=0;  
    u16 nmemb;	//需要的内存块数  
	u16 cmemb=0;//连续空内存块数
    u32 i;  
    if(!mallco_dev.memrdy)mallco_dev.init();	//未初始化,先执行初始化 
    if(size==0)return 0XFFFFFFFF;				//不需要分配
    nmemb=size/memblksize;  					//获取需要分配的连续内存块数
    if(size%memblksize)nmemb++;  
    for(offset=memtblsize-1;offset>=0;offset--)	//搜索整个内存控制区  
    {     
		if(!mallco_dev.memmap[offset])cmemb++;	//连续空内存块数增加
		else cmemb=0;							//连续内存块清零
		if(cmemb==nmemb)						//找到了连续nmemb个空内存块
		{
            for(i=0;i<nmemb;i++)  				//标注内存块非空 
            {  
                mallco_dev.memmap[offset+i]=nmemb;  
            }  
            return (offset*memblksize);			//返回偏移地址  
		}
    }  
    return 0XFFFFFFFF;//未找到符合分配条件的内存块  
}  



static u8 mem_free(u32 offset)  
{  
    int i;  
    if(!mallco_dev.memrdy)//未初始化,先执行初始化
	{
		mallco_dev.init();    
        return 1;//未初始化  
    }  
    if(offset<memsize)//偏移在内存池内. 
    {  
        int index=offset/memblksize;		//偏移所在内存块号码  
        int nmemb=mallco_dev.memmap[index];	//内存块数量
        for(i=0;i<nmemb;i++)  				//内存块清零
        {  
            mallco_dev.memmap[index+i]=0;  
        }
        return 0;  
    }else return 2;//偏移超区了.  
}  

 
void usr_free(void *ptr)  
{  
	u32 offset;  
    if(ptr==NULL)return;//地址为0.  
 	offset=(u32)ptr-(u32)mallco_dev.membase;  
    mem_free(offset);	//释放内存     
}  




void *usr_malloc(u32 size)  
{  
    u32 offset;  									      
	offset=mem_malloc(size);  	   				   
    if(offset==0XFFFFFFFF)return NULL;  
    else return (void*)((u32)mallco_dev.membase+offset);  
}  



void *usr_realloc(void *ptr,u32 size)  
{  
    u32 offset;  
    offset=mem_malloc(size);  
    if(offset==0XFFFFFFFF)return NULL;     
    else  
    {  									   
	    usr_memcpy((void*)((u32)mallco_dev.membase+offset),ptr,size);	//拷贝旧内存内容到新内存   
        usr_free(ptr);  											  	//释放旧内存
        return (void*)((u32)mallco_dev.membase+offset);  			//返回新内存首地址
    }  
}












