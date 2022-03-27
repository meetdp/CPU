#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>

#include "task.h"
#include "list.h"
#include "cpu.h"

struct node *head = NULL;
struct node *current = NULL;



struct node *tmp;

int same_priority = 1;
int id = 0, count;
int bt[100] = {0};
int rem_bt[100] = {0};
int wt[100] = {0};
int time = 0;
double avg_wt = 0.0;
double avg_ta = 0.0;
Task *highestPriorityTask;
findNextTask();
calculate();

void add(char *name, int priority, int burst) {
    
    Task *newTask = (Task *) malloc(sizeof(Task));
    newTask->name = name;
    newTask->priority = priority;
    newTask->burst = burst;
    newTask->tid = id++;
    bt[count] = burst;
    rem_bt[count] = burst;
    count++;
    insert(&head, newTask);
}


 

void schedule() 
{
    Task *current;
    

    current = head;

    while (head != NULL) {
        findNextTask();
        current = highestPriorityTask;
        if (same_priority > 1){
            
            
            if (current->burst > QUANTUM) {
                
                run(current, QUANTUM);
                time+= QUANTUM;
                current->burst -= QUANTUM;
                delete(&head, current);
                insert(&head, current);
            }
            else {
                run(current, current->burst);
                time+= current->burst;
                wt[current->tid] = time - bt[current->tid];      
                delete(&head, current);
            }
        }
        else{
            
            run(current, current->burst);
            time+= current->burst;
            wt[current->tid] = time - bt[current->tid];  
            delete(&head, current);

        }
    }
    calculate();
    printf("Average wting time = %.2f\n", avg_wt);
    printf("Average turnaround time = %.2f\n", avg_ta);
    //printf("Average response time = %.2f\n", avgrt);
    
}



calculate(){
    int i;
    for(i = 0; i < count; i++){
        avg_wt += wt[i];
        avg_ta = avg_ta + (wt[i] + bt[i]);
    }
    avg_wt /= (double) count;
    avg_ta /= (double) count;

    /*for(j = 0; j < n; j++ ){

        if(bt[j] > QUANTUM){
            avgrt = avgrt + prev_burst;
            prev_burst = prev_burst + QUANTUM;
        }
        else{
            avgrt = avgrt + prev_burst;
            prev_burst = prev_burst + bt[j];
        }
    

    }
*/
}

 

findNextTask()
{
    
    struct node *current;
    current = head;
    
    highestPriorityTask = current->task;

    same_priority = 1;  

    
    while(current->next != NULL){
        current = current->next;
        if(current->task->priority > highestPriorityTask->priority){
            highestPriorityTask = current->task;
            same_priority = 1;    
        }
        else if(current->task->priority == highestPriorityTask->priority){
            same_priority++;
            highestPriorityTask = current->task;

        }

    }
}