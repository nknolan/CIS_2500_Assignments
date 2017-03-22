#include <stdlib.h>
#include "compareElements.h"

int compare_id_ascending ( const void *a, const void *b )
{
    return ( *(element*)a.id_number - *(element*)b.id_number );
}
