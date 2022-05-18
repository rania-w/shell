#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<readline/readline.h>
#include<readline/history.h>
#include<limits.h>
#include<libgen.h>
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
int status;
char* output_redirection_file;
int output_redirection = 0;
int output_redirection_concat = 0;

void clear_variables()
{
    fd =0;
    flag=0;
    pipe_count=0;
    pid=0;
    //free(output_redirection_file);
    output_redirection = 0;
    output_redirection_concat = 0;
}

void print_help(){

}


//COMPILE WITH gcc -Wall -o main main.c -lreadline

char* printDir(){
    char* dir = (char*) malloc(512);
    getcwd(dir, sizeof(dir));
    //printf("%s", dir);
    return dir;
    //printf("%s",dirname(dir));
    //printf("%s",basename(dir));
}
char* printMachineAndUser(){
    char* userName = getenv("USER");
    char machineName[HOST_NAME_MAX + 1];
    char* returnValue = (char*) malloc(1024);
    *returnValue = 0;
    gethostname(machineName, HOST_NAME_MAX + 1);
    char dir[1024];
    getcwd(dir, sizeof(dir));
    strcat(returnValue, "\033[0;32m");
    strcat(returnValue, machineName);
    strcat(returnValue, "@");
    strcat(returnValue, userName);
    strcat(returnValue, ":\033[0;34m~");
    strcat(returnValue, dir);
    strcat(returnValue, "\033[0m$ ");

    return returnValue;
}

void splitCommandOnSpace(char *com_exec) //pretvori prvu komandu u array
{
  int m=1;
  args[0] = com_exec;
  args[0]=strtok(com_exec," ");
  while((args[m]=strtok(NULL," "))!=NULL) m++;
}

char* skipSpace(char* character)
{
  while (isspace(*character)) ++character;
  return character;
}
void output_redirect_newFile(char* oneCommand)
{
  char *o_token[100]; // all parts before >
  char *copiedCommand;
  copiedCommand=strdup(oneCommand);
  int m=1;
  o_token[0]=strtok(copiedCommand,">"); //splita komandu citavu na 2 dijela, token[0] je komanda, token[1] je output file
  while((o_token[m]=strtok(NULL,">"))!=NULL) m++;
  o_token[1]=skipSpace(o_token[1]); // > *space* naziv_fajla (izbaci space)
  output_redirection_file=strdup(o_token[1]);
  //free(copiedCommand);
  //free(oneCommand);
  splitCommandOnSpace(o_token[0]);
}

void output_redirect_concat(char* oneCommand){
  char *o_token[100]; // all parts before >
  char *copiedCommand;
  copiedCommand=strdup(oneCommand);
  int m=1;
  o_token[0]=strtok(copiedCommand,">>"); //splita komandu citavu na 2 dijela, token[0] je komanda, token[1] je output file
  while((o_token[m]=strtok(NULL,">>"))!=NULL) m++;
  o_token[1]=skipSpace(o_token[1]); // > *space* naziv_fajla (izbaci space)
  output_redirection_file=strdup(o_token[1]);
  //free(copiedCommand);
  //free(oneCommand);
  splitCommandOnSpace(o_token[0]);
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
  //child
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

    if (strstr(stringForCheckingRedirect, ">>")){ //is ">>" is a substring of stringForCheckingRedirect...
        output_redirection_concat = 1;
        output_redirect_concat(stringForCheckingRedirect);
    }
    if (strchr(stringForCheckingRedirect, '>'))
    {
        output_redirection=1;
        output_redirect_newFile(stringForCheckingRedirect);
    }
    if(output_redirection_concat == 1)
    {
        output_fd = open(output_redirection_file, O_WRONLY|O_APPEND, 0644);
        //https://stackoverflow.com/questions/18415904/what-does-mode-t-0644-mean
        //creat(output_redirection_file, 0644);
        //make a redirection for appending (O_TRUNC probably problem)
        if (output_fd < 0)
            {
                fprintf(stderr, "Failed to open %s for writing\n", output_redirection_file);
                //free(output_redirection_file);
                return(EXIT_FAILURE);
            }
        dup2(output_fd, 1);
        close(output_fd);
        output_redirection=0;
    }
    else if(output_redirection == 1)
    {
        output_fd = open(output_redirection_file, O_WRONLY|O_CREAT|O_TRUNC, 0644);
        //https://stackoverflow.com/questions/18415904/what-does-mode-t-0644-mean
        //creat(output_redirection_file, 0644);
        //make a redirection for appending (O_TRUNC probably problem)
        if (output_fd < 0)
            {
                fprintf(stderr, "Failed to open %s for writing\n", output_redirection_file);
                free(output_redirection_file);
                return(EXIT_FAILURE);
            }
        dup2(output_fd, 1);
        close(output_fd);
        output_redirection=0;
    }
    if(execvp(args[0], args)<0) {printf("%s: command not found\n", args[0]);}
    exit(0);
    //end of child process
  }
  else
  {
    //parent
     waitpid(pid, 0, 0);
  }

  if (last == 1) close(mypipefd[0]);
  if (input != 0) close(input);
  close(mypipefd[1]);
  free(stringForCheckingRedirect); //freeing strdup() malloced space
  //free(output_redirection_file); //since it's causing memory leaks (and it's annoying)
  return mypipefd[0];
}

