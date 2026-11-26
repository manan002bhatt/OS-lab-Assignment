/* 6. Dining Philosophers Problem using Semaphores */
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define N 5
sem_t fork_sem[N];
sem_t room;

void *philosopher(void *arg)
{
    int id = *(int *)arg;
    int left = id;
    int right = (id + 1) % N;

    printf("Philosopher %d is thinking.\n", id + 1);

    sem_wait(&room);
    sem_wait(&fork_sem[left]);
    sem_wait(&fork_sem[right]);

    printf("Philosopher %d is eating.\n", id + 1);

    sem_post(&fork_sem[right]);
    sem_post(&fork_sem[left]);
    sem_post(&room);

    return NULL;
}

int main()
{
    pthread_t t[N];
    int id[N];

    sem_init(&room, 0, N - 1);
    for (int i = 0; i < N; i++)
        sem_init(&fork_sem[i], 0, 1);

    for (int i = 0; i < N; i++) {
        id[i] = i;
        pthread_create(&t[i], NULL, philosopher, &id[i]);
    }

    for (int i = 0; i < N; i++)
        pthread_join(t[i], NULL);

    for (int i = 0; i < N; i++)
        sem_destroy(&fork_sem[i]);
    sem_destroy(&room);
    return 0;
}
