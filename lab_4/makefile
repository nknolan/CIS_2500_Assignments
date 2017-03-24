CC=gcc
CFLAGS=-Wall -ansi
objects = sortMe.o compare_id_ascending.o compare_id_descending.o compare_name_ascending.o compare_name_descending.o compare_money_ascending.o compare_money_descending.o

sortMe: $(objects)
	$(CC) $(CFLAGS) -o sortMe $(objects)

sortMe.o: sortMe.c compareFunctions.h compareElements.h
	$(CC) $(CFLAGS) -c sortMe.c

compare_id_ascending.o: compare_id_ascending.c compareElements.h
	$(CC) $(CFLAGS) -c compare_id_ascending.c

compare_id_descending.o: compare_id_descending.c compareElements.h
	$(CC) $(CFLAGS) -c compare_id_descending.c

compare_name_ascending.o: compare_name_ascending.c compareElements.h
	$(CC) $(CFLAGS) -c compare_name_ascending.c

compare_name_descending.o: compare_name_descending.c compareElements.h
	$(CC) $(CFLAGS) -c compare_name_descending.c

compare_money_ascending.o: compare_money_ascending.c compareElements.h
	$(CC) $(CFLAGS) -c compare_money_ascending.c


compare_money_descending.o: compare_money_descending.c compareElements.h
	$(CC) $(CFLAGS) -c compare_money_descending.c

clean: sortMe
	rm sortMe sortMe.o compare_id_ascending.o compare_id_descending.o compare_name_ascending.o compare_name_descending.o compare_money_ascending.o compare_money_descending.o
