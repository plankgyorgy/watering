/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   dataset.h
 * Author: irokez
 *
 * Created on 18 October 2018, 23:28
 */

#ifndef DATASET_H
#define DATASET_H

#include <stdbool.h>
#include <linux/kernel.h> // for container_of()

#ifdef __cplusplus
extern "C" 
{
#endif

    /******************
    * Type definitions
    *******************/
    
    typedef struct dataset_header
    {
        dataset_head *previous;
        dataset_head *next;
    } dataset_header;
    
    /******************
    * Macros
    *******************/
    
	#define PickElement(knownElement, type, headerField, searchedField, searchValue) \
		({                                                                           \
			type *currentElement = container_of(knownElement, type, headerField);    \
			do                                                                       \
			{                                                                        \
				if (currentElement->searchedField == searchValue)                    \
				{                                                                    \
					
				}                                                                    \
				                                                                     \
				currentElement = currentElement->next;                               \
			} while (currentElement->next != knownElement->next)                     \
		})
    
    
    /***********************
    * Function declarations
    ************************/
	
	// Adds a new element to the set
	bool AddElement(dataset_header *knownElement, dataset_header *newElement);
	
	// Removes an element from the set
	bool RemoveElement(dataset_header *element);

#ifdef __cplusplus
}
#endif

#endif /* DATASET_H */

