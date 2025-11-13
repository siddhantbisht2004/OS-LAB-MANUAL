#include <stdio.h>
struct Process
{
    int pid, at, bt, rt, ct, tat, wt;
};
#define MAX 100
int queue[MAX], front = 0, rear = 0;
void enqueue(int x)
{
    queue[rear++] = x;
}
int dequeue()
{
    return (front == rear) ? -1 : queue[front++];
}
int isEmpty()
{
    return front == rear;
}
int main()
{
    int n, tq;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];
    for (int i = 0; i < n; i++)
    {
        p[i].pid = i + 1;
        printf("P%d (AT BT): ", i + 1);
        scanf("%d %d", &p[i].at, &p[i].bt);
        p[i].rt = p[i].bt; // remaining
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &tq);

    int time = 0, completed = 0;
    float totalWT = 0, totalTAT = 0;
    int visited[n];
    for (int i = 0; i < n; i++)
        visited[i] = 0;

    // start -> enqueue processes that arrive at 0
    for (int i = 0; i < n; i++)
        if (p[i].at == 0)
        {
            enqueue(i);
            visited[i] = 1;
        }

    printf("\nGantt Chart:\n0");
    while (completed < n)
    {
        if (isEmpty())
        { // CPU idle
            time++;
            for (int i = 0; i < n; i++)
                if (!visited[i] && p[i].at <= time)
                {
                    enqueue(i);
                    visited[i] = 1;
                }
            continue;
        }

        int idx = dequeue();
        int exec = (p[idx].rt > tq ? tq : p[idx].rt);

        time += exec;
        p[idx].rt -= exec;

        printf(" | P%d | %d", p[idx].pid, time);

        // add new arrivals to queue
        for (int i = 0; i < n; i++)
            if (!visited[i] && p[i].at <= time)
            {
                enqueue(i);
                visited[i] = 1;
            }
        if (p[idx].rt > 0)
            enqueue(idx); // not finished, requeue
        else
        {
            p[idx].ct = time; // finished
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            totalWT += p[idx].wt;
            totalTAT += p[idx].tat;
            completed++;
        }
    }
    printf("\n\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++)
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].at, p[i].bt,
               p[i].ct, p[i].tat, p[i].wt);
    printf("\nAvg WT=%.2f, Avg TAT=%.2f\n", totalWT / n, totalTAT / n);
    return 0;
}
