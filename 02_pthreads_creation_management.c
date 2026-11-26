/* 2. Thread Creation and Management using POSIX Threads */
#include <stdio.h>
#include <pthread.h>

void *display(void *arg)
{
    int id = *(int *)arg;
    printf("Thread %d is running.\n", id);
    pthread_exit(NULL);
}

int main()
{
    pthread_t t[3];
    int id[3];

    for (int i = 0; i < 3; i++)
    {
        id[i] = i + 1;
        pthread_create(&t[i], NULL, display, &id[i]);
    }

    for (int i = 0; i < 3; i++)
        pthread_join(t[i], NULL);

    printf("All threads completed.\n");
    return 0;
}
