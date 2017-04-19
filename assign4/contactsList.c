
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "functionDefns.h"
#include "structDefn.h"

/* Program to maintain and access a database of personal
contacts. It cannot read structs from disks for the life
of me, but it can write to them (use od -cd myContactsList.db
to check). This version has reading COMMENTED OUT, and shows
all of the other features necessary, using only structs stored
in memory. Bits tacked on to facilitate this are commented as such.
If you end the program, you cannot recover the data written to
myContactsList.db
If you were wondering, more sane attempts to extract file data gave me
null pointers and random strings of garbage data.
At some point in my life, I *will* revisit this to see what went wrong. */

int main(void)
{
    int current, exitFlag, i, j, isNum, len, numContacts, numDeleted, scroll, scrollMax, tempInt = 0;
    int *originalAddress;
    /*long offset, nextAddress = 0;*/
    char lastLetter, currentLetter;
    char *continueInput = NULL;
    char *first, *last, *company, *phone, *email = NULL;
    /*char *readFirst, *readLast, *readCompany, *readEmail = NULL;*/
    char firstAndLast[301];
    char nameA[101];
    char nameB[101];
    contact contactInput, temp;
    contact *contacts = malloc(sizeof(contact) * 1);
    /*long fileLen = 0;*/
    
    char **firstNames;
    char **lastNames;
    char **companyNames;
    char **emails;
    
    FILE *fptr = fopen("myContactsList.db", "a+");
    
    /* Arrays to hold string data. These are supposed
    to be refilled each loop
    but because *that's* not happening... */
    firstNames = malloc(sizeof(char *) * 1);
    lastNames = malloc(sizeof(char *) * 1);
    companyNames = malloc(sizeof(char *) * 1);
    emails = malloc(sizeof(char *) * 1);
    originalAddress = malloc(sizeof(int) * 1);
    
    while(1) {
        /*fptr = fopen("myContactsList.db", "a+");
        offset = 0;
        numContacts = 0;
        fseek(fptr, 0, SEEK_END);
        fileLen = (long)ftell(fptr);
        rewind(fptr);
        if(ftell(fptr) != fileLen)
        {
            while(1) {
                fseek(fptr, offset, SEEK_SET);
                contacts = realloc(contacts, (sizeof(contact) * (numContacts + 1)));
                fread(&temp, sizeof(contact), 1, fptr);
                fseek(fptr, temp.firstNamePosn, SEEK_SET);
                if(ftell(fptr) != contacts[numContacts].next + sizeof(contact) || (long)ftell(fptr) > 50)
                {
                    break;
                }
                if(feof(fptr))
                {
                    break;
                }
                numContacts++;
                contacts = realloc(contacts, (sizeof(contact) * numContacts));
                offset = temp.next;
                contacts[i] = temp;
                printf("t-first: %li\nc-first: %li\nnum = %d\n", temp.firstNamePosn, contacts[numContacts-1].firstNamePosn, numContacts);
            }
        }*/
        
        /*for(i = 0; i < numContacts; i++) {
            originalAddress[i] = i;
            
            if(contacts[i].lastNamePosn != 0)
            {
                nextAddress = contacts[i].lastNamePosn;
            }
            else
            {
                nextAddress = contacts[i].companyNamePosn;
            }
            readString(readFirst, contacts[i].firstNamePosn, nextAddress, fptr);
            printf("first: %li, diff: %li\n", contacts[i].firstNamePosn, nextAddress - contacts[i].firstNamePosn);
            
            if(contacts[i].companyNamePosn != 0)
            {
                nextAddress = contacts[i].companyNamePosn;
            }
            else
            {
                nextAddress = contacts[i].emailPosn;
            }
            readString(readLast, contacts[i].lastNamePosn, nextAddress, fptr);
            printf("last: %li, diff: %li\n", contacts[i].lastNamePosn, nextAddress - contacts[i].lastNamePosn);
            
            nextAddress = contacts[i].emailPosn;
            readString(readCompany, contacts[i].companyNamePosn, nextAddress, fptr);
            
            nextAddress = contacts[i].next;
            readString(readEmail, contacts[i].emailPosn, nextAddress, fptr);
            
            if(contacts[i].firstNamePosn != 0)
            {
                strncpy(firstNames[i], readFirst, strlen(readFirst));
            }
            else if(contacts[i].firstNamePosn == 0)
            {
                strcpy(firstNames[i], "");
            }
            if(contacts[i].lastNamePosn != 0)
            {
                strncpy(lastNames[i], readLast, strlen(readLast));
            }
            else if(contacts[i].lastNamePosn == 0)
            {
                strcpy(lastNames[i], "");
            }
            if(contacts[i].companyNamePosn != 0)
            {
                strncpy(companyNames[i], readCompany, strlen(readCompany));
            }
            else if(contacts[i].companyNamePosn == 0)
            {
                strcpy(companyNames[i], "");
            }
            
            strncpy(emails[i], readEmail, strlen(readEmail));
        }*/
        
        /* Bubblesort algorithm for ordering structs. */
        for(i = 0; i < (numContacts - 1); i++) {
            for(j = 0; j < (numContacts - i - 1); j++) {

                if(contacts[j].lastNamePosn != 0)
                {
                    strcpy(nameA, lastNames[originalAddress[j]]);
                }
                else
                {
                    strcpy(nameA, companyNames[originalAddress[j]]);
                }

                if(contacts[j+1].lastNamePosn != 0)
                {
                    strcpy(nameB, lastNames[originalAddress[j]]);
                }
                else
                {
                    strcpy(nameB, companyNames[originalAddress[j]]);
                }

                if(atoi(nameA) > atoi(nameB) || contacts[j].phoneNumber == 0) {
                    temp = contacts[j];
                    contacts[j] = contacts[j+1];
                    contacts[j+1] = temp;
                    
                    /* Same transformation applied to originalAddress
                    so if contacts[0] goes to contacts[2], originalAddress[2] = 0
                    Also if phone = 0 shuffle to the back. */
                    tempInt = originalAddress[j];
                    originalAddress[j] = originalAddress[j+1];
                    originalAddress[j+1] = tempInt;
                }
            }
        }
        
        printf("Number of contacts = %d\n", numContacts - numDeleted);
        if(numContacts > 0)
        {
            if(numContacts <= 5)
            {
                scrollMax = numContacts;
                scroll = 0;
            }
            else
            {
                scrollMax = numContacts - 5;
            }
            for(i = scroll; i < scrollMax; i++) {
                last = lastNames[originalAddress[i]];
                if(contacts[i].lastNamePosn != 0)
                {
                    first = firstNames[originalAddress[i]];
                    strcpy(firstAndLast, first);
                    strcat(firstAndLast, " ");
                    strcat(firstAndLast, last);

                    if(i == scroll)
                    {
                        lastLetter = toupper(last[0]);
                        currentLetter = lastLetter;
                    }
                    else if(i > scroll)
                    {
                        currentLetter = toupper(last[0]);
                    }
                }
                else if(contacts[i].companyNamePosn != 0)
                {
                    company = companyNames[originalAddress[i]];
                    if(i == scroll)
                    {
                        lastLetter = toupper(company[0]);
                        currentLetter = lastLetter;
                    }
                    else if(i > scroll)
                    {
                        currentLetter = toupper(company[0]);
                    }
                }

                if(currentLetter > lastLetter || i == scroll)
                {
                    printf("%c\n", currentLetter);
                    lastLetter = currentLetter;
                }

                printf("\t%d.  %s\n", i + 1, (contacts[i].lastNamePosn != 0) ? firstAndLast : company);
            }
        }
        /* Originally supposed to switch from a+ to w+, now it doesn't matter :'(
        fclose(fptr);
        fptr = fopen("myContactsList.db", "w+");
        */
        
        continueInput = getInput("Action: ");
        len = strlen(continueInput);
        if(continueInput[0] == '+' && len == 1)
        {
            scroll++;
            if(scroll > numContacts)
            {
                scroll = numContacts - 1;
                if(scroll < 0)
                {
                    scroll = 0;
                }
            }
        }
        else if(continueInput[0] == '-' && len == 1)
        {
            scroll--;
            if(scroll < 0)
            {
                scroll = 0;
            }
        }
        else if(continueInput[0] == 'A' && len == 1)
        {
            first = NULL;
            last = NULL;
            company = NULL;
            phone = NULL;
            email = NULL;
            
            first = getInput("First Name: ");
            while(1) {
                last = getInput("Last Name: ");
                company = getInput("Company Name: ");
                if(strlen(last) == 0 && strlen(company) == 0)
                {
                    printf("Please enter a last name or a company name.\n");
                    continue;
                }
                else
                {
                    break;
                }
            }
            while(1) {
                phone = getInput("Phone Number (enter only numbers): ");
                if(validatePhone(phone) == 1)
                {
                    break;
                }
                else
                {
                    continue;
                }
            }
            while(1) {
                email = getInput("Email: ");
                if(validateEmail(email) == 1)
                {
                    break;
                }
                else
                {
                    continue;
                }
            }
            
            while(1) {
                continueInput = getInput("Action: ");
                len = strlen(continueInput);
                if(len > 1)
                {
                    continue;
                }
                else
                {
                    break;
                }
            }
            if(continueInput[0] == 'S')
            {
                current = numContacts;
                numContacts++;
                contactInput.phoneNumber = strtoul(phone, &phone, 10);
                contacts = realloc(contacts, sizeof(contact) * numContacts);
                contacts[current] = contactInput;
                
                firstNames = realloc(firstNames, sizeof(char *) * numContacts);
                lastNames = realloc(lastNames, sizeof(char *) * numContacts);
                companyNames = realloc(companyNames, sizeof(char *) * numContacts);
                emails = realloc(emails, sizeof(char *) * numContacts);
                originalAddress = realloc(originalAddress, sizeof(int) * numContacts);
                originalAddress[current] = current;
                
                if(first != NULL)
                {
                    firstNames[current] = malloc(sizeof(char) * (strlen(first) + 1));
                    strcpy(firstNames[current], first);
                    contacts[current].firstNamePosn = current;
                }
                else
                {
                   contacts[current].firstNamePosn = 0;
                }
                if(last != NULL)
                {
                    lastNames[current] = malloc(sizeof(char) * (strlen(last) + 1));
                    strcpy(lastNames[current], last);
                    contacts[current].lastNamePosn = current;
                }
                else
                {
                    contacts[current].lastNamePosn = 0;
                }
                if(company != NULL)
                {
                    companyNames[current] = malloc(sizeof(char) * (strlen(company) + 1));
                    strcpy(companyNames[current], company);
                    contacts[current].companyNamePosn = current;
                }
                else
                {
                    contacts[current].companyNamePosn = 0;
                }
                emails[current] = malloc(sizeof(char) * (strlen(email) + 1));
                strcpy(emails[current], email);
                contacts[current].emailPosn = current;
            }
            else if(continueInput[0] == 'R')
            {}
        }
        
        else if(continueInput[0] == 'X' && len == 1)
        {
            exitFlag = 1;
        }
        else if(isdigit(continueInput[0]))
        {
            isNum = 0;
            for(i = 0; i < strlen(continueInput); i++) {
                if(!isdigit(continueInput))
                {
                    isNum = 1;
                }
                current = atoi(continueInput);
                if(current < 1 || current > numContacts)
                {
                    isNum = 1;
                }
            }
            if(isNum == 0)
            {
                printf("Contact #%d\n", current);
                printf("First Name: %s\n", firstNames[originalAddress[current]]);
                printf("Last Name: %s\n", lastNames[originalAddress[current]]);
                printf("Company Name: %s\n", companyNames[originalAddress[current]]);
                printf("Phone Number: %lu\n", contacts[i].phoneNumber);
                printf("Email: %s\n", emails[originalAddress[current]]);
                while(1) {
                    continueInput = getInput("Action: ");
                    if(strlen(continueInput) != 1 || (continueInput[0] != 'R' || continueInput[0] != 'E' || continueInput[0] != 'D'))
                    {
                        continue;
                    }
                    else
                    {
                        break;
                    }
                }
                /* Return, Edit, Delete */
                if(continueInput[0] == 'R')
                {}
                else if(continueInput[0] == 'E')
                {
                    phone = NULL;
                    email = NULL;
                    printf("Contact #%d\n", current);
                    printf("First Name: %s\n", firstNames[originalAddress[current]]);
                    printf("Last Name: %s\n", lastNames[originalAddress[current]]);
                    printf("Company Name: %s\n", companyNames[originalAddress[current]]);
                    while(1) {
                        phone = getInput("Phone Number (enter only numbers): ");
                        if(validatePhone(phone) == 1 || phone == NULL)
                        {
                            break;
                        }
                        else
                        {
                            continue;
                        }
                    }
                    while(1) {
                        email = getInput("Email: ");
                        if(validateEmail(email) == 1 || email == NULL)
                        {
                            break;
                        }
                        else
                        {
                            continue;
                        }
                        /* Edit, Save */
                        while(1) {
                            continueInput = getInput("Action: ");
                            if(strlen(continueInput) != 1 || (continueInput[0] != 'R' || continueInput[0] != 'S'))
                            {
                                break;
                            }
                            else
                            {
                                continue;
                            }
                        }
                        if(continueInput[0] == 'R')
                        {}
                        else if(continueInput[0] == 'S')
                        {
                            contacts[current].phoneNumber = strtoul(phone, &phone, 10);
                            emails[originalAddress[current]] = malloc(sizeof(char) * (strlen(email) + 1));
                            strcpy(emails[originalAddress[current]], email);
                        }
                    }
                    
                }
                else if(continueInput[0] == 'D')
                {
                    /* Does not write contacts if the phone number is 0, which cannot happen naturally. */
                    contacts[current].phoneNumber = 0;
                    /* Because this isn't filtered out by the file, use numDeleted to give a number to the user. */
                    numDeleted++;
                }
                
            }
        }
        
        /* To my knowledge this actually records the data correctly. */
        rewind(fptr);
        i = 0;
        for(i = 0; i < numContacts; i++) {
            if(contacts[i].phoneNumber != 0)
            {
                first = NULL;
                last = NULL;
                company = NULL;
                email = NULL;
                first = firstNames[originalAddress[i]];
                last = lastNames[originalAddress[i]];
                company = companyNames[originalAddress[i]];
                email = emails[originalAddress[i]];

                contacts[i].firstNamePosn = ftell(fptr) + sizeof(contact);

                contacts[i].lastNamePosn = contacts[i].firstNamePosn + (sizeof(char) * (strlen(first) + 1));
                if(strlen(first) == 0)
                {
                    contacts[i].lastNamePosn = contacts[i].firstNamePosn;
                    contacts[i].firstNamePosn = 0;
                }

                contacts[i].companyNamePosn = contacts[i].lastNamePosn + (sizeof(char) * (strlen(last) + 1));
                if(strlen(last) == 0)
                {
                    contacts[i].companyNamePosn = contacts[i].lastNamePosn;
                    contacts[i].lastNamePosn = 0;
                }

                contacts[i].emailPosn = contacts[i].companyNamePosn + (sizeof(char) * (strlen(company) + 1));
                if(strlen(company) == 0)
                {
                    contacts[i].emailPosn = contacts[i].companyNamePosn;
                    contacts[i].companyNamePosn = 0;
                }

                contacts[i].next = contacts[i].emailPosn + (sizeof(char) * (strlen(email) + 1));

                fwrite(&contacts[i], sizeof(contact), 1, fptr);
                if(contacts[i].firstNamePosn != 0)
                {
                    fwrite(first, sizeof(char), strlen(first) + 1, fptr);
                }
                if(contacts[i].lastNamePosn != 0)
                {
                    fwrite(last, sizeof(char), strlen(last) + 1, fptr);
                }
                if(contacts[i].companyNamePosn != 0)
                {
                    fwrite(company, sizeof(char), strlen(company) + 1, fptr);
                }
                fwrite(email, sizeof(char), strlen(email) + 1, fptr);
            }
        }
        
        if(exitFlag != 0)
        {
            break;
        }
    }
    fclose(fptr);
    return 0;
}
