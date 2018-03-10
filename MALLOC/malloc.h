#ifndef _USR_MALLOC_H
#define _USR_MALLOC_H
 
  
#ifndef NULL
#define NULL 0
#endif


//�ڴ�����趨.
#define MEM_BLOCK_SIZE			32  	  						//�ڴ���СΪ32�ֽ�
#define MEM_MAX_SIZE			32*40  						//�������ڴ� 35K
#define MEM_ALLOC_TABLE_SIZE	MEM_MAX_SIZE/MEM_BLOCK_SIZE 	//�ڴ���С
 
		 


void usr_memset(void *buf,unsigned char c,unsigned int count);	//�����ڴ�
void usr_memcpy(void *des,void *src,unsigned int n);//�����ڴ�     
void mem_init(void);					 //�ڴ�����ʼ������(��/�ڲ�����)

unsigned char mem_perused(void);					//���ڴ�ʹ����(��/�ڲ�����) 
////////////////////////////////////////////////////////////////////////////////
//�û����ú���
void usr_free(void *ptr);  				//�ڴ��ͷ�(�ⲿ����)
void *usr_malloc(unsigned int size);				//�ڴ����(�ⲿ����)
void *usr_realloc(void *ptr,unsigned int size);	//���·����ڴ�(�ⲿ����)
#endif













