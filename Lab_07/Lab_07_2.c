#include<stdio.h>

struct process{
    int pid,at,bt,priority,queue,ct,tat,wt,rt;
};

void display(struct process p[], int n)
{
    float avgwt=0,avgtat=0;

    printf("\nPID AT BT Q PR CT TAT WT\n");

    for(int i=0;i<n;i++)
    {
        p[i].tat=p[i].ct-p[i].at;
        p[i].wt=p[i].tat-p[i].bt;

        avgwt+=p[i].wt;
        avgtat+=p[i].tat;

        printf("P%d %d %d %d %d %d %d %d\n",
        p[i].pid,p[i].at,p[i].bt,p[i].queue,
        p[i].priority,p[i].ct,p[i].tat,p[i].wt);
    }

    printf("\nAverage WT=%.2f",avgwt/n);
    printf("\nAverage TAT=%.2f\n",avgtat/n);
}

void multilevel_nonpreemptive(struct process p[],int n)
{
    int time=0;

    for(int i=0;i<n;i++)
    {
        if(time<p[i].at)
            time=p[i].at;

        time+=p[i].bt;
        p[i].ct=time;
    }

    printf("\n--- Multilevel Queue Non Preemptive ---\n");
    display(p,n);
}

void multilevel_preemptive(struct process p[],int n)
{
    int completed=0,time=0;

    for(int i=0;i<n;i++)
        p[i].rt=p[i].bt;

    while(completed<n)
    {
        int idx=-1;

        for(int i=0;i<n;i++)
        {
            if(p[i].at<=time && p[i].rt>0)
            {
                if(idx==-1 || p[i].queue<p[idx].queue ||
                   (p[i].queue==p[idx].queue && p[i].priority<p[idx].priority))
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

    printf("\n--- Multilevel Queue Preemptive ---\n");
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
        p[i].pid=i+1;

        printf("\nProcess P%d\n",i+1);

        printf("Arrival Time: ");
        scanf("%d",&p[i].at);

        printf("Burst Time: ");
        scanf("%d",&p[i].bt);

        printf("Queue Number (1 or 2): ");
        scanf("%d",&p[i].queue);

        printf("Priority (for Queue1): ");
        scanf("%d",&p[i].priority);
    }

    for(int i=0;i<n;i++)
    {
        p1[i]=p[i];
        p2[i]=p[i];
    }

    multilevel_nonpreemptive(p1,n);
    multilevel_preemptive(p2,n);

    return 0;
}