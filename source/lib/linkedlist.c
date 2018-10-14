#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "linkedlist.h"
#include "linkedlist_static.h"

// Error description (if any)
static struct linkedlist_error linkedlist_lastError;

/*
* Creates a new, empty list having data members of the given size
*
* size: data size of the future element
*/
linkedlist *LinkedList_CreateSized(int size)
{
    linkedlist *ret;

    if ((ret = malloc(sizeof(linkedlist))) != NULL)
    {
        LinkedList_InitializeWithSize(ret, size);
    }

    return ret;
}

/*
* Creates and adds a new element to a list, initialized with given data
*
* list: the address of list
* data: the address of data to add to the list
*
* Returns true in case of success, otherwise false
*/
bool LinkedList_AddData(linkedlist *list, void *data)
{
	bool ret = false;
	linkedlist_element *newElement;
	
	if (list != NULL && data != NULL)
	{
		if ((newElement = (linkedlist_element *)malloc(sizeof(linkedlist_element))) != NULL)
		{
			// Add data to the element
			LinkedList_InitializeElementByData(newElement, data);
			
			// Add element to the list
			if (list->lastElement == NULL)
			{
				// This element is the first in the list
				list->firstElement = newElement;
				list->lastElement = newElement;
			}
			else
			{
				// Append the element to the end of the chain
				newElement->previous = list->lastElement;
				list->lastElement->next = newElement;
				list->lastElement = newElement;
			}
			
			list->count += 1;
			ret = true;
		}
	}

	return ret;
}

/*
* Removes an element from the list identified by its index
*
* list: the list containing the element
* index: the zero based index of the element
*/
void LinkedList_RemoveByIndex(linkedlist *list, int index)
{
	linkedlist_element *element;
	
	if ((element = LinkedList_GetElementByIndex(list, index)) != NULL)
	{
		LinkedList_RemoveElement(list, element);
	}
}

/*
* Gets the address of data field of the index-th element of the list (indexing starts at 0)
*
* list: address of the list containing the data
* index: the zero based index of the element containing the desired data
*
* Returns a pointer to the data of the element residing at given index, or NULL if the list doesn't exists or the index is out of valid range
*/
void *LinkedList_GetDataByIndex(linkedlist *list, int index)
{
	void *ret = NULL;
	linkedlist_element *element;
	
	if ((element = LinkedList_GetElementByIndex(list, index)) != NULL)
	{
		ret = element->data;
	}
	
	return ret;
}

/*
* Search for data
*
* list: address of the list containing the data
* comparator: address of function telling which element's data is the winner
*
* Returns the address of the first data element field that satisfies the comparator function
* 		or NULL pointer if none found.
* Comparator is satisfied when returns true value.
*/
void *LinkedList_SearchData(linkedlist *list, bool (*comparator)(void *))
{
	void *ret = NULL;
	linkedlist_element *element;

	if (list != NULL)
	{
		element = list->firstElement;

		while (element != NULL)
		{
			if ((*comparator)(element))
			{
				ret = element->data;
				break;
			}

			element = element->next;
		}
	}

	return ret;
}

/*
* Sorts the list
* 
* list: address of the list containing the data to sort
* ascending: when true, first will be the smallest and last the largest element; false means the opposite
* comparator: address of function that compares two data member
*
* Comparator function must accept two pointers of data members and return true, 
* if the first is "smaller" then the second, otherwise false.
*/
void LinkedList_Sort(linkedlist *list, bool ascending, bool (*comparator)(void *, void *))
{
	// TODO: Add prototype to header file
	linkedlist_element *pivot;

	if (list != NULL)
	{

	}
}

/*
* Removes and free all elements (with data) of a list
*
* list: address of list to clear
*/
bool LinkedList_Clear(linkedlist *list)
{
	bool ret = false;
	linkedlist_element *currentElement;
	
	if(list != NULL)
	{
		currentElement = list->firstElement;
		while(currentElement != list->lastElement)
		{
			free(currentElement->data);
			currentElement = currentElement->next;
			free(currentElement->previous);
		}
		free(list->lastElement->data);
		free(list->lastElement);
		
		list->count = 0;
		list->firstElement = NULL;
		list->lastElement = NULL; 

		ret = true;
	}

	return ret;	
}

/*
* Free all elements with data and also the list itself
*
* list: address of the list to destroy
*/
bool LinkedList_Free(linkedlist *list)
{
	bool ret = false;
	linkedlist_element *currentElement;
	
	if(list != NULL)
	{
		if(LinkedList_Clear(list))
		{
			free(list);

			ret = true;
		}
	}

	return ret;	
}

/*
* Gives the details of the last error
*
* pError: address of an error structure to fill
*/
void LinkedList_GetLastError(struct linkedlist_error *pError)
{
	if(LINKEDLIST_LASTERROR_EMPTY)
	{
		LinkedList_SetLastError("NOERROR");
	}

	if((*pError).errorCode = (char*)malloc(strlen(linkedlist_lastError.errorCode) + 1))
	{
		strcpy((*pError).errorCode, linkedlist_lastError.errorCode);
	}
	
	if((*pError).errorMessage = (char*)malloc(strlen(linkedlist_lastError.errorMessage) + 1))
	{
		strcpy((*pError).errorMessage, linkedlist_lastError.errorMessage);
	}
}

