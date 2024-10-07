///////////////////////////////////////////////////////////////////////////////
//
// Copyright 2020-2023 Deb Deppeler based on work by Jim Skrentny
// Posting or sharing this file is prohibited, including any changes/additions.
// Used by permission FALL 2023, CS354-deppeler
//
///////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// Main File:        p3Heap.c
// This File:        p3Heap.c
// Other Files:      log-p3b.pdf
// Semester:         CS 354 Lecture 002 Fall 2023
// Instructor:       deppeler
// 
// Author:           Sidney Heberlein
// Email:            sheberlein@wisc.edu
// CS Login:         sidney
//
///////////////////////////  WORK LOG  //////////////////////////////
//  Document your work sessions on your copy http://tiny.cc/work-log
//  Download and submit a pdf of your work log for each project.
/////////////////////////// OTHER SOURCES OF HELP ////////////////////////////// 
// Persons:          none
//
// Online sources:   https://www.guru99.com/c-bitwise-operators.html?fbclid=IwAR
// 1ZC7eABnySHyf93aS7QC0Vgq5EkWM5cgbybL19yvkfbLgTRgjVRq-YJD0_aem_AfdlSCafzAD5aul
// cCQ5BN661lWz5d4uXeXXVMacBHNKXsT4qn6jL3cY3QyIVhO7pHc0
// the above site helped me understand bitwise operators in c (& and |) 
//
// AI chats:         none
//////////////////////////// 80 columns wide ///////////////////////////////////


#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdio.h>
#include <string.h>
#include "p3Heap.h"

/*
 * This structure serves as the header for each allocated and free block.
 * It also serves as the footer for each free block.
 */
typedef struct blockHeader {           

    /*
     * 1) The size of each heap block must be a multiple of 8
     * 2) heap blocks have blockHeaders that contain size and status bits
     * 3) free heap block contain a footer, but we can use the blockHeader 
     *.
     * All heap blocks have a blockHeader with size and status
     * Free heap blocks have a blockHeader as its footer with size only
     *
     * Status is stored using the two least significant bits.
     *   Bit0 => least significant bit, last bit
     *   Bit0 == 0 => free block
     *   Bit0 == 1 => allocated block
     *
     *   Bit1 => second last bit 
     *   Bit1 == 0 => previous block is free
     *   Bit1 == 1 => previous block is allocated
     * 
     * Start Heap: 
     *  The blockHeader for the first block of the heap is after skip 4 bytes.
     *  This ensures alignment requirements can be met.
     * 
     * End Mark: 
     *  The end of the available memory is indicated using a size_status of 1.
     * 
     * Examples:
     * 
     * 1. Allocated block of size 24 bytes:
     *    Allocated Block Header:
     *      If the previous block is free      p-bit=0 size_status would be 25
     *      If the previous block is allocated p-bit=1 size_status would be 27
     * 
     * 2. Free block of size 24 bytes:
     *    Free Block Header:
     *      If the previous block is free      p-bit=0 size_status would be 24
     *      If the previous block is allocated p-bit=1 size_status would be 26
     *    Free Block Footer:
     *      size_status should be 24
     */
    int size_status;

} blockHeader;         

/* Global variable - DO NOT CHANGE NAME or TYPE. 
 * It must point to the first block in the heap and is set by init_heap()
 * i.e., the block at the lowest address.
 */
blockHeader *heap_start = NULL;     

/* Size of heap allocation padded to round to nearest page size.
 */
int alloc_size;

/*
 * Additional global variables may be added as needed below
 * TODO: add global variables needed by your function
 */

// this is the end of the heap
blockHeader *heap_end = NULL;



/* 
 * Function for allocating 'size' bytes of heap memory.
 * Argument size: requested size for the payload
 * Returns address of allocated block (payload) on success.
 * Returns NULL on failure.
 *
 * This function must:
 * - Check size - Return NULL if size < 1 
 * - Determine block size rounding up to a multiple of 8 
 *   and possibly adding padding as a result.
 *
 * - Use BEST-FIT PLACEMENT POLICY to chose a free block
 *
 * - If the BEST-FIT block that is found is exact size match
 *   - 1. Update all heap blocks as needed for any affected blocks
 *   - 2. Return the address of the allocated block payload
 *
 * - If the BEST-FIT block that is found is large enough to split 
 *   - 1. SPLIT the free block into two valid heap blocks:
 *         1. an allocated block
 *         2. a free block
 *         NOTE: both blocks must meet heap block requirements 
 *       - Update all heap block header(s) and footer(s) 
 *              as needed for any affected blocks.
 *   - 2. Return the address of the allocated block payload
 *
 *   Return if NULL unable to find and allocate block for required size
 *
 * Note: payload address that is returned is NOT the address of the
 *       block header.  It is the address of the start of the 
 *       available memory for the requesterr.
 *
 * Tips: Be careful with pointer arithmetic and scale factors.
 */
