#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <time.h>
#include <semaphore.h>

int potencialCpatients = 0, C_Patient = 0, F_Patient = 0;
sem_t mutex;
sem_t coronaPatient;
sem_t fluPatient;

void* POTENCIALcPATIENTS_Came(void* arg)
{
    sem_wait(&mutex);
    potencialCpatients++;
    sem_post(&mutex);
    pthread_exit(0);
}
int CoronaTest()
{
    srand(time(0));
    int test_result = rand() % 2;
    return test_result;
}
void Testing()
{
    potencialCpatients--;
    int test = CoronaTest();
    int c = 1;

    if (test == 0)///crona positive
    {
        C_Patient++;
        sem_post(&coronaPatient);
        while (c != 0)
        {
            if (CoronaTest() == 1)
            {
                if (CoronaTest() == 1)
                {
                    sem_wait(&coronaPatient);
                    c = 0;
                }
            }
        }
    }
    else
    {
        F_Patient++;
        sem_post(&fluPatient);
    }
}
int main()
{
    sem_init(&mutex, 0, 1);
    sem_init(&fluPatient, 0, 1);
    sem_init(&coronaPatient, 0, 1);
    int i = 0, key = 0, NumberofPatients;    
    printf("Enter Number of Patients\n");
    scanf("%d", &NumberofPatients);
    pthread_t id[NumberofPatients];
    for (i = 0; i < NumberofPatients; i++)
    {
        key = pthread_create(&id[i], NULL, POTENCIALcPATIENTS_Came, NULL);
        pthread_join(id[i], NULL);
        if (key != 0)
            printf("error\n");
    }
    for (i = 0; i < NumberofPatients; i++)
    {
        Testing();
    }
    printf("\nTotal Patients are : %d ", potencialCpatients);
    printf("\nFlu Patients are : %d ", F_Patient);
    printf("\nCorona Patients are : %d ", C_Patient);
    printf("\nDischarge Patients are : %d ", potencialCpatients);
}