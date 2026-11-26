/* 9. Page Replacement Algorithms: FIFO, LRU and Optimal */
#include <stdio.h>

int main()
{
    int n, f, page[50], frame[10], i, j, faults, hit;

    printf("Enter number of pages: ");
    scanf("%d", &n);
    printf("Enter page reference string:\n");
    for (i = 0; i < n; i++) scanf("%d", &page[i]);
    printf("Enter number of frames: ");
    scanf("%d", &f);

    /* FIFO */
    for (i = 0; i < f; i++) frame[i] = -1;
    int next = 0;
    faults = 0;
    printf("\nFIFO\n");
    for (i = 0; i < n; i++) {
        hit = 0;
        for (j = 0; j < f; j++)
            if (frame[j] == page[i]) hit = 1;
        if (!hit) {
            frame[next] = page[i];
            next = (next + 1) % f;
            faults++;
        }
        for (j = 0; j < f; j++) printf("%d ", frame[j]);
        printf("\n");
    }
    printf("Page faults = %d\n", faults);

    /* LRU */
    int time[10], count = 0;
    for (i = 0; i < f; i++) { frame[i] = -1; time[i] = 0; }
    faults = 0;
    printf("\nLRU\n");
    for (i = 0; i < n; i++) {
        hit = 0;
        for (j = 0; j < f; j++)
            if (frame[j] == page[i]) { hit = 1; time[j] = ++count; }
        if (!hit) {
            int pos = 0;
            for (j = 0; j < f; j++)
                if (frame[j] == -1) { pos = j; break; }
                else if (time[j] < time[pos]) pos = j;
            frame[pos] = page[i];
            time[pos] = ++count;
            faults++;
        }
        for (j = 0; j < f; j++) printf("%d ", frame[j]);
        printf("\n");
    }
    printf("Page faults = %d\n", faults);

    /* Optimal */
    for (i = 0; i < f; i++) frame[i] = -1;
    faults = 0;
    printf("\nOptimal\n");
    for (i = 0; i < n; i++) {
        hit = 0;
        for (j = 0; j < f; j++)
            if (frame[j] == page[i]) hit = 1;
        if (!hit) {
            int pos = -1, farthest = -1;
            for (j = 0; j < f; j++) {
                int k;
                if (frame[j] == -1) { pos = j; break; }
                for (k = i + 1; k < n && page[k] != frame[j]; k++);
                if (k > farthest) { farthest = k; pos = j; }
            }
            frame[pos] = page[i];
            faults++;
        }
        for (j = 0; j < f; j++) printf("%d ", frame[j]);
        printf("\n");
    }
    printf("Page faults = %d\n", faults);

    return 0;
}
