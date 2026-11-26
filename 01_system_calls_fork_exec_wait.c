/* 1. Linux system calls, fork(), exec() and wait().
   gcc -Wall -Wextra -o p 01_system_calls_fork_exec_wait.c && ./p */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>
int main(void) {
 const char *name="syscall_demo.txt", *msg="Created using open(), write() and close().\n";
 int fd=open(name,O_WRONLY|O_CREAT|O_TRUNC,0644); if(fd<0){perror("open");return 1;}
 if(write(fd,msg,strlen(msg))<0){perror("write");close(fd);return 1;} close(fd);
 printf("Parent PID: %ld; created %s\n",(long)getpid(),name);
 pid_t pid=fork(); if(pid<0){perror("fork");return 1;}
 if(pid==0){printf("Child PID: %ld; running ls through exec()\n",(long)getpid()); fflush(stdout);
   execlp("ls","ls","-l",name,(char*)NULL); perror("execlp"); _exit(1);}
 int status; if(waitpid(pid,&status,0)<0){perror("waitpid");return 1;}
 if(WIFEXITED(status)) printf("Child exit status: %d\n",WEXITSTATUS(status));
 fd=open(name,O_RDONLY); if(fd<0){perror("open read");return 1;}
 char buf[256]; ssize_t n=read(fd,buf,sizeof buf-1); if(n<0){perror("read");close(fd);return 1;}
 buf[n]='\0'; printf("Read from file: %s",buf); close(fd); return 0;
}
