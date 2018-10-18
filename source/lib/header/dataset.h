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
    
    typedef struct dataset_head
    {
        dataset_head *previous;
        dataset_head *next;
    } dataset_head;
    
    /******************
    * Macros
    *******************/
    
    
    
    /***********************
    * Function declarations
    ************************/

#ifdef __cplusplus
}
#endif

#endif /* DATASET_H */

