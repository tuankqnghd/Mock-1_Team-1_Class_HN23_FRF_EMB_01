#ifndef _FAT_12_HANDLING_H
#define _FAT_12_HANDLING_H
#include <stdint.h>

/********************************************************************
 * Include Library
********************************************************************/

/********************************************************************
 * API
********************************************************************/


/*
* @brief add node data to the end of linklist
*
*@param inputdata is input data to new node
*
*@return void
*/
void boot_block_read(FILE* file);


/*
* @brief add node data to the head of linklist
*
*@param inputdata is input data to new node
*
*@return void
*/
uint32_t convert(uint8_t a[], size_t size);


/*
* @brief delete the last node data of linklist
*
*@return void
*/
void print_root_directory(FILE* file);


/*
* @brief delete the last node data of linklist
*
*@return void
*/
void print_root(uint8_t* data[]);


/*
* @brief print the list of data
*
*@return void
*/


#endif




