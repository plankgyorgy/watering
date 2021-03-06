/* 
 * File:   singleset.h
 * Author: irokez
 *
 * Created on 18 October 2018, 23:28
 */

#ifndef SINGLESET_H
#define SINGLESET_H

#include <stdbool.h>
#include <stddef.h> // for offsetof()

#ifdef __cplusplus
extern "C" 
{
#endif

    /******************
    * Type definitions
    *******************/
    
    typedef struct singleset_header
    {
        struct singleset_header *previous;
        struct singleset_header *next;
    } singleset_header;
    
    /******************
    * Macros
    *******************/
    
    /**
     * Gives the container structure of a member of the structure
     * 
     * @param ptr Address of a member of a structure 
     * @param type The type of the structure
     * @param member The name of the member given as 1st. parameter
     * @return Pointer to the structure containing the set element handler
     * 
     * (c)This is an exact copy of the famous macro from the Linux kernel
     */
    #define container_of(ptr, type, member) ({                      \
            const typeof(((type *)0)->member) *__mptr = (ptr);      \
            (type *)( (char *)__mptr - offsetof(type,member));})
    
    /**
     * Picks the first element found based on a scalar value of a field
     * 
     * @param knownElement
     * @param newElement
     * @return One element when found, NULL when not found
     */    
    #define singleset_PickElement(knownElement, type, headerField, searchedField, searchValue)     \
            ({                                                                           \
                type *currentElement = container_of(knownElement, type, headerField);    \
                do                                                                       \
                {                                                                        \
                        if (currentElement->searchedField == searchValue)                \
                        {                                                                \
                            break;                                                       \
                        }                                                                \
                                                                                         \
                        currentElement = container_of(currentElement->headerField.next,  \
                                                      type,                              \
                                                      headerField);                      \
                } while (&currentElement->headerField != (knownElement));                \
                currentElement->searchedField == (searchValue) ? currentElement : NULL;  \
            })



    /***********************
     * Function declarations
     ************************/

    // Adds a new element to the set
    bool singleset_AddElement(singleset_header *knownElement, singleset_header *newElement);

    // Removes an element from the set
    bool singleset_RemoveElement(singleset_header *element);

    // Wether the set contains exactly one element
    bool singleset_IsLone(singleset_header *knownElement);

    // Testing the functionalities of the whole singleset stuff
    int singleset_tests();

#ifdef __cplusplus
}
#endif

#endif /* SINGLESET_H */

