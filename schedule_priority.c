
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "list.h"
#include "task.h"
#include "cpu.h"
#include "utility.h"


struct node *head = NULL;
struct node *current;
int id = 1;
int count = 0;
struct node *shortestBurstNode;
struct node *tempHead;

void add(char *name, int priority, int burst){
    Task *newTask = (Task *)malloc(sizeof(Task));
    newTask->name = name;
    newTask->priority = priority;
    newTask->burst = burst;
    newTask->tid = id;
    id++;
    insert(&head, newTask);
    count++;
}


void schedule(){
    int i;
       for (i = 0; i<count; i++){
            getHighestPriorityNode();
            tempHead = shortestBurstNode;
            run(tempHead->task, tempHead->task->burst);
            sum(tempHead->task->burst);
            delete(&head, shortestBurstNode->task);
       }
    
    average(count);
    print_averages();     
}



getHighestPriorityNode(){
        current = head;
        shortestBurstNode = current;
        while(current->next != NULL){
            current = current->next;
            if(current->task->priority >= shortestBurstNode->task->priority){
                shortestBurstNode = current;
            }
        }   
}








