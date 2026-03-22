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

    int tq1=2,tq2=4,time=0,completed=0;
    int q1[50],q2[50],q3[50],f1=0,r1=0,f2=0,r2=0,f3=0,r3=0;
    int q1left[20]={0},q2left[20]={0};
    int cur=-1,curQ=0;

    while(completed<n)
    {
        for(int i=0;i<n;i++)
        {
            if(p[i].at==time)
            {
                q1[r1++%50]=i;
                q1left[i]=tq1;
            }
        }

        if(cur!=-1)
        {
            if((curQ==2 && f1!=r1) || (curQ==3 && (f1!=r1 || f2!=r2)))
            {
                if(curQ==2)
                    q2[r2++%50]=cur;
                else
                    q3[r3++%50]=cur;
                cur=-1;
            }
        }

        if(cur==-1)
        {
            if(f1!=r1)
            {
                cur=q1[f1++%50];
                curQ=1;
            }
            else if(f2!=r2)
            {
                cur=q2[f2++%50];
                curQ=2;
            }
            else if(f3!=r3)
            {
                cur=q3[f3++%50];
                curQ=3;
            }
            else
            {
                time++;
                continue;
            }
        }

        p[cur].rt--;
        time++;

        if(curQ==1)
            q1left[cur]--;
        else if(curQ==2)
            q2left[cur]--;

        if(p[cur].rt==0)
        {
            p[cur].ct=time;
            completed++;
            cur=-1;
        }
        else if(curQ==1 && q1left[cur]==0)
        {
            q2[r2++%50]=cur;
            q2left[cur]=tq2;
            cur=-1;
        }
        else if(curQ==2 && q2left[cur]==0)
        {
            q3[r3++%50]=cur;
            cur=-1;
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