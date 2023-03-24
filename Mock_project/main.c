#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "Linklist_Lib.h"
#include "FAT_12_Handling.h"
#pragma pack(1)

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

void command_RDET(FILE*file);

void command_folder(FILE*file, uint16_t cluster);

void command_RDET(FILE*file)
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
		// skip sub-entry
		if (data[11] != 0x0F)
		{
			count++;
			printf("%d. ", count);
			print_entry(data);
		}
	}

	printf("\n-----------------------------------------------------\n");
	printf("0. Exit\n");
	
	// Type number to open file, exit program
	uint8_t value;
	while (1) 
	{
    	scanf("%d", &value);
    	// Exit program
    	if (value == 0) 
		{
			exit(0);
    	} 
    	// Invalid value, type again
		else if ((value < 0) || (value > count))
		{
      		printf("Invalid value, please re-enter!\n");
    	}
    	// Number to open file
    	else 
    	{
    		// read 32 bytes of entry
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
				// Add first node is number cluster entry
				AddNodeHeader(cluster_entry(data));
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
	// file poiter to data address, skip first 64 bytes
	fseek(file, cluster_address(cluster) + 64, SEEK_SET);

	uint8_t data[32];
	uint8_t count = 0;
	
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
	
	// Type number to open file, exit program
	uint8_t value;
	while (1) 
	{
    	scanf("%d", &value);
    	// Exit program
    	if (value == 0) 
		{
			system("cls");
			// Delete first node
			DeleteNodeHeader();
			return;
    	} 
    	// Invalid value, type again
		else if ((value < 0) || (value > count))
		{
      		printf("Invalid value, please re-enter!\n");
    	}
    	// Number to open file
    	else 
    	{
    		// read 32 bytes of entry
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
				// Add first node is number cluster entry 
				AddNodeHeader(cluster_entry(data));
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
	// Add cluster number of RDET = 0
	AddNodeHeader(0);
	while (1)
	{
		// command by cluster number manage by linklist lib, add first node while enter a folder, and delete fisrt node when back folder -> present folder's cluster number is first node
		// check if cluster number = 0 (RDET)
		if (ReadNodeHeader() == 0)
		{
			command_RDET(file);
		}
		else
		{
			command_folder(file, ReadNodeHeader());
		}
	}
	fclose(file);
}