void* balloc(int size) {     
    // check the size - return NULL if size < 1
    if (size < 1)
    {
      return NULL;
    }
    int actual_size = size + sizeof(blockHeader);
    while (actual_size % 8 != 0)
    {
      actual_size += 1;
    }    
    // for best fit, we start at the beginning of the heap.
    blockHeader *current = heap_start;

    // stores the size_status of the current block
    int curr_size_status;    

    // stores the size of the memory block of the current block
    int curr_size;

    // a new blockHeader to keep track of the previous best fit memory block
    blockHeader *keepTrackOf = NULL;
    // stores the size_status of the current block
    int keep_size_status;

    // stores the size of the memory block to keep track of
    int keep_size;

    // this stores the difference between the block's size and the size needed to alloc
    int keep_size_difference;

    // find the best fit free block first
    while (current->size_status != 1)
    {
      curr_size_status = current->size_status;      
      // extract just the current size
      curr_size = curr_size_status & 0xFFF8;
      if (curr_size_status & 1)
      {
        // the a-bit is 1, so the block is allocated already, so we don't use it
        current = (blockHeader*)((char*)current + curr_size);
        continue;
      }
      else
      {
        // else, the block is free, so we can potentially use it
        if (curr_size == actual_size)
        {
          // stop early if there is an exact size match
          keepTrackOf = current;
          break;
        }
        else if (curr_size > actual_size)
        {
          // the block is big enough! now we need to figure out if it's a better fit
          if (keepTrackOf == NULL || ((curr_size - actual_size) < keep_size_difference))
          {
            // update the previous block - we've found a better fit
            keepTrackOf = current;
            // update the difference between the size and size needed
            keep_size_difference = curr_size - actual_size;
          }
        }
      }
      // update the current block header to store the next block of memory
      current = (blockHeader*)((char*)current + curr_size);
    }
     
    // if no best fit is found, return NULL.
    if (keepTrackOf == NULL)
    {
      return NULL;
    }    
    // update the best fit block's size
    keep_size_status = keepTrackOf->size_status;
    keep_size = keep_size_status & 0xFFF8;

    // keep track of the p-bit of keep_size_status
    int keep_p_bit = keep_size_status & 0x0002;
    // after we find the best fit block, check its size and split if the remaining block
    // is at least 8 bytes
    if (keep_size >= actual_size + 8)
    {
      blockHeader *newBlock = (blockHeader*)((char*)keepTrackOf + actual_size);
      newBlock->size_status = keep_size - actual_size;
      // add 2 since the previous block is allocated (changes p bit to 1)
      newBlock->size_status += 2;

      keepTrackOf->size_status = actual_size;
      keepTrackOf->size_status += keep_p_bit;
      blockHeader *nextFooter = (blockHeader*)((char*)keepTrackOf + actual_size - sizeof(blockHeader));
      nextFooter->size_status = newBlock->size_status & 0xFFF8;
    }
    keepTrackOf->size_status += 1;

     // we need to make sure the p-bit of the next block is 1
     keep_size_status = keepTrackOf->size_status;
     keep_size = keep_size_status & 0xFFF8;
     blockHeader* next_block = (blockHeader*)((char*)keepTrackOf + keep_size);
     if (next_block->size_status != 1)
     {
       next_block->size_status = next_block->size_status & 0xFFFD;
       next_block->size_status += 2;
     }


    keepTrackOf = (blockHeader*)((char*)keepTrackOf + sizeof(blockHeader));

    return keepTrackOf;
} 

/* 
 * Function for freeing up a previously allocated block.
 * Argument ptr: address of the block to be freed up.
 * Returns 0 on success.
 * Returns -1 on failure.
 * This function should:
 * - Return -1 if ptr is NULL.
 * - Return -1 if ptr is not a multiple of 8.
 * - Return -1 if ptr is outside of the heap space.
 * - Return -1 if ptr block is already freed.
 * - Update header(s) and footer as needed.
 *
 * If free results in two or more adjacent free blocks,
 * they will be immediately coalesced into one larger free block.
 * so free blocks require a footer (blockHeader works) to store the size
 *
 * TIP: work on getting immediate coalescing to work after your code 
 *      can pass the tests in partA and partB of tests/ directory.
 *      Submit code that passes partA and partB to Canvas before continuing.
 */                    
