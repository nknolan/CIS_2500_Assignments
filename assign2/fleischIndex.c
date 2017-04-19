#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int i = 0;
    int wordCount = 0;
    int syllableCount = 0;
    int sentenceCount = 0;
    int currWords = 0;
    int currSyllables = 0;
    int lChar = 0;
    char terminators[5] = ".:;?!";
    char vowels[12] = "aeiouyAEIOUY";
    int fIndex = 0;
    FILE *inputFile;
    int fileSize;
    
    if(argc < 2)
    {
        printf("Expected a command line argument: name of input file.\n");
        return 1;
    } else if(argc > 2)
    {
        printf("Too many arguments supplied.\n");
        return 2;
    }
    
    if ((inputFile = fopen(argv[1], "r")) == NULL)
    {
        printf("Could not open file.\n");
        return 3;         
    }
    
    inputFile = fopen(argv[1], "r");
    fseek(inputFile, 0, SEEK_END);
    fileSize = ftell(inputFile);
    fseek(inputFile, 0, SEEK_SET);
    
    /*The +1 is to accomodate the terminating character.*/
    char *input = malloc((fileSize + 1) * sizeof(char));
    fread(input, sizeof(char), fileSize, inputFile);
    fclose(inputFile);
    input[fileSize] = 0;

    printf("%s\n\n", input);

    for(i = 0; i < strlen(input); i++) {
        currWords = wordCount;
        currSyllables = syllableCount;
        if(input[i] == ' ' || input[i] == '\n') {
            wordCount++;
//printf("%d @ %c$", wordCount, input[i]);
        }
        if(strchr(terminators, input[i]) != NULL && strchr(terminators, input[i + 1]) == NULL) {
            sentenceCount++;
        }
        if(strchr(vowels, input[i]) != NULL && strchr(vowels, input[i+1]) == NULL) {
            syllableCount++;
            printf("%c%c%c ", input[i-1], input[i], input[i+1]);
            if(input[i] == 'e' && isalpha(input[i+1]) == 0) {
               syllableCount--;
            }
	}
        if(isdigit(input[i]) && isdigit(input[i+1]) != 0) {
            syllableCount++;
        }
        if(currWords > wordCount && currSyllables == syllableCount) {
            syllableCount++;
        }
    }
    lChar = strlen(input) - 1;
    if(strchr(terminators, input[lChar]) == NULL && !isalpha(input[lChar])) {
        wordCount--;
printf("fuck %c", input[lChar]);
    }
    fIndex = 206.835 - (84.6 * (syllableCount / wordCount)) - (1.015 * (wordCount / sentenceCount));
    printf("Flesch Index = %d\nSyllable Count = %d\nWord Count = %d\nSentence Count = %d\n", fIndex, syllableCount, wordCount, sentenceCount);
    return 0;
}
