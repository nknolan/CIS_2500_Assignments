#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "functionDefns.h"

typedef struct contact {
    unsigned long phoneNumber;
    long firstNamePosn;
    long lastNamePosn;
    long companyNamePosn;
    long emailPosn;
    long next;
} contact;

/* Reads and writes contact data to disk, stored in a linked list.
While loop #1 is data entry, #2 is search and retrieval (will only
return the first match; works on phone #s). Entry of the contact's
phone number and email is mandatory. */
int main()
{
    unsigned long pnSearch = 0;
    unsigned long printPhone = 0;
    int isFound, noFirst, noSecond = 0;
    int i = 0;
    long offset, nextItem = 0;
    long item[5];
    char continueInput[5];
    char *fName, *lName, *cName, *pNum, *email = NULL;
    char *printFirst, *printLast, *printCompany, *printEmail = NULL;
    contact contactInput;
    contact searchOutput;
    FILE *fptr = fopen("myContactsList.db", "a+");
    
    while(1) {
        while(1) {
            printf("Do you wish to enter a new contact (Yes or No)?: ");
            fgets(continueInput, 5, stdin);
            if(strncmp("No\n", continueInput, 5) == 0)
            {
                noFirst = 1;
                break;
            }
            else if(strncmp("Yes\n", continueInput, 5) == 0)
            {
                noSecond = 0;
                fName = getInput("First name: ");
                lName = getInput("Last name: ");
                cName = getInput("Company name: ");

                while(1) {
                    pNum = getInput("Phone Number (enter only numbers): ");
                    if(strlen(pNum) == 0)
                    {
                        continue;
                    }
                    else
                    {
                        break;
                    }
                }

                while(1) {
                    email = getInput("Email: ");

                    if(strlen(email) == 0)
                    {
                        continue;
                    }
                    else
                    {
                        break;
                    }
                }

                contactInput.phoneNumber = strtoul(pNum, &pNum, 10);

                contactInput.firstNamePosn = ftell(fptr) + sizeof(contact);
                contactInput.lastNamePosn = contactInput.firstNamePosn + (sizeof(char) * (strlen(fName) + 1));
                if(strlen(fName) == 0)
                {
                    contactInput.lastNamePosn = contactInput.firstNamePosn;
                    contactInput.firstNamePosn = 0;
                }
                contactInput.companyNamePosn = contactInput.lastNamePosn + (sizeof(char) * (strlen(lName) + 1));
                if(strlen(lName) == 0)
                {
                    contactInput.companyNamePosn = contactInput.lastNamePosn;
                    contactInput.lastNamePosn = 0;
                }
                contactInput.emailPosn = contactInput.companyNamePosn + (sizeof(char) * (strlen(cName) + 1));
                if(strlen(cName) == 0)
                {
                    contactInput.emailPosn = contactInput.companyNamePosn;
                    contactInput.companyNamePosn = 0;
                }
                contactInput.next = contactInput.emailPosn + (sizeof(char) * (strlen(email) + 1));

                fwrite(&contactInput, sizeof(contact), 1, fptr);
                if(contactInput.firstNamePosn != 0)
                {
                    fwrite(fName, sizeof(char), strlen(fName) + 1, fptr);
                }
                if(contactInput.lastNamePosn != 0)
                {
                    fwrite(lName, sizeof(char), strlen(lName) + 1, fptr);
                }
                if(contactInput.companyNamePosn != 0)
                {
                    fwrite(cName, sizeof(char), strlen(cName) + 1, fptr);
                }
                fwrite(email, sizeof(char), strlen(email) + 1, fptr);
            }
            else
            {
                printf("Please enter \"Yes\" or \"No\" only.\n");
            }
        }

        while(1) {
            continueInput[0] = '\0';
            printf("Do you wish to retrieve a contact (Yes or No)?: ");
            fgets(continueInput, 5, stdin);
            if(strncmp("No\n", continueInput, 5) == 0)
            {
                noSecond = 1;
                break;
            }
            else if(strncmp("Yes\n", continueInput, 5) == 0)
            {
                while(1) {
                    pNum = getInput("Phone Number (enter only numbers): ");
                    if(strlen(pNum) == 0)
                    {
                        continue;
                    }
                    else
                    {
                        break;
                    }
                }

                pnSearch = strtoul(pNum, &pNum, 10);
                isFound = 0;
                offset = 0;
                nextItem = 0;
                fseek(fptr, 0, SEEK_SET);
                while(!feof(fptr)) {
                    fseek(fptr, offset, SEEK_SET);
                    fread(&searchOutput, sizeof(contact), 1, fptr);
                    if(searchOutput.phoneNumber == pnSearch) {
                        isFound = 1;
                        break;
                    }
                    else
                    {
                        offset = searchOutput.next;
                    }
                }

                if(isFound == 0)
                {
                    printf("No match found.\n");
                    break;
                }
                else if(isFound == 1)
                {
                    item[0] = searchOutput.firstNamePosn;
                    item[1] = searchOutput.lastNamePosn;
                    item[2] = searchOutput.companyNamePosn;
                    item[3] = searchOutput.emailPosn;
                    item[4] = searchOutput.next;

                    if(item[0] != 0)
                    {
                        i = 1;
                        nextItem = item[1];
                        while(nextItem == 0) {
                            i++;
                            nextItem = item[i];
                        }
                        fseek(fptr, item[0], SEEK_SET);
                        printFirst = malloc(sizeof(char) * (nextItem - item[0]));
                        fread(printFirst, 1, nextItem - item[0], fptr);
                    }

                    if(item[1] != 0)
                    {
                        i = 2;
                        nextItem = item[2];
                        while(nextItem == 0) {
                            i++;
                            nextItem = item[i];
                        }
                        fseek(fptr, item[1], SEEK_SET);
                        printLast = malloc(sizeof(char) * (nextItem - item[1]));
                        fread(printLast, 1, nextItem - item[1], fptr);
                    }

                    if(item[2] != 0)
                    {
                        i = 3;
                        nextItem = item[3];
                        while(nextItem == 0) {
                            i++;
                            nextItem = item[i];
                        }
                        fseek(fptr, item[2], SEEK_SET);
                        printCompany = malloc(sizeof(char) * (nextItem - item[2]));
                        fread(printCompany, 1, nextItem - item[2], fptr);
                    }
                    
                    printPhone = searchOutput.phoneNumber;
                    
                    fseek(fptr, item[3], SEEK_SET);
                    printEmail = malloc(sizeof(char) * (item[4] - item[3]));
                    fread(printEmail, 1, item[4] - item[3], fptr);

                    printf("First Name: %s\n", (item[0] == 0) ? "" : printFirst);
                    printf("Last Name: %s\n", (item[1] == 0) ? "" : printLast);
                    printf("Company Name: %s\n", (item[2] == 0) ? "" : printCompany);
                    printf("Phone Number: %lu\n", printPhone);
                    printf("Email: %s\n", printEmail);
                    free(printEmail);
                    break;
                }
            }

            else
            {
                printf("Please enter \"Yes\" or \"No\" only.\n");
            }
        }
        
        if(noSecond == 1 && noFirst == 1)
        {
            break;
        }
        else {
            continue;
        }
    }
    fclose(fptr);
    return 0;
}
