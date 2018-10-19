#include "dataset.h"

/**
 * Adds a new element to the set
 *
 * @knownElement address of set header struct of a known element of the set
 * @newElement   address of set header struct of the wannabe element
 *
 * If newElement is going to be the first one, there can't be known element, so it should be NULL.
 */
bool AddElement(dataset_header *knownElement, dataset_header *newElement)
{
	bool ret = false;
	
	if (newElement != NULL)
	{
		if (knownElement != NULL)
		{
			newElement->previous = knownElement;
			newElement->next = knownElement->next;
			knownElement->next = newElement;
		}
		else
		{
			newElement->previous = newElement;
			newElement->next = newElement;
		}
		
		ret = true;
	}
	
	return ret;
}

/**
 * Removes an element from the set
 * 
 * @element address of set header structure to remove
 *
 * Set will be dereferenced in the removed header but neither the header nor its container will be changed (even not freed) any other way.
 */
bool RemoveElement(dataset_header *element)
{
	bool ret = false;
	
	element->previous->next = element->next;
	element->next->previous = element->previous;
	
	// Looks weird at the moment, but future can bring unknown changes.
	ret = true;
	
	return ret;
}

