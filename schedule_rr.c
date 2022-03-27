
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "list.h"
#include "task.h"
#include "cpu.h"
#include "utility.h"


struct node *head = NULL;
struct node *current;
int task_id = 1;
int n = 0; // number of process
int i,j; // looping variable
int q = QUANTUM;
double prev_burst = 0.0;
double avgrt = 0.0;
int counter = 0;
int count = 0; // counts number of processes that are completed
int temp, sq; // temporary variables;
int bt[100];    //stores burst time of all processes
int wt[100];    //stores waiting time of all processes
int tat[100];   //stores touraround time of all processes
int rem_bt[100]; // stores remaining burst time of all processes
float awt = 0;  // average waiting time
float atat = 0; // average turnaround time


void add(char *name, int priority, int burst){
    Task *newTask = (Task *)malloc(sizeof(Task));
    newTask->name = name;
    newTask->priority = priority;
    newTask->burst = burst;
    bt[n] = burst;
    rem_bt[n]=bt[n];
    newTask->tid = task_id;
    task_id++;
    insert(&head, newTask);
    n++;
    counter++;

}

void schedule(){
    calc();
    while(count > 0){
        run_scheduler();
        }
   
    printf("Average waiting time = %.2f\n", awt);
    printf("Average turnaround time = %.2f\n", atat);
    printf("Average response time = %.2f\n", avgrt);


}
calc(){
  while (1){
    for(i=0,count=0;i<n;i++){
        temp = QUANTUM;
        if(rem_bt[i]==0){
            count++;
            continue;
        }
        if(rem_bt[i]>QUANTUM)
            rem_bt[i] = rem_bt[i]-QUANTUM;
        
        else
            if(rem_bt[i]>=0){
                temp = rem_bt[i];
                rem_bt[i]=0;
            }
            sq = sq + temp;
            tat[i]=sq;
    }
    
        if(n==count)
        break;
  }

    for(i=0;i<n;i++){
        wt[i]=tat[i]-bt[i];
        awt = awt + wt[i];
        atat = atat + tat[i];
    }
    awt = awt/n;
    atat = atat/n;

    
    for(j = 0; j < n; j++ ){

        if(bt[j] > QUANTUM){
            avgrt = avgrt + prev_burst;
            prev_burst = prev_burst + QUANTUM;
        }
        else{
            avgrt = avgrt + prev_burst;
            prev_burst = prev_burst + bt[j];
        }
    

    }

    avgrt = avgrt / (double) n;


}

run_scheduler(){
    current = head;
    runRecursive(current, head);
}

runRecursive(struct node *current, struct node *head){
    if(current->next == NULL){
        if(current->task->burst > QUANTUM){
            run(current->task, QUANTUM);
            current->task->burst -= QUANTUM;

        }
        else{
            run(current->task, current->task->burst);
            delete(&head, current->task);
            counter--;

        }
        return;
    }
    else{
        runRecursive(current->next, head);
        if(current->task->burst > QUANTUM){
            run(current->task, QUANTUM);
            current->task->burst -= QUANTUM;

        }
        else{
            run(current->task, current->task->burst);
            delete(&head, current->task);
            counter--;


        }
    }

}











