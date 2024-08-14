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

    char *text = NULL;
    char *pattern = NULL;
    size_t textSize = 0;
    size_t patternSize = 0;
    
    ssize_t len = getline(&text, &textSize, inputFile);
    if (len == -1) {
        fprintf(stderr, "Erro ao ler o texto.\n");
        fclose(inputFile);
        return 0;
    }

    text[strcspn(text, "\n")] = '\0';
    text[strcspn(text, "\r")] = '\0';

    len = getline(&pattern, &patternSize, inputFile);
    if (len == -1) {
        fprintf(stderr, "Erro ao ler o padrão.\n");
        free(text);
        fclose(inputFile);
        return 0;
    }
    
    pattern[strcspn(pattern, "\n")] = '\0';
    pattern[strcspn(pattern, "\r")] = '\0';

    int num_intervals;

    if (fscanf(inputFile, "%d", &num_intervals) != 1) {
        fprintf(stderr, "Formato de arquivo de entrada inválido.\n");
        free(text);
        free(pattern);
        fclose(inputFile);
        return 0;
    }

    if (num_intervals < 0 || num_intervals > 100) {
        fprintf(stderr, "Valor fora do intervalo permitido: %d\n", num_intervals);
        free(text);
        free(pattern);
        fclose(inputFile);
        return 0;
    }

    int intervals[num_intervals][2];
    for (int i = 0; i < num_intervals; i++) {
        if (fscanf(inputFile, "%d %d", &intervals[i][0], &intervals[i][1]) != 2) {
            fprintf(stderr, "Erro ao ler os dados dos intervalos.\n");
            free(text);
            free(pattern);
            fclose(inputFile);
            return 0;
        }
    }
    fclose(inputFile);

    FILE *outputFile = fopen("saida.txt", "w");
    if (!outputFile) {
        perror("Erro ao abrir o arquivo de saída");
        free(text);
        free(pattern);
        return 0;
    }

    if (strategy == 'B') {
        boyer_moore_horspool(text, pattern, num_intervals, intervals, outputFile);
    } else if (strategy == 'K') {
        kmpComIndices(text, pattern, num_intervals, intervals, outputFile);
    }

    fclose(outputFile);
    free(text);
    free(pattern);
    return 1;
}
