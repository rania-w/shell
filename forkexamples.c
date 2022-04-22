#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
/**
 *  
 * a simple program showing the implementation of fork() and wait() system calls
 * where wait() is used to terminate the child process
 * 
 */
void forkExample(){
    printf("henlo\n");
    int x = fork();
    if(x < 0){
        printf("fork failed ;(\n");
    } else if (x == 0){
        printf("henlo I am child and this is my id: %d\n", (int)getpid());
    } else {
        printf("henlo I am parent and this is my id: %d\n", (int)getpid());
        wait(NULL);
        printf("child has terminated\n");
    }
}
/**
 * 
 * implementation of forkbomb with warnings for the user
 * 
 */
void forkbombExample(){
    char input;
    printf("are you sure you want to do this? \n");
    printf("[Y/n]\n");
    scanf("%c", &input);
    
    if(input == 'y'|| input == 'Y'){
        while(1){
            fork();
        }
    } else if(input == 'n' || input == 'N') {
        printf("you made the right choice\n");
    } else printf("error. pls select [Y/n]\n");
}
/**
 * 
 * an example showing the child process being terminated with kill() as opposed to the example with wait()
 * 
 */
void killExample(){
    int x = fork();
    if(x>0){
        printf("Parent; id: %d\n", (int)getpid());
        kill(x, SIGTERM);//SIGKILL is not very nice
        puts("The child process will not run since it was terminated");
    } else {
        printf("Child; id: %d\n", (int)getpid());
    }

}

int main(int argc, char **argv)
{
    killExample();
    return 0;
}