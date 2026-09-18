#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#define N 5

int buffer[N];
int in = 0, out = 0;
int n;

sem_t mutex;  
sem_t empty;   
sem_t full;    

void* producers(void* arg){
    for (int i = 0; i < n; i++)
    {
       int item;
        printf("Enter item to produce: ");
        scanf("%d", &item);

        sem_wait(&empty);
        sem_wait(&mutex);

        buffer[in] = item;

        printf("Produced: %d\n", item);
        in = (in + 1) % N;

        sem_post(&mutex);
        sem_post(&full);
    }
    return NULL;
}

void* consumers(void* arg){
    for (int i = 0; i < n; i++)
    {
        sem_wait(&full);
        sem_wait(&mutex);

        int item = buffer[out];

        printf("Consumed: %d\n", item);
        out = (out + 1) % N;

        sem_post(&mutex);
        sem_post(&empty);

    }
    return NULL;
}

int main(){
    pthread_t producer,consumer;
    printf("Enter number of items: ");
    scanf("%d", &n);

    sem_init(&mutex, 0, 1);
    sem_init(&empty, 0, N);
    sem_init(&full, 0, 0);

    pthread_create(&producer, NULL, producers, NULL);
    pthread_create(&consumer, NULL, consumers, NULL);

    pthread_join(producer, NULL);
    pthread_join(consumer, NULL);

    sem_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);
    return 0;
}
