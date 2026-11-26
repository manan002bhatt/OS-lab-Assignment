/* 3. FCFS, non-preemptive SJF, non-preemptive Priority and Round Robin.
   Lower priority value = higher priority. RR accepts a time quantum.
   gcc -Wall -Wextra -o p 03_cpu_scheduling_algorithms.c && ./p */
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define N 100
#define QMAX 20000
typedef struct {int id,at,bt,pr,ct,done,rem;} P;
void reset(P p[],int n){for(int i=0;i<n;i++)p[i].ct=p[i].done=0,p[i].rem=p[i].bt;}
int nexttime(P p[],int n,int t){int x=INT_MAX;for(int i=0;i<n;i++)if(!p[i].done&&p[i].at>t&&p[i].at<x)x=p[i].at;return x==INT_MAX?t:x;}
void show(const char *s,P p[],int n){double w=0,ta=0;printf("\n%s\nPID AT BT PR CT TAT WT\n",s);for(int i=0;i<n;i++){int tat=p[i].ct-p[i].at,wt=tat-p[i].bt;w+=wt;ta+=tat;printf("P%d %d %d %d %d %d %d\n",p[i].id,p[i].at,p[i].bt,p[i].pr,p[i].ct,tat,wt);}printf("Average TAT=%.2f, Average WT=%.2f\n",ta/n,w/n);}
void fcfs(P p[],int n){reset(p,n);int t=0,c=0;while(c<n){int k=-1;for(int i=0;i<n;i++)if(!p[i].done&&p[i].at<=t&&(k<0||p[i].at<p[k].at))k=i;if(k<0){t=nexttime(p,n,t);continue;}t+=p[k].bt;p[k].ct=t;p[k].done=1;c++;}show("FCFS",p,n);}
void nonpre(P p[],int n,int priority){reset(p,n);int t=0,c=0;while(c<n){int k=-1;for(int i=0;i<n;i++)if(!p[i].done&&p[i].at<=t&&(k<0||(priority?p[i].pr<p[k].pr:p[i].bt<p[k].bt)))k=i;if(k<0){t=nexttime(p,n,t);continue;}t+=p[k].bt;p[k].ct=t;p[k].done=1;c++;}show(priority?"Priority (non-preemptive)":"SJF (non-preemptive)",p,n);}
void rr(P p[],int n,int quantum){
 int queue[N+1],front=0,rear=0,countq=0,added[N]={0},t=0,completed=0;
 reset(p,n);
 while(completed<n){
  for(int i=0;i<n;i++) if(!added[i]&&p[i].at<=t){queue[rear]=i;rear=(rear+1)%(N+1);countq++;added[i]=1;}
  if(countq==0){t=nexttime(p,n,t);continue;}
  int k=queue[front];front=(front+1)%(N+1);countq--;
  int run=p[k].rem<quantum?p[k].rem:quantum;t+=run;p[k].rem-=run;
  for(int i=0;i<n;i++) if(!added[i]&&p[i].at<=t){queue[rear]=i;rear=(rear+1)%(N+1);countq++;added[i]=1;}
  if(p[k].rem>0){queue[rear]=k;rear=(rear+1)%(N+1);countq++;}
  else{p[k].ct=t;p[k].done=1;completed++;}
 }
 show("Round Robin",p,n);
}
int main(void){P p[N];int n,q;printf("Number of processes (1-%d): ",N);if(scanf("%d",&n)!=1||n<1||n>N)return 1;for(int i=0;i<n;i++){p[i].id=i+1;printf("P%d arrival burst priority: ",i+1);if(scanf("%d%d%d",&p[i].at,&p[i].bt,&p[i].pr)!=3||p[i].at<0||p[i].bt<=0)return 1;}printf("RR time quantum: ");if(scanf("%d",&q)!=1||q<=0)return 1;fcfs(p,n);nonpre(p,n,0);nonpre(p,n,1);rr(p,n,q);return 0;}
