/* 4. Producer-consumer using POSIX semaphores.
   gcc -Wall -Wextra -pthread -o p 04_producer_consumer_semaphores.c && ./p */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#define SIZE 5
#define ITEMS 10
int b[SIZE],in=0,out=0;sem_t empty,full;pthread_mutex_t lock=PTHREAD_MUTEX_INITIALIZER;
void *producer(void *x){(void)x;for(int v=1;v<=ITEMS;v++){sem_wait(&empty);pthread_mutex_lock(&lock);b[in]=v;printf("Produced %d at %d\n",v,in);in=(in+1)%SIZE;pthread_mutex_unlock(&lock);sem_post(&full);usleep(80000);}return NULL;}
void *consumer(void *x){(void)x;for(int i=0;i<ITEMS;i++){sem_wait(&full);pthread_mutex_lock(&lock);int v=b[out];printf("Consumed %d from %d\n",v,out);out=(out+1)%SIZE;pthread_mutex_unlock(&lock);sem_post(&empty);usleep(120000);}return NULL;}
int main(void){pthread_t p,c;sem_init(&empty,0,SIZE);sem_init(&full,0,0);if(pthread_create(&p,NULL,producer,NULL)||pthread_create(&c,NULL,consumer,NULL)){perror("pthread_create");return 1;}pthread_join(p,NULL);pthread_join(c,NULL);sem_destroy(&empty);sem_destroy(&full);pthread_mutex_destroy(&lock);return 0;}
