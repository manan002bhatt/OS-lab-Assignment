/* 8. Contiguous Memory Allocation: First Fit, Best Fit and Worst Fit */
#include <stdio.h>

int main()
{
    int nb, np, block[20], process[20], i, j;

    printf("Enter number of memory blocks: ");
    scanf("%d", &nb);
    printf("Enter sizes of memory blocks:\n");
    for (i = 0; i < nb; i++)
        scanf("%d", &block[i]);

    printf("Enter number of processes: ");
    scanf("%d", &np);
    printf("Enter sizes of processes:\n");
    for (i = 0; i < np; i++)
        scanf("%d", &process[i]);

    /* First Fit */
    int temp[20], alloc[20];
    for (i = 0; i < nb; i++) temp[i] = block[i];
    for (i = 0; i < np; i++) alloc[i] = -1;
    for (i = 0; i < np; i++)
        for (j = 0; j < nb; j++)
            if (temp[j] >= process[i]) {
                alloc[i] = j;
                temp[j] -= process[i];
                break;
            }
    printf("\nFirst Fit\nProcess\tSize\tBlock\n");
    for (i = 0; i < np; i++)
        printf("P%d\t%d\t%s%d\n", i+1, process[i],
               alloc[i] == -1 ? "Not allocated " : "B", alloc[i]+1);

    /* Best Fit */
    for (i = 0; i < nb; i++) temp[i] = block[i];
    for (i = 0; i < np; i++) alloc[i] = -1;
    for (i = 0; i < np; i++) {
        int best = -1;
        for (j = 0; j < nb; j++)
            if (temp[j] >= process[i] &&
                (best == -1 || temp[j] < temp[best]))
                best = j;
        if (best != -1) { alloc[i] = best; temp[best] -= process[i]; }
    }
    printf("\nBest Fit\nProcess\tSize\tBlock\n");
    for (i = 0; i < np; i++) {
        if (alloc[i] == -1) printf("P%d\t%d\tNot allocated\n", i+1, process[i]);
        else printf("P%d\t%d\tB%d\n", i+1, process[i], alloc[i]+1);
    }

    /* Worst Fit */
    for (i = 0; i < nb; i++) temp[i] = block[i];
    for (i = 0; i < np; i++) alloc[i] = -1;
    for (i = 0; i < np; i++) {
        int worst = -1;
        for (j = 0; j < nb; j++)
            if (temp[j] >= process[i] &&
                (worst == -1 || temp[j] > temp[worst]))
                worst = j;
        if (worst != -1) { alloc[i] = worst; temp[worst] -= process[i]; }
    }
    printf("\nWorst Fit\nProcess\tSize\tBlock\n");
    for (i = 0; i < np; i++) {
        if (alloc[i] == -1) printf("P%d\t%d\tNot allocated\n", i+1, process[i]);
        else printf("P%d\t%d\tB%d\n", i+1, process[i], alloc[i]+1);
    }

    return 0;
}
