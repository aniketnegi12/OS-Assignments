#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>
#include <unistd.h>

#define N 5

int buffer[N];
int in = 0;
int out = 0;
int n;

sem_t *mutex;
sem_t *empty;
sem_t *full;

void* producer(void* arg)
{
    for (int i = 0; i < n; i++)
    {
        int item;

        printf("Enter item to produce: ");
        fflush(stdout);

        scanf("%d", &item);

        sem_wait(empty);
        sem_wait(mutex);

        buffer[in] = item;

        printf("Produced: %d\n", item);

        in = (in + 1) % N;

        sem_post(mutex);
        sem_post(full);
    }

    return NULL;
}

void* consumer(void* arg)
{
    for (int i = 0; i < n; i++)
    {
        sem_wait(full);
        sem_wait(mutex);

        int item = buffer[out];

        printf("Consumed: %d\n", item);

        out = (out + 1) % N;

        sem_post(mutex);
        sem_post(empty);
    }

    return NULL;
}

int main()
{
    pthread_t producer_thread;
    pthread_t consumer_thread;

    printf("Enter number of items: ");
    scanf("%d", &n);

    /*
       Remove old named semaphores.
       This ensures every execution starts with:
       mutex = 1
       empty = 5
       full  = 0
    */
    sem_unlink("/os_mutex");
    sem_unlink("/os_empty");
    sem_unlink("/os_full");

    mutex = sem_open("/os_mutex", O_CREAT, 0644, 1);
    empty = sem_open("/os_empty", O_CREAT, 0644, N);
    full  = sem_open("/os_full", O_CREAT, 0644, 0);

    if (mutex == SEM_FAILED ||
        empty == SEM_FAILED ||
        full == SEM_FAILED)
    {
        perror("sem_open");
        return 1;
    }

    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    sem_close(mutex);
    sem_close(empty);
    sem_close(full);

    sem_unlink("/os_mutex");
    sem_unlink("/os_empty");
    sem_unlink("/os_full");

    return 0;
}