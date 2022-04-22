#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h> // we can call open() with this
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
  printf("Opened\n");
  char x[] = "lol";
  //int z = 'Z';
  //write(fd, &z, sizeof(x)) //pass the address of the argument we want to write to the file
  if(write(fd, x, sizeof(x)) == -1){
    return -2; //error
  }
  printf("Written\n");
  close(fd);
  printf("Closed\n");


  return 0;
}
