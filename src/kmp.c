#include <stdio.h>
#include <string.h>

// Função que constrói a tabela de falhas para o algoritmo KMP
void buildFailureTable(char *pattern, int patternLength, int *failureTable) {
    int prefixLength = 0;
    failureTable[0] = 0;
    int index = 1;

    // Preenche a tabela de falhas baseada nos prefixos do padrão
    while (index < patternLength) {
        if (pattern[index] == pattern[prefixLength]) {
            prefixLength++;
            failureTable[index] = prefixLength;
            index++;
        } else {
            if (prefixLength != 0) {
                prefixLength = failureTable[prefixLength - 1];
            } else {
                failureTable[index] = 0;
                index++;
            }
        }
    }
}

// Função que executa o algoritmo KMP e verifica a ocorrência do padrão dentro dos intervalos
void kmpWithIndices(char *text, char *pattern, int numberOfIntervals, int intervals[][2], FILE *outputFile) {
    int textLength = strlen(text);
    int patternLength = strlen(pattern);

    int failureTable[patternLength]; 
    buildFailureTable(pattern, patternLength, failureTable);

    int matchPositions[textLength];
    int matchCount = 0;
    int textIndex = 0;
    int patternIndex = 0;

    // Executa a busca do padrão no texto
    while (textIndex < textLength) {
        if (pattern[patternIndex] == text[textIndex]) {
            textIndex++;
            patternIndex++;
        }

        // Padrão encontrado, salva a posição e ajusta o índice do padrão usando a tabela de falhas
        if (patternIndex == patternLength) {
            matchPositions[matchCount++] = textIndex - patternIndex;
            patternIndex = failureTable[patternIndex - 1];
        } else if (textIndex < textLength && pattern[patternIndex] != text[textIndex]) {
            if (patternIndex != 0) {
                patternIndex = failureTable[patternIndex - 1];
            } else {
                textIndex++;
            }
        }
    }

    // Verifica se as posições encontradas estão dentro dos intervalos especificados
    for (int i = 0; i < numberOfIntervals; i++) {
        int start = intervals[i][0] - 1;
        int end = intervals[i][1] - 1;
        int found = 0;
        for (int j = 0; j < matchCount; j++) {
            if (matchPositions[j] >= start && matchPositions[j] <= end - patternLength + 1) {
                found = 1;
                break;
            }
        }
        if (found) {
            fprintf(outputFile, "sim\n");
        } else {
            fprintf(outputFile, "não\n");
        }
    }
}