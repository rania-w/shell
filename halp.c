#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    if (argc == 1)
    {
        puts("call './forkexamples bomb' for forkbomb\ncall './forkexamples kill' to see example with kill()\ncall './forkexamples forkExample' for examples with fork()");
        puts("call './nasRm [filename]' for implementation of remove");
        puts("call './kitten [filename]' for implementation of cat");
        puts("call 'cd' and 'ls' regularly\n");
        puts("call './halp' to see this message again\ncall './halp [command]' to see the proper use of the command");
        puts("call './unisay [message]' for implementation of cowsay");
        puts("call 'clear' to clear the terminal");
        puts("piping and redirecting are implemented for all commands");
        puts("to use piping use '|' between commands");
        puts("to use redirecting use '>' to truncate files and '>>' to append to existing files");
        puts("all executables can be called with midterminal");
        puts("call 'Ctrl+C' to stop all child processess");
        puts("call 'exit' to exit the terminal");
    }
    else if (strcmp(argv[1], "unisay") == 0)
    {
        puts("call './unisay [message]' OR './unisay' + ENTER + [message]");
    }
    else if (strcmp(argv[1], "kitten") == 0)
    {
        puts("call './kitten [filename]' to print content of file\ncall './kitten [filename] [filename]' to concatenate and print files \ncall the command with -e flag to print end of line as $\ncall the command with -n flag to print contents of file with line numbers");
    }
    else if (strcmp(argv[1], "trash") == 0)
    {
        puts("call './trash [filename]' to remove files\ncall './trash [filename] [filename]' to remove multiple files");
    }
    else if (strcmp(argv[1], "forkexamples") == 0)
    {
        puts("call './forkexamples bomb' for forkbomb");
        puts("call './forkexamples kill' to see example with kill()");
        puts("call './forkexamples forkExample' for examples with fork()");
    }
    return 0;
}