/*******************
* Static functions
********************/

/*
* Initializes a list as an empty one with known datasize
*
* list: address of the list to initialize
* size: data size of the future element
*/
static void LinkedList_InitializeWithSize(linkedlist *list, int size)
{
	if (list != NULL)
	{
		list->count = 0;
		list->dataSize = size;
		list->firstElement = NULL;
	}
}

/*
* Initializes data part of a wannabe list element
*
* element: the address of list element to initialize
* data: the address of data to initialize with
*/
static void LinkedList_InitializeElementByData(linkedlist_element *element, void *data)
{
	if (element != NULL)
	{
		element->previous = NULL;
		element->next = NULL;
		element->data = data;
	}
}

/*
* Gets the index-th element of the list (indexing starts at 0)
*
* list: address of the list containing the element
* index: the zero based index of the element
*
* Returns a pointer to the element residing at given index, or NULL if the list doesn't exists or the index is out of valid range
*/
static linkedlist_element *LinkedList_GetElementByIndex(linkedlist *list, int index)
{
	linkedlist_element *ret = NULL;
	
	if (list != NULL && index >= 0)
	{
		// TODO: can be optimized by count backward if index > count/2
		if (index < list->count)
		{
			for (int i = 0; i <= index ; i++)
			{
				if (i == 0)
				{
					ret = list->firstElement;
				}
				else
				{
					ret = ret->next;
				}
			}
		}
	}
	
	return ret;
}

/*
* Removes an element from the list
*
* list: the list containing the element
* element: the element to remove
*/
static void LinkedList_RemoveElement(linkedlist *list, linkedlist_element *element)
{
	if (list != NULL && element != NULL)
	{
		linkedlist_element *nextElement = element->next;
		linkedlist_element *previousElement = element->previous;
		
		// Detach the front of the element
		if (previousElement != NULL)
		{
			previousElement->next = nextElement;
		}
		else
		{
			list->firstElement = nextElement;
		}
		
		// Detach the tail of the element
		if (nextElement != NULL)
		{
			nextElement->previous = previousElement;
		}
		else
		{
			list->lastElement = previousElement;
		}
		
		// There's one less element in the list
		list->count -= 1;
		
		// Free memory
		free(element->data);
		free(element);
	}
}

/*
* Swaps data of two element
*
* list: the list containing the two element
* one: one element to swap data
* other: other elemen to swap data
*/
static void LinkedList_Swap(linkedlist *list, linkedlist_element* one, linkedlist_element *other)
{
	void *temp;

	if (list != NULL && one != NULL && other != NULL)
	{
		temp = one->data;
		one->data = other->data;
		other->data = temp;
	}
}

/*
* Merges two sorted list into a third sorted list
*
* one: one of two lists to merge
* other: other one of the two lists to merge
* ascending: when true, first will be the smallest and last the largest element; false means the opposite
* comparator: function that takes the decision which of two data element is bigger than other
*
* Comparator function must accept two pointers of data members and return true, 
* if the first is "smaller" then the second, otherwise false.
*/
static linkedlist *LinkedList_SortedMerge(linkedlist *one, linkedlist *other, bool ascending, bool (*comparator)(void *, void*))
{
	linkedlist *ret = NULL;
	linkedlist_element *oneElement, *otherElement;
	void *data;
	
	// Both lists have to exist
	if (one != NULL && other != NULL)
	{
		// Both have to have at least the same size of data
		if (one->dataSize == other->dataSize)
		{
			// Create the new list to return with
			ret = LinkedList_CreateSized(one->dataSize);

			// Starting with the first elements, read and compare 'till one of the lists ends
			oneElement = one->firstElement;
			otherElement = other->firstElement;
			while (oneElement != NULL && otherElement != NULL)
			{
				// We'll copy data of the next element
				if(data = malloc(ret->dataSize))
				{
					// Add the next element to the new list and step to the next one to compare
					if (comparator(oneElement->data, otherElement->data) && ascending)
					{
						LinkedList_AddData(ret, memcpy(data, oneElement->data, ret->dataSize));
						oneElement = oneElement->next;
					}
					else
					{
						LinkedList_AddData(ret, memcpy(data, otherElement->data, ret->dataSize));
						otherElement = otherElement->next;
					}
				}
				else
				{
					LinkedList_SetLastError("MEMORYOUT");
				}
			}

			// Finished with one, but the other has at least one member to add
			if (oneElement == NULL)
			{
				oneElement = otherElement;
			}
			while(oneElement != NULL)
			{
				if(data = malloc(ret->dataSize))
				{
					LinkedList_AddData(ret, memcpy(data, oneElement->data, ret->dataSize));
					oneElement = oneElement->next;
				}
				else
				{
					LinkedList_SetLastError("MEMORYOUT");
				}
			}
		}
	}

	return ret;
}

