/* 6. Dining philosophers using semaphores. A room semaphore allows N-1 philosophers in,
   preventing circular-wait deadlock.
   gcc -Wall -Wextra -pthread -o p 06_dining_philosophers_semaphores.c && ./p */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#define N 5
sem_t forksem[N],room;
void *philosopher(void *a){int id=*(int*)a,left=id,right=(id+1)%N;printf("Philosopher %d thinking\n",id+1);usleep(80000);sem_wait(&room);sem_wait(&forksem[left]);sem_wait(&forksem[right]);printf("Philosopher %d eating with forks %d and %d\n",id+1,left+1,right+1);usleep(100000);sem_post(&forksem[right]);sem_post(&forksem[left]);sem_post(&room);printf("Philosopher %d finished\n",id+1);return NULL;}
int main(void){pthread_t t[N];int id[N];sem_init(&room,0,N-1);for(int i=0;i<N;i++)sem_init(&forksem[i],0,1);for(int i=0;i<N;i++){id[i]=i;if(pthread_create(&t[i],NULL,philosopher,&id[i])){perror("pthread_create");return 1;}}for(int i=0;i<N;i++)pthread_join(t[i],NULL);for(int i=0;i<N;i++)sem_destroy(&forksem[i]);sem_destroy(&room);return 0;}
