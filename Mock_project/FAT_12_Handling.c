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
#include "FAT_12_Handling.h"

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


void boot_block_read(FILE* file)
{
	// pointer file to 0x0
	fseek(file, 0x0, SEEK_SET);
	// read 512 byte of boot_block and save to struct boot_block_data
	fread((Boot_block *) Ptr, sizeof(Boot_block), 1, file);
	// printf("%d\n", convert(boot_block_data.number_root_entry, 2));
}



void print_entry(uint8_t* data[])
{
	printf("entry");
	// Hieu
}



void print_data(uint16_t cluster, uint32_t size)
{
	printf("data");
	// Son
}



uint32_t convert(uint8_t a[], size_t size)
{	
	uint32_t result = 0;
	uint8_t index;
	for (index = 0; index < size; index++)
	{
		result += a[index]*pow(256, index);
	}	
	return result;
}

