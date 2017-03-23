#include <stdio.h>
#include <stdlib.h>
#include "compareFunctions.h"
#include "compareElements.h"
 
int main()
{
   int i = 0;
   int size;
   int (*compare_ptr)(const void *a, const void *b);

   struct element array[] = { { 10, "Brown",   10000.0 },
                              { 1,  "White",   20000.0 },
                              { 20, "Black",   30000.0 },
                              { 5,  "Pink",    50000.0 },
                              { 3,  "Orange",  25000.0 },
                              { 2,  "Gray",   200000.0 } };

   size = 6;

   printf ("Original Array:\n");
   for ( i=0; i<size; i++ ) {
      printf ( "%02d. %10s %10.2f\n", array[i].id_number, array[i].last_name, array[i].salary );
   }

   compare_ptr = &compare_id_ascending;
   qsort ( array, size, sizeof(struct element), compare_ptr);
   printf ("Sorted by ID Number (ascending):\n");
   for ( i=0; i<size; i++ ) {
      printf ( "%02d. %10s %10.2f\n", array[i].id_number, array[i].last_name, array[i].salary );
   }

   compare_ptr = &compare_id_descending;
   qsort ( array, size, sizeof(struct element), compare_ptr);
   printf ("Sorted by ID Number (descending):\n");
   for ( i=0; i<size; i++ ) {
      printf ( "%02d. %10s %10.2f\n", array[i].id_number, array[i].last_name, array[i].salary );
   }

   compare_ptr = &compare_name_ascending;
   qsort ( array, size, sizeof(struct element), compare_ptr);
   printf ("Sorted by Last Name (ascending):\n");
   for ( i=0; i<size; i++ ) {
      printf ( "%02d. %10s %10.2f\n", array[i].id_number, array[i].last_name, array[i].salary );
   }

   compare_ptr = &compare_name_descending;
   qsort ( array, size, sizeof(struct element), compare_ptr);
   printf ("Sorted by Last Name (descending):\n");
   for ( i=0; i<size; i++ ) {
      printf ( "%02d. %10s %10.2f\n", array[i].id_number, array[i].last_name, array[i].salary );
   }

   compare_ptr = &compare_money_ascending;
   qsort ( array, size, sizeof(struct element), compare_ptr);
   printf ("Sorted by Salary (ascending):\n");
   for ( i=0; i<size; i++ ) {
      printf ( "%02d. %10s %10.2f\n", array[i].id_number, array[i].last_name, array[i].salary );
   }

   compare_ptr = &compare_money_descending;
   qsort ( array, size, sizeof(struct element), compare_ptr);
   printf ("Sorted by Salary (descending):\n");
   for ( i=0; i<size; i++ ) {
      printf ( "%02d. %10s %10.2f\n", array[i].id_number, array[i].last_name, array[i].salary );
   }

   return 0;
}
