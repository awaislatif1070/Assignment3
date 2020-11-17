#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include<sys/wait.h>
#include <unistd.h>
#include <stdbool.h>
#include <semaphore.h>

sem_t *Process_first;
sem_t *Process_second;
sem_t *Process_third;
sem_t *Process_fourth;

char buffer[20];

int main()
{
    Process_first = sem_open("my_semaphore_1", O_CREAT, 0644, 0);
    Process_second = sem_open("my_semaphore_2", O_CREAT,0644 , 0);    
    Process_third = sem_open("my_semaphore_3", O_CREAT, 0644, 0);
    Process_fourth = sem_open("my_semaphore_4", O_CREAT, 0644, 0);

    int pid_A=fork();

    if(pid_A==0)
    {
        printf(" process 1\n ");
        printf(" write 1\n ");
        sem_post(Process_first);
		exit(0);
    }
    else if(pid_A > 0)
    {
	
        int pid_B=fork();
        if(pid_B == 0)
        {
            printf(" process 2 \n");
            sem_wait(Process_first);
             printf(" write 2 \n");
            sem_post(Process_third);
            exit(0);
        }
        else if(pid_B > 0)
        {    
            sem_wait(Process_third);
            int pid_C=fork();
            if(pid_C == 0)
            {
                printf(" process 3 \n");

                sem_post(Process_fourth);
                    exit(0);    

            }
            else if(pid_C > 0)
            {    
                sem_wait(Process_fourth);
                int pid_D=fork();
                if(pid_D == 0)
                {
                    printf(" process 4 \n");
                    exit(0);    
                }
                 else if(pid_D > 0) 
{
	wait(NULL);
	}           
              else{}
            } 
        else{}
        } 
    else{}
    }
    else
    {
        printf("ERROR CREATING CHILD!!");
    }
sem_destroy(Process_first);   
sem_destroy(Process_second);
sem_destroy(Process_third);   
sem_destroy(Process_fourth);

return 0;
}