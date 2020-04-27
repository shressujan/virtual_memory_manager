//
// Created by SujanShrestha on 4/20/20.
//

#ifndef PA5_PART1_H
#define PA5_PART1_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/******************************************************
 * Declarations
 ******************************************************/

#define BUFFER_SIZE 7
#define LOGICAL_ADDRESS_MASK 0xFFFF
#define OFFSET_MASK 0x00FF

#define TLB_SIZE 16
#define PAGE_TABLE_SIZE 256
#define FRAME_SIZE 256
#define TOTAL_FRAMES 256

#define FIFO "FIFO"
#define LRU "FRU"

typedef struct TLB{
    int page_number;
    int frame_number;
};

int page_table[PAGE_TABLE_SIZE][2];
struct TLB tlb[TLB_SIZE];
int physical_memory[TOTAL_FRAMES][FRAME_SIZE];

typedef enum {
    NO_ERROR, INVALID_ARGUMENTS, ERROR_OPENING_FILE
}error;



/**
 * function to extract the page number and offset from the given address integer
 * Uses Bit Masking and Bit Shifting concept
 * @param address
 */
int* get_pageNum_offset(int address);

/**
 * function to translate the logical address to physical address based on input parameters
 * @param page_number
 * @param offset
 */
void translate_to_physical_address(int page_number, int offset);

/******************************************************
 * Function Declarations
 ******************************************************/
int readFromBackingStore();

int searchTLB(int page_number);

void updateTLB(int page_number, int frame_number);

#endif //PA5_PART1_H
