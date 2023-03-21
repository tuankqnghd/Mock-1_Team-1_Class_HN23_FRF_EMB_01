#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "Linklist_Lib.h"
#include "FAT_12_Handling.h"
#pragma pack(1)

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

void command_root(FILE*file);

void command_folder(FILE*file, uint16_t cluster);

void command_root(FILE*file)
{
	// root_address = (number_reserved_sector + number_FATs * number_sectors_per_FAT) * number_bytes_per_sectors = 0x2600
	uint32_t root_address = (convert(boot_block_data.number_reserved_sector, 2) + (uint32_t)boot_block_data.number_FATs[0] * convert(boot_block_data.number_sectors_per_FAT, 2)) * convert(boot_block_data.number_bytes_per_sectors, 2);
	fseek(file, root_address, SEEK_SET);
	uint8_t data[32];
	// print root directory list and order count
	printf("   Name            Extension  Date modified     Size\n");
	uint8_t i = 0;
	uint8_t count = 0;
	while (1)
	{
		fread(data, 32, 1, file);

		if (data[0] == 0)
		{
			break;
		}
		// bo cac entry phu
		if (data[11] != 0x0F)
		{
			count++;
			printf("%d. ", count);
			print_entry(data);
			for (i = 0; i<32; i++)
			{
				printf("%x", data[i]);	
			}
			printf("\n");
		}
	}
	printf("\n-----------------------------------\n");
	printf("Type the number to open file\n");
	printf("Type '0' to exit!\n");
	uint8_t value;
	while (1) 
	{
    	scanf("%d", &value);
    	if (value == 0) 
		{
			exit(0);
    	} 
		else if ((value < 0) || (value > count))
		{
      		printf("Invalid value, please re-enter!\n");
    	}
    	else 
    	{
    		// read root have to entry to data[32]
    		fseek(file, root_address, SEEK_SET);
			for (count = 0; count < value; count++)
			{
				fread(data, 32, 1, file);
				if (data[11] == 0x0F)
				{
					count--;
				}
			}
			// check if extention is floder = "   " = 0x2020202 
			if ((data[8] == 0x20) && (data[9] == 0x20) && (data[10] == 0x20))
			{
				printf("%x %x", cluster_entry(data), size_entry(data));
				//command_folder(file, convert(cluster, 2))
			}
			// if entry to data, print data
			else 
			{
				system("cls");
				print_data(file, cluster_entry(data), size_entry(data));
				printf("\n\n-----------------------------------\n");
				printf("Type '0' to return!\n");
				// Type '0' to back to command root
				while (1) 
				{
    				scanf("%d", &value);
    				if (value == 0) 
					{
						system("cls");
						command_root(file);
      					break;
    				}
					else
					{
						printf("Invalid value, please re-enter!\n");
					}	
				}
    		}
		}
	}
}

void command_folder(FILE* file, uint16_t cluster)
{
/*	if (cluster == 0)
	{
		command_root(file);
	}
	else
	{
	// root_address = (number_reserved_sector + number_FATs * number_sectors_per_FAT) * number_bytes_per_sectors = 0x2600
	uint32_t root_address = (convert(boot_block_data.number_reserved_sector, 2) + (uint32_t)boot_block_data.number_FATs[0] * convert(boot_block_data.number_sectors_per_FAT, 2)) * convert(boot_block_data.number_bytes_per_sectors, 2);
	// data_address = cluster[2] = root_address + number_root_entry * 32 = 0x4200
	uint32_t data_address = root_address + convert(boot_block_data.number_root_entry, 2) * 32;
	fseek(file, (data_address + (cluster - 2) * convert(boot_block_data.number_bytes_per_sectors, 2)), SEEK_SET);
	printf("   Name            Extension  Date modified     Size\n");
	uint8_t check_folder[64];
	fread(check_folder, 64, 1, file);
	if ((check_folder[0] == 0x2E) && (check_folder[32] == 0x2E) && (check_folder[33] == 0x2E) )
	{
		while (1)
		{
			uint8_t data[32];
			fread(data, 32, 1, file);
			uint8_t i = 0;
			uint8_t count;
			if (data[0] == 0)
			{
				break;
			}
			// bo cac entry phu
			if (data[11] != 0x0F)
			{
				printf("%d. ", count + 1);
				print_entry(data);
				for (i = 0; i<32; i++)
				{
					printf("%x", data[i]);	
				}
				printf("\n");
				count++;
			}
		}
		printf("-----------------------------------");
		printf("\nType the file number to open:");
		printf("\nType '0' to exit!");
	}
	else 
	{
		print_data(file, cluster, size);
		printf("-----------------------------------");
		printf("\nType '0' to return");
		uint8_t value;
		while (1) 
		{
    		scanf("%d", &value);
    		if (value == 0) 
			{
				command_folder(file, cluster, size);
      			break;
    		} 
			else
			{
      			printf("Invalid value, please re-enter!\n");
    		}
		}*/
}

void main() 
{
	FILE * file = fopen ("floppy1.img", "r");
	boot_block_read(file);
	command_root(file);
	fclose(file);
}