int bfree(void *ptr) {    
    //TODO: Your code goes in here.
    if (ptr == NULL)
    {
      return -1;
    }
    if (*(int*)ptr % 8 != 0)
    {
      return -1;
    }
    // we need to find the end of the heap.
    heap_end = (blockHeader*)((char*)heap_start + alloc_size);
    if ((char*)ptr < (char*)heap_start || (char*)ptr > (char*)heap_end)
    {
      return -1;
    }
    
    // first we need to free the block of memory pointed to by ptr

    // this points to the header of the block to be freed
    blockHeader *headerPointer = (blockHeader*)((char*)ptr - sizeof(blockHeader));
    // check if the block is already freed
    if ((headerPointer->size_status & 0x0001) == 0)
    {
      return -1;
    }

    // this is the size of the block to be freed
    int curr_size = headerPointer->size_status & 0xFFF8;
    // now we need to update the header of the block we are freeing
    headerPointer->size_status -= 1;
    // now we need to update the footer of the block we are freeing
    blockHeader * footerPointer = (blockHeader*)((char*)ptr - sizeof(blockHeader) + (curr_size - sizeof(blockHeader)));
    footerPointer->size_status = curr_size;
    // now, update the p-bit of the header of the next block (if it's not the end mark)
    blockHeader * nextHeader = (blockHeader*)((char*)ptr - sizeof(blockHeader) + curr_size);
    if (nextHeader->size_status != 1)
    {
      nextHeader->size_status -= 2;
    }


    // now, implement immediate coalescing

     // coalesce right, if possible
     int next_a_bit = nextHeader->size_status & 0x0001;
 
     if (next_a_bit == 0 && nextHeader->size_status != 1)
     {
       // the size of the next block
       int next_size = nextHeader->size_status & 0xFFF8;
 
       // the footer of the next block
       blockHeader *nextFooter = (blockHeader*)((char*)nextHeader + (next_size - sizeof(blockHeader)));
 
       int newSize = next_size + (headerPointer->size_status & 0xFFF8);
       int prev_p_bit = headerPointer->size_status & 0x0002;
       // update the footer of the new big block
       nextFooter->size_status = newSize;
       // update the header of the new free block
       headerPointer->size_status = newSize + prev_p_bit;

       // update curr_size
       curr_size = newSize;
 
       // we need to update ptr
       ptr = (blockHeader*)((char*)headerPointer + sizeof(blockHeader));
       headerPointer = (blockHeader*)((char*)ptr - sizeof(blockHeader));
       // the p-bit of the next block should already be 0.
      }

  
    // now, coalesce left, if possible
    headerPointer = (blockHeader*)((char*)ptr - sizeof(blockHeader));    
    if ((headerPointer->size_status & 0x0002) == 0)
   {
    // get the previous footer to tell us the size of the previous block
    blockHeader *prevFooter = (blockHeader*)((char*)ptr - sizeof(blockHeader*) - sizeof(blockHeader));
    int prevSize = prevFooter->size_status & 0xFFF8;
    // get the header of the previous block
    blockHeader *prevHeader = (blockHeader*)((char*)ptr - sizeof(blockHeader) - prevSize);

    int prev_p_bit = prevHeader->size_status & 0x0002;
    // update the header of the new free block (the previous block)
    int newSize = prevSize + curr_size;
    prevHeader->size_status = newSize + prev_p_bit;

    // change the footer of the current block
    footerPointer->size_status = newSize;
    // update curr_size
    curr_size = newSize;

    // the p-bit of the next block should already be 0.

    // we need to update ptr
    ptr = (blockHeader*)((char*)prevHeader + sizeof(blockHeader));
    headerPointer = (blockHeader*)((char*)ptr - sizeof(blockHeader));
   }

    return 0;
} 


/* 
 * Initializes the memory allocator.
 * Called ONLY once by a program.
 * Argument sizeOfRegion: the size of the heap space to be allocated.
 * Returns 0 on success.
 * Returns -1 on failure.
 */                    
