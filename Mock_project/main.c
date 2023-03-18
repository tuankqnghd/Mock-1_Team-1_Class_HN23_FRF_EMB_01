#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "Linklist_Lib.h"
#pragma pack(1)

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

typedef struct {
	uint8_t part[3];
	uint8_t manufacturer_description[8];
	uint8_t number_bytes_per_sectors[2];                 //512 			 
	uint8_t number_secters_per_cluster[1];	  		     //01	  //SL sector cua cluster	
	uint8_t number_reserved_sector[2];					 //01     //SL sector truoc bang FAT		
	uint8_t number_FATs[1];								 //02     //SL bang FAT	
	uint8_t number_root_entry[2];						 //224	  //SL root directory entry	 
	uint8_t number_total_sectors[2];					 //2880   //SL sector cua o dia, neu bang 0 thi doc 0x20
	uint8_t media[1]; 												
	uint8_t number_sectors_per_FAT[2];					 //9	  //SL sector cua bang FAT
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

uint32_t convert_number(uint8_t a[], size_t size)
{	
	uint32_t result = 0;
	uint8_t index;
	for (index = 0; index < size; index++)
	{
		result += a[index]*pow(256, index);
	}	
	return result;
}

void main() 
{
	FILE * file = fopen ("floppy1.img", "r");
	Boot_block boot_block_data;
	Boot_block * Ptr = &boot_block_data;
	fread((Boot_block *)Ptr, sizeof(Boot_block), 1, file);
	printf("%d", convert_number(boot_block_data.number_root_entry, 2));
	// (root directory number_FATs*number_bytes_per_sectors + 1)*512 = (2*9+1)*512 = 9728 = 0x2600
	fclose(file);
}
