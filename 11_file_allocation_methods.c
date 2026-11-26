/* 11. Simulation of Contiguous, Linked and Indexed file allocation.
   gcc -Wall -Wextra -o p 11_file_allocation_methods.c && ./p */
#include <stdio.h>
#include <stdlib.h>
#define MAX 200
void show(int a[],int n){for(int i=0;i<n;i++)printf("%d%s",a[i],i==n-1?"\n":" -> ");}
int main(void){int n,start,len,index,blocks[MAX],count=0;printf("Total disk blocks (max %d): ",MAX);if(scanf("%d",&n)!=1||n<1||n>MAX)return 1;printf("Starting block for contiguous allocation: ");if(scanf("%d",&start)!=1)return 1;printf("Number of data blocks required: ");if(scanf("%d",&len)!=1||len<1||len>n)return 1;printf("Index block for indexed allocation: ");if(scanf("%d",&index)!=1)return 1;
printf("\nCONTIGUOUS ALLOCATION\n");if(start<0||start+len>n)puts("Allocation failed: range outside disk.");else{for(int i=0;i<len;i++)blocks[i]=start+i;show(blocks,len);printf("Directory stores start=%d and length=%d.\n",start,len);}
printf("\nLINKED ALLOCATION\n");count=0;for(int i=0;i<n&&count<len;i++)blocks[count++]=i;printf("Blocks linked by pointers: ");show(blocks,count);printf("Directory stores first block %d; each block points to the next.\n",blocks[0]);
printf("\nINDEXED ALLOCATION\n");if(index<0||index>=n||len+1>n)puts("Allocation failed: invalid index block or insufficient space.");else{count=0;for(int i=0;i<n&&count<len;i++)if(i!=index)blocks[count++]=i;printf("Index block: %d\nData block addresses: ",index);show(blocks,count);puts("Directory stores the index-block address.");}return 0;}
