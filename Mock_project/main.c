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
	// file pointer to root_address
	fseek(file, address.RDET, SEEK_SET);
	
	// print root directory list and order count
	uint8_t data[32];
	printf("   [Name]\t[Type]\t\t[Size]\t\t[Date]\t\t[Time]\n");
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
		}
	}

	printf("\n-----------------------------------------------------\n");
	printf("0. Exit\n");
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
    		fseek(file, address.RDET, SEEK_SET);
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
				system("cls");
				command_folder(file, cluster_entry(data));
				return;
			}
			// if entry to data, print data
			else 
			{
				system("cls");
				print_data(file, cluster_entry(data), size_entry(data));
				printf("\n\n-----------------------------------------------------\n");
				printf("0. Return\n");
				// Type '0' to back to command root
				while (1) 
				{
    				scanf("%d", &value);
    				if (value == 0) 
					{
						system("cls");
						command_root(file);
      					return;
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
	if (cluster == 0)
	{
		command_root(file);
		return;
	}
	// file poiter to data address
	fseek(file, cluster_address(cluster), SEEK_SET);
	
	// read pre_entry_address and entry_address
	uint8_t data[32];
	uint8_t i = 0;
	uint8_t count = 0;
	fread(data, 32, 1, file);
	uint16_t current_address = cluster_entry(data);	
	fread(data, 32, 1, file);	
	uint16_t pre_address = cluster_entry(data);	
	
	// print entry list and order count
	printf("   [Name]\t[Type]\t\t[Size]\t\t[Date]\t\t[Time]\n");	
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
		}
	}
	printf("\n\n-----------------------------------------------------\n");
	printf("0. Return\n");
	uint8_t value;
	while (1) 
	{
    	scanf("%d", &value);
    	if (value == 0) 
		{
			system("cls");
			command_folder(file, pre_address);
			return;
    	} 
		else if ((value < 0) || (value > count))
		{
      		printf("Invalid value, please re-enter!\n");
    	}
    	else 
    	{
    		// read root have to entry to data[32]
			fseek(file, cluster_address(cluster) + 64, SEEK_SET);
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
				system("cls");
				command_folder(file, cluster_entry(data));
				return;
			}
			// if entry to data, print data
			else 
			{
				system("cls");
				print_data(file, cluster_entry(data), size_entry(data));
				printf("\n\n-----------------------------------------------------\n");
				printf("0. return\n");
				// Type '0' to back to command root
				while (1) 
				{
    				scanf("%d", &value);
    				if (value == 0) 
					{
						system("cls");
						command_folder(file, current_address);
      					return;
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

void main() 
{
	FILE * file = fopen ("floppy1.img", "r");
	boot_block_read(file);
	command_root(file);
	AddNodeHeader(0);
	AddNodeHeader(100);
	AddNodeHeader(100);
	fclose(file);
}
