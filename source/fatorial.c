#include "fatorial.h"


// Functions to calculate simple fatorial with result in unsigned long long int
unsigned long long int recursive_fatorial(long int input_max, long int input_min, unsigned long long int result){
// Calculate fatorial of input (long int), returning the result (unsigned long long int)

    FILE *wait_file;
    wait_file = fopen("wait.txt", "w");
    fprintf(wait_file, "wait\n");
    fclose(wait_file);
    fflush(stdout);

    if(input_max == (input_min-1)){
        return result;
    } else if(input_max){
        return input_max * recursive_fatorial(input_max - 1, input_min, result);
    } else {
        return result;
    }
}


unsigned long long int fatorial_single(long int input_max, long int input_min){
    return recursive_fatorial(input_max, input_min, 1);
}


void fatorial_pipe(long int input_max, long int input_min, int *fd){
    unsigned long long int result = recursive_fatorial(input_max, input_min, 1);
    write(fd[PIPE_WRITE], &result, sizeof(result));
    wait(NULL);
}


void * fatorial_thread(void *arg){
    long int input_max = *(long int *)(arg+sizeof(long int));
    long int input_min = *(long int *)arg;

    unsigned long long int result = recursive_fatorial(input_max, input_min, 1);
    pthread_exit(result);
}