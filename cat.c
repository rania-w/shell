#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _GNU_SOURCE
#include <unistd.h> //exec
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h> // we can call open() with this
#include <time.h>
/*
int main(int argc, char* argv[])
{
  // path, filename, ()> for overwrite, >> for append, new filename) -> optional
  // cat -n filename prints contents of a file with line numbers https://linuxize.com/post/linux-cat-command/
  // use -s to omit repeated empty lines
  // use -e to display invisible line ending characters ($)
  // cat file1.txt file2.txt > combinedfile.txt
  // cat file1.txt file2.txt >> file3.txt
  // cat > filename.txt -> enter text after this and press control + d to save the file
  // cat >> filename.txt -> same as above, just append


    FILE* filePtr;
    filePtr=fopen(argv[1], "r"); //open file in read mode
    if(!filePtr || argc<2) //if no filename is given or num of args is less than 2
    {
        printf("Error");
    }
    char character;
    while((character = fgetc(filePtr))!=EOF) //gets each character from a file until it reaches or End Of File
    {
      printf("%c", character);
    }
    fclose(filePtr);

    return 0;
}
*/
/*
void piping(){


}
int main2(int argc, char* argv[]){
    int fd[2]; //file descriptors -> 2 ends
    //fd[0] -> where to read from
    //fd[1] -> where to write
    if(pipe(fd) == -1){
      printf("An error occured while opening the pipe\n");
      return 1;
    }
    int id = fork();
    if(id == -1){
      printf("An error occured while forking\n");
      return 4;
    }
    if(id == 0){
      close(fd[0]);
      int x;
      printf("Input a number");
      scanf("%d", &x);
      if(write(fd[1], &x, sizeof(int)) == -1){
        printf("An error occured while writing to the pipe\n");
        return 2;
      }
      close(fd[1]);
    }
    else {
      wait(NULL);
      close(fd[1]);
      int y;
      if(read(fd[0], &y, sizeof(int)) == -1){
        printf("An error occured while reading from the pipe\n");
        return 3;
      }
      close(fd[0]);
      printf("Got from child process %d\n", y);
    }
    return 0;
}*/

/*
int main(int argc, char* argv[]){
  //FIFOs -> file types to which you can read / write from any process (named pipes)

  if(mkfifo("myfifo1", 0777) == -1){//octal 0777 -> this file can be read from or written into by anybody
      if(errno != EEXIST){ // error other than "file already exists", print below message
          printf("Could not create fifo file\n");
          return 1;
      }
  }

  printf("Opening...\n"); //blocks here because it won't allow us to do anything until the fifo is opened by another process or thread

  int fd = open("myfifo1", O_WRONLY); // write only -> returns file descriptor
  //for reading -> int fd = open("myfifo1", O_RDONLY);


  // if we open the file with O_RDWR (read and write) it won't wait for anything
  if(fd == -1){
    return -3; //couldn't open file
  }
  printf("Opened\n");
  char x[] = "lol";
  //int z = 'Z';
  //write(fd, &z, sizeof(x)) //pass the address of the argument we want to write to the file
  //for reading -> read(fd, &z, sizeof(int));
  // for reading string -> read(fd, x, sizeof(char)*1000);
  if(write(fd, x, sizeof(x)) == -1){
    return -2; //error
  }
  printf("Written\n");
  close(fd);
  printf("Closed\n");


  return 0;
}

*/

int main(int argc, char* argv[]){
    // all exec functions
    // exec l -> l = list of arguments
    // exec v -> v = vector
    // execvp
    // execl() -> path and filename to exe, argument1 (path again), arg2 (actual first argument), arg3, etc, NULL
    // exelp() -> no need to pass the path, exe filename is enough (looks at the current directory)
    // execvpe() -> pass in an environment (set of variables that can be pased through another array)
    // execvpe requires int main(int argc, char* argv[], char* envp[])

    char * arr[] = {
      "ping",
      "google.com",
      NULL
    };
    char * env[] = {
      "TEST=environment variable",
      NULL
    };
    //execvp("ping", arr);
    execvpe("ping", arr, env);

    return 0;

}

// step 1: fork
// step 2: in child, call execlp
// step 3: in paren, wait for child to finish, then do something else

// 2 error types:
  // 1: when exec can't find the executable (execlp returns -1 in that case)
  // 2: when the executable inside of exec throws an error (wait function takes int &waitStatus that tells us what happened to the program)
  /*
  int waitStatus;
  wait($waitStatus);
  if(WIFEXITED(waitStatus)){ //if the child terminated normally (wasn't forcefully closed / crashed / idk)
      int statusCode = WEXITSTATUS(waitStatus); // return value inside the main function in the program (or the exit() function in the program)
      if(statusCode == 0){
        printf("Success\n");
      }
      else{
        pritnf("Failure\n");
      }
  }*/

  /*
  //redirecting standard output (into another file)
  int file = open("pingResults.txt", O_WRONLY | O_CREAT, 0777); //write only + create if it doesn't  with "bitwise or"; 0777 everyone has access to the file
  // file descriptors are numbers that are unique accross a process
  // fd 0 -> STDIN
  // fd 1 -> STOUT
  // fd 2 -> STDERR
  // fd 3 could be the one that points to pingResults.txt (file that was opened aboved)
  // these 3 file descriptors are automatically opened before we even get to main()
  // read(0) = scanf() (without formating though)
  // write(1, something) = printf()

  // using dup() or dup2() we can change where the ouptut goes
  // int file2 = dup(file); // dup function took fd3, duplicated it and it returned a new fd (with id 4 probably) which points to the same file
  // int file3 = dup2(file, 1) // first param is the fd that we want to duplicate, and the second is the value that we want the new fd to actually have
  // this code closes fd 1 (STDOUT), and reopens it with the new fd that was duplicated (shows to pingnResults.txt)
  // execlp changes the whole code / program that is being executed, but it doesn't change the fds that are alerady opened and the pid of the process
  // now, if we try to printf("Something"); under file3 = dup2(), it will print to the file instead of printing to the terminal
  // Also, this fd 1 for STDOUT should be replaced with STDOUT_FILENO for good practice, since that's the standard
  // Even though fd 3 was duplicated, we can close it without any consequences by using close(file)
  // the "int file3 = " part in dup2() can be removed since we already know that we are opening a new fd that goes to STDOUT
  */
