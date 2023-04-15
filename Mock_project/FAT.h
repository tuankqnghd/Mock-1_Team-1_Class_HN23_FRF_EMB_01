#ifndef _FAT_H
#define _FAT_H
#include <stdint.h>

/********************************************************************
 * Include Library
********************************************************************/

/********************************************************************
 * API
********************************************************************/

typedef struct {
	uint8_t part[3];
	uint8_t manufacturer_description[8];
	uint8_t number_bytes_per_sectors[2];	//512	SL byte tren sector		 
	uint8_t number_secters_per_cluster[1];	//01	SL sector cua cluster	
	uint8_t number_reserved_sector[2];		//01	SL sector truoc bang FAT		
	uint8_t number_FATs[1];					//02	SL bang FAT	
	uint8_t number_root_entry[2];			//224	SL root directory entry	 
	uint8_t number_total_sectors[2];		//2880	SL sector cua o dia, neu bang 0 thi doc 0x20
	uint8_t media[1]; 												
	uint8_t number_sectors_per_FAT[2];		//9		SL sector cua bang FAT
	uint8_t number_sectors_per_track[2];	//18
	uint8_t number_heads[2];				//02
	uint8_t number_hidden_blocks[4];		//0
	uint8_t number_2_total_sectors[4];		//0
	uint8_t number_physical_drive[2];		//0
	uint8_t extended_signnature[1];
	uint8_t volume_ID[4];
	uint8_t volume_label[11];
	uint8_t file_system_identifier[8];
	uint8_t remainder[0x1c0];
	uint8_t signature[2];
} Boot_block;

typedef struct {
	uint8_t name[8];
	uint32_t size;
	uint8_t type[3];
	uint8_t day;
	uint8_t month;
	uint16_t year;
	uint8_t second;
	uint8_t minute;
	uint8_t hour;
} Entry;

typedef struct {
	uint32_t VBS;
	uint32_t FAT;
	uint32_t RDET;
	uint32_t DATA;
} FAT12_Address;

typedef union 
{
	struct date
	{
		uint16_t d : 5;
		uint16_t m : 4;
		uint16_t y : 7;
	}fdate;
	uint16_t data;
}DATE;

typedef union 
{
	struct time
	{
		uint16_t s : 5;
		uint16_t m : 6;
		uint16_t h : 5;
	}ftime;
	uint16_t data;
}TIME;



/*
* @brief read boot block and calculate all address
*
*@param inputdata is file pointer need to read
*
*@return struct boot_block_data with value of each parameter and struct address
*/
void boot_block_read();



/*
* @brief convert number
*
*@param inputdata a is a uint8_t array 
*@param inputdata size is size of array a 
*
*@return value after convert 
*/
uint32_t convert(uint8_t a[], size_t size);



/*
* @brief calculate address cluster by cluster order
*
*@param inputdata cluster_order is cluster number 
*
*@return address of cluster
*/
uint32_t cluster_address(uint32_t cluster_order);



/*
* @brief read the cluster entry of a entry 32 bytes
*
*@param inputdata a is uint8_ t array[32] contains entry  
*
*@return number of cluster try
*/
uint32_t cluster_entry(uint8_t a[]);



/*
* @brief read the FAT table to define the next cluster
*
*@param inputdata present_cluster is present cluster
*
*@return next cluster of present cluster
*/
uint32_t cluster_next(uint32_t present_cluster);



/*
* @brief read the size entry of a entry 32 bytes
*
*@param inputdata a is uint8_ t array[32] contains entry  
*
*@return size of file entry
*/
uint32_t size_entry(uint8_t a[]);



/*
* @brief print file name of a entry 32 bytes 
*
*@param inputdata data is uint8_ t array[32] contains entry  
*
*@return void print to command
*/
void Filename(uint8_t data[]);



/*
* @brief print size file of a entry 32 bytes 
*
*@param inputdata data is uint8_ t array[32] contains entry  
*
*@return void print to command
*/
void Sizefile(uint8_t data[]);



/*
* @brief print type file of a entry 32 bytes 
*
*@param inputdata data is uint8_ t array[32] contains entry  
*
*@return void print to command
*/
void Typefile(uint8_t data[]);



/*
* @brief print date modified file of a entry 32 bytes 
*
*@param inputdata data is uint8_ t array[32] contains entry  
*
*@return void print to command
*/
void Date(uint8_t data[]);



/*
* @brief print time modified file of a entry 32 bytes 
*
*@param inputdata data is uint8_ t array[32] contains entry  
*
*@return void print to command
*/
void Time(uint8_t data[]);

void openfile(char* filename);

void closefile();

Entry get_entry(uint8_t data[]);

FILE* get_file_ptr();

Boot_block get_boot_block_data();

FAT12_Address get_address();

#endif
