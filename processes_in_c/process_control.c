/**
 * This is a program for process creation and termination. Multiple child processes created from one parent process 
 * child processes print "hello" together with their PIDS, then exit. Uses fork() and wait().
*/
 //headers go here
#include <stdio.h> 
#include <stdlib.h> 
#include <sys/types.h> 
#include <sys/wait.h> 
#include <unistd.h> 

//program functions
//main, parent, child
void parent(int args){ //this function is a parent that creates a child
    int pid;//process id
    int i;
    i = 0; i <args; i ++;
    while(1){
        pid = fork(); //create a child process then print a message with PID
        do{
            printf("Hello. My PID is %d\n", getpid());
            exit(1);
        }while(pid == 0);
        do{
            printf("Failed to create child process");
            exit(2);
        }while (pid < 0);
        do{
            wait(NULL);
        }while (pid != 0 || pid != -1);
    }
}

void childprocess(int args){
    int pid;
    int i; //process id
    i = 0; i <args; i ++;
    while(1){
        pid=fork();
        do{
            wait(NULL);
            break;
        }while(pid > 0);
        do{
            printf("failed to create child");
            exit(2);
        }while(pid < 0);
        do{
            printf("Hello. My PID is %d\n", getpid());
        }while(pid == 0);
    }

}

int main(int argc, char**argv){
    if (argc==1){ // if no arguments are given
    printf("Kindly provide the command line argument of 1 integer\n");
    return 0; // exit the program
  }

  int arg = atoi(argv[1]); // convert the argument to an integer
  if (arg<1){ // if the argument is less than 1
  printf("Provide an integer greater than 0\n");
  exit(0); // exit the program
  }

  /**
   * call parent and childprocess functions
  */
  parent(arg); 
  childprocess(arg); 

  return 0;
}