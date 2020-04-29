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

#define BUFFER_SIZE 10
#define LOGICAL_ADDRESS_MASK 0xFFFF
#define OFFSET_MASK 0xFF

#define PAGE_TABLE_SIZE 256
#define FRAME_SIZE 256
#define PHYSICAL_MEMORY_SIZE 128
#define TLB_SIZE 16

const char *FIFO = "fifo";
const char *LRU = "lru";

int TLB[TLB_SIZE][2];
int PAGE_TABLE[PAGE_TABLE_SIZE][2];
int PHYSICAL_MEMORY[PHYSICAL_MEMORY_SIZE][FRAME_SIZE];

int page_num, frame_num;
int offset, num_page_fault = 0, frame = 0, num_addr_translated = 0, num_TLB_hits = 0;

char strategy[5];

typedef enum {
    NO_ERROR, NOT_FOUND = -1
}error;

/******************************************************
 * Function Declarations
 ******************************************************/


/**
 * function to extract the page number and offset from the given address integer
 * Uses Bit Masking and Bit Shifting concept
 * @param logical_address
 * @param page_num
 * @param offset
 */
void get_page_and_offset(int logical_address, int* page_num, int* offset);

/***********************************************************
 * Function: get_frame_TLB - tries to find the frame number in the TLB
 * Parameters: page_num
 * Return Value: the frame number, else NOT_FOUND if not found
 ***********************************************************/
int get_frame_TLB(int page_num);


/***********************************************************
 * Function: get_frame_pagetable - tries to find the frame in the page table
 * Parameters: page_num
 * Return Value: page number, else NOT_FOUND if not found (page fault)
 ***********************************************************/
int get_frame_pageTable(int page_num);

/***********************************************************
 * Function: get_available_frame - get a valid frame
 * Parameters: strategy
 * Return Value: frame number
 ***********************************************************/
int get_available_frame(const char *strategy);

/***********************************************************
 * Function: backing_store_to_memory - finds the page in the backing store and
 *   puts it in memory
 * Parameters: page_num - the page number (used to find the page)
 *   frame_num - the frame number for storing in physical memory
 * Return Value: none
 ***********************************************************/
void backing_store_to_memory(int page_num, int frame_num, const char *fname);

/***********************************************************
 * Function: update_page_table - update the page table with frame info
 * Parameters: page_num, frame_num
 * Return Value: none
 ***********************************************************/
void update_page_table(int page_num, int frame_num);

/***********************************************************
 * Function: update_TLB - update TLB (FIFO)
 * Parameters: page_num, frame_num
 * Return Value: none
 ***********************************************************/
void update_TLB(int page_num, int frame_num);


#endif //PA5_PART1_H
