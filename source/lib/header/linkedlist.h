#ifndef LINKEDLIST_INCLUDED
    #define LINKEDLIST_INCLUDED

    #include <stdbool.h>

    /******************
    * Macros
    *******************/
    #define LINKEDLIST_LASTERROR_EMPTY (linkedlist_lastError.errorCode == NULL && linkedlist_lastError.errorMessage == NULL)
    
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

    struct linkedlist_error
    {
        char *errorCode;
        char *errorMessage;
    };

    /***********************
    * Constants
    ************************/
    
    

    /***********************
    * Function declarations
    ************************/

    // Creates a new, empty list having data members of the given size
    linkedlist *LinkedList_CreateSized(int size);

    // Creates and adds a new element to a list, initialized with given data
    bool LinkedList_AddData(linkedlist *list, void *data);

    // Removes an element from the list identified by its index
    void LinkedList_RemoveByIndex(linkedlist *list, int index);

    // Gets the address of data field of the index-th element of the list
    void *LinkedList_GetDataByIndex(linkedlist *list, int index);

    // Search for data
    void *LinkedList_SearchData(linkedlist *list, bool (*comparator)(void *));

    // Removes and free all elements (with data) of a list
    bool LinkedList_Clear(linkedlist *list);

    // Free all elements with data of the list and also the list itself
    bool LinkedList_Free(linkedlist *list);

    // Gives the details of the last error
    void LinkedList_GetLastError(struct linkedlist_error *pError);
#endif /* !LINKEDLIST_INCLUDED */