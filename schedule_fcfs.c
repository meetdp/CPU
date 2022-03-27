
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "list.h"
#include "task.h"
#include "cpu.h"
#include "utility.h"


struct node *head = NULL;
struct node *tempHead;
int task_id = 1;
int count = 0;

void add(char *name, int priority, int burst){
    Task *newTask = (Task *)malloc(sizeof(Task));
    newTask->name = name;
    newTask->priority = priority;
    newTask->burst = burst;
    newTask->tid = task_id;
    task_id++;
    insert(&head, newTask);
    count++;

}

void schedule(){
    int i;
    tempHead = reverse(head);
    
        for (i = 0; i<count; i++){
            run(tempHead->task, tempHead->task->burst);
            sum(tempHead->task->burst);
            tempHead = tempHead->next;
        }
    
    average(count);
    print_averages();     
}












