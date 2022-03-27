#include "utility.h"

double wait_sum = 0; 
double turnaround_sum = 0; 
double response_sum = 0;
double previous_ta = 0; 
double current_ta;
double previous_wait = 0; 
double current_wait;
double response_time;
double previous_burst;
struct node *current;
struct node *shortestTask;


sum(double current_burst){

    current_ta = previous_ta + current_burst;
    previous_ta = current_ta;
    turnaround_sum = turnaround_sum + current_ta;
    response_sum = response_sum + previous_burst;
    previous_burst = previous_burst + current_burst;
    current_wait = current_ta - current_burst;
    wait_sum = wait_sum + current_wait;
    
}

average(int counter ){
    int count = counter;
    wait_sum = wait_sum / (double) count;
    turnaround_sum = turnaround_sum / (double) count;
    response_sum = response_sum / (double) count;
}

print_averages(){
    printf("Average waiting time = %.2f\n", wait_sum);
    printf("Average turnaround time = %.2f\n", turnaround_sum);
    printf("Average response time = %.2f\n", response_sum);
   
}

