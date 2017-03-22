#include <stdlib.h>
#include "compareElements.h"

/* Compares the values of the float salary, ascending. */

int compare_money_descending( const void *a, const void *b )
{
    return ( *(element *)b.salary - *(element *)a.salary );
}
