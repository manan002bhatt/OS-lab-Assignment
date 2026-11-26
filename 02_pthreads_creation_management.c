/* 2. POSIX thread creation and management.
   gcc -Wall -Wextra -pthread -o p 02_pthreads_creation_management.c && ./p */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
typedef struct { int id, limit; } Data;
void *worker(void *arg) {
 Data *d=arg; long *sum=malloc(sizeof *sum); if(!sum)return NULL; *sum=0;
 for(int i=1;i<=d->limit;i++) *sum+=i;
 printf("Thread %d: sum 1..%d = %ld\n",d->id,d->limit,*sum); return sum;
}
int main(void) {
 pthread_t t[3]; Data d[3];
 for(int i=0;i<3;i++){d[i]=(Data){i+1,(i+1)*5}; int e=pthread_create(&t[i],NULL,worker,&d[i]);
   if(e){fprintf(stderr,"pthread_create: %s\n",strerror(e));return 1;}}
 for(int i=0;i<3;i++){void *r=NULL;int e=pthread_join(t[i],&r);if(e){fprintf(stderr,"pthread_join: %s\n",strerror(e));return 1;}
   if(r){printf("Main received result: %ld\n",*(long*)r);free(r);}}
 puts("All threads completed."); return 0;
}
