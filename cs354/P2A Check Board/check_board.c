///////////////////////////////////////////////////////////////////////////////
//
// Copyright 2021-23 Deb Deppeler
// Posting or sharing this file is prohibited, including any changes/additions.
//
// We have provided comments and structure for this program to help you get 
// started.  Later programs will not provide the same level of commenting,
// rather you will be expected to add same level of comments to your work.
// 09/20/2021 Revised to free memory allocated in get_board_size function.
// 01/24/2022 Revised to use pointers for CLAs
//
////////////////////////////////////////////////////////////////////////////////
// Main File:        check_board.c
// This File:        check_board.c
// Other Files:      log-p2a.pdf
// Semester:         CS 354 Fall 2023
// Instructor:       Debra Deppeler
//
// Author:           Sidney Heberlein
// Email:            sheberlein@wisc.edu
// CS Login:         sidney
// GG#:              9
//                   (See https://canvas.wisc.edu/groups for your GG number)
//
/////////////////////////// OTHER SOURCES OF HELP //////////////////////////////
//                   Track all work you do in your work log-p2a.pdf
//                   and fully credit all sources of help, including family, 
//                   friends, tutors, Peer Mentors, TAs, and Instructor.
//
// Online sources:   Avoid relying on eeb searches to solve your problems, 
//                   but if you do search, be sure to include Web URLs and 
//                   description of any information you find in your work log.
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *DELIM = ",";  // commas ',' are a common delimiter character for data strings

/* COMPLETED (DO NOT EDIT):       
 * Read the first line of input file to get the size of that board.
 * 
 * PRE-CONDITION #1: file exists
 * PRE-CONDITION #2: first line of file contains valid non-zero integer value
 *
 * fptr: file pointer for the board's input file
 * size: a pointer to an int to store the size
 *
 * POST-CONDITION: the integer whos address is passed in as size (int *) 
 * will now have the size (number of rows and cols) of the board being checked.
 */
void get_board_size(FILE *fptr, int *size) {      
   char *line1 = NULL;
   size_t len = 0;

   if ( getline(&line1, &len, fptr) == -1 ) {
      printf("Error reading the input file.\n");
      free(line1);
      exit(1);
   }

   char *size_chars = NULL;
   size_chars = strtok(line1, DELIM);
   *size = atoi(size_chars);

   // free memory allocated for reading first link of file
   free(line1);
   line1 = NULL;
}



/* TODO:
 * Returns 1 if and only if the board is in a valid Sudoku board state.
 * Otherwise returns 0.
 * 
 * A valid row or column contains only blanks or the digits 1-size, 
 * with no duplicate digits, where size is the value 1 to 9.
 * 
 * Note: p2A requires only that each row and each column are valid.
 * 
 * board: heap allocated 2D array of integers 
 * size:  number of rows and columns in the board
 */
int valid_board(int **board, int size) 
{
  // if the board size is not between 1 and 9, return 0.
  if (size < 1 || size > 9)
  {
    return 0;
  }

  // check that every cell is between 0 and n. If not, return 0.
  for (int col = 0; col < size; col++) 
  {
	for (int row = 0; row < size; row++) 
    {
	  if ((*(*(board + row) + col)) < 0 || (*(*(board + row) + col)) > size)
	  {
	    return 0;
	  }
	 }
   }

  // check each column
  for (int col = 0; col < size; col++) 
  {
	for (int row = 0; row < (size - 1); row++) 
    {
	  // temporary variable holding the current cell we are looking at
	  int currCell = *(*(board + row) + col);
		
      // compare the current cell to every other cell in the column
      for (int i = row + 1; i < size; i++) 
      {
	    if ((currCell != 0) && currCell == (*(*(board + i) + col))) 
        {
		  // duplicate in the column
		  return 0;
	    }
      }
     } 
   }

   // check each row
   for (int row = 0; row < size; row++) 
   {
	 for (int col = 0; col < (size - 1); col++) 
     {
	   // temporary variable holding the current cell we are looking at
       int currCell = *(*(board + row) + col);

	   // compare the current cell to every other cell in the row
     for (int i = col + 1; i < size; i++) 
	 {
	   if ((currCell != 0) && currCell == (*(*(board + row) + i))) 
       {
		 // duplicate in the row
		 return 0;
	   }
     }
	 }
    } 

  // return 1 if the board is valid.
  return 1;
}    



/* TODO: COMPLETE THE MAIN FUNCTION
 * This program prints "valid" (without quotes) if the input file contains
 * a valid state of a Sudoku puzzle board wrt to rows and columns only.
 *
 * A single CLA is required, which is the name of the file 
 * that contains board data is required.
 *
 * argc: the number of command line args (CLAs)
 * argv: the CLA strings, includes the program name
 *
 * Returns 0 if able to correctly output valid or invalid.
 * Only exit with a non-zero result if unable to open and read the file given.
 */
int main( int argc, char **argv ) {              

   // TODO: Check if number of command-line arguments is correct.
   if (argc != 2)
     {
       printf("Number of command-line arguments is incorrect.");
       exit(1);
     }

   // Open the file and check if it opened successfully.
   FILE *fp = fopen(*(argv + 1), "r");
   if (fp == NULL) {
      printf("Can't open file for reading.\n");
      exit(1);
   }

   // Declare local variables.
   int size;

   // TODO: Call get_board_size to read first line of file as the board size.
   
   get_board_size(fp, &size);

   // TODO: Dynamically allocate a 2D array for given board size.
   // DO NOT create a 1D array of ints on the stack or heap
   // You must dyamically create a 1D arrays of pointers to other 1D arrays of ints
   
   // make a 2D array pointer named array.
   int **array;

   // assign array an array of arrays
   array = malloc(sizeof(int*)*(size));

   // check if the memory was allocated correctly
   if (array == NULL)
	 {
	   printf("Memory was not allocated correctly.");
	   exit(1);
	 }

   // assign each element in the array of arrays its own row of integers.
   for (int i = 0; i < size; i++)
	 {
	   *(array + i) = malloc(sizeof(int)*(size));

	   // check if the memory was allocated correctly.
	   if (*(array + i) == NULL)
		{
		  printf("Memory was not allocated correctly.");
		  exit(1);
		}
	 }


   // Read the rest of the file line by line.
   // Tokenize each line wrt the delimiter character 
   // and store the values in your 2D array.
   char *line = NULL;
   size_t len = 0;
   char *token = NULL;
   for (int i = 0; i < size; i++) {

      if (getline(&line, &len, fp) == -1) {
         printf("Error while reading line %i of the file.\n", i+2);
         exit(1);
      }

      token = strtok(line, DELIM);
      for (int j = 0; j < size; j++) {
         // TODO: Complete the line of code below
         // to initialize your 2D array.
         *(*(array + i) + j) = atoi(token);
         token = strtok(NULL, DELIM);
      }
   }

   // TODO: Call the function valid_board and print the appropriate
   //       output depending on the function's return value.
   if (valid_board(array, size) == 1)
	 {
	   printf("valid");
	 }
   else
	 {
	   printf("invalid");
	 }

   // TODO: Free all dynamically allocated memory.
   for (int i = 0; i < size; i++)
	 {
	   free(array[i]);
	 }

   free(array);

   //Close the file.
   if (fclose(fp) != 0) {
      printf("Error while closing the file.\n");
      exit(1);
   } 

   return 0;       
}       

