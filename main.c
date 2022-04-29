#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<readline/readline.h>
#include<readline/history.h>
#include<limits.h>
#include<libgen.h>
//#include "cd.c"
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/stat.h> //open, O_RDONLY,O_CREAT, etc.
#include<fcntl.h>


#define MAXINPLEN 1000
#define MAXLIST 100

// globals
int pipe_count=0, fd;
static char* args[512];
char *cmd_exec[100];
int flag;
pid_t pid;
int pid, status;
char* output_redirection_file;
int output_redirection = 0;

void clear_variables()
{
  fd =0;
  flag=0;
  pipe_count=0;
  pid=0;
  output_redirection_file = NULL;
  output_redirection = 0;
}

void print_help(){

}


//COMPILE WITH gcc -Wall -o main main.c -lreadline

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

/*
char** arrIntoArrArr(char* arr){
	int counter;
	counter = 0;

	char *tempString, *cpPassedString;
	cpPassedString = malloc(100);
	strcpy(cpPassedString,arr);

	tempString = strtok(cpPassedString," \n");
	char **tempArray = malloc(100);

	while(tempString != NULL){
			tempArray[counter] = malloc(100);
			tempArray[counter] = strdup(tempString);
			tempString = strtok(NULL, " \n");
			++counter;
	}
	//tempArray[counter] = NULL;

	free(cpPassedString);
	return tempArray;
}*/

/*
void execute_command(char* command) {
    int i = 0;
    int argument_count = 0;

    while (command[i] == ' ') {
        i++;
    }
    command = command + i;

    i = 0;

    while (command[i] != '\0') {
         if (command[i] == ' ')
             argument_count++;
         i++;
     }

    char** argv = calloc(argument_count + 2, sizeof(char*));
    char* argument = NULL;
    i = 0;
    while ((argument = strsep(&command, " ")) != NULL) {
       if (strlen(argument) != 0) {
           argv[i] = calloc(strlen(argument) + 1, sizeof(char));
           strncpy(argv[i], argument, strlen(argument));
       }
       i++;
    }
    argv[i] = NULL;

    if (execvp(argv[0], argv) != 0) {
        fprintf(stderr, "Error creating pipe. %s",         strerror(errno));
    }
}*/

void tokenise_commands(char *com_exec) //pretvori prvu komandu u array
{
  int m=1;
  args[0]=strtok(com_exec," ");
  while((args[m]=strtok(NULL," "))!=NULL) m++;
}

char* skipSpace(char* character)
{
  while (isspace(*character)) ++character;
  return character;
}
void tokenise_redirect_output(char *cmd_exec)
{
  char *o_token[100];
  char *new_cmd_exec1;
  new_cmd_exec1=strdup(cmd_exec);
  int m=1;
  o_token[0]=strtok(new_cmd_exec1,">"); //splita komandu citavu na 2 dijela, token[0] je komanda, token[1] je output file
  while((o_token[m]=strtok(NULL,">"))!=NULL) m++;
  o_token[1]=skipSpace(o_token[1]); // > *space* naziv_fajla (izbaci space)
  output_redirection_file=strdup(o_token[1]);
  tokenise_commands(o_token[0]);
}

static int command(int input, int first, int last, char* stringForCheckingRedirect)
{
  int mypipefd[2], output_fd;
  if(pipe(mypipefd)){
		perror("pipe failed");
		return 1;
	}
  pid = fork();

	if (pid < 0) {
		perror("fork failed");
		return 2;
	}
  if (pid == 0)
  {
    if (first==1 && last==0 && input==0)
    {
      dup2( mypipefd[1], 1 );
    }
    else if (first==0 && last==0 && input!=0)
    {
      dup2(input, 0);
      dup2(mypipefd[1], 1);
    }
    else
    {
      dup2(input, 0);
    }

    if (strchr(stringForCheckingRedirect, '>'))
        {
          output_redirection=1;
          tokenise_redirect_output(stringForCheckingRedirect);
        }
    if(output_redirection == 1)
        {
          output_fd = open(output_redirection_file, O_WRONLY|O_CREAT|O_TRUNC, 0644); //https://stackoverflow.com/questions/18415904/what-does-mode-t-0644-mean
          //creat(output_redirection_file, 0644);
          //make a redirection for appending (O_TRUNC probably problem)
          if (output_fd < 0)
              {
                fprintf(stderr, "Failed to open %s for writing\n", output_redirection_file);
                return(EXIT_FAILURE);
              }
            dup2(output_fd, 1);
            close(output_fd);
            output_redirection=0;
        }
    if(execvp(args[0], args)<0) {printf("%s: command not found\n", args[0]);}
		exit(0);
  }
  else
  {
     waitpid(pid, 0, 0);
   }

  if (last == 1)
    close(mypipefd[0]);
  if (input != 0)
    close(input);
  close(mypipefd[1]);
  return mypipefd[0];

}

void cd(){
		char *home_dir="/home";

	// Go to home dir
		if((args[1]==NULL)||(strcmp(args[1],"~")==0)||(strcmp(args[1],"--")==0))
			chdir(home_dir);

	// Go to passed dir
		else {
			if(chdir(args[1])<0){perror("Error: ");}
	}
}

static int split(char *cmd_exec, int input, int first, int last)
{
        int m=1;
        char* stringForCheckingRedirect = strdup(cmd_exec);
        args[0]=strtok(cmd_exec," ");
        while((args[m]=strtok(NULL," "))!=NULL)
              m++;
        args[m]=NULL;
        if (args[0] != NULL)
            {
						if(strcmp("cd",args[0])==0)
                    {
                    cd();
                    return 1;
                    }
            }
    return command(input, first, last, stringForCheckingRedirect);
}

void with_pipe_execute(char* commandInput)
{
	int i, n=1, input, first;

	input=0;
	first=1;

	cmd_exec[0]=strtok(commandInput,"|");

	while ((cmd_exec[n]=strtok(NULL,"|"))!=NULL)
	      n++;
	cmd_exec[n]=NULL;
	pipe_count=n-1;
	for(i=0; i<n-1; i++)
	    {
	      input = split(cmd_exec[i], input, first, 0);
	      first=0;
	    }
	input=split(cmd_exec[i], input, first, 1);
	input=0;
	return;
}



int main(){
    char* commandInput;
    while(1){
				clear_variables();
				fflush(stdin);
				fflush(stdout);
        //printMachineAndUser();
        //commandInput = readline("");
        commandInput = readline(printMachineAndUser());

				//call single-word commands
        if(strlen(commandInput)>0) add_history(commandInput);
        if (!strcmp(commandInput, "ls")) system("ls");
        else if(!strcmp(commandInput, "clear")) system("clear");
				//else if(!strcmp(commandInput, "cat")) system("cat");
        else if (!strcmp(commandInput, "exit")) break;
				else with_pipe_execute(commandInput);
			}
			free(commandInput);
    return 0;
  }
