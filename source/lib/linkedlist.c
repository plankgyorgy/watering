#include <stdlib.h>

#include "linkedlist.h"

/*
* List "factory"
*/
list *CreateList(int size)
{
    list *ret;

    if ((ret = malloc(sizeof(list))) != NULL)
    {
        ret -> count = 0;
        ret -> dataSize = size;
    }

    return ret;
}