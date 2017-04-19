#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Function to automate collecting user input, stripping the final newline,
and calling malloc to add the string to the main program.*/

char *getInput(char *message)
{
    char tempString[101];
    char *target;
    printf("%s", message);
    fgets(tempString, 100, stdin);
    tempString[strlen(tempString) - 1] = '\0';
    target = malloc(sizeof(char) * (strlen(tempString) + 1));
    strncpy(target, tempString, strlen(tempString) + 1);

    return target;
}
