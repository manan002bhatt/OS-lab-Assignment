/* 9. FIFO, LRU and Optimal page replacement.
   gcc -Wall -Wextra -o p 09_page_replacement_algorithms.c && ./p */
#include <stdio.h>
#include <stdlib.h>
#define MAXR 200
#define MAXF 50
int find(int f[],int n,int x){for(int i=0;i<n;i++)if(f[i]==x)return i;return -1;}
void display(int f[],int n,int fault){for(int i=0;i<n;i++)if(f[i]<0)printf(" -");else printf(" %d",f[i]);printf("  %s\n",fault?"FAULT":"Hit");}
void fifo(int r[],int n,int nf){int f[MAXF],next=0,err=0;for(int i=0;i<nf;i++)f[i]=-1;puts("\nFIFO:");for(int i=0;i<n;i++){int miss=find(f,nf,r[i])<0;if(miss){f[next]=r[i];next=(next+1)%nf;err++;}printf("%d:",r[i]);display(f,nf,miss);}printf("Page faults = %d\n",err);}
void lru(int r[],int n,int nf){int f[MAXF],last[MAXF],tm=0,err=0;for(int i=0;i<nf;i++)f[i]=last[i]=-1;puts("\nLRU:");for(int i=0;i<n;i++){tm++;int k=find(f,nf,r[i]),miss=k<0;if(miss){k=0;for(int j=0;j<nf;j++)if(f[j]<0){k=j;break;}else if(last[j]<last[k])k=j;f[k]=r[i];err++;}last[k]=tm;printf("%d:",r[i]);display(f,nf,miss);}printf("Page faults = %d\n",err);}
void optimal(int r[],int n,int nf){int f[MAXF],err=0;for(int i=0;i<nf;i++)f[i]=-1;puts("\nOptimal:");for(int i=0;i<n;i++){int miss=find(f,nf,r[i])<0;if(miss){int victim=-1,far=-1;for(int j=0;j<nf;j++){if(f[j]<0){victim=j;break;}int k;for(k=i+1;k<n&&r[k]!=f[j];k++);if(k==n){victim=j;break;}if(k>far)far=k,victim=j;}f[victim]=r[i];err++;}printf("%d:",r[i]);display(f,nf,miss);}printf("Page faults = %d\n",err);}
int main(void){int n,nf,r[MAXR];printf("Reference string length: ");if(scanf("%d",&n)!=1||n<1||n>MAXR)return 1;printf("Enter %d page numbers: ",n);for(int i=0;i<n;i++)if(scanf("%d",&r[i])!=1)return 1;printf("Number of frames: ");if(scanf("%d",&nf)!=1||nf<1||nf>MAXF)return 1;fifo(r,n,nf);lru(r,n,nf);optimal(r,n,nf);return 0;}
