#ifndef LINKEDLIST_STATIC_INCLUDED
    #define LINKEDLIST_STATIC_INCLUDED

    #include "linkedlist.h"

    /******************
    * Macros
    *******************/
    
    
    /***********************
    * Constants
    ************************/
    
    static struct linkedlist_error const LINKEDLIST_ERRORS[] =
    {
        {"UNKNOWN", "Unknown error"}
        ,{"MEMORYOUT", "Out of memory"}
        ,{"NOERROR", ""}
    };

    /***********************
    * Function declarations
    ************************/

    // Initializes a list as an empty one with known datasize
    static void LinkedList_InitializeWithSize(linkedlist *list, int size);

    // Initializes data part of a wannabe list element
    static void LinkedList_InitializeElementByData(linkedlist_element *element, void *data);

    // Gets the index-th element of the list (indexing starts at 0)
    static linkedlist_element *LinkedList_GetElementByIndex(linkedlist *list, int index);

    // Removes an element from the list
    static void LinkedList_RemoveElement(linkedlist *list, linkedlist_element *element);

    // Swaps data of two element
    static void LinkedList_Swap(linkedlist *list, linkedlist_element* one, linkedlist_element *other);

    // Merges two sorted list into a third sorted list
    static linkedlist *LinkedList_SortedMerge(linkedlist *one, linkedlist *other, bool ascending, bool (*comparator)(void *, void*));
    
    // Splits a list to two (almost)half part
    static bool LinkedList_SplitToTwo(linkedlist *whole, linkedlist *one, linkedlist *other);

    // Sets the global error information structure.
    static void LinkedList_SetLastError(char *errorCode);

#endif /* !LINKEDLIST_STATIC_INCLUDED */