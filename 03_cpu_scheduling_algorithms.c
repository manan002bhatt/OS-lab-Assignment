/* 3. CPU Scheduling: FCFS, SJF, Priority and Round Robin */
#include <stdio.h>

int main()
{
    int n, bt[20], p[20], wt[20], tat[20], i, j, temp;
    int quantum, rem[20], time = 0, done;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++)
    {
        p[i] = i + 1;
        printf("Enter burst time and priority for P%d: ", i + 1);
        scanf("%d%d", &bt[i], &rem[i]);
    }

    /* FCFS */
    wt[0] = 0;
    for (i = 1; i < n; i++)
        wt[i] = wt[i-1] + bt[i-1];
    printf("\nFCFS\nProcess\tBT\tWT\tTAT\n");
    for (i = 0; i < n; i++)
        printf("P%d\t%d\t%d\t%d\n", p[i], bt[i], wt[i], wt[i] + bt[i]);

    /* SJF: sort by burst time */
    int b[20], pr[20], id[20];
    for (i = 0; i < n; i++) { b[i] = bt[i]; pr[i] = rem[i]; id[i] = p[i]; }
    for (i = 0; i < n-1; i++)
        for (j = i+1; j < n; j++)
            if (b[i] > b[j]) {
                temp=b[i]; b[i]=b[j]; b[j]=temp;
                temp=id[i]; id[i]=id[j]; id[j]=temp;
                temp=pr[i]; pr[i]=pr[j]; pr[j]=temp;
            }
    wt[0] = 0;
    for (i = 1; i < n; i++) wt[i] = wt[i-1] + b[i-1];
    printf("\nSJF (Non-preemptive)\nProcess\tBT\tWT\tTAT\n");
    for (i = 0; i < n; i++)
        printf("P%d\t%d\t%d\t%d\n", id[i], b[i], wt[i], wt[i]+b[i]);

    /* Priority: smaller number means higher priority */
    for (i = 0; i < n; i++) { b[i] = bt[i]; pr[i] = rem[i]; id[i] = p[i]; }
    for (i = 0; i < n-1; i++)
        for (j = i+1; j < n; j++)
            if (pr[i] > pr[j]) {
                temp=pr[i]; pr[i]=pr[j]; pr[j]=temp;
                temp=b[i]; b[i]=b[j]; b[j]=temp;
                temp=id[i]; id[i]=id[j]; id[j]=temp;
            }
    wt[0] = 0;
    for (i = 1; i < n; i++) wt[i] = wt[i-1] + b[i-1];
    printf("\nPriority (Non-preemptive)\nProcess\tBT\tWT\tTAT\n");
    for (i = 0; i < n; i++)
        printf("P%d\t%d\t%d\t%d\n", id[i], b[i], wt[i], wt[i]+b[i]);

    /* Round Robin */
    for (i = 0; i < n; i++) rem[i] = bt[i];
    printf("\nEnter time quantum: ");
    scanf("%d", &quantum);
    if (quantum <= 0) return 1;

    for (i = 0; i < n; i++) tat[i] = 0;
    done = 0;
    while (done < n)
    {
        for (i = 0; i < n; i++)
        {
            if (rem[i] > 0)
            {
                if (rem[i] > quantum) {
                    time += quantum;
                    rem[i] -= quantum;
                } else {
                    time += rem[i];
                    rem[i] = 0;
                    tat[i] = time;
                    done++;
                }
            }
        }
    }
    printf("Round Robin\nProcess\tBT\tWT\tTAT\n");
    for (i = 0; i < n; i++)
        printf("P%d\t%d\t%d\t%d\n", p[i], bt[i], tat[i]-bt[i], tat[i]);

    return 0;
}
