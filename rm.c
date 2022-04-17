#include <stdio.h>

void rm(char* file){
    if (remove(file) == 0) {
        printf("The file %s is deleted successfully.\n", file);
    } else {
        printf("The file %s is not deleted.\n", file);
    }
}

int main(int argc, char **argv)
{
    //char* t = "uwu.txt";
    rm(argv[1]);
    return 0;
}
