#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>
#include "../include/time.h"
#include "../include/file_io.h"
#include "../include/boyerMoore.h"
#include "kmp.h"

int main(int argc, char *argv[]) {
    struct timeval start, end;
    struct rusage usageStart, usageEnd;
    char *inputFileName = NULL;
    char strategy;
    
    if (argc != 3) {
        fprintf(stderr, "Use: %s <estrategia> <arquivo de entrada>\n", argv[0]);
        return EXIT_FAILURE;
    }

    strategy = argv[1][0];
    inputFileName = argv[2];

    if (strategy != 'S' && strategy != 'K' ) {
        fprintf(stderr, "Estratégia inválida! Use 'K' para KMP ou 'B' para Boyer-Moore.\n");
        return EXIT_FAILURE;
    }

    gettimeofday(&start, NULL);
    getrusage(RUSAGE_SELF, &usageStart);

    if (!processInputOutput(inputFileName, strategy)) {
        fprintf(stderr, "Falha no processamento dos arquivos.\n");
        return EXIT_FAILURE;
    }

    gettimeofday(&end, NULL);
    getrusage(RUSAGE_SELF, &usageEnd);
    calculateExecutionTime(start, end, usageStart, usageEnd);

    return EXIT_SUCCESS;
}