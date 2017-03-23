#include <stdlib.h>
#include <string.h>
#include "compareElements.h"

/* Compares names in descending alphabetical order using strcmp. */

int compare_name_descending( const void *a, const void *b )
{
    struct element *element_a = (struct element *)a;
    struct element *element_b = (struct element *)b;
    return strcmp( element_b->last_name, element_a->last_name );
}
