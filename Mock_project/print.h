#ifndef _PRINT_H
#define _PRINT_H
#include <stdint.h>



/*
* @brief print 1 entry (file name, type, size, date, time created) to screen
*
*@param inputdata data is a aray 32 bytes contain this entry
*
*@return void print to command
*/
void print_entry(uint8_t data[]);



/*
* @brief print data of a file 
*
*@param inputdata cluster is number of cluster which save data
*
*@return void print data to command
*/
void print_data(uint32_t cluster);

void command_RDET();

void command_folder(uint32_t cluster);

void command_screen();

#endif
