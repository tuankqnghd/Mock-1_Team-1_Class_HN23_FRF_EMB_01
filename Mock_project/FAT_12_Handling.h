#ifndef _FAT_12_HANDLING_H
#define _FAT_12_HANDLING_H
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
	uint8_t number_bytes_per_sectors[2];                 //512 			 
	uint8_t number_secters_per_cluster[1];	  		     //01	  SL sector cua cluster	
	uint8_t number_reserved_sector[2];					 //01     SL sector truoc bang FAT		
	uint8_t number_FATs[1];								 //02     SL bang FAT	
	uint8_t number_root_entry[2];						 //224	  SL root directory entry	 
	uint8_t number_total_sectors[2];					 //2880   SL sector cua o dia, neu bang 0 thi doc 0x20
	uint8_t media[1]; 												
	uint8_t number_sectors_per_FAT[2];					 //9	  SL sector cua bang FAT
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

Boot_block boot_block_data;

static Boot_block * Ptr = &boot_block_data;

/*
* @brief add node data to the end of linklist
*
*@param inputdata is input data to new node
*
*@return void
*/
void boot_block_read(FILE* file);


/*
* @brief add node data to the head of linklist
*
*@param inputdata is input data to new node
*
*@return void
*/
uint32_t convert(uint8_t a[], size_t size);



/*
* @brief delete the last node data of linklist
*
*@return void
*/
void print_entry(uint8_t* data[]);



/*
* @brief delete the last node data of linklist
*
*@return void
*/
void print_data(uint16_t cluster, uint32_t size);

#endif




