#include <stdio.h>
#include <string.h>

/**
 * rm can take multiple files and remove them
 * it is implemented by simply using the remove function
 *
 */


void rm(char *file)
{
    if (remove(file) == 0)
    {
        printf("The file %s is deleted successfully.\n", file);
    }
    else
    {
        printf("The file %s is not deleted.\n", file);

    }
}

int main(int argc, char **argv)
{
    if (argc == 1) {
    return 1;
  }
    for (int i = 1; i < argc; i++)
    {
        rm(argv[i]);
    }
    return 0;
}
