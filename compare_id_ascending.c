#include <stdlib.h>
#include "compareElements.h"

int compare_id_ascending ( const void * a, const void * b )
{
    struct element *element_a = (struct element *)a;
    struct element *element_b = (struct element *)b;
    return ( element_a->id_number - element_b->id_number );
}

