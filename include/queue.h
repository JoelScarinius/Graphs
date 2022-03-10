//the interface for the priority queue ADT based on min binary heap,
//and binary heap is implemented using array. 
//Written by He Tan, Feb 2022
#include "task.h"

#ifndef QUEUE_H_ /* Include guard */
#define QUEUE_H_

#include <stdio.h>
#include <stdlib.h>

#define MAX 20 // This define sets the maximum size of the array used to implement the min binary heap.

//an incomplete declaration for a min binary heap
//complete this in .c file.
typedef struct minheap {
    Task *heap[MAX];
} Minheap;

//create an empty binary heap
//parameters: m, the max size of the array
Minheap *create_heap();
//insert an element 
//parameters: h, the pointer points to the heap.
//            t, the task to be inserted into the queue
//return:  0, the heap is full.
//		   1, the element is inserted.
int insert_heap(Minheap *h, Task *t);
//delete an element 
//parameters: h, the pointer points to the heap.
//return: 0, the heap is empty.
//		  1, the element is deleted.
int delete_heap(Minheap *h);
//find the minimun value in a heap 
//parameters: h, the pointer points to the heap.
//return: the printing task which has the smallest number of pages 
Task *findmin(Minheap *h);
//destroy a heap and release the space allocated to the heap
//parameters: h, the pointer points to the heap.
void destroy_heap(Minheap *h);
//prints the heap represented in the array
//parameters: h, the pointer points to the heap.
void display_heap(Minheap *h);
//check whether the queue is empty
//parameters: *h, the pointer that points to the heap 
//returns: 1 (true) or 0 (false)
int is_empty(Minheap *h);


#endif