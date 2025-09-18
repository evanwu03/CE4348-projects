

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <time.h>

typedef struct
{
    int pid;
    int num;
} Message;

const int MIN = 1;
const int MAX = 10;

const int NUM_CHILDREN = 3;

// Comparison function to sort data in assending order
int comp(const void *a, const void* b);


int main()
{

    printf("begin\n");

    int childToParentPipe[2] = {0};
    Message msgBuf[NUM_CHILDREN];

    if (pipe(childToParentPipe) < 0)
        exit(EXIT_FAILURE);

    /* Fork example */
    for (int i = 0; i < NUM_CHILDREN; i++)
    {

        pid_t pid = fork();

        if (pid == 0)
        {
            srand(time(NULL) + getpid());
            printf("child %u\n", i);

            // generate random number [0,10]
            int randNum = (rand() % (MAX - MIN + 1)) + MIN;

            Message msg = {.pid = getpid(), .num = randNum};

            // Send random # and child PID to parent
            write(childToParentPipe[1], &msg, sizeof(Message));

            exit(EXIT_SUCCESS);
        }
    }

    close(childToParentPipe[1]);

    for (int i = 0; i < NUM_CHILDREN; i++)
    {
        wait(NULL);
        read(childToParentPipe[0], &msgBuf[i], sizeof(Message));
    }

    // Sort numbers in buffer in ascending order (Least -> Greatest)
    qsort(msgBuf, NUM_CHILDREN, sizeof(Message), comp);

    printf("[pid:num]\n");
    for(int i = 0; i < NUM_CHILDREN; i++) { 
        printf("(%d, %d) ", msgBuf[i].pid, msgBuf[i].num);
    }
    printf("\n");

    close(childToParentPipe[0]);

    return 0;
}

int comp(const void *a, const void* b) { 
    return ((Message*)a)->num - ((Message*)b)->num;
}
