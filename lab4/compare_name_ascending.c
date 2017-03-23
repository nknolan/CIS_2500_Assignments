#include <stdlib.h>
#include "compareElements.h"

/*Compares names in ascending alphabetical order. TODO: cast char to int?*/

int compare_name_ascending( const void *a, const void *b )
{
    struct element *element1 = (struct element *)a;
    struct element *element1 = (struct element *)b;
    return strcmp(element1.last_name, element2.last_name);
}
    
