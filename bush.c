#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>  

pid_t p1=0;
pid_t p2=0;
pid_t p3=0;

int main(int argc, char * argv[]) 
{
    int fd[2];
    pipe(fd);  

    pid_t ppid;
    ppid = getpid();
    p1 = ppid;
    printf("Bush pid: %d\n", p1);
    printf("Parent: %d, Group: %d, Session: %d\n\n", getppid(), getgid(), getsid(getpid()) );

    p2 = fork();
    ppid = getpid();

    if(ppid != p1) 
    {
        p2 = ppid;
        printf("P2 pid: %d\n", p2);
        printf("Parent: %d, Group: %d, Session: %d\n\n", getppid(), getgid(), getsid(getpid()) );
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);
        execl("/bin/ls", "ls", "-la", NULL);
    }

    if(ppid != p2)
    {
        p3 = fork();
        ppid = getpid();

        if((ppid != p1)&&(ppid != p2)) 
        {
            p3 = ppid;
            printf("P3 pid: %d\n", p3);
            printf("Parent: %d, Group: %d, Session: %d\n\n", getppid(), getgid(), getsid(getpid()) );
            close(fd[1]);
            dup2(fd[0], STDIN_FILENO);
            close(fd[0]);
            execlp("sort", "sort", "-i", "-r", "-k9", NULL);
        }
    }

    if(ppid==p1) sleep(3);
    if(ppid==p2) sleep(1);
    if(ppid==p3) sleep(2);
    printf("End process %d\n\n", getpid());
    exit(0);
}
