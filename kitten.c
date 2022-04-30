#include <stdio.h>
#include <string.h>

int lineCount = 0;
int numOfFlags = 0;
int printingLines = 0;
int numOfLines = 1;
int printingEndline = 0;

void cat(char *file)
{
  FILE *filePtr;
  filePtr = fopen(file, "r"); // open file in read mode
  // if no filename is given or num of args is less than 2
  char character;
  char prev_character = '\0';
  /**
   *
   * four cases: one if both flags are called, one if only one is called for each, and one if no flags
   *
   */
  if (printingLines && printingEndline)
  {
    printf("%d\t", numOfLines);
    numOfLines++;
    while ((character = fgetc(filePtr)) != EOF) // gets each character from a file until it reaches or End Of File
    {
      if (prev_character == '\n')
      {
        printf("%d\t", numOfLines);
        numOfLines++;
      }
      if (character == '\n')
        printf("$");
      printf("%c", character);
      prev_character = character;
    }
  }
  else if (printingLines)
  {
    printf("%d\t", numOfLines);
    numOfLines++;
    while ((character = fgetc(filePtr)) != EOF) // gets each character from a file until it reaches or End Of File
    {
      if (prev_character == '\n')
      {
        printf("%d\t", numOfLines);
        numOfLines++;
      }
      printf("%c", character);
      prev_character = character;
    }
  }
  else if (printingEndline)
  {
    while ((character = fgetc(filePtr)) != EOF) // gets each character from a file until it reaches or End Of File
    {
      if (character == '\n')
        printf("$");
      printf("%c", character);
      prev_character = character;
    }
  }
  else
  {
    while ((character = fgetc(filePtr)) != EOF) // gets each character from a file until it reaches or End Of File
    {
      printf("%c", character);
    }
  }
  fclose(filePtr);
}

int main(int argc, char *argv[])
{
  // path, filename, ()> for overwrite, >> for append, new filename) -> optional
  // cat -n filename prints contents of a file with line numbers https://linuxize.com/post/linux-cat-command/
  // use -e to display invisible line ending characters ($)
  // cat file1.txt file2.txt > combinedfile.txt
  // cat file1.txt file2.txt >> file3.txt

  for (int i = 1; i < argc; i++)
  {
    if (strcmp(argv[i], "-n") == 0)
    {
      printingLines = 1;
      numOfFlags++;
    }
    else if (strcmp(argv[i], "-e") == 0)
    {
      printingEndline = 1;
      numOfFlags++;
    }

    else
      break;
  }

  for (int i = numOfFlags + 1; i < argc; i++)
  {
    cat(argv[i]);
  }

  return 0;
}
