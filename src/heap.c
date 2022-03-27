#include "heap.h"
#include <stdlib.h>

MinHeapNode* new_min_heap_node(int n, int dist) // Allocates memory for a new min heap node
{
    MinHeapNode *newHeapNode = (MinHeapNode*) malloc(sizeof(MinHeapNode));
    if (newHeapNode == NULL) // If memory wasn't possible to allocate for any reason.
    { 
        puts("Failed to allocate memory on the heap!");
        exit(-1);
    }
    newHeapNode->graph_node_id = n;
    newHeapNode->dist = dist;
    return newHeapNode;
}

Minheap* create_heap(int m) // Creates the heap where nodes will be stored.
{
    Minheap *newMinHeap = (Minheap*) malloc(sizeof(Minheap)); // Allocates memmory on the heap for the heap;
    newMinHeap->array = (MinHeapNode**) malloc(sizeof(MinHeapNode*)*m); // Create an N-size array of adjacency lists.  
    newMinHeap->pos = malloc(sizeof(int)*m);
    if (newMinHeap == NULL || newMinHeap->array == NULL || newMinHeap->pos == NULL) // If memory wasn't possible to allocate for any reason.
    { 
        puts("Failed to allocate memory on the heap!");
        exit(-1);
    }
    newMinHeap->max_size = m;
    newMinHeap->cur_size = 0;
    return newMinHeap;
}

int insert_heap(Minheap *h, MinHeapNode *n) // FRÅGA står "t" adjacent listnode to be inserted to the heap is that wrong or correct? // Inserts a task at the end of the heap.
{
    int pos;
    if (h->max_size == h->cur_size) return 0; // puts("Failed to insert, minheap is FULL"); // If minheap is full.
    else {
        h->cur_size++;
        pos = h->cur_size;
        h->array[pos] = n; // Inserts a MinHeapNode at the end of the heap.
        while (pos > 1) {
            int par = pos / 2;
            if (h->array[pos]->dist >= h->array[par]->dist) return 1; // MinHeapNode was inserted to heap.
            else { // Swaps the MinHeapNode inserted with the parent MinHeapNode.
                MinHeapNode *temp = h->array[pos];
                h->array[pos] = h->array[par];
                h->array[par] = temp;
                pos = par;
            }
        }
    }
    return 1; // MinHeapNode was inserted to heap.
}

int delete_heap(Minheap *h) // Delete a task from the heap.
{
    if ((is_empty(h)) == 1) return 0; // Heap is empty.
    else {
        MinHeapNode *last = h->array[h->cur_size];
        h->cur_size--;
        int ptr = 1, left = 2, right = 3;
        h->array[ptr] = last;
        if (h->cur_size == 0) h->array[1] = NULL; // If only one element in the array set the root to NULL.
        while (left <= h->cur_size) {
            if (h->array[ptr]->dist <= h->array[left]->dist && h->array[ptr]->dist <= h->array[right]->dist) return 1; // MinHeapNode was deleted.
            if(h->array[right]->dist >= h->array[left]->dist) { // Swaps the task pointed to by ptr with its left child.
                MinHeapNode *temp = h->array[ptr];
                h->array[ptr] = h->array[left];
                h->array[left] = temp;
                ptr = left;
            }
            else { // Swaps the task pointed to by ptr with its right child.
                MinHeapNode *temp = h->array[ptr];
                h->array[ptr] = h->array[right];
                h->array[right] = temp;
                ptr = right;
            }
            left = 2 * ptr; // Changes the value of left so that it represents the value of ptrs left child.
            right = left + 1; // Changes the value of right so that it represents the value of ptrs right child.
        }
    }
    return 1; // MinHeapNode was deleted.
}

void decreaseKey(Minheap* h, int n, int dist) // Decrease the distance value for given node and heapify the heap.
{
    int adjNodeId = h->pos[n], par; // Retrieve current index of node
    h->array[adjNodeId]->dist = dist; // Update value of distance of the node
    if ((par = (adjNodeId-1) / 2) == 0) par++; // Par can't be 0.

    while (h->array[adjNodeId]->dist < h->array[par]->dist && adjNodeId)
    {	 
        // Changes pos to still point to the correct index for both par and current node
        h->pos[h->array[adjNodeId]->graph_node_id] = par; 
        h->pos[h->array[par]->graph_node_id] = adjNodeId;
        // Swap
        MinHeapNode *temp = h->array[adjNodeId];
        h->array[adjNodeId] = h->array[par];
        h->array[par] = temp;
        // Move to par 
        adjNodeId = par;
        if ((par = (adjNodeId-1)/2) == 0) par++; // Par can't be 0.
    }
}

MinHeapNode* findmin(Minheap *h)  // Finds the node with the shortest dist (always the root of the binary minheap).
{
    if (is_empty(h) == 1) return NULL; // Empty heap.
    MinHeapNode *minDist = h->array[1];
    return minDist; // Return node with the shortest dist.
}

void destroy_heap(Minheap *h) // Frees the allocated memory for the heap.
{
    if (h != NULL) {
        free(h->array);
        free(h);
        h = NULL;
    }
    else puts("Failed to destroy heap");
}

void display_heap(Minheap *h) // Displays all the nodes in the heap.
{
    if(is_empty(h) == 1) puts("HEAP IS EMPTY");
    else {
        for(size_t i = 1; i <= h->cur_size; i++) 
        {
            printf("Heap elements are: %d\t", h->array[i]->graph_node_id);
        }
        printf("\n");
    }
}

int is_empty(Minheap *h) // Checks whether the heap is empty
{
    return (h->array[1] == NULL) ? 1 : 0; // If root is NULL heap is empty.
}