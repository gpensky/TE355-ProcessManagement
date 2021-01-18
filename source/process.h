// libraries
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h>

// program files
#include "fatorial.h"

// defines
#define PIPE_READ 0
#define PIPE_WRITE 1

// prototypes for the functions
double process_single(long int input_max, int print);
double process_fork(long int input_max, int print, int fork_qtd);
double process_thread(long int input_max, int print, int thread_qtd);