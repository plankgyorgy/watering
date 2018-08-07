#include <stdbool.h>
#include <stdlib.h>

#include "linkedlist.h"

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