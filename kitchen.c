#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>
#include <limits.h>
#include <semaphore.h>
#include <unistd.h>

sem_t s0;
sem_t s1;
sem_t s2;

void *prepFood(void *ptr) {
    int count = 1;
    while(true) {
        sem_wait(&s0);
        sleep(1);
        printf("Prepping item %d\n", count++);
        sem_post(&s1);
    }
    return NULL;
}

void *cookFood(void *ptr) {
    int count = 1;
    while(true) {
        sem_wait(&s1);
        sleep(2);
        printf("Cooking item %d\n", count++);
        sem_post(&s2);
    }
    return NULL;
}

void *plateFood(void *ptr) {
    int count = 1;
    while(true) {
        sem_wait(&s2);
        sleep(1);
        printf("Plating item %d\n", count++);
    }
    return NULL;
}

int main() {
    sem_init(&s0, 0, 7);
    sem_init(&s1, 0, 0);
    sem_init(&s2, 0, 0);
    pthread_t worker[3];
    pthread_create(&(worker[2]), NULL, plateFood, NULL);
    pthread_create(&(worker[1]), NULL, cookFood, NULL);
    pthread_create(&(worker[0]), NULL, prepFood, NULL);
    
    pthread_join(worker[0], NULL);
    pthread_join(worker[1], NULL);
    pthread_join(worker[2], NULL);
    
    return EXIT_SUCCESS;
}