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
#include <math.h>
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



void print_data(FILE* file, uint16_t cluster, uint32_t size)
{
	// cluster[2]_address = (number_reserved_sector + number_FATs * number_sectors_per_FAT) * 512+ 32*number_root_entry = 0x4200
	uint32_t cluster2_address = (convert(boot_block_data.number_reserved_sector, 2) + (uint32_t)boot_block_data.number_FATs[0]*convert(boot_block_data.number_sectors_per_FAT, 2)) * 512+32*convert(boot_block_data.number_root_entry,2);
	// pointer file to data_address = 0x4200
	uint32_t data_address = cluster2_address + 512 * (cluster-2);
	// fseek(file, data_address, SEEK_SET);
	fseek(file,data_address,SEEK_SET);
	uint8_t buffer[512];
	uint8_t i;
	for (i = 0; i < (size/0x200) + 1; i++ )
	{
		fread(buffer,512,1,file);
		printf("%s",buffer);
	}
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



uint16_t cluster_entry(uint8_t a[])
{
	uint16_t result;
	uint8_t cluster[2] = {a[26], a[27]};
	result = a[26] + a[27] * 256;
	return result;
}



uint32_t size_entry(uint8_t a[])
{
	uint32_t result;
	uint8_t size[4] = {a[28], a[29], a[30], a[31]};
	result = convert(size, 4);
	return result;
}

