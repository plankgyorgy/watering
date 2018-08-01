/*
* Type definitions
*/
typedef struct linkedlist_element
{
    // Previous element in the chain (NULL means this is the first)
    struct listelement *previous;

    // Next element in the chain (NULL means this is the last)
    struct listelement *next;

    // Data element
    void *data;
} linkedlist_element;

/*
* Global variables
*/
linkedlist_element *linkedlist_firstElement;

/*
* Function declarations
*/

/*
* List "class"
*/
typedef struct list
{
    // Number of contained elements
    int count;

    // Size of one contained data element
    int dataSize;

    // First element of the chain (null if empty); for inner use only
    linkedlist_element *linkedlist_firstElement;
} list;

/*
* List "factory" declaration
*/
list *CreateList(int size);