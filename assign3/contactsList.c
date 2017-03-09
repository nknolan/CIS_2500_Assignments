#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct contact {
    unsigned long phone_number;
    long first_name_posn;
    long last_name_posn;
    long company_name_posn;
    long email_posn;
    long next;
} contact;

/* Reads and writes contact data to disk, stored in a linked list.
While loop #1 is data entry, #2 is search and retrieval (will only
return the first match; works on phone #s). */
int main()
{
    int i = 0;
    int end = 0;
    int pnSearch = 0;
    int len = 0;
    int valid = 0;
    char continueInput[3];
    char fName[50];
    char lName[50];
    char cName[50];
    unsigned long pNum[50];
    char email[50];
    FILE *fptr = fopen("myContactsList.db", "a+");/*a+ opens for reading and appending*/
    
    while(end == 0) {
        printf("Do you wish to enter a new contact (Yes or No)?: ");
        fgets(continueInput, 3, stdin);
        if(strcmp("No", continueInput))
        {
            end = 1;
            break;
        }
        else if(!strcmp("Yes", continueInput))
        {
            printf("Enter \"Yes\" or \"No\", please.\n");
            continue;
        }
        else
        {
            printf("First Name: ");
            fgets(fName, 50, stdin);
            printf("Last Name: ");
            fgets(lName, 50, stdin);
            printf("Company Name: ");
            fgets(cName, 50, stdin);
            valid = 0;
            while(valid == 0) {
                printf("Phone Number (enter only numbers): ");
                scanf("%d", pNum);
                if(pNum > 999999999 && pNum < 10000000000)
                {
                    valid = 1;
                    break;
                }
                else
                {
                    printf("Must be a valid phone number. Enter without spaces, hyphens, periods or parentheses.\n");
                    continue;
                }
            }
            printf("Email: ");
            fgets(email, 50, stdin);
            
            /*add to disc*/
            
            continue;
        }
    }
    
    end = 0;
    while(end == 0) {
        printf("Do you wish to retrieve a contact (Yes or No)?: ");
        fgets(continueInput, 3, stdin);
        if(strcmp("No", continueInput))
        {
            end = 1;
            break;
        }
        else if(!strcmp("Yes", continueInput))
        {
            printf("Enter \"Yes\" or \"No\", please.\n");
            continue;
        }
        else
        {
            printf("Phone Number: ");
            fscanf(pnSearch, 10, stdin);
            
            continue;
        }
    
    fclose(fptr);
    return 0;
}
