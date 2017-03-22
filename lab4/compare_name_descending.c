#include <stdlib.h>
#include "compareElements.h"

/* Compares names in descending alphabetical order. */

int compare_name_descending( const void *a, cont void *b )
{
    return ( *(element *)b.last_name - *(element *)a.last_name);
}
