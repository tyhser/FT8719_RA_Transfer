#include "NodeList.h"
#include "malloc.h"
static void* NodeList_Malloc(int size){
	return usr_malloc(size);
}

static void NodeList_Free(void*p){
	usr_free(p);
}

void NodeList_Init(NodeListType *NodeList, int Node_DataSize, int MaxNodeCount){

	if(NodeList == NULL){
		return;
	}

	NodeList->pHead 			= NULL;
	NodeList->pEnd				= NULL;
	NodeList->ListLen 			= 0;
	NodeList->MaxNodeCount		= MaxNodeCount;
	NodeList->Node_DataSize 	= Node_DataSize;

}

int NodeList_AddNode(NodeListType *NodeList, void *pBuf){
	NodeType *pNode;
	DISABLE_ALL_INTERRUPT;
	if(NodeList == NULL){
		return -1;
	}

	if(NodeList->ListLen == NodeList->MaxNodeCount){
		return -2;
	}
	
	pNode 			= (NodeType*)NodeList_Malloc(sizeof(NodeType));
	if(pNode == NULL){
		return -3;
	}
	
	pNode->pData 	= NodeList_Malloc(NodeList->Node_DataSize);
	if(pNode->pData == NULL){
		return -3;
	}
	
	usr_memcpy(pNode->pData, pBuf, NodeList->Node_DataSize);

	

	if(NodeList->ListLen == 0){
		pNode->Pre = NULL;
		pNode->Next = NULL;

		NodeList->pHead = pNode;
		NodeList->pEnd = pNode;
	}else{
		pNode->Next = NULL;
		pNode->Pre  = NodeList->pEnd;
		NodeList->pEnd->Next = pNode;
		NodeList->pEnd = pNode;
	
	}

	NodeList->ListLen++;
ENABLE_ALL_INTERRUPT;
	return 0;
}


int  NodeList_RemoveNodeAt(NodeListType *NodeList, int at){
	NodeType *pNode;
	int i;
	DISABLE_ALL_INTERRUPT;
	if(NodeList == NULL){
		return -1;
	}

	if(at >= NodeList->ListLen){
		return -2;
	}
	pNode = NodeList->pHead;

	for(i=0; i<at; i++){
		pNode = pNode->Next;
	}


	if(pNode->Pre != NULL){
		pNode->Pre->Next = pNode->Next;

	}else{
		NodeList->pHead = pNode->Next;

	}

	if(pNode->Next != NULL){
		pNode->Next->Pre = pNode->Pre;
	}else{
		NodeList->pEnd = pNode->Pre;
	}
	

	NodeList->ListLen--;

	NodeList_Free(pNode->pData);
	NodeList_Free(pNode);
	ENABLE_ALL_INTERRUPT;
	return 0;
}



int NodeList_ReadNodeAt(NodeListType *NodeList, int index, void *pRet){
	int i;
	NodeType *pNode;
	DISABLE_ALL_INTERRUPT;
	if(NodeList == NULL){
		return -1;
	}

	if(index >= NodeList->MaxNodeCount){
		return -2;
	}
	
	pNode = NodeList->pHead;

	for(i=0; i<index; i++){
		pNode = pNode->Next;

	}

	usr_memcpy(pRet, pNode->pData, NodeList->Node_DataSize);
ENABLE_ALL_INTERRUPT;
	return 0;

}

int NodeList_GetLen(NodeListType *NodeList){

	return NodeList->ListLen;
}

