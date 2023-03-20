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

typedef struct {
	uint8_t part[3];
	uint8_t manufacturer_description[8];
	uint8_t number_bytes_per_sectors[2];                 //512 			 
	uint8_t number_secters_per_cluster[1];	  		     //01	  SL sector cua cluster	
	uint8_t number_reserved_sector[2];					 //01     SL sector truoc bang FAT		
	uint8_t number_FATs[1];								 //02     SL bang FAT	
	uint8_t number_root_entry[2];						 //224	  SL root directory entry	 
	uint8_t number_total_sectors[2];					 //2880   SL sector cua o dia, neu bang 0 thi doc 0x20
	uint8_t media[1]; 												
	uint8_t number_sectors_per_FAT[2];					 //9	  SL sector cua bang FAT
	uint8_t number_sectors_per_track[2];				 //18
	uint8_t number_heads[2];							 //02
	uint8_t number_hidden_blocks[4];					 //0
	uint8_t number_2_total_sectors[4];					 //0
	uint8_t number_physical_drive[2];					 //0
	uint8_t extended_signnature[1];
	uint8_t volume_ID[4];
	uint8_t volume_label[11];
	uint8_t file_system_identifier[8];
	uint8_t remainder[0x1c0];
	uint8_t signature[2];
} Boot_block;

static Boot_block boot_block_data;

static Boot_block * Ptr = &boot_block_data;



void boot_block_read(FILE* file)
{
	// pointer file to 0x0
	fseek(file, 0x0, SEEK_SET);
	// read 512 byte of boot_block and save to struct boot_block_data
	fread((Boot_block *) Ptr, sizeof(Boot_block), 1, file);
	// printf("%d\n", convert(boot_block_data.number_root_entry, 2));
}



void print_root_directory(FILE* file)
{
	// root_address = (number_reserved_sector + number_FATs * number_sectors_per_FAT) * 512
	uint32_t root_address = (convert(boot_block_data.number_reserved_sector, 2) + (uint32_t)boot_block_data.number_FATs[0]*convert(boot_block_data.number_sectors_per_FAT, 2)) * 512;
	// pointer file to root_address = 0x2600
	fseek(file, root_address, SEEK_SET);
	uint8_t data[32];
	uint8_t* ptr = &data;
	while (1)
	{
		fread(ptr, 32, 1, file);
		uint8_t i;
		if (data[0] == 0)
		{
			return;
		}
		// bo cac entry phu
		if (data[11] != 0x0F)
		{
			print_root(data); // Ham printf cua hieu in ra thuoc tinh file
			for (i = 0; i<32; i++)
			{
				printf("%x", data[i]);	
			}
			printf("\n");
		}
	}
}



void print_root(uint8_t* data[])
{
	// Ham printf cua hieu nhap vao con tro ham 32 byte, tra ra cac thuoc tinh cua file
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

