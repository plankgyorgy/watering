#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "singleset.h"

/**
 * Adds a new element to the set
 *
 * @param knownElement address of set header struct of a known element of the set
 * @param newElement   address of set header struct of the wannabe element
 *
 * If newElement is going to be the first one, there can't be known element, so it should be NULL.
 */
bool singleset_AddElement(singleset_header *knownElement, singleset_header *newElement)
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
 * @param element address of set header structure to remove
 *
 * Set will be dereferenced in the removed header but neither the header nor its container will be changed (even not freed) any other way.
 */
bool singleset_RemoveElement(singleset_header *element)
{
    bool ret = false;

    element->previous->next = element->next;
    element->next->previous = element->previous;

    // Looks weird at the moment, but future can bring unknown changes.
    ret = true;

    return ret;
}

/**
 * Wether the set contains exactly one element
 * 
 * @param knownElement Address of a set header of a known member
 */
bool singleset_IsLone(singleset_header *knownElement)
{
    return knownElement->next == knownElement && knownElement->previous == knownElement;
}

/******************** TESTS *****************************************/

/**
 * Testing the functionalities of the whole singleset stuff
 * 
 * @return EXIT_SUCCESS when everything is OK, otherwise EXIT_FAILURE
 */
int singleset_tests()
{
    struct teststruct
    {
        char firstName[10];
        char lastName[10];
        struct singleset_header listheader;
        int age;
    };
    
    int returnCode = EXIT_SUCCESS;

    struct teststruct testData[3];

    testData[0].age = 31;
    strcpy(testData[0].firstName, "Finnigan");
    strcpy(testData[0].lastName, "Filigrain");

    testData[1].age = 17;
    strcpy(testData[1].firstName, "Abigail");
    strcpy(testData[1].lastName, "Zealote");

    testData[2].age = 29;
    strcpy(testData[2].firstName, "Golotea");
    strcpy(testData[2].lastName, "Brainbrush");

    printf("Creating the set by \"adding\" the first element: %s, %s; aged %d\n",
           testData[0].lastName,
           testData[0].firstName,
           testData[0].age);
    if (singleset_AddElement(NULL, &testData[0].listheader))
    {
        printf("Set created.\n");
        
        if (singleset_IsLone(&testData[0].listheader))
        {
            printf("Set is lone now.\n");
        }
        else
        {
            printf("Error: set contains one element but looks like it's not lone.");
            printf(" Just a tipp: start to debug at IsLone() function.\n");
            
            returnCode = EXIT_FAILURE;
        }

        for (int i = 1; 
             (i < sizeof(testData) / sizeof(struct teststruct))
                                           && (returnCode == EXIT_SUCCESS);
             i++)
        {
            printf("Adding the next element: %s, %s; aged %d\n",
                   testData[i].lastName,
                   testData[i].firstName,
                   testData[i].age);
            if (singleset_AddElement(&testData[0].listheader, &testData[i].listheader))
            {
                printf("Element added.\n");
                
                if (!singleset_IsLone(&testData[i - 1].listheader))
                {
                    printf("Set is not lone now.\n");
                }
                else
                {
                    printf("Error: set contains more then one element but looks like it's lone.");
                    printf(" Just a tipp: start to debug at IsLone() function.\n");

                    returnCode = EXIT_FAILURE;
                }
            }
            else
            {
                printf("Adding the element failed.\n");
                returnCode = EXIT_FAILURE;
            }
        }
        
        if (returnCode == EXIT_SUCCESS)
        {
            printf("Picking an element by the value of a field.\n");
            singleset_header *testptr = &(testData[2].listheader);
            struct teststruct *pickedElement = singleset_PickElement(testptr, struct teststruct, listheader, age, 17);
            if (pickedElement == NULL)
            {
                printf("No element found");
                returnCode = EXIT_FAILURE;
            }
            else
            {
                printf("Found matching element: %s, %s", pickedElement->lastName, pickedElement->firstName);
            }
        }
    }
    else
    {
        printf("Creation of set failed.\n");
        returnCode = EXIT_FAILURE;
    }
    
    return returnCode;
}


