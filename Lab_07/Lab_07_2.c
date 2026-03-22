#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

void nonPremptive(int *at, int *bt, int *ct, int *wt, int *tat, int n, int *finished, int *p, int *q){
    printf("NonPremptive\n");
    int completed = 0;
    int time = 0;
    int best;

    while(completed < n){
        int idx = -1;
        best = 99;

        for(int i = 0; i < n; i++){
            if(at[i] <= time && p[i] < best && finished[i] == 0 && q[i] == 1){
                best = p[i];
                idx = i;
            }
        }

        if(idx == -1){
            for(int i = 0; i < n; i++){
                if(at[i] <= time && finished[i] == 0 && q[i] == 2){
                    idx = i;
                    break;
                }
            }
        }

        if(idx == -1){
            time++; 
        } else {
            time += bt[idx];  
            ct[idx] = time;  
            finished[idx] = 1;  
            completed++; 
        }
    }

    for(int i = 0; i < n; i++){
        tat[i] = ct[i] - at[i];  
        wt[i] = tat[i] - bt[i]; 
    }
}

void preemptive(int *at, int *bt, int *ct, int *wt, int *tat, int *rt, int n, int *finished, int *p, int *q) {
    int completed = 0;
    int time = 0;
    int best;

    while(completed < n) {
        int idx = -1;
        best = 99;

        for (int i = 0; i < n; i++) {
            if (at[i] <= time && p[i] < best && finished[i] == 0 && q[i] == 1) {
                best = p[i];
                idx = i;
            }
        }

        if (idx == -1) {
            for (int i = 0; i < n; i++) {
                if (at[i] <= time && finished[i] == 0 && q[i] == 2) {
                    idx = i;
                    break;
                }
            }
        }

        if (idx == -1) {
            time++;
        } else {
            time++;   
            rt[idx]--; 


            if (rt[idx] == 0) {
                ct[idx] = time; 
                finished[idx] = 1;  
                completed++; 
            }
        }
    }

    for (int i = 0; i < n; i++) {
        tat[i] = ct[i] - at[i];  
        wt[i] = tat[i] - bt[i];  
    }
}
int main(){

    int n;
    printf("Enter the no of processes: ");
    scanf("%d",&n);

    int at[n], bt[n], ct[n], wt[n], tat[n], rt[n],p[n], q[n], finished[n];
    for(int i = 0 ; i < n; i++){
        printf("Enter the AT, BT, Priority and Queue no for process %d : ",i);
        scanf("%d %d %d %d",&at[i],&bt[i],&p[i],&q[i]);
        rt[i] = bt[i];
        finished[i] = 0;

    }

   
    int select;
    printf(" For Non-Premptive enter 1 and for Premptive enter 2 : ");
    scanf("%d",&select);               


    if(select == 1){
        nonPremptive(at,bt,ct,wt,tat,n, finished,p,q);

    }else{
        preemptive(at,bt,ct,wt,tat,rt,n,finished,p,q);
    }
   

    float avgtat = 0;
    float avgwt = 0;

    printf("| AT | CT | BT | WT | TAT |\n");
    for(int i = 0; i < n; i++){
        printf("|  %d   |  %d   |  %d   |  %d   |   %d   |\n",at[i],ct[i],bt[i],wt[i],tat[i]);
        avgtat += tat[i];
        avgwt += wt[i];
    }

    printf("Average TAT: %f\n",avgtat/n);
    printf("Average WT: %f\n",avgwt/n);

    return 0;
}