int init_heap(int sizeOfRegion) {    

    static int allocated_once = 0; //prevent multiple myInit calls

    int   pagesize; // page size
    int   padsize;  // size of padding when heap size not a multiple of page size
    void* mmap_ptr; // pointer to memory mapped area
    int   fd;

    blockHeader* end_mark;

    if (0 != allocated_once) {
        fprintf(stderr, 
                "Error:mem.c: InitHeap has allocated space during a previous call\n");
        return -1;
    }

    if (sizeOfRegion <= 0) {
        fprintf(stderr, "Error:mem.c: Requested block size is not positive\n");
        return -1;
    }

    // Get the pagesize from O.S. 
    pagesize = getpagesize();

    // Calculate padsize as the padding required to round up sizeOfRegion 
    // to a multiple of pagesize
    padsize = sizeOfRegion % pagesize;
    padsize = (pagesize - padsize) % pagesize;

    alloc_size = sizeOfRegion + padsize;

    // Using mmap to allocate memory
    fd = open("/dev/zero", O_RDWR);
    if (-1 == fd) {
        fprintf(stderr, "Error:mem.c: Cannot open /dev/zero\n");
        return -1;
    }
    mmap_ptr = mmap(NULL, alloc_size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
    if (MAP_FAILED == mmap_ptr) {
        fprintf(stderr, "Error:mem.c: mmap cannot allocate space\n");
        allocated_once = 0;
        return -1;
    }

    allocated_once = 1;

    // for double word alignment and end mark
    alloc_size -= 8;

    // Initially there is only one big free block in the heap.
    // Skip first 4 bytes for double word alignment requirement.
    heap_start = (blockHeader*) mmap_ptr + 1;

    // Set the end mark
    end_mark = (blockHeader*)((void*)heap_start + alloc_size);
    end_mark->size_status = 1;

    // Set size in header
    heap_start->size_status = alloc_size;

    // Set p-bit as allocated in header
    // note a-bit left at 0 for free
    heap_start->size_status += 2;

    // Set the footer
    blockHeader *footer = (blockHeader*) ((void*)heap_start + alloc_size - 4);
    footer->size_status = alloc_size;

    return 0;
} 

/* STUDENTS MAY EDIT THIS FUNCTION, but do not change function header.
 * TIP: review this implementation to see one way to traverse through
 *      the blocks in the heap.
 *
 * Can be used for DEBUGGING to help you visualize your heap structure.
 * It traverses heap blocks and prints info about each block found.
 * 
 * Prints out a list of all the blocks including this information:
 * No.      : serial number of the block 
 * Status   : free/used (allocated)
 * Prev     : status of previous block free/used (allocated)
 * t_Begin  : address of the first byte in the block (where the header starts) 
 * t_End    : address of the last byte in the block 
 * t_Size   : size of the block as stored in the block header
 */                     
void disp_heap() {     

    int    counter;
    char   status[6];
    char   p_status[6];
    char * t_begin = NULL;
    char * t_end   = NULL;
    int    t_size;

    blockHeader *current = heap_start;
    counter = 1;

    int used_size =  0;
    int free_size =  0;
    int is_used   = -1;

    fprintf(stdout, 
            "*********************************** HEAP: Block List ****************************\n");
    fprintf(stdout, "No.\tStatus\tPrev\tt_Begin\t\tt_End\t\tt_Size\n");
    fprintf(stdout, 
            "---------------------------------------------------------------------------------\n");

    while (current->size_status != 1) {
        t_begin = (char*)current;
        t_size = current->size_status;

        if (t_size & 1) {
            // LSB = 1 => used block
            strcpy(status, "alloc");
            is_used = 1;
            t_size = t_size - 1;
        } else {
            strcpy(status, "FREE ");
            is_used = 0;
        }

        if (t_size & 2) {
            strcpy(p_status, "alloc");
            t_size = t_size - 2;
        } else {
            strcpy(p_status, "FREE ");
        }

        if (is_used) 
            used_size += t_size;
        else 
            free_size += t_size;

        t_end = t_begin + t_size - 1;

        fprintf(stdout, "%d\t%s\t%s\t0x%08lx\t0x%08lx\t%4i\n", counter, status, 
                p_status, (unsigned long int)t_begin, (unsigned long int)t_end, t_size);

        current = (blockHeader*)((char*)current + t_size);
        counter = counter + 1;
    }

    fprintf(stdout, 
            "---------------------------------------------------------------------------------\n");
    fprintf(stdout, 
            "*********************************************************************************\n");
    fprintf(stdout, "Total used size = %4d\n", used_size);
    fprintf(stdout, "Total free size = %4d\n", free_size);
    fprintf(stdout, "Total size      = %4d\n", used_size + free_size);
    fprintf(stdout, 
            "*********************************************************************************\n");
    fflush(stdout);

    return;  
} 


// end p3Heap.c (Fall 2023)                                         

