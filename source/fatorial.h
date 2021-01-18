// libraries
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h>

// defines
#define PIPE_READ 0
#define PIPE_WRITE 1

// prototypes for the functions
unsigned long long int recursive_fatorial(long int input_max, long int input_min, unsigned long long int result);
unsigned long long int fatorial_single(long int input_max, long int input_min);
void fatorial_pipe(long int input_max, long int input_min, int *fd);
void * fatorial_thread(void *arg);
