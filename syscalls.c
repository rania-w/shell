#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

void forkwKillExample()
{
    printf("henlo\n");
    int x = fork();
    if(x < 0){
        printf("fork failed ;(\n");
    } else if (x == 0){
        printf("henlo I am child and this is my id: %d\n", (int)getpid());
    } else {
        //kill the child process
        kill(x, SIGKILL);
        printf("child is killed\n");
        printf("henlo I am parent and this is my id: %d\n", (int)getpid());
    }
}

void forkExample(){
    printf("henlo\n");
    int x = fork();
    if(x < 0){
        printf("fork failed ;(\n");
    } else if (x == 0){
        printf("henlo I am child and this is my id: %d\n", (int)getpid());
    } else {
        printf("henlo I am parent and this is my id: %d\n", (int)getpid());
    }
}
void forkbombExample(){
    char input;
    printf("pls don't do this\n");
    printf("[Y/n]\n");
    scanf("%c", &input);
    //int i = 0;
    
    if(input == 'y'|| input == 'Y'){
        printf("oof\n");
        //a random large number was used so that the forkbomb would eventually stop because we cherish our laptops
        /*while(i < 250){
            fork();
            i++;
        }*/
    } else if(input == 'n' || input == 'N') {
        printf("you made the right choice\n");
    } else printf("shta je pisac htio da kazhe?\n");
}
void waitExample(){
    if (fork()== 0)
        printf("HC: hello from child\n");
    else
    {
        printf("HP: hello from parent\n");
        wait(NULL);
        printf("CT: child has terminated\n");
    }
 
    printf("Bye\n");
}

void execvExample(){
    char *binaryPath = "/bin/ls";
    char *args[] = {binaryPath, "-lh", "/home", NULL};
 
    execv(binaryPath, args);
}
int main(int argc, char **argv)
{
    forkwKillExample();
    return 0;
}