char* replace_string(char* str, char* find, char* replace_str)
{
    int len  = strlen(str);
    int len_find = strlen(find), len_replace = strlen(replace_str);
    for (char* ptr = str; (ptr = strstr(ptr, find)); ++ptr) {
        if (len_find != len_replace){
            memmove(ptr+len_replace, ptr+len_find,
            len - (ptr - str) + len_replace);
            memcpy(ptr, replace_str, len_replace);
        }
    }
        return str;
    }

void cd(char* fullPath){
    char *home_dir="/home";
    //char s2[] = "\\  ";

    //printf("%s", args[1]);
   // replace_string(fullPath, "\\", s2);
    //printf("%s", args[1]);

    /*
    char* s3 = malloc(strlen(s1) + strlen(s2));
    size_t pos = strcspn( s1, " " );
    while(!pos){
      strncpy( s3, home_dir, pos );
      strcat(s3, home_dir + pos + 1);
      size_t pos = strcspn( s1, " ");
    }*/



	// Go to home dir
    if((args[1]==NULL)||(strcmp(args[1],"~")==0)||(strcmp(args[1],"--")==0)) chdir(home_dir);

	// Go to passed dir
    else {
          if(chdir(fullPath)<0){perror("Error: ");}
	}
}

static int split(char *cmd_exec, int input, int first, int last)
{
    int m=1;
    char* stringForCheckingRedirect = strdup(cmd_exec);
    args[0]=strtok(cmd_exec," ");
    while((args[m]=strtok(NULL," "))!=NULL) m++;
    args[m]=NULL;
    if (args[0] != NULL)
    {
        if(strcmp("cd",args[0])==0)
        {
            char fullPath[10000] = "";
            //printf("%s\n", args[1]);

            //strcpy(fullPath, args[1]);
            //printf("%s\n", fullPath);

            for(int i = 1 ; i < m; i++){
              if(args[i][strlen(args[i])-1] == '\\'){
                  args[i][strlen(args[i])-1] = ' ';
                  strcat(fullPath, args[i]);
              }
              else strcat(fullPath, args[i]);
              }
            cd(fullPath);
            return 1;
        }
    }
    int fdReturn = command(input, first, last, stringForCheckingRedirect);
    //free(stringForCheckingRedirect);
    return fdReturn;
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
    split(cmd_exec[i], input, first, 1);
}

  //handling signals
  void handle_sigint(int sig){
    fflush(stdout);
  }

  /*
  void handle_sigtstp(int sig){
    //printf("Stop not allowed\n");
    fflush(stdout);
  }
  */
int main(){

    // this first part is for handling CTRL+C signals, making it so that once CTRL+C is clicked, the execv child processes will get terminated
    // while the terminal will stay alive
    struct sigaction sa;  //predefined struct (probably from signal.h)
    sa.sa_handler = &handle_sigint; //pointer to function
    sa.sa_flags = SA_RESTART; //this fixes issues if we're using scanf and sending SIGTSTP at the same time
    sigaction(SIGINT, &sa, NULL); //binds the signal to the handler, the 3rd param could be an old sigaction handler (optional)
    //signal(SIGTSTP, &handle_sigtstp); // this does exactly the same thing as the above part, but it's an unsafe function for portability reasons (AVOID ITS USE)


    // this second part is for handling CTRL+Z signals, but since all child processes are in the same group (foreground), this would
    // prevent us from stopping the terminal in case something goes wrong...

    //struct sigaction sa2;
    //sa2.sa_handler = &handle_sigtstp;
    //sa2.sa_flags = SA_RESTART;
    //sigaction(SIGTSTP, &sa2, NULL);

    char* commandInput;
    while(1){
        clear_variables();
        fflush(stdin);
        fflush(stdout);
        char* machineAndUser = printMachineAndUser();
        //commandInput = readline(printMachineAndUser());
        commandInput = readline(machineAndUser);
        free(machineAndUser);

        //call single-word commands
        if(strlen(commandInput)>0) add_history(commandInput);
        if (!strcmp(commandInput, "ls")) system("ls --color=always");
        else if(!strcmp(commandInput, "clear")) system("clear");
				//else if(!strcmp(commandInput, "cat")) system("cat");
        else if (!strcmp(commandInput, "exit")){ free(commandInput); break; }
        else if(strlen(commandInput) == 0) { free(commandInput); continue; } //THIS WILL PREVENT A VERY ANNOYING CRASHING PROBLEM
        //THAT I WAS TRYING TO FIX FOR AN HOUR
        else with_pipe_execute(commandInput);
        free(commandInput);
    }
    return 0;
  }
