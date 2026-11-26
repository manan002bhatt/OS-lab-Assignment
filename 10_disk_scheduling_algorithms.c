/* 10. Disk Scheduling: FCFS, SSTF, SCAN and C-SCAN */
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n, req[50], i, j, head, disk, total, current;
    printf("Enter number of requests: ");
    scanf("%d", &n);
    printf("Enter request queue:\n");
    for (i = 0; i < n; i++) scanf("%d", &req[i]);
    printf("Enter initial head position: ");
    scanf("%d", &head);
    printf("Enter disk size (cylinders 0 to size-1): ");
    scanf("%d", &disk);

    /* FCFS */
    current = head; total = 0;
    printf("\nFCFS order: ");
    for (i = 0; i < n; i++) {
        printf("%d ", req[i]);
        total += abs(current - req[i]);
        current = req[i];
    }
    printf("\nTotal head movement = %d\n", total);

    /* SSTF */
    int visited[50] = {0};
    current = head; total = 0;
    printf("\nSSTF order: ");
    for (i = 0; i < n; i++) {
        int min = 99999, pos = -1;
        for (j = 0; j < n; j++)
            if (!visited[j] && abs(current - req[j]) < min) {
                min = abs(current - req[j]);
                pos = j;
            }
        visited[pos] = 1;
        printf("%d ", req[pos]);
        total += min;
        current = req[pos];
    }
    printf("\nTotal head movement = %d\n", total);

    /* Sort requests for SCAN and C-SCAN */
    for (i = 0; i < n-1; i++)
        for (j = i+1; j < n; j++)
            if (req[i] > req[j]) {
                int t = req[i]; req[i] = req[j]; req[j] = t;
            }

    /* SCAN: initially moves towards cylinder 0 */
    current = head; total = 0;
    printf("\nSCAN order: ");
    for (i = n-1; i >= 0; i--)
        if (req[i] < head) {
            printf("%d ", req[i]);
            total += abs(current - req[i]);
            current = req[i];
        }
    total += current; /* move to cylinder 0 */
    current = 0;
    for (i = 0; i < n; i++)
        if (req[i] >= head) {
            printf("%d ", req[i]);
            total += abs(current - req[i]);
            current = req[i];
        }
    printf("\nTotal head movement = %d\n", total);

    /* C-SCAN: initially moves towards higher cylinders */
    current = head; total = 0;
    printf("\nC-SCAN order: ");
    for (i = 0; i < n; i++)
        if (req[i] >= head) {
            printf("%d ", req[i]);
            total += abs(current - req[i]);
            current = req[i];
        }
    total += abs((disk - 1) - current);
    total += disk - 1; /* circular return to zero */
    current = 0;
    for (i = 0; i < n; i++)
        if (req[i] < head) {
            printf("%d ", req[i]);
            total += abs(current - req[i]);
            current = req[i];
        }
    printf("\nTotal head movement = %d\n", total);

    return 0;
}
