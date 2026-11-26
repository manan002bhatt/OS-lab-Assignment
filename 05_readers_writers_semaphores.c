/* 5. Readers-writers using semaphores (reader-preference solution).
   Readers may share access; writers require exclusive access. Writer starvation is possible.
   gcc -Wall -Wextra -pthread -o p 05_readers_writers_semaphores.c && ./p */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#define NR 5
#define NW 2
sem_t resource,mutex;int readers=0,data=0;
void *reader(void *a){int id=*(int*)a;sem_wait(&mutex);readers++;if(readers==1)sem_wait(&resource);sem_post(&mutex);printf("Reader %d reads %d\n",id,data);usleep(100000);sem_wait(&mutex);readers--;if(readers==0)sem_post(&resource);sem_post(&mutex);return NULL;}
void *writer(void *a){int id=*(int*)a;sem_wait(&resource);data++;printf("Writer %d writes %d\n",id,data);usleep(140000);sem_post(&resource);return NULL;}
int main(void){pthread_t r[NR],w[NW];int ri[NR],wi[NW];sem_init(&resource,0,1);sem_init(&mutex,0,1);for(int i=0;i<NR;i++){ri[i]=i+1;if(pthread_create(&r[i],NULL,reader,&ri[i])){perror("reader create");return 1;}}for(int i=0;i<NW;i++){wi[i]=i+1;if(pthread_create(&w[i],NULL,writer,&wi[i])){perror("writer create");return 1;}}for(int i=0;i<NR;i++)pthread_join(r[i],NULL);for(int i=0;i<NW;i++)pthread_join(w[i],NULL);sem_destroy(&resource);sem_destroy(&mutex);return 0;}
