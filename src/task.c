#include "task.h"
#include <stdlib.h>
#include <stdio.h>

#define M 10 // The size of the print tasks ranges from 1 to M pages.

Task* create_task(int ct) { // Creates a printing task with a random number of pages.
    Task *t = (Task*)malloc(sizeof(Task)); // Allocates memory for a task on the heap.
    if (t == NULL) { // If memory wasn't possible to allocate for any reason.
        puts("Failed to allocate memory on the heap!");
        exit(-1);
    }
    t->pages = 1 + rand() % M; // Generates a random number of pages from 1-M for the task.
    t->time_stamp = ct;
    return t;
}