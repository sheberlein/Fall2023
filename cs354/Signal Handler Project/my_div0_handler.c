////////////////////////////////////////////////////////////////////////////////
// Main File:        my_c_signal_handler.c
// This File:        my_div0_handler.c
// Other Files:      my_c_signal_handler.c, send_signal.c
// Semester:         CS 354 Lecture 002 Fall 2023
// Grade Group:      gg9  (See canvas.wisc.edu/groups for your gg#)
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
// Persons:          None
//
// Online sources:   None
// 
// AI chats:         None
//////////////////////////// 80 columns wide ///////////////////////////////////

#include <stdlib.h> 
#include <stdio.h> 
#include <signal.h> 
#include <unistd.h> 
#include <time.h> 
#include <string.h> 
#include <sys/types.h> 

// global variable to keep track of the number of successful divisions
int divops = 0;

/* This is the handler for the SIGFPE that is triggered when there is a divide
* by zero error. It states that the operation was attempted, print the number
* of successful divisions, and then exit(0) instead of crashing.
*/
void handler_SIGFPE()
{
  printf("Error: a division by 0 operation was attempted.\n");
  printf("Total number of operations completed successfully: %i\n", divops);
  printf("The program will be terminated.\n");
  exit(0);
}

/* This is the handler for SIGINT. It responds to the user typing ^C on the
 * command-line. It exits the current program, and also prints the amount of times
 * that a successful division was performed during this execution of the program.
 * it then exits the program..
 */
void handler_INT()
{
  printf("\nTotal number of operations completed successfully: %i\n", divops);
  printf("The program will be terminated.\n");
  exit(0);
}


/* This is the main function for the program. It has an infinite loop to prompt
* the user for numbers to divide. It figures out the result and remainder of the
* division, and counts the number of successful divisions that happened during
* this execution of the program. It can also handle SIGINT and SIGFPE.
*/
int main()
{
  // handler for SIGFPE
  struct sigaction fpe;
  memset(&fpe, 0, sizeof(fpe));
  fpe.sa_handler = handler_SIGFPE;
  
  // check that it was registered correctly
  if (sigaction(SIGFPE, &fpe, NULL) != 0)
  {
    printf("Error biding SIGFPE\n");
    exit(1);
  }

  // code to handle an INT signal is below
  struct sigaction interrupt;
  memset(&interrupt, 0, sizeof(interrupt));
  interrupt.sa_handler = handler_INT;
 
  // check that it was registered correctly
  if (sigaction(SIGINT, &interrupt, NULL) != 0)
  {
    printf("Error handling SIGINT.\n");
    exit(1);
  }

  // infinite loop
  while (1)
  {
    // the first number gotten from the user (the numerator)
    int first;

    // the second number gotten from the user (the denominator)
    int second;

    // get the first integer and convert it
    printf("Enter first integer: ");
    char string1[100];
    if (fgets(string1, 100, stdin) == NULL)
    {
      printf("Could not get the string correctly.\n");
      exit(1);
    }

    // convert the first number string to an integer
    first = atoi(string1);

    // get the second integer and convert it
    printf("Enter second integer: ");
    char string2[100];
    if (fgets(string2, 100, stdin) == NULL)
    {
      printf("Could not get the string correctly.\n");
      exit(1);
    }

    // convert the second number string to an integer
    second = atoi(string2);

    // calculate the result and remainder
    // the result of the division (quotient)
    int result = first / second;

    // the remainder of the division
    int remainder = first % second;

    // print the message and increment the number of successes
    printf("%i / %i is %i with a remainder of %i\n", first, second, result, remainder);

    // increment the number of successful division operations
    divops++;
  }
}
