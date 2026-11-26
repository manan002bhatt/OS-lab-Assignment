/* 7. Deadlock avoidance using Banker's safety algorithm.
   gcc -Wall -Wextra -o p 07_bankers_algorithm.c && ./p */
#include <stdio.h>
#include <stdlib.h>
#define P 20
#define R 20
int main(void){int n,m,a[P][R],mx[P][R],need[P][R],avail[R],work[R],finish[P]={0},seq[P];
printf("Processes and resource types: ");if(scanf("%d%d",&n,&m)!=2||n<1||n>P||m<1||m>R)return 1;
printf("Allocation matrix:\n");for(int i=0;i<n;i++)for(int j=0;j<m;j++)if(scanf("%d",&a[i][j])!=1||a[i][j]<0)return 1;
printf("Maximum matrix:\n");for(int i=0;i<n;i++)for(int j=0;j<m;j++)if(scanf("%d",&mx[i][j])!=1||mx[i][j]<a[i][j]){puts("Max must be >= allocation.");return 1;}
printf("Available vector: ");for(int j=0;j<m;j++)if(scanf("%d",&avail[j])!=1||avail[j]<0)return 1;
puts("Need = Max - Allocation:");for(int i=0;i<n;i++){for(int j=0;j<m;j++){need[i][j]=mx[i][j]-a[i][j];printf("%d ",need[i][j]);}puts("");}
for(int j=0;j<m;j++) work[j]=avail[j];
int count=0,progress;
do {
    progress=0;
    for(int i=0;i<n;i++) if(!finish[i]) {
        int ok=1;
        for(int j=0;j<m;j++) if(need[i][j]>work[j]) ok=0;
        if(ok) {
            for(int j=0;j<m;j++) work[j]+=a[i][j];
            seq[count++]=i; finish[i]=1; progress=1;
        }
    }
} while(progress);
if(count==n){printf("SAFE state. Safe sequence: ");for(int i=0;i<n;i++)printf("P%d%s",seq[i],i==n-1?"\n":" -> ");}else puts("UNSAFE state: no safe sequence found.");return 0;}
