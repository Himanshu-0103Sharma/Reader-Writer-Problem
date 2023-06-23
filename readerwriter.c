#include <stdio.h>
#include <pthread.h>

pthread_mutex_t mutex;
pthread_mutex_t rw_mutex;
int read_count = 0;

void *reader() {
    pthread_mutex_lock(&mutex);
    read_count++;
    if (read_count == 1) {
        pthread_mutex_lock(&rw_mutex);
    }
    pthread_mutex_unlock(&mutex);

    printf("Reading process\n");

    pthread_mutex_lock(&mutex);
    read_count--;
    if (read_count == 0) {
        pthread_mutex_unlock(&rw_mutex);
    }
    pthread_mutex_unlock(&mutex);

    return NULL;
}

void *writer() {
    pthread_mutex_lock(&rw_mutex);

    printf("Writing process in critical section\n");

    pthread_mutex_unlock(&rw_mutex);
    return NULL;
}

int main() {
    int R,W;

    printf("Enter the number of processes that wants to read : ");
    scanf("%d",&R);

    printf("Enter the number of processes that wants to write : ");
    scanf("%d",&W);

    pthread_t readers[R];
    pthread_t writers[W];

    pthread_mutex_init(&mutex, NULL);
    pthread_mutex_init(&rw_mutex, NULL);

    int i;

    for (i = 0; i < R; i++) {
        if (pthread_create(&readers[i], NULL, reader, NULL) != 0) {
            fprintf(stderr, "Error creating reader thread %d\n", i);
            exit(1);
        }
    }
    for (i = 0; i < W; i++) {
        if (pthread_create(&writers[i], NULL, writer, NULL) != 0) {
            fprintf(stderr, "Error creating writer thread %d\n", i);
            exit(1);
        }
    }

    for (i = 0; i < R; i++) {
        if (pthread_join(readers[i], NULL) != 0) {
            fprintf(stderr, "Error joining reader thread %d\n", i);
            exit(1);
        }
    }

    for (i = 0; i < W; i++) {
        if (pthread_join(writers[i], NULL) != 0) {
            fprintf(stderr, "Error joining writer thread %d\n", i);
            exit(1);
        }
    }

    pthread_mutex_destroy(&mutex);
    pthread_mutex_destroy(&rw_mutex);

    return 0;
}


