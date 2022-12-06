/**
 * This is a program for process creation and termination. Multiple child processes created from one parent process 
 * child processes print "hello" together with their PIDS, then exit. Uses fork() and wait().
*/
//Author : S M

/**
 * Logic for process creation:
 * -ve value indicates an error i.e unsuccessful in creating child process
 * 0 ===> child process created
 * +ve value indicates parent process.
*/


//headers go here
#include <stdlib.h> //for atoi() ===> conversion of declared str type to int type
#include <sys/types.h> //pid
#include <stdio.h> //for input output 
#include <sys/wait.h> //wait() system call
#include <unistd.h> //fork() system call

//program functions ===> main, parent, child

int main(int argc, char **argv){ 

   /**
    * prompt to pass command line argument value. 
    * take the number of child processes as an argument when the parent process creates child processes.
    * for this program we will test using 2, 4, 8
    * argc --->command line arguments value
    * argv ---> array
    *
   */
    
  if (argc==1){ 
    printf("Provide the command line argument value greater than 1\n");
    return 0; 
  } //if arguments provided is 1, prompt to provide value greater than 1

  int arg = atoi(argv[1]); // Parse str  value of arguments to int type
  //if arguments provided are lesser than 0, abort program. print error message
  if (arg<1){ 
  printf("Error. Enter a number greater than 0\n");
  exit(0); // exit the program
  }

    /*
        * call parent and child functions here
        * parent(arg) ---> a function that creates child processes
        * child(arg) ---> a function that let's the child process create more processes. While this happens the parent process waits
    */

  parent(arg); 
  child(arg);

  return 0;
}

int parent(int argument){
    printf("\n\nHello. I am a parent creating multiple child processes. These are my children:\n");
    printf("--------------------------------------------------\n");

 
    int pid; // declare process id as int type

    /**
     * a loop that creates a child process. 
     * if child process is created display "Hello. I am a child process. My PID is ----"
     * if child process fails to create display "Failed to create child process"
     */
    
    for(int i=0; i<argument; i++){ 
        pid = fork(); // create a child process
        /**
         * if the process is a child print message, display process ID and then exit.
         * else print error message and exit.
        */
        if (pid==0){ 
        printf("Hello. My PID is %d. I am a child process\n", getpid()); 
        exit(1); 
        }
        else if (pid==-1){ 
        printf("Failed to create child processes\n");
        exit(2); 
        }
        else{
        wait(NULL); // parent process waits for the child process to terminate
        }
    } 
}

int child(int argument){
    printf("\n\nHello. I am a child creating more child processes\n");
    printf("--------------------------------------------------\n");
    int pid; 
    
    for(int i=0; i < argument; i++){ 
        pid = fork(); 
        if (pid > 0){ 
        wait(NULL); 
        break; 
        }
        else if (pid < 0){ 
        printf("Failed to create child processes\n");
        exit(2); 
        }
        else{ 
            printf("Hello. My PID is %d. I am a child process\n", getpid()); 

        }
    }

}