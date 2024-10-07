////////////////////////////////////////////////////////////////////////////////
// Main File:        my_c_signal_handler.c
// This File:        send_signal.c
// Other Files:      my_c_signal_handler.c, my_div0_handler.c
// Semester:         CS 354 Lecture 002 Fall 2023
// Grade Group:      g9  (See canvas.wisc.edu/groups for your gg#)
// Instructor:       deppeler
// 
// Author:           Sidney Heberlein
// Email:            sheberlein@wisc.edu
// CS Login:         sidney
//
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
#include <ctype.h>

/*
* This is the main function for this program. It handles two modes: u and i.
* u will send a kill signal with SIGUSR1. i will send a kill signal with SIGINT.
* It calls exit(1) if there was an error.
* 
* argc is the number of arguments passed to the program via the command line
* argv is the array of arguments passed to the program via the command line
*/
int main(int argc, char *argv[])
{
  // number of command lines must be 3
  if (argc != 3)
  {
    printf("Usage: send_signal <signal type> <pid>\n");
    exit(1);
  }
  
  // the next 2 lines get the first command line argument passed (should be u or i)
  char *currsignalptr = argv[1];
  char currsignal = currsignalptr[1];
  
  // currsignal must be either u or i
  if (currsignal != 'u' && currsignal != 'i')
  {
    printf("Usage: send_signal <signal type> <pid>\n");
    exit(1);
  }

  // currpid (below) is the second command line argument passed (the current pid)
  char *currpid = argv[2];

  // we need to check that the pid is a number
  for (int i = 0; i < strlen(currpid); i++)
  {
    if(!isdigit(currpid[i]))
    {
      printf("Usage: send_signal <signal type> <pid>\n");
      exit(1);
    }
  }

  // pidnum (below) is the integer version of the string gotten from the command line, now
  // that we know it is a number
  int pidnum = atoi(currpid);

  // now, which signal should we send?
  if (currsignal == 'u')
  {
    // we are sending a kill signal with SIGUSR1, and we need to check if it works correctly.
    if (kill(pidnum, SIGUSR1) == -1)
    {
      printf("SIGUSR1 not sent properly.\n");
      exit(1);
    }
  }

  if (currsignal == 'i')
  {
    // we are sending a kill signal with SIGINT, and we need to check if it works correctly.
    if (kill(pidnum, SIGINT) == -1)
    { 
      printf("SIGINT not sent properly.\n");
      exit(1);
    }
  }
}
