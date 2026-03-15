#include<stdio.h>

struct process{
    int pid,at,bt,rt,ct,tat,wt;
};

int main()
{
    int n;
    printf("Enter number of processes: ");
    scanf("%d",&n);

    struct process p[20];

    for(int i=0;i<n;i++)
    {
        p[i].pid=i+1;

        printf("\nProcess P%d\n",i+1);

        printf("Arrival Time: ");
        scanf("%d",&p[i].at);

        printf("Burst Time: ");
        scanf("%d",&p[i].bt);

        p[i].rt=p[i].bt;
    }

    int tq1=2,tq2=4,time=0;

    // Queue1
    for(int i=0;i<n;i++)
    {
        if(p[i].rt>0)
        {
            if(p[i].rt>tq1)
            {
                time+=tq1;
                p[i].rt-=tq1;
            }
            else
            {
                time+=p[i].rt;
                p[i].rt=0;
                p[i].ct=time;
            }
        }
    }

    // Queue2
    for(int i=0;i<n;i++)
    {
        if(p[i].rt>0)
        {
            if(p[i].rt>tq2)
            {
                time+=tq2;
                p[i].rt-=tq2;
            }
            else
            {
                time+=p[i].rt;
                p[i].rt=0;
                p[i].ct=time;
            }
        }
    }

    // Queue3 FCFS
    for(int i=0;i<n;i++)
    {
        if(p[i].rt>0)
        {
            time+=p[i].rt;
            p[i].rt=0;
            p[i].ct=time;
        }
    }

    float avgwt=0,avgtat=0;

    printf("\nPID AT BT CT TAT WT\n");

    for(int i=0;i<n;i++)
    {
        p[i].tat=p[i].ct-p[i].at;
        p[i].wt=p[i].tat-p[i].bt;

        avgwt+=p[i].wt;
        avgtat+=p[i].tat;

        printf("P%d %d %d %d %d %d\n",
        p[i].pid,p[i].at,p[i].bt,
        p[i].ct,p[i].tat,p[i].wt);
    }

    printf("\nAverage WT=%.2f",avgwt/n);
    printf("\nAverage TAT=%.2f\n",avgtat/n);

    return 0;
}