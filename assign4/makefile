CC = gcc
CFLAGS = -Wall -ansi
objects = contactsList.o getInput.o readString.o validateEmail.o validatePhone.o

contactsList: $(objects)
	$(CC) $(CFLAGS) -o contactsList $(objects)

contactsList.o: contactsList.c functionDefns.h structDefn.h
	$(CC) $(CFLAGS) -c contactsList.c

getInput.o: getInput.c
	$(CC) $(CFLAGS) -c getInput.c

readString.o: readString.c
	$(CC) $(CFLAG) -c readString.c

validateEmail.o: validateEmail.c
	$(CC) $(CFLAGS) -c validateEmail.c

validatePhone.o: validatePhone.c
	$(CC) $(CFLAGS) -c validatePhone.c

clear: myContactsList.db
	rm myContactsList.db

clean: contactsList
rm contactsList $(objects)
