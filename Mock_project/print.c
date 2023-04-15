/*
* @file print.c
* @brief print command RDET and FILE folder, entry extention, ... use FAT.h lib
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
#include "Linklist.h"
#include "print.h"

/********************************************************************
 * Definition
********************************************************************/

/*********************************************************************
* Variable
*********************************************************************/

void print_entry(uint8_t data[])
{
	Entry entry = get_entry(data);
	// print file name
	uint8_t i = 0;
	for(i = 0; i < 8 ; i++)
	{
		printf("%c",entry.name[i]);
	}
	printf("\t");
	
	// print file type
	if(size_entry(data)==0)
	{
		printf("File Folder");
	}
	else
	{
		printf("File ");
		for(i = 0; i < 3; i++)
		{
			printf("%c",entry.type[i]);
		}
	}
	printf("\t");
	
	// print size of file
	if(entry.size != 0)
	{
		printf("%d ",entry.size);
		printf("bytes\t");
	}
	else
	{
		printf("         \t");
	}
	
	// print date
	if (entry.day < 10)
	{
		printf("0");
	}
	printf("%d/",entry.day);
	if (entry.month < 10)
	{
		printf("0");
	}
	printf("%d/",entry.month);
	printf("%d\t",entry.year);
	
	// print time
	if (entry.hour < 10)
	{
		printf("0");
	}
	printf("%d:",entry.hour);
	if (entry.month < 10)
	{
		printf("0");
	}
	printf("%d:",entry.month);
	if (entry.second < 10)
	{
		printf("0");
	}
	printf("%d\n",entry.second);
}



void print_data(uint32_t cluster)
{
	FILE* file_ptr = get_file_ptr();
	Boot_block boot_block_data = get_boot_block_data();
	FAT12_Address address = get_address();
	uint8_t buffer[512];
	uint32_t present_cluster = cluster;
	while (present_cluster != 0xFFF)
	{
		// fseek(file, present_cluster_address, SEEK_SET);
		fseek(file_ptr,address.DATA + convert(boot_block_data.number_bytes_per_sectors, 2) * (present_cluster - 2),SEEK_SET);
		fread(buffer,512,1,file_ptr);
		printf("%s",buffer);
		present_cluster = cluster_next(present_cluster);
	}
}



void command_RDET()
{
	FILE* file = get_file_ptr();
	Boot_block boot_block_data = get_boot_block_data();
	FAT12_Address address = get_address();
	
	system("cls");
	// print root directory list and order count
	uint8_t data[32];
	uint8_t index = 0;
	uint8_t count = 0;
	printf("   [Name]\t[Type]\t\t[Size]\t\t[Date]\t\t[Time]\n");
	// file pointer to root_address
	fseek(file, address.RDET, SEEK_SET);
	for (index = 0; index < convert(boot_block_data.number_root_entry,2); index++)
	{
		fread(data, 32, 1, file);
		// break when type of file entry = 0x000000
		if ((data[8] == 0x00) && (data[9] == 0x00) && (data[10] == 0x00))
		{
			break;
		}
		// skip sub-entry
		else if (data[11] != 0x0F)
		{
			count++;
			printf("%d. ", count);
			print_entry(data);
		}
	}

	printf("\n-----------------------------------------------------\n");
	printf("0. Exit\n");
	
	// Type number to open file, exit program
	uint8_t value_1, value_2;
	do
	{
    	scanf("%d", &value_1);
    	// Exit program
    	if (value_1 == 0) 
		{
			exit(0);
    	} 
    	// Invalid value, type again
		else if ((value_1 < 0) || (value_1 > count))
		{
      		printf("Invalid value, please re-enter!\n");
    	}
    	// Number to open file
    	else 
    	{
    		// read 32 bytes of entry
    		fseek(file, address.RDET, SEEK_SET);
			for (count = 0; count < value_1; count++)
			{
				fread(data, 32, 1, file);
				if (data[11] == 0x0F)
				{
					count--;
				}
			}
			// check if extention is floder = 0x2020202 
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
				print_data(cluster_entry(data));
				printf("\n\n-----------------------------------------------------\n");
				printf("0. Return\n");
				// Type '0' to back to command root
				do
				{
    				scanf("%d", &value_2);
    				if (value_2 == 0) 
					{
						system("cls");
      					return;
    				}
					else
					{
						printf("Invalid value, please re-enter!\n");
					}	
				} while (value_2 != 0);
    		}
		}
	} while (value_1 < 0 || value_1 > count);
}



void command_folder(uint32_t cluster)
{
	FILE* file = get_file_ptr();
	Boot_block boot_block_data = get_boot_block_data();
	FAT12_Address address = get_address();
	
	uint32_t present_cluster = cluster;
	uint8_t data[32];
	uint8_t index = 0;
	uint8_t count = 0;
	
	// print entry list and order count
	printf("   [Name]\t[Type]\t\t[Size]\t\t[Date]\t\t[Time]\n");	
	while (present_cluster != 0xFFF)
	{
		// file poiter to data address
		fseek(file, cluster_address(present_cluster), SEEK_SET);
		
		for (index = 0; index < (convert(boot_block_data.number_bytes_per_sectors, 2)/32); index++)
		{
			fread(data, 32, 1, file);
			if ((data[8] == 0x00) && (data[9] == 0x00) && (data[10] == 0x00))
			{
				break;
			}
			// skip sub-entry and 64 first bytes
			else if (data[11] != 0x0F && data[0] != 0x2E)
			{
				count++;
				printf("%d. ", count);
				print_entry(data);
			}
		}
		present_cluster = cluster_next(present_cluster);
	}
	printf("\n\n-----------------------------------------------------\n");
	printf("0. Return\n");
	
	// Type number to open file, exit program
	uint8_t value_1, value_2;
	do
	{
    	scanf("%d", &value_1);
    	// Exit program
    	if (value_1 == 0) 
		{
			system("cls");
			// Delete first node
			DeleteNodeHeader();
			return;
    	} 
    	// Invalid value, type again
		else if ((value_1 < 0) || (value_1 > count))
		{
      		printf("Invalid value, please re-enter!\n");
    	}
    	// Number to open file
    	else 
    	{
    		// read 32 bytes of entry
			fseek(file, cluster_address(cluster) + 64, SEEK_SET);
			for (count = 0; count < value_1; count++)
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
				print_data(cluster_entry(data));
				printf("\n\n-----------------------------------------------------\n");
				printf("0. return\n");
				// Type '0' to back to command root
				do 
				{
    				scanf("%d", &value_2);
    				if (value_2 == 0) 
					{
						system("cls");
      					return;
    				}
					else
					{
						printf("Invalid value, please re-enter!\n");
					}	
				} while (value_2 != 0);
    		}
		}
	} while (value_1 < 0 || value_1 > count);
}



void command_screen()
{
	// Add cluster number of RDET = 0
	AddNodeHeader(0);
	while (1)
	{
		// command by cluster number manage by linklist lib, add first node while enter a folder, and delete fisrt node when back folder -> present folder's cluster number is first node
		// check if cluster number = 0 (RDET)
		if (ReadNodeHeader() == 0)
		{
			command_RDET();
		}
		else
		{
			command_folder(ReadNodeHeader());
		}
	}
}


