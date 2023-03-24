/*
* @file List.c
* @brief Linklist library support user add, delete, print student data list
*/
/********************************************************************
 * Include Library
********************************************************************/
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "Linklist_Lib.h"

/********************************************************************
 * Definition
********************************************************************/

/*********************************************************************
* Variable
*********************************************************************/

/*static boolean status = false;

/*********************************************************************
* Static function
*********************************************************************/

/*********************************************************************
* Global function 
*********************************************************************/

void AddNodeLast(uint32_t inputdata)
{
	NodeType* node = HEAD;
	// 1. Create a node - Dynamic Allocate
	NodeType* ptrNode = (NodeType *)malloc(sizeof(NodeType));
	
	// 2. Assign Data
    ptrNode->data = inputdata;

	// 3. Last node is pointing to NULL => Now, it point to Node
	// Node 1 : HEAD = ptrNode1;
	// Node 2 : HEAD->next = ptrNode2;
	// Node 3 : HEAD->next->next = ptrNode3;
	if (HEAD == NULL)
	{
		HEAD = ptrNode;		// Add Node 1
	}
	else
	{
		while(node->next != NULL)
		{
			node = node->next;		// node = HEAD->next
		}
		node->next = ptrNode;
	}
	
	// 4. next of node -> NULL
	ptrNode->next = NULL;
}


void AddNodeHeader(uint32_t inputdata)
{
	//1. Create a note - Dynamic Allocate
	NodeType * ptrNode = (NodeType *)malloc(sizeof(NodeType));

	//2. Assign Data
    ptrNode->data = inputdata;

	//3. Newnode point to last node
	if (HEAD == NULL)
	{
		ptrNode->next = NULL;
	}
	else
	{
		ptrNode->next = HEAD;	
	}
	
	//4. HEAD->newnode
	HEAD = ptrNode;
}


uint32_t ReadNodeHeader()
{
	return (HEAD->data);
}


void DeleteNode(uint32_t inputdata)
{
	NodeType* node = HEAD;
	NodeType* prev = NULL;
	// Check if the first node need to delete
	if ((node != NULL) && (HEAD->data == inputdata))
	{
		HEAD = node->next;
		free (node);
		return;
	}
	// If not the first node
    while ((node != NULL) && (node->data != inputdata)) 
	{
        prev = node;
        node = node->next;
    }
    // No node exist to delete
    if (node == NULL) 
	{
        return;
    }
    // Node exist to delete
    else
	{
		prev->next = node->next;
		return;
	}
    // Free memory
    free(node);
}


void DeleteNodeHeader()
{
	NodeType* node = HEAD;
	// Check if node is not empty
	if (node != NULL)
	{
		HEAD = node->next;
		free (node);
		return;	
	} 
	// If node empty
	else
	{
		return;
	}
}


void PrintList(void)
{	
	NodeType*node=HEAD;
	while (node != NULL)
	{
		printf("%d\t", node->data);
		node=node->next;
	}
	printf("\n");
}




