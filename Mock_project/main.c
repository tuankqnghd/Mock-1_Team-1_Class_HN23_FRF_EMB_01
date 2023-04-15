#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "Linklist.h"
#include "FAT.h"
#include "print.h"
#pragma pack(1)

// gcc -o main main.c FAT.c Linklist.c print.c
// main C:/Users/LENOVO/Desktop/Mock_project/floppy1.img
int main(int argc, char *argv[]) 
{
	openfile(argv[1]);
	boot_block_read();
	command_screen();
	closefile();
	return 0;
}


//void main() 
//{
//	openfile("floppy1.img");
//	boot_block_read();
//	command_screen();
//	closefile();
//}
