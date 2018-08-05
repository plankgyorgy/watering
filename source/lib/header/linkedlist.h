#include <stdbool.h>

/******************
* Type definitions
*******************/

// List element frame
typedef struct linkedlist_element
{
    // Previous element in the chain (NULL means this is the first)
    struct linkedlist_element *previous;

    // Next element in the chain (NULL means this is the last)
    struct linkedlist_element *next;

    // Data element
    void *data;
} linkedlist_element;

// List "class"
typedef struct linkedlist
{
    // Number of contained elements
    int count;

    // Size of one contained data element
    int dataSize;

    // First element of the chain (null when the list is empty); for inner use only
    linkedlist_element *firstElement;

    // Last element of the chain (null when the list is empty); for inner use only
    linkedlist_element *lastElement;
} linkedlist;

/***********************
* Function declarations
************************/

// Creates a new, empty list having data members of the given size
bool LinkedList_AddData(linkedlist *list, void *data);

// Removes an element from the list identified by its index
void LinkedList_RemoveByIndex(linkedlist *list, int index);

// Gets the address of data field of the index-th element of the list
void *LinkedList_GetDataByIndex(linkedlist *list, int index);

// Removes an element from the list
static void LinkedList_RemoveElement(linkedlist *list, linkedlist_element *element);

// Initializes a list as an empty one with known datasize
static void LinkedList_InitializeWithSize(linkedlist *list, int size);

// Initializes data part of a wannabe list element
static void LinkedList_InitializeElementByData(linkedlist_element *element, void *data);

// Gets the index-th element of the list (indexing starts at 0)
static linkedlist_element *LinkedList_GetElementByIndex(linkedlist *list, int index);