/* 8. First Fit, Best Fit and Worst Fit memory allocation.
   gcc -Wall -Wextra -o p 08_contiguous_memory_allocation.c && ./p */
#include <stdio.h>
#include <stdlib.h>
#define MAX 100
void run(const char *title,int b[],int nb,int p[],int np,int mode){int rem[MAX],assigned[MAX];for(int j=0;j<nb;j++)rem[j]=b[j];for(int i=0;i<np;i++)assigned[i]=-1;for(int i=0;i<np;i++){int k=-1;for(int j=0;j<nb;j++)if(rem[j]>=p[i]&&(k<0||(mode==1 && rem[j]<rem[k])||(mode==2 && rem[j]>rem[k]))){k=j;if(mode==0)break;}if(k>=0){assigned[i]=k;rem[k]-=p[i];}}printf("\n%s\nProcess Size Block Remaining\n",title);for(int i=0;i<np;i++)if(assigned[i]<0)printf("P%d %d Not-allocated -\n",i+1,p[i]);else printf("P%d %d B%d %d\n",i+1,p[i],assigned[i]+1,rem[assigned[i]]);}
int main(void){int nb,np,b[MAX],p[MAX];printf("Number of blocks: ");if(scanf("%d",&nb)!=1||nb<1||nb>MAX)return 1;for(int i=0;i<nb;i++){printf("Block %d size: ",i+1);if(scanf("%d",&b[i])!=1||b[i]<=0)return 1;}printf("Number of processes: ");if(scanf("%d",&np)!=1||np<1||np>MAX)return 1;for(int i=0;i<np;i++){printf("Process %d size: ",i+1);if(scanf("%d",&p[i])!=1||p[i]<=0)return 1;}run("FIRST FIT",b,nb,p,np,0);run("BEST FIT",b,nb,p,np,1);run("WORST FIT",b,nb,p,np,2);return 0;}
