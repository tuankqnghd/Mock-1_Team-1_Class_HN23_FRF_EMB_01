#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "Linklist_Lib.h"
#include "FAT_12_Handling.h"
#pragma pack(1)

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

void main() 
{
	FILE * file = fopen ("floppy1.img", "r");
	boot_block_read(file);
	// root_address = (number_reserved_sector + number_FATs * number_sectors_per_FAT) * 512 = 0x2600
	uint32_t root_address = (convert(boot_block_data.number_reserved_sector, 2) + (uint32_t)boot_block_data.number_FATs[0]*convert(boot_block_data.number_sectors_per_FAT, 2)) * 512;
	// pointer file to root_address = 0x2600
	fseek(file, root_address, SEEK_SET);
	uint8_t data[32];
	uint8_t* ptr_data = &data;
	while (1)
	{
		fread(ptr_data, 32, 1, file);
		uint8_t i;
		if (data[0] == 0)
		{
			return;
		}
		// bo cac entry phu
		if (data[11] != 0x0F)
		{
			print_entry(data); // Ham printf cua hieu in ra thuoc tinh file
			for (i = 0; i<32; i++)
			{
				printf("%x", data[i]);	
			}
			printf("\n");
		}
	}
	fclose(file);
}
