// coding by yakir
// power by NKET
// time: 2017.05.04
// vertion: v1.0.0

#ifndef NODE_LIST_H
#define NODE_LIST_H
#define ENABLE_ALL_INTERRUPT 	//__enable_irq
#define DISABLE_ALL_INTERRUPT	//__disable_irq

typedef struct Node {
	void *pData;//指向数据区的指针
	struct Node *Next;//指向下一个节点
	struct Node *Pre;//指向上一个有效节点
}NodeType;

typedef struct {
	int Node_DataSize;	//节点数据大小
	int ListLen;		//链表有多长--即链表节点的个数
	int MaxNodeCount;	//最大节点个数
	NodeType *pHead;	//指向头节点
	NodeType *pEnd;		//指向最后一个有效节点
	
}NodeListType;

/**
 * function	: NodeList_Init
 * parameter	:
 *			  NodeList, 需要初始化的链表管理器
 *			  Node_DataSize, 节点大小,需字节对齐---sizeof
 *			  MaxNodeCount, 支持最大链表节点个数
 * return 		: none
 * descrition	: 初始化链表管理器
 */
extern void NodeList_Init(NodeListType *NodeList, int Node_DataSize, int MaxNodeCount);

/**
 * function 	: NodeList_AddNode
 * parameter	: 
 *			  NodeList,链表管理器
 *			  pBuf, 需要存储到链表当中的数据,其大小必须和初始化时候的Node_DataSize一致
 * return		: 
 *			  -1,链表管理器为空
 *			  -2,链表节点数已经达到上限,不能再添加了
 *			    0,节点添加成功
 * descrition	: 节点添加的位置为整个链表的最后面
 */
extern int NodeList_AddNode(NodeListType *NodeList, void *pBuf);


/**
 * function 	: NodeList_RemoveNodeAt
 * parameter	: 
 *			  NodeList,链表管理器
 *			    at,需要删除的节点的位置(第一个有效节点对应的index=0)
 * return		: 
 *			  -1,链表管理器为空
 *			  -2,链表节点数为0,不能进行删除节点操作
 *			    0,节点删除成功
 * descrition	: 节点删除的位置为整个链表的最前面
 */
extern	int  NodeList_RemoveNodeAt(NodeListType *NodeList, int at);

/**
 * function 	: NodeList_ReadNodeAt
 * parameter	: 
 *			  NodeList,链表管理器
 *			  at,需要读取的节点的位置(第一个有效节点对应的index=0)
 *			  pRet,用来存储需要读取的节点的内容
 * return		: 
 *			  -1,链表管理器为空
 *			  -2,索引值不合法
 *			    0,读取成功
 * descrition	: 读取对应节点的内容
 */
int NodeList_ReadNodeAt(NodeListType *NodeList, int at, void *pRet);


/**
 * function name 	: NodeList_GetLen
 * parameter		: NodeList, 链表管理器
 * return			: 返回链表节点个数(链表长度)
 */
extern int NodeList_GetLen(NodeListType *NodeList);


#endif



