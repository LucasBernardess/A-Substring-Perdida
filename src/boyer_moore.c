#include <stdio.h>
#include <string.h>

#define MAX_ALPHABET 256

// Função para pré-processar o padrão, construindo a tabela de deslocamento para o algoritmo BMH
void preprocessShift(char *pattern, int patternLength, int shiftTable[MAX_ALPHABET]) {
    for (int i = 0; i < MAX_ALPHABET; i++) {
        shiftTable[i] = patternLength;
    }
    for (int i = 0; i < patternLength - 1; i++) {
        shiftTable[(unsigned char)pattern[i]] = patternLength - 1 - i;
    }
}

// Função que executa o algoritmo Boyer-Moore-Horspool e verifica a ocorrência do padrão dentro dos intervalos
void bmhWithIndices(char *text, char *pattern, int numberOfIntervals, int intervals[][2], FILE *outputFile) {
    int patternLength = strlen(pattern);

    int shiftTable[MAX_ALPHABET];
    preprocessShift(pattern, patternLength, shiftTable);

    // Processa cada intervalo especificado
    for (int i = 0; i < numberOfIntervals; i++) {
        int start = intervals[i][0] - 1;
        int end = intervals[i][1] - 1;

        int found = 0;
        int j = start + patternLength - 1;

        // Executa a busca no intervalo
        while (j <= end) {
            int k = j;
            int l = patternLength - 1;
            // Compara o padrão com o texto de trás para frente
            while (l >= 0 && text[k] == pattern[l]) {
                k--;
                l--;
            }
            // Se o padrão foi encontrado, interrompe a busca
            if (l < 0) {
                found = 1;
                break;
            } else {
                // Desloca o índice de acordo com a tabela de deslocamento
                j += shiftTable[(unsigned char)text[j]];
            }
        }

        // Escreve o resultado no arquivo de saída
        if (found) {
            fprintf(outputFile, "sim\n");
        } else {
            fprintf(outputFile, "não\n");
        }
    }
}
