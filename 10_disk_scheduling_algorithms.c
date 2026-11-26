/* 10. FCFS, SSTF, SCAN and C-SCAN disk scheduling.
   SCAN moves toward cylinder 0 first; C-SCAN moves upward first.
   gcc -Wall -Wextra -o p 10_disk_scheduling_algorithms.c && ./p */
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define MAX 200
int cmp(const void*a,const void*b){int x=*(const int*)a,y=*(const int*)b;return (x>y)-(x<y);}
void result(const char*s,int o[],int n,int head,int move){printf("\n%s\n%d",s,head);for(int i=0;i<n;i++)printf(" -> %d",o[i]);printf("\nTotal head movement = %d\n",move);}
int main(void){int n,r[MAX],s[MAX],o[MAX+2],head,size,m=0,c=0,cur;printf("Number of requests: ");if(scanf("%d",&n)!=1||n<1||n>MAX)return 1;printf("Request queue: ");for(int i=0;i<n;i++)if(scanf("%d",&r[i])!=1)return 1;printf("Initial head: ");if(scanf("%d",&head)!=1)return 1;printf("Disk size (cylinders 0 to size-1): ");if(scanf("%d",&size)!=1||size<2||head<0||head>=size)return 1;for(int i=0;i<n;i++)if(r[i]<0||r[i]>=size){puts("Invalid request cylinder.");return 1;}
cur=head;for(int i=0;i<n;i++){o[i]=r[i];m+=abs(cur-r[i]);cur=r[i];}result("FCFS",o,n,head,m);
int used[MAX]={0};cur=head;m=0;c=0;for(int k=0;k<n;k++){int best=-1,d=INT_MAX;for(int i=0;i<n;i++)if(!used[i]&&abs(cur-r[i])<d)d=abs(cur-r[i]),best=i;used[best]=1;o[c++]=r[best];m+=d;cur=r[best];}result("SSTF",o,c,head,m);
for(int i=0;i<n;i++) s[i]=r[i];
qsort(s,n,sizeof(int),cmp);
cur=head;m=0;c=0;for(int i=n-1;i>=0;i--)if(s[i]<head)o[c++]=s[i],m+=abs(cur-s[i]),cur=s[i];if(cur!=0)m+=cur,cur=0;for(int i=0;i<n;i++)if(s[i]>=head)o[c++]=s[i],m+=abs(cur-s[i]),cur=s[i];result("SCAN (toward 0 first)",o,c,head,m);
cur=head;m=0;c=0;for(int i=0;i<n;i++)if(s[i]>=head)o[c++]=s[i],m+=abs(cur-s[i]),cur=s[i];if(cur!=size-1)m+=(size-1-cur),cur=size-1;m+=size-1;cur=0;for(int i=0;i<n;i++)if(s[i]<head)o[c++]=s[i],m+=abs(cur-s[i]),cur=s[i];result("C-SCAN (toward higher cylinders first; wrap counted)",o,c,head,m);return 0;}
