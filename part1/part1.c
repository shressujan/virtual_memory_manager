/****************************************************************
 *
 * Author: Sujan
 * Title: Designing a Virtual Memory Manager
 * Date: 2020-04-20
 * Description: In this programming assignment we will be implementing a virtual memory manager.
 *
 ****************************************************************/

#include "part1.h"


int* get_pageNum_offset(int address) {
    int logical_address = address & LOGICAL_ADDRESS_MASK;
    // Shifting the bits to right 8 times to get the page number
    int page_num = logical_address >> 8;
    int offset = logical_address & OFFSET_MASK;

    return page_num, offset;
}


void translate_to_physical_address(int page_number, int offset) {
    int frame_number = searchTLB(page_number);
    // In case frame number was not found in the TLB
    if(frame_number == -1) {
        for (int i = 0; i < PAGE_TABLE_SIZE; ++i) {
            // do sth here
        }
        updateTLB(page_number, frame_number);
    }
}

int searchTLB(int page_number) {
    int frame_number = -1; //initialized to certain value
    for (int i = 0; i < TLB_SIZE; ++i) {
        if(tlb[i].page_number == page_number) {
            frame_number = tlb[i].frame_number;
        }
    }

    return frame_number;
}

void updateTLB(int page_number, int frame_number) {

}

/******************************************************
 * Assumptions:
 *   If you want your solution to match follow these assumptions
 *   1. In Part 1 is is assumed memory is large enough to accommodate
 *      all frames -> no need for frame replacement
 *   2. Part 1 solution uses FIFO for TLB updates
 *   3. In the solution binaries it is assumed a starting point at frame 0,
 *      subsequently, assign frames sequentially
 *   4. In Part 2 you should use 128 frames in physical memory
 ******************************************************/

int main(int argc, char ** argv) {

    if(argc < 3) {
        printf("invalid number of arguments!!");
        return INVALID_ARGUMENTS;
    } else if (argc > 3) {
        const char * strategy = argv[3];
        if (strategy != FIFO || strategy != LRU) {
            return INVALID_ARGUMENTS;
        }
    }

    const char * backing_store_file = argv[1];
    const char * address_file = argv[2];

    char temp[BUFFER_SIZE];

    FILE *fp = fopen(address_file, "r");
    if(fp == NULL) {
        printf("error opening the address file");
        return ERROR_OPENING_FILE;
    }

    while(fgets(temp, BUFFER_SIZE, fp) != NULL) {
        int address = atoi(temp);
        int* page_num_offset = get_pageNum_offset(address);
        translate_to_physical_address(page_num_offset[0], page_num_offset[1]);

    }


    fclose(fp);
    return NO_ERROR;
}
