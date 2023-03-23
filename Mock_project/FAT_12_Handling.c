/*
* @file FAT_12_Handling.c
* @brief FAT library support user read boot block sector, calculate address of boot block sector, FAT table, root directory, data.
read a entry 32 bytes, return entry address, size, print entry to command & print data of a file
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
	
	// address calculate
	address.VBS = 0;
	address.FAT = convert(boot_block_data.number_reserved_sector, 2) * convert(boot_block_data.number_bytes_per_sectors, 2);
	address.RDET = address.FAT + (uint32_t)boot_block_data.number_FATs[0]*convert(boot_block_data.number_sectors_per_FAT, 2) * convert(boot_block_data.number_bytes_per_sectors, 2);
	address.DATA = address.RDET + 32 * convert(boot_block_data.number_root_entry,2);
}



void print_entry(uint8_t data[])
{
	print_Filename(data);
	printf("\t");
	print_Typefile(data);
	printf("\t");
	print_Sizefile(data);
	printf("\t");
	print_Date(data);
	printf("\t");
	print_Time(data);
	printf("\n");
}



void print_Filename(uint8_t data[])
{
	uint32_t i=0;
	for(;i<8;i++)
	{
		printf("%c",data[i]);
	}
}



void print_Sizefile(uint8_t data[])
{
	if(size_entry(data)!=0)
	{
		printf("%d ",size_entry(data));
		printf("bytes");
	}
	else
	{
		printf("         ");
	}
}



void print_Typefile(uint8_t data[])
{
	uint32_t i;
	if(size_entry(data)==0)
		printf("File Folder");
	else
	{
		printf("File ");
		for(i=8; i<11;i++)
		{
			printf("%c",data[i]);
		}
	}
}



void print_Date(uint8_t data[])
{
	uint8_t day = data[24] & 0x1F;
	if (day < 10)
	{
		printf("0");
	}
	printf("%d/", day);
	uint8_t month = (data[24] >> 5) + (data[25] & 0x01)*8;
	if (month < 10)
	{
		printf("0");
	}
	printf("%d/", month);
	uint16_t year = (data[25] >> 1) + 1980;
	printf("%d", year);
}



void print_Time(uint8_t data[])
{
	uint8_t hour = data[23] >> 3;
	if (hour < 10)
	{
		printf("0");
	}
	printf("%d:", hour);
	uint8_t minute = (data[22] >> 5) + (data[23] & 0x07)*8;
	if (minute < 10)
	{
		printf("0");
	}
	printf("%d:", minute);
	uint8_t second = (data[22] & 0x1F)*2;
	if (second < 10)
	{
		printf("0");
	}
	printf("%d", second);
}



void print_data(FILE* file, uint16_t cluster, uint32_t size)
{
	// fseek(file, data_address, SEEK_SET);
	fseek(file,cluster_address(cluster),SEEK_SET);
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



uint32_t cluster_address(uint16_t cluster_order)
{
	return (address.DATA + convert(boot_block_data.number_bytes_per_sectors, 2) * (cluster_order-2));
}

