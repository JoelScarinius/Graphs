#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "task.h"
#include "queue.h"
#include "printer.h"

#define N 1 // On average there will be one print task in N seconds.
#define P 60 // The printer in the lab can process P pages per minute (i.e. 60 seconds) at good quality.

static void printWelcomeMessage(); // This function prints a short welcome message.

void main() { 
    printWelcomeMessage(); // Prints welcome message to the screen.
    srand(time(NULL)); // Seeds the random function to not create the same sequences.
    int ct = 1; // Variable used to display current time in second.
    Printer *p = (Printer*)malloc(sizeof(Printer)); // Allocates memory for the printer.
    p->page_rate = P; // Decides the time it takes to print P pages per minute at good quality.
    p->current_task = NULL; // Sets the printer to be empty from start.
    p->time_remaining = 0; // Sets remaining time to 0 to kick of the printer simulation.
    Minheap *h = create_heap(); // Allocates memory for the binary heap and initializes its elements to NULL.
    Task *t = NULL;
    printf("\n Simulation starts...");
    while (ct != 10) { // Loops until current time has reached its limit.
        printer_status(p); // Displays the printers status to the screen.
        if (p->time_remaining > 0) printf("%d seconds to complete the current task.\n", p->time_remaining);
        // On average there will be one print task in N seconds but it is restricted to always creat a task at first iteration.
        if ((1 + rand() % N) == N || ct == 1) { 
            t = create_task(ct); // Creates a new task.
            // Inserts the new task at the correct place in the binary heap (if it is not full).
            if (insert_heap(h, t) == 0) puts("CAN'T INSERT TASK TO FULL QUEUE");
        }
        display_heap(h); // Displays the entire queue.
        if (is_busy(p) == 0) { // If the printer isn't busy.
            t = findmin(h); // Find task with the smallest number of pages.
            if (delete_heap(h) == 0) puts("CAN'T DELETE TASK FROM EMPTY QUEUE"); // Deletes task from the queue (if it is not empty).
            else {
                start_next(p, t); // Starts printing the task that was deleted from the queue.
                p->time_remaining = t->pages * (P / 60); // Initialize time remaining with proper time in seconds to preform task.
            }
        }
        if (p->time_remaining > 0) tick(p); // Decrement the remaining time of a task with 1 second.
        ct++; // Increment current time by 1 second.
    }
    destroy_heap(h); // Frees the memory allocated for the binary heap.
    puts("\nSIMULATION ENDS");
    fflush(stdin);
    getchar();
}

static void printWelcomeMessage() { // Prints welcome message to the screen.
    puts("*********************************************************************************************\n"
        "Welcome!\n"
        "This is a program that uses a binary heap implemented as an array to create a priority queue\n"
        "that is used to preform a simulation of a laboratory printer.\n"
        "Please enjoy!\n"
        "*********************************************************************************************");
}