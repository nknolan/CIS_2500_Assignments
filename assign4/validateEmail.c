#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Detects whether emails are properly formatted and returns 0 if yes,
1 if not. Proper format: string@string.[3 chars]
There are 3 criteria to meet, so if all are met then score will equal
3 and the function returns 1 for true, else it returns 0.*/

int validateEmail(char *email)
{
    int i, next, score = 0;
    int len = strlen(email);
    
    for(i = 0; i < len; i++) {
        if(email[i] == '@')
        {
            score++;
            next = i;
            break;
        }
    }
    
    for(i = next; i < len; i++) {
        if(email[i] == '.')
        {
            score++;
            next = i;
            break;
        }
    }
    
    if((len - next) == 4)
    {
        score++;
    }
    
    if(score == 3)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
