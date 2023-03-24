#ifndef _LINKLIST_LIB_H
#define _LINKLIST_LIB_H
#include <stdint.h>

/********************************************************************
 * Include Library
********************************************************************/

/********************************************************************
 * API
********************************************************************/

struct node_t
{
	uint32_t data;
	struct node_t* next;
};

typedef struct node_t NodeType;

static NodeType * HEAD = NULL;


/*
* @brief add node data to the end of linklist
*
*@param inputdata is input data to new node
*
*@return void
*/
void AddNodeLast(uint32_t inputdata);


/*
* @brief add node data to the head of linklist
*
*@param inputdata is input data to new node
*
*@return void
*/
void AddNodeHeader(uint32_t inputdata);


/*
* @brief read the fisrt node data
*
*@return data of the first node
*/
uint32_t ReadNodeHeader();


/*
* @brief delete the last node data of linklist
*
*@return void
*/
void DeleteNode(uint32_t inputdata);


/*
* @brief delete the last node data of linklist
*
*@return void
*/
void DeleteNodeHeader();


/*
* @brief print the list of data
*
*@return void
*/
void PrintList(void);

#endif




