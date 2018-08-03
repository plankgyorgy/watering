/******************
* Type definitions
*******************/

// List element frame
typedef struct linkedlist_element
{
    // Previous element in the chain (NULL means this is the first)
    struct listelement *previous;

    // Next element in the chain (NULL means this is the last)
    struct listelement *next;

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
linkedlist_element *LinkedList_AddData(linkedlist *list, void *data);

// Creates and adds a new element to a list, initialized with given data
linkedlist *LinkedList_Add(void *data);

// Removes an element from the list
void LinkedList_RemoveElement(linkedlist *list, linkedlist_element *element);

// Removes an element from the list identified by its index
void LinkedList_RemoveByIndex(linkedlist *list, int index);

// Gets the address of data field of the index-th element of the list
void *LinkedList_GetDataByIndex(linkedlist *list, int index);

// Initializes a list as an empty one with known datasize
void LinkedList_InitializeSize(linkedlist *list, int size);

// Initializes data part of a wannabe list element
void LinkedList_InitializeElementByData(linkedlist_element *element, void *data);

// Gets the index-th element of the list (indexing starts at 0)
linkedlist_element *LinkedList_GetElementByIndex(linkedlist *list, int index);