// The interface for the task ADT.
#ifndef TASK_H_ /* Include guard */
#define TASK_H_

//declare task
typedef struct task{
    //the timestamp when the printing task arrives 
    int time_stamp;
    //the number of pages to be printed in the task
    int pages;
} Task;

//create a printing task with the number of pages. 
//parameters:
//  ct, the current time (in second) when the task is created.
//return:
//  the pointer that points to to the task
Task* create_task(int ct);


#endif