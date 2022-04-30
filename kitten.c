#include <stdio.h>
#include <string.h>
/**
 * rm can take multiple files and remove them
 * it is implemented by simply using the remove function
 * hmmmmmmmm
 */

 int lineCount = 0;
 int numOfFlags = 0;
 int printingLines = 0;
 int numOfLines = 1;
 int printingEndline = 0;
 int append = 0;
 int overwrite = 0;

 void cat(char* file){
   FILE* filePtr;
   filePtr=fopen(file, "r"); //open file in read mode
   //if no filename is given or num of args is less than 2
   char character;
   char prev_character = '\0';

   if(printingLines && printingEndline){
     printf("%d\t", numOfLines);
     numOfLines++;
     while((character = fgetc(filePtr))!=EOF) //gets each character from a file until it reaches or End Of File
     {
       if(prev_character == '\n'){printf("%d\t", numOfLines); numOfLines++;}
       if (character == '\n') printf("$");
       printf("%c", character);
       prev_character = character;
/*
       printf("%c", character);
       if(character == '\n'){printf("%d\t$", numOfLines); numOfLines++;}
       prev_character = character;
       */
     }
   }
   else if(printingLines){
     printf("%d\t", numOfLines);
     numOfLines++;
     while((character = fgetc(filePtr))!=EOF) //gets each character from a file until it reaches or End Of File
     {
       if(prev_character == '\n'){printf("%d\t", numOfLines); numOfLines++;}
       printf("%c", character);
       prev_character = character;
     }
   }
   else if(printingEndline){
     while((character = fgetc(filePtr))!=EOF) //gets each character from a file until it reaches or End Of File
     {
       if (character == '\n') printf("$");
       printf("%c", character);
       prev_character = character;
     }
   }
   else{
     while((character = fgetc(filePtr))!=EOF) //gets each character from a file until it reaches or End Of File
     {
       printf("%c", character);
     }
   }
   fclose(filePtr);
 }


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


   for(int i = 1; i < argc; i++){
    if(strcmp(argv[i], "-n") == 0){
      printingLines = 1;
      numOfFlags++;
      //printf("numOfFlags%d\n", numOfFlags);
    }
    else if(strcmp(argv[i], "-e") == 0){
      printingEndline = 1;
      numOfFlags++;}
      //printf("numOfFlags%d\n", numOfFlags);
    else break;
   }
   //if(strcmp(argv[argc-2], ">>")) append = 1;
   for(int i = numOfFlags+1; i < argc; i++){
     //printf("argc:%d\n", i);
     cat(argv[i]);
   }


     return 0;
 }

/*
int main(int argc, char **argv)
{
    // custom signals

    int x=0; //global because signals can't be used to send data between processes
    void handle_sigusr1(int sig){
      if (x == 0){
        printf("\n(HINT) 14+1 :)\n");
      }
    }

    int main(int argc, char* argv[]){
      int pid = fork();
      if(pid == -1){
        return 1;
      }
      if(pid == 0){
        // Child process
        sleep(5);
        kill(getppid(), SIGUSR1); // gettppid() gets the parent's pid, SIGUSR1 is the custom signal that we will send to the parent
      } else {
        // Parent process
        struct sigaction sa = {0};
        sa.sa_flags = SA_RESTART; //restarts scanf once it finishes its execution
        sa.sa_handler = &handle_sigusr1;
        sigaction(SIGUSR1, &sa, NULL);



        printf("What is the result of 3 x 5: ");
        scanf("%d", &x);
        if(x==15){
          printf("Correct\n");
        }
        else{
          printf("Incorrect\n");
        }
        wait(NULL);
      }

      return 0;
    }

    return 0;
}*/
