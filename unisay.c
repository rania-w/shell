#include <stdio.h>
#include <string.h>
#define MAX_WIDTH 40
#define MAX(a, b) ((a > b) ? a : b)
#define MIN(a, b) ((a < b) ? a : b)

/**
 *  
 * Implementation of cowsay, with a different design at the end
 *  
 */

// Returns the length of the longst line of the message.
static size_t LongestLineLength(int argc, char **argv)
{
    size_t max_len = 0;
    size_t cur_line = 0;
    for (int i = 0; i < argc; i++)
    {
        size_t word_len = strlen(argv[i]) + 1;
        // If the word itself is too long to fit in a line, then
        // we return the maximum width.
        if (word_len >= MAX_WIDTH)
            return MAX_WIDTH;
        if (cur_line + word_len >= MAX_WIDTH)
        {
            cur_line = word_len;
        }
        else
        {
            cur_line += word_len;
        }
        max_len = MAX(cur_line, max_len);
    }
    return max_len;
}
static void PrintPaddedBreak(size_t pad)
{
    for (size_t i = 0; i < pad; i++)
    {
        printf(" ");
    }
    printf(" |\n");
}
// Prints the message
static void PrintMessage(int argc, char **argv, size_t longest)
{
    size_t cur_line_len = 0;
    for (int i = 0; i < argc; i++)
    {
        size_t word_len = strlen(argv[i]) + 1;
        if (cur_line_len == 0)
            printf("| ");
        // If it all fits in the line, then print the word.
        if (cur_line_len + word_len <= MAX_WIDTH)
        {
            printf("%s ", argv[i]);
            if (cur_line_len + word_len == MAX_WIDTH)
            {
                PrintPaddedBreak(longest - cur_line_len - word_len);
                cur_line_len = 0;
                continue;
            }
            cur_line_len += word_len;
            if (i == argc - 1)
                PrintPaddedBreak(longest - cur_line_len);
            continue;
        }
        // Create a line break if the current line is nonempty.
        if (cur_line_len > 0)
        {
            PrintPaddedBreak(longest - cur_line_len);
            printf("| ");
        }
        // If the word itself is too long, then we need to break it apart.
        // Otherwise, we print the current word.
        if (word_len > MAX_WIDTH)
        {
            char *str = argv[i];
            size_t processed = 0;
            for (size_t j = 0; j <= word_len / MAX_WIDTH; j++)
            {
                size_t len = MIN(MAX_WIDTH, strlen(str));
                printf("%.*s", (int)len, str);
                PrintPaddedBreak(longest - len);
                str += len;
                processed += len;
                if (processed >= word_len - 1)
                    break;
                printf("| ");
            }
            cur_line_len = 0;
        }
        else
        {
            printf("%s ", argv[i]);
            cur_line_len = word_len;
            if (word_len == MAX_WIDTH || i == argc - 1)
            {
                PrintPaddedBreak(longest - cur_line_len);
            }
        }
    }
}
int main(int argc, char **argv)
{
    if (argc == 1)
    {
        printf("Usage: unisay [message]\n");
        return 1;
    }
    
    size_t bubble_width = LongestLineLength(argc - 1, argv + 1) + 1;
    printf(" _");
    for (size_t i = 0; i < bubble_width; i++)
        printf("_");
    printf(" \n");
    PrintMessage(argc - 1, argv + 1, bubble_width - 1);
    printf(" -");
    for (size_t i = 0; i < bubble_width; i++)
        printf("-");
    printf(" \n");

    printf("                              ,,))))))));,\n");
    printf("                           __)))))))))))))), \n");
    printf("             \\|/            -((((((''''((((((((. \n");
    printf("              ---*-==//////((''  .     `)))))), \n");
    printf("             /|\\         ))| o    ;-.    '(((((                                  ,(, \n");
    printf("                         ( `|    /  )    ;))))'                               ,_))^;(~ \n");
    printf("                            |   |   |   ,))((((_     _____------~~~-.        %%,;(;(>';'~ \n");
    printf("                            o_);   ;    )))(((` ~---~  `::           \\      %%~~)(v;(`('~ \n");
    printf("                                  ;    ''''````         `:       `:::|\\,__,%%    );`'; ~ \n");
    printf("                                 |   _                )     /      `:|`----'     `-' \n");
    printf("                           ______/ /~    |                 /        / \n");
    printf("                         /~;;.____/;;'  /          ___--,-(   `;;;/ \n");
    printf("                        / //  _;______;'------~~~~~    /;;/\\    / \n");
    printf("                       //  | |                        / ;   \\;;,\\ \n");
    printf("                      (<_  | ;                      /',/-----'  _> \n");
    printf("                        _| ||_                     //~;~~~~~~~~~ \n");
    printf("                           `_|                   (,~~ \n");
    printf("                                                   |~| \n");
    printf("                                                    ~~ \n");

    return 0;
}