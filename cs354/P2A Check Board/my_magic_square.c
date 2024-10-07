///////////////////////////////////////////////////////////////////////////////
// Copyright 2020 Jim Skrentny
// Posting or sharing this file is prohibited, including any changes/additions.
// Used by permission, CS 354 Spring 2022, Deb Deppeler
////////////////////////////////////////////////////////////////////////////////
   
// add your own File Header information here (as provided in p2A or Commenting guide)
////////////////////////////////////////////////////////////////////////////////
// Main File:        my_magic_square.c
// This File:        my_magic_square.c
// Other Files:      log-p2b.pdf
// Semester:         CS 354 Lecture 001 Fall 2023
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
// Online sources:   none
// 
// AI chats:         none
//////////////////////////// 80 columns wide ///////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

// Structure that represents a magic square
typedef struct {
    int size;           // dimension of the square
    int **magic_square; // pointer to heap allocated magic square
} MagicSquare;

/* TODO:
 * Promps the user for the magic square's size, read it,
 * check if it's an odd number >= 3 (if not, display the required
 * error message and exit)
 *
 * return the valid number
 */
int getSize() {
   // prompt user for size
   printf("Enter magic square's size (odd integer >=3)\n");

   // the variable sizeInput will store the size inputted by the user
   int sizeInput;
   // scan for the size input, store it in sizeInput variable
   scanf("%d", &sizeInput); 
   // check if the inputted size is correct
   if (sizeInput % 2 == 0)
     {
       printf("Magic square size must be odd.\n");
       exit(1);
     }
   else if (sizeInput < 3)
     {
       printf("Magic square size must be >= 3.\n");
       exit(1);
     }
   else
    {
      return sizeInput;
    }
} 
   
/* TODO:
 * Makes a magic square of size n,
 * and stores it in a MagicSquare (on the heap)
.*
 * It may use the Siamese magic square algorithm 
 * or alternate from assignment 
 * or another valid algorithm that produces a magic square.
 *
 * n - the number of rows and columns
 *
 * returns a pointer to the completed MagicSquare struct.
 */
MagicSquare *generateMagicSquare(int n) 
{
  // create a 2D array of size n and allocate memory for it
  int **square;
  square = malloc(sizeof(int*)*n);
  if (square == NULL)
  {
    printf("Memory was not allocated correctly.\n");
    exit(1);
  }
  for (int i = 0; i < n; i++)
  {
    *(square + i) = malloc(sizeof(int)*n);
    if (*(square + i) == NULL)
    {
      printf("Memory was not allocated correctly.\n");
      exit(1);
    }
  }

  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      *(*(square + i) + j) = 0;
    }
  }

  // make the magic square with size n
  MagicSquare *currSquare = malloc(sizeof(MagicSquare));
  currSquare->size = n;
  currSquare->magic_square = square;
  // initialize the current row and column we're looking at.
  // this is the first row and the middle column
  int currRow = 0;
  int currCol = n / 2;
  // iterate through all of the numbers that need to be put in the array
  // start at 1 and go through n squared
  for (int i = 1; i <= n*n; i++)
  {
    *(*(currSquare->magic_square + currRow) + currCol) = i;
    // get the next rows and columns
    int nextRow = (currRow - 1 + n) % n;
    int nextCol = (currCol + 1) % n;

    // if the next cell already has a number in it, move one row down
    if (*(*(currSquare->magic_square + nextRow) + nextCol) != 0)
    {
      currRow = (currRow + 1) % n;
    }
    else
    {
      // update currRow and currCol to nextRow and nextCol
      currRow = nextRow;
      currCol = nextCol;
    }
  }
  //free(square);
  return currSquare;    
} 

/* TODO:  
 * Opens a new file (or overwrites the existing file)
 * and writes the magic square values to the file
 * in the specified format.
 *
 * magic_square - the magic square to write to a file
 * filename - the name of the output file
 */
void fileOutputMagicSquare(MagicSquare *magic_square, char *filename) 
{
  // open the new file
  FILE *fp = fopen(filename, "w");
  // check if the file opened correctly.
  if (fp == NULL)
  {
    printf("Can't open file for reading.\n");
    exit(1);
  }
  fprintf(fp, "%d\n", magic_square->size);
  // write the magic square values to the file in the specified format
  for (int i = 0; i < magic_square->size; i++)
  {
    for (int j = 0; j < magic_square->size; j++)
    {
      if (j == (magic_square->size - 1))
      {
        fprintf(fp, "%d\n", *(*(magic_square->magic_square + i) + j));
      }
      else
      {
        fprintf(fp, "%d,", *(*(magic_square->magic_square + i) + j));
      }
    }
  }

  // close the file
  if (fclose(fp) != 0)
  {
    printf("Error while closing the file.\n");
    exit(1);
  }
}


/* TODO:
 * Generates a magic square of the user specified size and
 * outputs the square to the output filename.
 * 
 * The command-line must be as follows: ./my_magic_square <file>
 * where file is the file to write to.
 */
int main(int argc, char **argv) {
    // TODO: Check input arguments to get output filename
    if (argc != 2)
    {
      printf("Number of command-line arguments is incorrect.\n");
      exit(1);
    }
    char* filename = *(argv + 1);

    // TODO: Get magic square's size from user
    int sizeOfSquare;
    sizeOfSquare = getSize();

    // TODO: Generate the magic square by correctly interpreting 
    //       the algorithm(s) in the write-up or by writing or your own.  
    //       You must confirm that your program produces a 
    //       Magic Sqare as described in the linked Wikipedia page.
    MagicSquare *square = generateMagicSquare(sizeOfSquare);

    // TODO: Output the magic square
    fileOutputMagicSquare(square, filename);

    for (int i = 0; i < square->size; i++)
    {
      free(*(square->magic_square + i));
    }
    free(square->magic_square);
    free(square);
    return 0;
} 

//    F23


