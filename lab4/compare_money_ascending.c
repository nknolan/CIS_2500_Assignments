#include <stdlib.h>
#include "compareElements.h"

/* Compares the values of the float salary, ascending. */

int compare_money_ascending( const void *a, const void *b )
{
    return ( *(element *)a.salary - *(element *)b.salary );
}
