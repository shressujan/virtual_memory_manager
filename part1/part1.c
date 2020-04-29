/****************************************************************
 *
 * Author: Sujan
 * Title: Designing a Virtual Memory Manager
 * Date: 2020-04-20
 * Description: In this programming assignment we will be implementing a virtual memory manager.
 *
 ****************************************************************/

#include "part1.h"


void get_page_and_offset(int logical_address, int *page_num, int *offset) {
    // Shifting the bits to right 8 times to get the page number
    *page_num = ((logical_address & LOGICAL_ADDRESS_MASK) >> 8);
    *offset = logical_address & OFFSET_MASK;
}

int get_frame_TLB(int page_num) {
    for (int i = 0; i < TLB_SIZE; i++) {
        if (TLB[i][0] == page_num) {
            num_TLB_hits++;
            return TLB[i][1];
        }
    }
    return NOT_FOUND;
}


int get_frame_pageTable(int page_num) {
    for (int i = 0; i < PAGE_TABLE_SIZE; i++) {
        if (PAGE_TABLE[i][0] == page_num) {
            return PAGE_TABLE[i][1];
        }
    }
    return NOT_FOUND;
}

int get_available_frame() {
    return frame;
}

//good
void backing_store_to_memory(int page_num, int frame_num, const char *fname) {
    FILE *backing_store_file = fopen(fname, "rb");
    if (fseek(backing_store_file, page_num * PAGE_TABLE_SIZE, SEEK_SET) != 0) {
        fprintf(stderr, "Error seeking in backing store file\n");
    }
    signed char *buffer = (signed char *) malloc(sizeof(signed char) * PAGE_TABLE_SIZE);
    if (fread(buffer, sizeof(signed char), PAGE_TABLE_SIZE, backing_store_file) == 0) {
        fprintf(stderr, "Error reading from backing store file\n");
    }
    // Copy the content of value into PHYSICAL_MEMORY
    for (int i = 0; i < FRAME_SIZE; ++i) {
        PHYSICAL_MEMORY[frame_num][i] = buffer[i];
    }
    free(buffer);
    fclose(backing_store_file);
}

void update_page_table(int page_num, int frame_num) {
    for (int i = 0; i < PAGE_TABLE_SIZE; i++) {
        if (PAGE_TABLE[i][0] == -1) {
            PAGE_TABLE[i][0] = page_num;
            PAGE_TABLE[i][1] = frame_num;
            break;
        }
    }
}

void update_TLB(int page_num, int frame_num) {
    int i;
    for (i = 0; i < TLB_SIZE; ++i) {
        if (TLB[i][0] == -1) {
            TLB[i][0] = page_num;
            TLB[i][1] = frame_num;
            break;
        }
        // If last index in TLB
        if (i == TLB_SIZE -1) {
            for (int j = 0; j < i; ++j) {
                TLB[j][0] = TLB[j+1][0];
                TLB[j][1] = TLB[j+1][1];
            }
            TLB[i][0] = page_num;
            TLB[i][1] = frame_num;
            break;
        }
        // IF page_num found somewhere in TLB, update the position to most recent
        if(TLB[i][0] == page_num) {
            int j;
            for (j = i; j < TLB_SIZE -1; ++j) {
                TLB[j][0] = TLB[j+1][0];
                TLB[j][1] = TLB[j+1][1];
            }
            TLB[j][0] = page_num;
            TLB[j][1] = frame_num;
        }
    }

}

/******************************************************
 * Assumptions:
 *   If you want your solution to match follow these assumptions
 *   1. In Part 1 is is assumed memory is large enough to accommodate
 *      all frames -> no need for frame replacement
 *   2. Part 1 solution uses FIFO for TLB updates
 *   3. In the solution binaries it is assumed a starting point at frame 0,
 *      subsequently, assign frames sequentially
 ******************************************************/

int main(int argc, char **argv) {

    if (argc != 3) {
        fprintf(stderr, "Usage %s backing_store_file address_file\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    const char *backing_file = argv[1];
    FILE *address_file = fopen(argv[2], "r");
    if (address_file == NULL) {
        printf("Error opening the address file!\n");
        exit(EXIT_FAILURE);
    }

    FILE *output_file = fopen("correct.txt", "w+");
    if (output_file == NULL) {
        printf("Error opening correct.txt!\n");
        exit(EXIT_FAILURE);
    }

    // Initialization of TLB
    for (int i = 0; i < TLB_SIZE; i++) {
        TLB[i][0] = -1;
        TLB[i][1] = -1;
    }
    // Initialization of PAGE_TABLE
    for (int i = 0; i < PAGE_TABLE_SIZE; i++) {
        PAGE_TABLE[i][0] = -1;
        PAGE_TABLE[i][1] = -1;
    }
    //Initialization of PHYSICAL_MEMORY
    for (int i = 0; i < PHYSICAL_MEMORY_SIZE; ++i) {
        for (int j = 0; j < FRAME_SIZE; ++j) {
            PHYSICAL_MEMORY[i][j] = -1;
        }
    }

    char address[BUFFER_SIZE];
    // Looping through the address file until empty
    while (fgets(address, BUFFER_SIZE, address_file) != NULL) {
        int logical_address = atoi(address); //convert char to integer
        get_page_and_offset(logical_address, &page_num, &offset); // getting page number and offset from given logical address
        frame_num = get_frame_TLB(page_num); //getting frame number from TLB if present
        if (frame_num == NOT_FOUND) {
            frame_num = get_frame_pageTable(page_num);
            if (frame_num == NOT_FOUND) { //Page fault occurs
                frame_num = get_available_frame();
                backing_store_to_memory(page_num, frame_num, backing_file);
                update_page_table(page_num, frame_num);
                frame++;
                num_page_fault++;
            }
            update_TLB(page_num, frame_num);
        }

        int value = PHYSICAL_MEMORY[frame_num][offset];
        fprintf(output_file, "Virtual address: %d Physical address: %d Value: %d\n", logical_address,
                (frame_num << 8) | offset, value);
        num_addr_translated++;
    }
    fclose(address_file);
    fprintf(output_file, "Number of Translated Addresses = %d\n", num_addr_translated);
    fprintf(output_file, "Page Faults = %d\n", num_page_fault);
    fprintf(output_file, "Page Fault Rate = %.3f\n", num_page_fault / (double) num_addr_translated);
    fprintf(output_file, "TLB Hits = %d\n", num_TLB_hits);
    fprintf(output_file, "TLB Hit Rate = %.3f\n", num_TLB_hits / (double) num_addr_translated);

    fclose(output_file);
    return NO_ERROR;
}
