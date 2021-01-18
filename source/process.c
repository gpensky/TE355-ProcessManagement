#include "process.h"


// Functions to calculate simple fatorial with result in unsigned long long int
double process_single(long int input_max, int print){

    // Start time count    
    struct timespec ts_begin;
    struct timespec ts_end;
    clock_gettime(CLOCK_REALTIME, &ts_begin);

    // Calculate fatorial
    unsigned long long int result = fatorial_single(input_max, 0);
    if(print) printf("%ld! = %llu\n", input_max, result);

    // End time count
    clock_gettime(CLOCK_REALTIME, &ts_end);
    double time_begin = (double)ts_begin.tv_sec + ((double)ts_begin.tv_nsec/1000000000);
    double time_end = (double)ts_end.tv_sec + ((double)ts_end.tv_nsec/1000000000);

    return time_end-time_begin;

}


double process_fork(long int input_max, int print, int fork_qtd){

    // Define max and min values for each process to calculate
    if (fork_qtd > input_max) fork_qtd = input_max/2;
    
    long int input_max_ind[fork_qtd];
    long int input_min_ind[fork_qtd];

    if (fork_qtd == 1){
        input_min_ind[0] = 0;
        input_max_ind[0] = input_max;
    } else {
        input_min_ind[0] = 0;
        input_max_ind[0] = (input_max/fork_qtd)-1;
        for (int i = 1; i < fork_qtd; i++){
            input_min_ind[i] = input_max_ind[i-1]+1;
            if (i == fork_qtd-1) {
                input_max_ind[i] = input_max;
            } else {
                input_max_ind[i] = input_min_ind[i] + (input_max/fork_qtd)-1;
            }
        }
    }
    
    // Start time count    
    struct timespec ts_begin;
    struct timespec ts_end;
    clock_gettime(CLOCK_REALTIME, &ts_begin);


    // Create children processes
    int process_number;
    int fd[fork_qtd][2];

    for (int i = 0; i < fork_qtd; i++){
        if (pipe(fd[i])==-1) printf("Pipe failed: %d", process_number);
        process_number = fork();

        // Assign work according to process
        if (process_number < 0){
            // Fork error
            printf("Fork failed: %d", process_number);

        } else if (process_number == 0) {
            // Children process
            close(fd[i][PIPE_READ]);
            fatorial_pipe(input_max_ind[i], input_min_ind[i], fd[i]);
            close(fd[i][PIPE_WRITE]);
            exit(0);
        }
    }

    if (process_number > 0){
        // Parent process

        unsigned long long int result_children;
        unsigned long long int result = 1;

        // Receive data from children in pipe
        for (int i = 0; i < fork_qtd; i++){

            close(fd[i][PIPE_WRITE]);
            wait(NULL);
            read(fd[i][PIPE_READ], &result_children, sizeof(result_children));
            result = result * result_children;
            close(fd[i][PIPE_READ]);

        }

        // Print result
        if(print) printf("%ld! = %llu\n", input_max, result);

        // End time count
        clock_gettime(CLOCK_REALTIME, &ts_end);
        double time_begin = (double)ts_begin.tv_sec + ((double)ts_begin.tv_nsec/1000000000);
        double time_end = (double)ts_end.tv_sec + ((double)ts_end.tv_nsec/1000000000);

        return time_end-time_begin;

    }

    return 0;

}


double process_thread(long int input_max, int print, int thread_qtd){
    
    // Define max and min values for each process to calculate
    if (thread_qtd > input_max) thread_qtd = input_max/2;
    
    long int input_max_ind[thread_qtd];
    long int input_min_ind[thread_qtd];

    if (thread_qtd == 1){
        input_min_ind[0] = 0;
        input_max_ind[0] = input_max;
    } else {
        input_min_ind[0] = 0;
        input_max_ind[0] = (input_max/thread_qtd)-1;
        for (int i = 1; i < thread_qtd; i++){
            input_min_ind[i] = input_max_ind[i-1]+1;
            if (i == thread_qtd-1) {
                input_max_ind[i] = input_max;
            } else {
                input_max_ind[i] = input_min_ind[i] + (input_max/thread_qtd)-1;
            }
        }
    }

    long int input_ind[thread_qtd][2];
    for (int i = 0; i < thread_qtd; i++){
        input_ind[i][0] = input_min_ind[i];
        input_ind[i][1] = input_max_ind[i];
    }

    // Start time count    
    struct timespec ts_begin;
    struct timespec ts_end;
    clock_gettime(CLOCK_REALTIME, &ts_begin);

    // Create threads
    pthread_t thread_id[thread_qtd];
    void * thread_res[thread_qtd];
    int rstatus[thread_qtd];

    for (int i = 0; i < thread_qtd; i++){
        rstatus[i] = pthread_create(&thread_id[i], NULL, fatorial_thread, (void*)(input_ind[i]));
        if (rstatus[i]){
            printf("Thread number %d failed: %d\n", i, rstatus[i]);
            exit(EXIT_FAILURE);
        }
    }

    // Wait for threads response and multiply results from the children
    unsigned long long int result = 1;
    for (int i = 0; i < thread_qtd; i++){
        rstatus[i] = pthread_join(thread_id[i], &thread_res[i]);
        result = result * (long int)(thread_res[i]);

    }

    // Print result
    if(print) printf("%ld! = %llu\n", input_max, result);

    // End time count
    clock_gettime(CLOCK_REALTIME, &ts_end);
    double time_begin = (double)ts_begin.tv_sec + ((double)ts_begin.tv_nsec/1000000000);
    double time_end = (double)ts_end.tv_sec + ((double)ts_end.tv_nsec/1000000000);

    return time_end-time_begin;
    
}