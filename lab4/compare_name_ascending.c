#include <stdlib.h>
#include "compareElements.h"

/*Compares names in ascending alphabetical order. TODO: cast char to int?*/

int compare_name_ascending( const void *a, const void *b )
{
    return ( *(element*)a.last_name - *(element*)b.last_name)
}
    
