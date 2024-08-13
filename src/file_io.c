#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/file_io.h"
#include "../include/boyerMoore.h"
#include "../include/kmp.h"

int processInputOutput(const char *inputFileName, char strategy) {
    
    FILE *inputFile = fopen(inputFileName, "r");
    if (!inputFile) {
        perror("Erro ao abrir o arquivo de entrada");
        return 0;
    }

    char text[1000];
    char pattern[100];
    int num_intervals;

    fscanf(inputFile, "%s", text);
    fscanf(inputFile, "%s", pattern);

    if (fscanf(inputFile, "%d", &num_intervals) != 1) {
        fprintf(stderr, "Formato de arquivo de entrada inválido.\n");
        fclose(inputFile);
        return 0;
    }

    if (num_intervals < 0 || num_intervals > 100) {
        fprintf(stderr, "Valor fora do intervalo permitido: %d\n", num_intervals);
        fclose(inputFile);
        return 0;
    }

    int intervals[num_intervals][2];
    for (int i = 0; i < num_intervals; i++) {
        if (fscanf(inputFile, "%d %d", &intervals[i][0], &intervals[i][1]) != 2) {
            fprintf(stderr, "Erro ao ler os dados dos intervalos.\n");
            fclose(inputFile);
            return 0;
        }
    }
    fclose(inputFile);

    FILE *outputFile = fopen("saida.txt", "w");
    if (!outputFile) {
        perror("Erro ao abrir o arquivo de saída");
        return 0;
    }

    if (strategy == 'B') {
        boyer_moore_horspool(text, pattern, num_intervals, intervals, outputFile);
    }else if(strategy == 'K') {
        kmpComIndices(text, pattern, num_intervals, intervals, outputFile);
    }

    fclose(outputFile);
    return 1;
}