#include "queue.h"
#include <stdlib.h>
#include <stdio.h>

static int n = 0;

Minheap *create_heap() { // Creates the heap where tasks will be stored.
    Minheap *h = (Minheap*)malloc(sizeof(Minheap)); // Allocates memmory on the heap for the heap;
    if (h == NULL) { // If memory wasn't possible to allocate for any reason.
        puts("Failed to allocate memory on the heap!");
        exit(-1);
    }
    for (size_t i = 0; i <= MAX ; i++) h->heap[i] = NULL;
    return h;
}

int insert_heap(Minheap *h, Task *t) { // Inserts a task at the end of the heap.
    int pos;
    if (n == MAX) return 0; // Heap is full.
    else {
        n = n + 1;
        pos = n;
        h->heap[n] = t; // Inserts a task at the end of the heap.
        while (pos > 1) {
            int par = pos / 2;
            if (h->heap[pos]->pages >= h->heap[par]->pages) return 1; // Task was inserted to heap.
            else { // Swaps the task inserted with the parent task.
                Task *temp = h->heap[pos];
                h->heap[pos] = h->heap[par];
                h->heap[par] = temp;
                pos = par;
            }
        }
    }
    return 1; // Task was inserted to heap.
}

int delete_heap(Minheap *h) { // Delete a task from the heap.
    if ((is_empty(h)) == 1) return 0; // Heap is empty.
    else {
        Task *last = h->heap[n];
        n = n - 1;
        int ptr = 1, left = 2, right = 3;
        h->heap[ptr] = last;
        if (n == 0) h->heap[1] = NULL; // If only one element in the heap set the root to NULL.
        while (left <= n) {
            if (h->heap[ptr]->pages <= h->heap[left]->pages && h->heap[ptr]->pages <= h->heap[right]->pages) return 1; // Task was deleted.
            if(h->heap[right]->pages >= h->heap[left]->pages) { // Swaps the task pointed to by ptr with its left child.
                Task *temp = h->heap[ptr];
                h->heap[ptr] = h->heap[left];
                h->heap[left] = temp;
                ptr = left;
            }
            else { // Swaps the task pointed to by ptr with its right child.
                Task *temp = h->heap[ptr];
                h->heap[ptr] = h->heap[right];
                h->heap[right] = temp;
                ptr = right;
            }
            left = 2 * ptr; // Changes the value of left so that it represents the value of ptrs left child.
            right = left + 1; // Changes the value of right so that it represents the value of ptrs right child.
        }
    }
    return 1; // Task was deleted.
}

Task *findmin(Minheap *h) { // Finds the task with the minimum number of pages (always the root of the binary minheap).
    if (is_empty(h) == 1) return NULL; // Empty queue.
    Task *minPages = h->heap[1];
    return minPages; // Return task with the minimum number of pages.
}

void destroy_heap(Minheap *h) { // Frees the allocated memory for the heap.
    if (h != NULL) {
        free(h);
        h = NULL;
    }
    else puts("failed to destroy heap");
}

void display_heap(Minheap *h) { // Displays all the tasks in the queue.
    if(is_empty(h) == 1) puts("QUEUE IS EMPTY");
    else {
        puts("TASKS IN QUEUE:");
        for(size_t i = 1; i <= n; i++) {
            printf("[task: %d pages, arrives at %d second], ", h->heap[i]->pages, h->heap[i]->time_stamp);
        }
        printf("\n");
    }
}

int is_empty(Minheap *h) { // Checks whether the queue is empty
    return (h->heap[1] == NULL) ? 1 : 0; // If root is NULL queue is empty.
}