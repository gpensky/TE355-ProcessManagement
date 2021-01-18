/*
Gabriel Janetzky Pensky
20/11/2020
Program to calculate fatorial fom value 
Arguments:
	[number]:                                       input value to calculate fatorial
    -im [number] or -input_min [number]:            minimum value to compute, only used in multithread
    -pm [number] or -processing_method [number]:    defines the processing method:  1 for single process
                                                                                    2 for fork
                                                                                    3 for thread
    --h or --help
*/

#include "main.h"


int main(int argc, char *argv[]){
    // Reads from input and calls the functions according

    long int input_max;
    int processing_method = 1;
    int process_qtd = 2;

    // read from input
    if (argc == 1){
        printf("No value entered, please refer to --help for reference\n");
        exit(1);
    } else {
        char *p;
        input_max = strtol(argv[1], &p, 10);

        for (int i = 0; i<argc; i++){

            if (!strcmp(argv[i], "-pm") || !strcmp(argv[i], "-processing_method")){
                if (i+2 >= argc){
                    printf("No value passed on parameter -pm");
                } else {
                    char *p;
                    processing_method = strtol(argv[i+1], &p, 10);
                    process_qtd = strtol(argv[i+2], &p, 10);
                }

            } else if (!strcmp(argv[i], "--h") || !strcmp(argv[i], "--help")){
                printf("Gabriel Janetzky Pensky \n");
                printf("20/11/2020 \n");
                printf("Program to calculate fatorial fom value \n");
                printf("Arguments: \n");
                printf("\t[number]: \tinput value to calculate fatorial \n");
                printf("\t-pm [number] or -processing_method [number]: \tdefines the processing method: \t1 for single process; 2 for fork; 3 for thread\n");
                printf("\t--h or --help \n");
                return 0;
            }
        }
    }

    double time = 0;
    switch (processing_method){
    case 1:
        time = process_single(input_max, 1);
        printf("Time elapsed in calculation (-pm=1): %fs \n", time);
        return 0;
        break;

    case 2:
        time = process_fork(input_max, 1, process_qtd);
        if (time > 0) printf("Time elapsed in calculation (-pm=2): %fs \n", time);
        return 0;
        break;

    case 3:
        time = process_thread(input_max, 1, process_qtd);
        if (time > 0) printf("Time elapsed in calculation (-pm=3): %fs \n", time);
        return 0;
        break;

    default:
        printf("No valid value entered, please refer to --help for reference\n");
        return 0;
        break;
    }
    
}