#include "printer.h"
#include <stdio.h>

void tick(Printer *p) { // Does one second of printing.
    p->time_remaining--;
}
int is_busy(Printer *p) { // Checks whehter the printer is printing.
    return (p->time_remaining != 0) ? 1 : 0;
}
void start_next(Printer *p, Task *t) { // Starts the task that is the front of the q. 
    p->current_task = t;
}
void printer_status(Printer *p) { // Prints the printers status to the screen.
    (p->time_remaining != 0) ? puts("\nTHE PRINTER IS BUSY") : puts("\nTHE PRINTER IS NO LONGER BUSY");
}