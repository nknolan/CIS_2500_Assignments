#include <ctype.h>
#include <stdio.h>
#include <string.h>

/* Ensures that a phone number has been entered, and that
it has 7 or 10 digits. Returns 1 for true if valid or 0 if
invalid. */

int validatePhone(char *phone)
{
    int i = 0;
    int len = strlen(phone);
    
    for(i = 0; i < len; i++) {
        if(!isdigit(phone[i]))
        {
            return 0;
        }
    }
    
    if(len == 7 || len == 10)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