/*
* Splits a list to two (almost)half part
*
* whole: the list that has to be split. Must have at least 2 elements.
* one: to-be-first part of whole.
* other: to-be-last part of whole.
*
* returns: true if the process was successful, otherwise false.
*
* remarks: List without at least 2 elements can't be splitted to two, this is why the restriction.
*			Both one and other has to be an address to an empty linkedlist with the same datasize as whole.
*			If count of elements in whole  is odd, one will have one more elements than other.
*			TODO: this algorythm is only good for unordered list.
*/
static bool LinkedList_SplitToTwo(linkedlist *whole, linkedlist *one, linkedlist *other)
{
	bool ret = false;
	linkedlist_element *oneElement, *otherElement;
	void *copyOfData;
// TODO: free memory in case of error
	if(whole != NULL && one != NULL && other != NULL // original and the two halves has to exist
		&& whole->count > 1 // original has to be splittable (have at least 2 elements)
		&& whole->dataSize == one->dataSize == other->dataSize // original and the two halves has to be initialized to the same size of data
		&& one->count == other->count == 0) // the two halves has to be empty
	{		
		// Start stepping from the beginning to the end and back, until meet
		oneElement = whole->firstElement;
		otherElement = whole->lastElement;
		while (oneElement != otherElement && (oneElement->previous != otherElement->next))
		{
			if(copyOfData = malloc(one->dataSize))
			{
				// TODO: handle return value
				LinkedList_AddData(one, memcpy(copyOfData, oneElement->data, one->dataSize));
			}

			if(copyOfData = malloc(other->dataSize))
			{
				// TODO: handle return value
				LinkedList_AddData(other, memcpy(copyOfData, otherElement->data, other->dataSize));
			}

			oneElement = oneElement->next;
			otherElement = otherElement->previous;
		}

		// In case of odd elements in whole, one element rested, wich is given to first half
		if(oneElement == otherElement)
		{
			if(copyOfData = malloc(one->dataSize))
			{
				// TODO: handle return value
				LinkedList_AddData(one, memcpy(copyOfData, oneElement->data, one->dataSize));
			}
		}

		ret = true;
	}

	return ret;
}

static bool LinkedList_MergeSort(linkedlist *list, bool ascending, bool (*comparator)(void *, void *))
{
	bool ret = false;
	linkedlist *splittedOne, *splittedOther, *sortedList;
	linkedlist_element *currentElement;
// TODO: handle errors
	if(list != NULL)
	{
		if(list->count > 1)
		{
			splittedOne = LinkedList_CreateSized(list->dataSize);
			splittedOther = LinkedList_CreateSized(list->dataSize);

			LinkedList_SplitToTwo(list, splittedOne, splittedOther);
			LinkedList_MergeSort(splittedOne, ascending, comparator);
			LinkedList_MergeSort(splittedOther, ascending, comparator);
			sortedList = LinkedList_SortedMerge(splittedOne, splittedOther, ascending, comparator);
			
			// Change elements (originals to sorted) and free original ones
			LinkedList_Clear(list);
			currentElement = sortedList->firstElement;
			while(currentElement != NULL)
			{
				LinkedList_AddData(list, currentElement->data);
				currentElement = currentElement->next;
			}
			LinkedList_Free(sortedList);

			LinkedList_Free(splittedOne);
			LinkedList_Free(splittedOther);
		}

		ret = true;
	}

	return ret;
}

/*
* Sets the global error information structure.
*
* errorCode: code of error to search for in the predefined list of errors
*
* remarks: if no errorCode found in the list, the first (with code "UNKNOWN") will be set
*/
static void LinkedList_SetLastError(char *errorCode)
{
	int i;
	int errorCount = sizeof(LINKEDLIST_ERRORS) / sizeof(struct linkedlist_error);

	if(!LINKEDLIST_LASTERROR_EMPTY)
	{
		free(linkedlist_lastError.errorCode);
		free(linkedlist_lastError.errorMessage);
	}

	for(i = 0; i < errorCount; i++)
	{
		if(strcmp(LINKEDLIST_ERRORS[i].errorCode, errorCode) == 0)
		{
			if(linkedlist_lastError.errorCode = (char*)malloc(strlen(errorCode) + 1))
			{
				strcpy(linkedlist_lastError.errorCode, errorCode);
			}
			
			if(linkedlist_lastError.errorMessage = (char*)malloc(strlen(LINKEDLIST_ERRORS[i].errorMessage) + 1))
			{
				strcpy(linkedlist_lastError.errorMessage, LINKEDLIST_ERRORS[i].errorMessage);
			}

			break;
		}
	}
	if(i == errorCount)
	{
		if(linkedlist_lastError.errorCode = (char*)malloc(strlen(LINKEDLIST_ERRORS[0].errorCode) + 1))
		{
			strcpy(linkedlist_lastError.errorCode, LINKEDLIST_ERRORS[0].errorCode);
		}
		
		if(linkedlist_lastError.errorMessage = (char*)malloc(strlen(LINKEDLIST_ERRORS[0].errorMessage) + 1))
		{
			strcpy(linkedlist_lastError.errorMessage, LINKEDLIST_ERRORS[0].errorMessage);
		}
	}

	// TODO: add code to write information to stderr	
}