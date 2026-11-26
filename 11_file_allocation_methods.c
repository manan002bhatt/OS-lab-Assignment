/* 11. File Allocation Methods: Contiguous, Linked and Indexed */
#include <stdio.h>

int main()
{
    int n, start, length, i, index;

    printf("Enter total number of disk blocks: ");
    scanf("%d", &n);
    printf("Enter starting block for contiguous allocation: ");
    scanf("%d", &start);
    printf("Enter number of blocks required: ");
    scanf("%d", &length);

    /* Contiguous Allocation */
    printf("\nContiguous Allocation:\n");
    if (start >= 0 && start + length <= n) {
        for (i = 0; i < length; i++)
            printf("%d ", start + i);
        printf("\n");
    } else
        printf("Not enough space.\n");

    /* Linked Allocation */
    printf("\nLinked Allocation:\n");
    printf("Blocks are linked using pointers: ");
    for (i = 0; i < length && i < n; i++)
        printf("%d ", i);
    printf("\n");

    /* Indexed Allocation */
    printf("\nIndexed Allocation:\n");
    printf("Enter index block: ");
    scanf("%d", &index);
    if (index >= 0 && index < n) {
        printf("Index block: %d\nData blocks: ", index);
        for (i = 0; i < length && i < n; i++)
            if (i != index) printf("%d ", i);
        printf("\n");
    } else
        printf("Invalid index block.\n");

    return 0;
}
