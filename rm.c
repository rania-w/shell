#include <stdio.h>

int main(char* argc, char const *argv[])
{
    //char* t = "death.txt";
    rm(argv);
    return 0;
}

void rm(char* file){
    if (remove(file) == 0) {
        printf("The file %s is deleted successfully.\n", file);
    } else {
        printf("The file %s is not deleted.\n", file);
    }
}