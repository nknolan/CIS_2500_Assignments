/* Function definitions for contactsList.c */
typedef struct contact contact;

char *getInput(char *message);
void readString(char *targetString, long start, long end, FILE *fptr);
int validateEmail(char *email);
int validatePhone(char *phone);
