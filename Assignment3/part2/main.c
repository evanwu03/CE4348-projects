
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

typedef struct
{
    pthread_t tid;
    int num;
} Message;

void* child_func(void* arg);

const int MIN = 1;
const int MAX = 10;

#define NUM_CHILDREN 3

// Comparison function to sort data in assending order
int comp(const void *a, const void* b);

Message msgBuf[NUM_CHILDREN];

int main()
{

    printf("begin\n");

    pthread_t threads[NUM_CHILDREN];

    for (int i = 0; i < NUM_CHILDREN; i++) {
        int* idx = malloc(sizeof(int));
        *idx = i;
        pthread_create(&threads[i], NULL, child_func, idx);
    }

    for (int i = 0; i < NUM_CHILDREN; i++) {
        pthread_join(threads[i], NULL);
    }

    // Sort numbers in buffer in ascending order (Least -> Greatest)
    qsort(msgBuf, NUM_CHILDREN, sizeof(Message), comp);

    printf("[tid:num]\n");
    for(int i = 0; i < NUM_CHILDREN; i++) { 
        printf("(%lu, %d) ", msgBuf[i].tid, msgBuf[i].num);
    }
    printf("\n");

    return 0;
}

int comp(const void *a, const void* b) { 
    return ((Message*)a)->num - ((Message*)b)->num;
}


void* child_func(void* arg) {
    int* actual_arg = arg;
    int idx = *actual_arg;

    srand(time(NULL) ^ pthread_self());   // unique seed
    int randNum = (rand() % (MAX - MIN + 1)) + MIN;            // [0,10]

    msgBuf[idx].tid = pthread_self();
    msgBuf[idx].num = randNum;

    free(actual_arg);
    return NULL;
}

