// The code only run on LINUX OS 


#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(){
    pid_t pid1, pid2;
    printf("Parent Process ID: %d\n", getpid());

    // first child
    pid1 = fork();

    if(pid1 == 0){
        printf("Child 1 process ID: %d | Parent ID: %d \n", getpid(), getppid());
    }else{
        // Only parent creates second child
        pid2 = fork();

        if (pid2 == 0) {
            printf("Child 2 Process ID: %d | Parent ID: %d\n",
                   getpid(), getppid());
        }
        else {
            // Parent process
            printf("Parent continues execution. PID: %d\n", getpid());
        }
        return 0;
    }
}


