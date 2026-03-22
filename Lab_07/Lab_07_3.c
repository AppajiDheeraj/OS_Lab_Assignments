#include<stdio.h>
#include<stdlib.h>

void preemptive(int *at, int *bt, int *ct, int *wt, int *tat,int *rt, int n, int *finished,  int *q){
 int completed = 0;
    int time = 0; 
    // int best = 9999;
    while(completed < n){
        int idx = -1;
        for(int i = 0; i <n; i++){
            if(at[i] <= time  && finished[i] == 0 && q[i] == 1){
                idx = i;
                break;
            }
        }
        if(idx == -1){
            for(int i = 0; i <n; i++){
            if(at[i] <= time &&finished[i] == 0 && q[i] == 2){
                idx = i;
                break;
            }
        }
        }
        if(idx == -1){
            for(int i = 0; i <n; i++){
            if(at[i] <= time &&finished[i] == 0 && q[i] == 3){
                idx = i;
                break;
            }
        }
        }
        if(idx == -1){
            time++;
        }else{
            
            if(q[idx] == 1){
                if(rt[idx] <= 2){
                    time += rt[idx];
                    rt[idx] = 0;
                    finished[idx] = 1;
                    ct[idx] = time;
                    completed++;
                }else{
                    time += 2;
                    rt[idx] -= 2;
                    q[idx] = 2;
                }

            }
             
            else if(q[idx] == 2){
                if(rt[idx] <= 4){
                    time += rt[idx];
                    rt[idx] = 0;
                    finished[idx] = 1;
                    ct[idx] = time;
                    completed++;
                }else{
                    time += 4;
                    rt[idx] -= 4;
                    q[idx] = 3;
                }

            }

            else{
                time += rt[idx];
                rt[idx] = 0;
                ct[idx] = time;
                finished[idx] = 1;
                completed++;
            }
        
        }
    }

    for(int i = 0; i < n; i++){
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
    }
}


int main(){

    int n;
    printf("Enter the no of processes: ");
    scanf("%d",&n);

    int at[n], bt[n], ct[n], wt[n], tat[n], rt[n], q[n], finished[n];
    for(int i = 0 ; i < n; i++){
        printf("Enter the AT, BT and Queue no for process %d : ",i);
        scanf("%d %d %d",&at[i],&bt[i],&q[i]);
        rt[i] = bt[i];
        finished[i] = 0;
    }
   
    preemptive(at,bt,ct,wt,tat,rt,n,finished,q);

    float avgtat = 0;
    float avgwt = 0;

    printf("\n| AT | CT | BT | WT | TAT |\n");
    for(int i = 0; i < n; i++){
        printf("|  %d  |  %d  |  %d  |  %d  |  %d  |\n",at[i],ct[i],bt[i],wt[i],tat[i]);
        avgtat += tat[i];
        avgwt += wt[i];
    }

    printf("Average TAT: %f\n",avgtat/n);
    printf("Average WT: %f\n",avgwt/n);

    return 0;
}
