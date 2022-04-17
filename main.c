#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<readline/readline.h>
#include<readline/history.h>
#include<limits.h>
#include<libgen.h>
#include "cd.c"

#define MAXINPLEN 1000

//COMPILE WITH GCC -Wall -o main main.c -lreadline

char* printDir(){
  char* dir = malloc(512);
  getcwd(dir, sizeof(dir));
  //printf("%s", dir);
  return dir;
  //printf("%s",dirname(dir));
  //printf("%s",basename(dir));
}
char* printMachineAndUser(){
    char* userName = getenv("USER");
    char machineName[HOST_NAME_MAX + 1];
    char* returnValue = malloc(1024);
    gethostname(machineName, HOST_NAME_MAX + 1);
    char dir[1024];
    getcwd(dir, sizeof(dir));
    //printf("%s", dir);
    //printf("\033[37m\033[41m"); // White foreground / Red background
    //printf("\035[0;31mhello, world\033[0m\n"); // prints "hello, world" in red

    //printf("\033[0;32m%s@%s:\033[0;34m~", machineName, userName);
    //printDir();
    //printf("\033[0m$ ");
    //char* dir = printDir();
    strcat(returnValue, "\033[0;32m");
    strcat(returnValue, machineName);
    strcat(returnValue, "@");
    strcat(returnValue, userName);
    strcat(returnValue, ":\033[0;34m~");
    //printf("%s", dir);
    strcat(returnValue, dir);
    strcat(returnValue, "\033[0m$ ");
    //printf("%s", returnValue);

    return returnValue;
}

int main(){

    char* commandInput;
    while(1){
        //printMachineAndUser();
        //commandInput = readline("");
        commandInput = readline(printMachineAndUser());
        //puts(commandInput);

        //if(!strcmp(commandInput, "cd")) cd(end);
        if(strlen(commandInput)>0) add_history(commandInput);
        if (!strcmp(commandInput, "ls")) system("ls");
        else if(!strcmp(commandInput, "clear")) system("clear");
        else if (!strcmp(commandInput, "exit")) break;
    }
    free(commandInput);
    return 0;
  }
