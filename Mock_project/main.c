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
	// (root directory number_FATs*number_bytes_per_sectors + 1)*512 = (2*9+1)*512 = 9728 = 0x2600
	print_root_directory(file);
	fclose(file);
}
