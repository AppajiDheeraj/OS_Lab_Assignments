#include <stdio.h>

struct process { int pid, at, bt, priority, queue, ct, tat, wt, rt; };

static void display(struct process p[], int n)
{
    float avgwt = 0.0f, avgtat = 0.0f;
    printf("\nPID AT BT Q PR CT TAT WT\n");
    for(int i = 0; i < n; i++)
    {
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
        avgwt += p[i].wt;
        avgtat += p[i].tat;
        printf("P%d %d %d %d %d %d %d %d\n",
               p[i].pid, p[i].at, p[i].bt, p[i].queue,
               p[i].priority, p[i].ct, p[i].tat, p[i].wt);
    }
    printf("\nAverage WT = %.2f", avgwt / n);
    printf("\nAverage TAT = %.2f\n", avgtat / n);
}

static void multilevel_nonpreemptive(struct process p[], int n)
{
    int time = 0, completed = 0, done[100] = {0};
    while(completed < n)
    {
        int idx = -1, min_priority = 9999;
        for(int i = 0; i < n; i++)
            if(!done[i] && p[i].queue == 1 && p[i].at <= time && p[i].priority < min_priority)
                min_priority = p[i].priority, idx = i;

        if(idx == -1)
        {
            int earliest_at = 9999;
            for(int i = 0; i < n; i++)
                if(!done[i] && p[i].queue == 2 && p[i].at <= time && p[i].at < earliest_at)
                    earliest_at = p[i].at, idx = i;
        }

        if(idx != -1)
        {
            if(time < p[idx].at) time = p[idx].at;
            time += p[idx].bt;
            p[idx].ct = time;
            done[idx] = 1;
            completed++;
        }
        else time++;
    }
    printf("\n--- NON-PREEMPTIVE BETWEEN QUEUES ---\n");
    display(p, n);
}

static void multilevel_preemptive(struct process p[], int n)
{
    int time = 0, completed = 0, current_q2 = -1;
    for(int i = 0; i < n; i++) p[i].rt = p[i].bt;

    while(completed < n)
    {
        int idx = -1, min_priority = 9999;
        for(int i = 0; i < n; i++)
            if(p[i].queue == 1 && p[i].at <= time && p[i].rt > 0 && p[i].priority < min_priority)
                min_priority = p[i].priority, idx = i;

        if(idx != -1)
        {
            if(time < p[idx].at) time = p[idx].at;
            time += p[idx].rt;
            p[idx].rt = 0;
            p[idx].ct = time;
            completed++;
            continue;
        }

        if(current_q2 != -1 && p[current_q2].rt > 0 && p[current_q2].queue == 2 && p[current_q2].at <= time)
            idx = current_q2;
        else
        {
            int earliest_at = 9999;
            for(int i = 0; i < n; i++)
                if(p[i].queue == 2 && p[i].at <= time && p[i].rt > 0 && p[i].at < earliest_at)
                    earliest_at = p[i].at, idx = i;
        }

        if(idx != -1)
        {
            p[idx].rt--;
            time++;
            current_q2 = idx;
            if(p[idx].rt == 0)
            {
                p[idx].ct = time;
                completed++;
                current_q2 = -1;
            }
        }
        else time++;
    }
    printf("\n--- PREEMPTIVE BETWEEN QUEUES ---\n");
    display(p, n);
}

int main(void)
{
    int n; struct process p[100], p1[100], p2[100];
    printf("Enter number of processes: ");
    scanf("%d", &n);
    if(n <= 0 || n > 100) { printf("Invalid number of processes. Must be 1 to 100.\n"); return 1; }

    for(int i = 0; i < n; i++)
    {
        p[i].pid = i + 1;
        printf("\nProcess P%d\n", i + 1);
        printf("Arrival Time: "); scanf("%d", &p[i].at);
        printf("Burst Time: "); scanf("%d", &p[i].bt);
        printf("Queue Number (1 or 2): "); scanf("%d", &p[i].queue);
        if(p[i].queue == 1) { printf("Priority: "); scanf("%d", &p[i].priority); }
        else p[i].priority = 9999;
    }

    for(int i = 0; i < n; i++) { p1[i] = p[i]; p2[i] = p[i]; }
    multilevel_nonpreemptive(p1, n);
    multilevel_preemptive(p2, n);
    return 0;
}
