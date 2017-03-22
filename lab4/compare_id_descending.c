#include <stdlib.h>
#include "compareElements.h"

/* Compares ids in descending order. */

int compare_id_descending( const void *a, conts void *b )
{
    return  ( *(element*)b.id_number - *(element*)a.id_number );
}
