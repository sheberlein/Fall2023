////////////////////////////////////////////////////////////////////////////////
// Main File:        my_c_signal_handler.c
// This File:        my_c_signal_handler.c
// Other Files:      send_signal.c, my_div0_handler.c
// Semester:         CS 354 Lecture 002 Fall 2023
// Grade Group:      g9  (See canvas.wisc.edu/groups for your gg#)
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
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

// this is the number of times SIGUSR1 is recieved
int sigusr1counter = 0;

// number of seconds
int seconds = 5;

/* This is the handler for a SIGALRM. It sets an alarm every 5 seconds, and prints
 * the current process ID and time every 5 seconds.
 *
 * calls exit(1) if the time could not be gotten.
 */
void handler_SIGALRM()
{
  // Get the process ID
  pid_t pid = getpid();

  // Get the current time
  time_t currtime;

  // check for errors on the time
  if (time(&currtime) == -1)
  {
    printf("There was an error getting the time.\n");
    exit(1);
  }

  time(&currtime);
  //struct tm* time_info = localtime(&currtime);

  if (ctime(&currtime) == NULL)
  {
    printf("There was an error getting the time.\n");
    exit(1);
  }

  // Print the process ID and current time
  printf("PID: %d CURRENT TIME: %s", pid, ctime(&currtime));

  // Set a new alarm to go off again in 5 seconds
  alarm(seconds);
}

/* This is the handler for SIGUSR1. It counts the number of times
 * that a SIGUSR1 must be handled. The user will use the kill command
 * on a different terminal window in order to call this signal.
 */
void handler_SIGUSR1()
{
  printf("SIGUSR1 handled and counted!\n");
  
  // increment the counter of the number of SIGUSR1 signals called.
  sigusr1counter ++;
}

/* This is the handler for SIGINT. It responds to the user typing ^C on the
 * command-line. It exits the current program, and also prints the amount of times
 * that SIGUSR1 was called during this execution of the program.
*/
void handler_INT()
{
  printf("\nSIGINT handled.\n");
  printf("SIGUSR1 was handled %d times. Exiting now.\n", sigusr1counter);
  exit(0);
}

/* This is the main function for this program. It registers the signal handlers
 * used above. It calls exit(1) if one of the signal handlers was not registered
 * properly. It starts an infinite loop that will be interrupted by a signal by the user.
 */
int main() 
{

  // code to register SIGALRM signal
  struct sigaction sa;
  memset(&sa, 0, sizeof(sa));
  sa.sa_handler = handler_SIGALRM;

  // check that it was registered correctly
  if (sigaction(SIGALRM, &sa, NULL) != 0)
  {
    printf("Error binding SIGALRM.\n");
    exit(1);
  }

  // set an alarm that will go off 5 seconds later
  alarm(seconds);

  printf("PID and time print every %i seconds.\nType Ctrl-C to end the program.\n", seconds);

  // code to handle a SIGUSR1 is below
  struct sigaction sigusr1struct;
  memset(&sigusr1struct, 0, sizeof(sigusr1struct));
  sigusr1struct.sa_handler = handler_SIGUSR1;

  // check that it was registered correctly
  if (sigaction(SIGUSR1, &sigusr1struct, NULL) != 0)
  {
    printf("Error handling SIGUSR1.\n");
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

  // empty infinite loop
  while (1) {}
}
