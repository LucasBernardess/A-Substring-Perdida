#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/file_io.h"
#include "../include/boyer_moore.h"
#include "../include/kmp.h"

// Função que processa o arquivo de entrada e executa o algoritmo de busca
int processInputOutput(const char *inputFileName, char strategy) {
    // Abre o arquivo de entrada para leitura
    FILE *inputFile = fopen(inputFileName, "r");
    if (!inputFile) {
        perror("Erro ao abrir o arquivo de entrada");
        return 0;
    }

    char *text = NULL;
    char *pattern = NULL;
    size_t textSize = 0;
    size_t patternSize = 0;

    // Lê o texto do arquivo
    ssize_t len = getline(&text, &textSize, inputFile);
    if (len == -1) {
        fprintf(stderr, "Erro ao ler o texto.\n");
        fclose(inputFile);
        return 0;
    }

    text[strcspn(text, "\n")] = '\0';
    text[strcspn(text, "\r")] = '\0';

    // Lê o padrão do arquivo
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

    // Lê o número de intervalos do arquivo
    if (fscanf(inputFile, "%d", &num_intervals) != 1) {
        fprintf(stderr, "Formato de arquivo de entrada inválido.\n");
        free(text);
        free(pattern);
        fclose(inputFile);
        return 0;
    }

    // Verifica se o número de intervalos é válido
    if (num_intervals < 0 || num_intervals > 100) {
        fprintf(stderr, "Valor fora do intervalo permitido: %d\n", num_intervals);
        free(text);
        free(pattern);
        fclose(inputFile);
        return 0;
    }

    // Aloca espaço para armazenar os intervalos
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

    // Abre o arquivo de saída para escrita
    FILE *outputFile = fopen("saida.txt", "w");
    if (!outputFile) {
        perror("Erro ao abrir o arquivo de saída");
        free(text);
        free(pattern);
        return 0;
    }

    // Executa o algoritmo de busca baseado na estratégia escolhida
    if (strategy == 'B') {
        bmhComIndices(text, pattern, num_intervals, intervals, outputFile);
    } else if (strategy == 'K') {
        kmpComIndices(text, pattern, num_intervals, intervals, outputFile);
    }

    // Fecha o arquivo de saída após a escrita
    fclose(outputFile);
    free(text);
    free(pattern);
    return 1;
}
