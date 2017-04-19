#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct student {
    int recordCount;
    char *firstName;
    char *lastName;
    char *id;
    char *email;
} student;

void sortStudents(student *toSort, int max)
{
    student temp;
    int i = 0;
    int j = 0;

    for(i = 0; i < (max - 1); i++) {
        for(j = 0; j < (max - i - 1); j ++) {
            if(atoi(toSort[j].id) > atoi(toSort[j+1].id)) {
                temp = toSort[j];
                toSort[j] = toSort[j+1];
                toSort[j+1] = temp;
            }
        }
    }
    return;
}

int main(void)
{
    char fName[50];
    char lName[50];
    char usrId[50];
    char usrEmail[300];
    
    int i = 0;
    int len = 0;
    int valid = 0;
    int count = 0;
    int current = 0;
    student *list = malloc(sizeof(student));
    
    while(1) {
        printf("First Name: ");
        fgets(fName, 50, stdin);
        if(fName[0] == '.' && strlen(fName) == 2) {
            break;
        }
        count++;
        printf("Last Name: ");
        fgets(lName, 50, stdin);
        
        valid = 0;
        while(valid == 0) {
            printf("ID#: ");
            fgets(usrId, 50, stdin);
            usrId[strlen(usrId)] = '\0';
            len = strlen(usrId);
            if(len == 10) {
                valid = 1;
            } else {
                printf("Must be 9 digits in length.\n");
                valid = 0;
            }
            
            for(i = 0; i < 9; i++) {
                if(isdigit(usrId[i]) == 0) {
                    printf("Must be numerical.\n");
                    valid = 0;
                }
            }
        }
        
        printf("Email:");
        fgets(usrEmail, 300, stdin);
        current = count - 1;
        
        list = realloc(list, sizeof(student) * count);
        list[current].recordCount = count;
        list[current].firstName = malloc((sizeof(char) * strlen(fName)) + 1);
        strncpy(list[current].firstName, fName, strlen(fName) - 1);
        list[current].lastName = malloc((sizeof(char) * strlen(lName)) + 1);
        strncpy(list[current].lastName, lName, strlen(lName) - 1);
        list[current].id = malloc((sizeof(char) * 9) + 1);
        strncpy(list[current].id, usrId, strlen(usrId) - 1);
        list[current].email = malloc((sizeof(char) * strlen(usrEmail)) + 1);
        strncpy(list[current].email, usrEmail, strlen(usrEmail));
    }   

    sortStudents(list, count);

    for(i = 0; i < count; i++) {
            printf("%s,%s,%s,%s", list[i].id, list[i].firstName, list[i].lastName, list[i].email);
    }
    return 0;
}
