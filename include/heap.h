//the interface for the priority queue ADT based on min binary heap,
//and binary heap is implemented using array. 
//Written by He Tan, Spring 2022

#ifndef QUEUE_H_ /* Include guard */
#define QUEUE_H_

#include <stdio.h>
#include "graph.h"

//structure to represent a min heap node
typedef struct minHeapNode
{
    //the id of the node in graph
    int graph_node_id;
    //the distance between the node and the starting node
    int dist;
} MinHeapNode;

//structure to the min binary heap
typedef struct minheap{
	//the array size
    int max_size;
    //the last position of the array
    int cur_size;
    //pointer points to an array
    //The arary is used to maintain a mapping between the graph node id and the position of the heap node in the array  
    //need for decreasing key value
    //for example, "pos[n] = i" tells that the heap node of the graph node n is located in position i in the array of the heap
    int *pos;
	//pointer points to an array of pointers to the nodes in min heap
	MinHeapNode** array;
} Minheap;

//create a new heap node
//parameters: n, the graph node id
//            dist, the distance between the graph node and the starting node
//return: the pointer points to the heap node
MinHeapNode* new_min_heap_node(int n, int dist);

//create an empty binary heap
//parameters: m, the max size of the array
Minheap *create_heap(int m);
//insert an element 
//parameters: h, the pointer points to the heap.
//            t, the adjacent list node to be inserted into the queue
//return:  0, the heap is full.
//		   1, the element is inserted.
int insert_heap(Minheap *h, MinHeapNode *n);
//delete an element from the heap
//parameters: h, the pointer points to the heap.
//return: 0, the heap is full.
//		  1, the element is deleted.
int delete_heap(Minheap *h);
//decrease the key value (i.e. the dist value of the node n to the starting node),
//  and move up the node until the heap property is satisfied 
//parameter: h, the pointer points to the heap.
//           n, the id of the node
//           dist, the dist value of the node
void decreaseKey(Minheap* h, int n, int dist);
//find the minimun value in a heap 
//parameters: h, the pointer points to the heap.
//return: the printing task which has the smallest number of pages 
MinHeapNode *findmin(Minheap *h);
//destroy a heap and release the space allocated to the heap
//parameters: h, the pointer points to the heap.
void destroy_heap(Minheap *h);
//prints the heap represented in the array
//parameters: h, the pointer points to the heap.
void display_heap(Minheap *h);
//check whether the queue is empty
//parameters: *q, the pointer that points to the queue 
//returns: 1 (true) or 0 (false)
int is_empty(Minheap *h);

#endif