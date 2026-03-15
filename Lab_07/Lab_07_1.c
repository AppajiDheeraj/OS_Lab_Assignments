#include<stdio.h>

struct process{
    int pid, at, bt, ct, tat, wt, rt;
};

void display(struct process p[], int n)
{
    float avgwt=0,avgtat=0;

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");

    for(int i=0;i<n;i++)
    {
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;

        avgwt += p[i].wt;
        avgtat += p[i].tat;

        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
        p[i].pid,p[i].at,p[i].bt,p[i].ct,p[i].tat,p[i].wt);
    }

    printf("\nAverage WT = %.2f",avgwt/n);
    printf("\nAverage TAT = %.2f\n",avgtat/n);
}

void sjf_nonpreemptive(struct process p[], int n)
{
    int completed=0,time=0,visited[20]={0};

    while(completed<n)
    {
        int idx=-1,min=9999;

        for(int i=0;i<n;i++)
        {
            if(p[i].at<=time && visited[i]==0 && p[i].bt<min)
            {
                min=p[i].bt;
                idx=i;
            }
        }

        if(idx!=-1)
        {
            time += p[idx].bt;
            p[idx].ct = time;
            visited[idx]=1;
            completed++;
        }
        else
            time++;
    }

    printf("\n--- SJF Non Preemptive ---\n");
    display(p,n);
}

void sjf_preemptive(struct process p[], int n)
{
    int completed=0,time=0;

    for(int i=0;i<n;i++)
        p[i].rt = p[i].bt;

    while(completed<n)
    {
        int idx=-1,min=9999;

        for(int i=0;i<n;i++)
        {
            if(p[i].at<=time && p[i].rt>0 && p[i].rt<min)
            {
                min=p[i].rt;
                idx=i;
            }
        }

        if(idx!=-1)
        {
            p[idx].rt--;
            time++;

            if(p[idx].rt==0)
            {
                p[idx].ct=time;
                completed++;
            }
        }
        else
            time++;
    }

    printf("\n--- SJF Preemptive (SRTF) ---\n");
    display(p,n);
}

int main()
{
    int n;
    struct process p[20],p1[20],p2[20];

    printf("Enter number of processes: ");
    scanf("%d",&n);

    for(int i=0;i<n;i++)
    {
        printf("\nProcess P%d\n",i+1);
        p[i].pid=i+1;

        printf("Arrival Time: ");
        scanf("%d",&p[i].at);

        printf("Burst Time: ");
        scanf("%d",&p[i].bt);
    }

    for(int i=0;i<n;i++)
    {
        p1[i]=p[i];
        p2[i]=p[i];
    }

    sjf_nonpreemptive(p1,n);
    sjf_preemptive(p2,n);

    return 0;
}