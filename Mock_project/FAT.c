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
#include "FAT.h"

/********************************************************************
 * Definition
********************************************************************/

/*********************************************************************
* Variable
*********************************************************************/

static Boot_block boot_block_data;

static Entry entry;

static FAT12_Address address;

static DATE date;

static TIME time;

static FILE * file;

static Boot_block * Ptr = &boot_block_data;

static FAT12_Address * Ptr_address = &address;

/*static boolean status = false;

/*********************************************************************
* Static function
*********************************************************************/

/*********************************************************************
* Global function 
*********************************************************************/



void boot_block_read()
{
	// pointer file to 0x0
	fseek(file, 0x0, SEEK_SET);
	// read 512 byte of boot_block and save to struct boot_block_data
	fread((Boot_block *) Ptr, sizeof(Boot_block), 1, file);
	// printf("%d\n", convert(boot_block_data.number_root_entry, 2));
	
	// address calculate
	address.VBS = 0;
	address.FAT = convert(boot_block_data.number_reserved_sector, 2) * convert(boot_block_data.number_bytes_per_sectors, 2);
	address.RDET = address.FAT + (uint32_t)boot_block_data.number_FATs[0]*convert(boot_block_data.number_sectors_per_FAT, 2) * convert(boot_block_data.number_bytes_per_sectors, 2);
	address.DATA = address.RDET + 32 * convert(boot_block_data.number_root_entry,2);
}



void Filename(uint8_t data[])
{
	uint8_t i;
	for (i = 0; i < 8; i++)
	{
		entry.name[i] = data[i];
	}
}



void Sizefile(uint8_t data[])
{
	entry.size = size_entry(data);
}



void Typefile(uint8_t data[])
{
	entry.type[0] = data[8];
	entry.type[1] = data[9];
	entry.type[2] = data[10];
}



void Date(uint8_t data[])
{
	uint16_t x = (data[25]<<8)+data[24];
	date.data=x;
	entry.day = date.fdate.d;
	entry.month = date.fdate.m;
	entry.year = date.fdate.y + 1980;
}



void Time(uint8_t data[])
{
	uint16_t x = (data[23]<<8)+data[22];
	time.data=x;
	entry.hour = time.ftime.h;
	entry.minute = time.ftime.m;
	entry.second = time.ftime.s * 2;
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



uint32_t cluster_entry(uint8_t a[])
{
	return a[26] + a[27] * 256;
}



uint32_t cluster_next(uint32_t present_cluster)
{
	fseek(file, address.FAT + (present_cluster/2) * 3, SEEK_SET);
	uint8_t buffer[3];
	fread(buffer, 3, 1, file);
	if (present_cluster%2 == 0)
	{
		return (((uint32_t)buffer[0] | (uint32_t)(buffer[1] << 8)) & 0xFFF);
	}
	else 
	{
		return ((uint32_t)(buffer[1] >> 4) | (uint32_t)(buffer[2] << 4));
	}
}



uint32_t size_entry(uint8_t a[])
{
	uint8_t size[4] = {a[28], a[29], a[30], a[31]};
	return convert(size, 4);
}



uint32_t cluster_address(uint32_t cluster_order)
{
	return (address.DATA + convert(boot_block_data.number_bytes_per_sectors, 2) * (cluster_order-2));
}



void openfile(char* filename)
{
	file = fopen(filename, "r");
}



void closefile()
{
	fclose(file);
}



Entry get_entry(uint8_t data[])
{
	Filename(data);
	Sizefile(data);
	Typefile(data);
	Date(data);
	Time(data);
	return entry;
}



FILE* get_file_ptr()
{
	return file;
}



Boot_block get_boot_block_data()
{
	return boot_block_data;
}



FAT12_Address get_address()
{
	return address;
}
