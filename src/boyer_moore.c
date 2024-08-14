#include <stdio.h>
#include <string.h>

#define MAX_ALFABETO 256

// Função para pré-processar o padrão, construindo a tabela de deslocamento para o algoritmo BMH
void preprocessarDeslocamento(char *padrao, int tamanhoPadrao, int deslocamento[MAX_ALFABETO]) {
    for (int i = 0; i < MAX_ALFABETO; i++) {
        deslocamento[i] = tamanhoPadrao;
    }
    for (int i = 0; i < tamanhoPadrao - 1; i++) {
        deslocamento[(unsigned char)padrao[i]] = tamanhoPadrao - 1 - i;
    }
}

// Função que executa o algoritmo Boyer-Moore-Horspool e verifica a ocorrência do padrão dentro dos intervalos
void bmhComIndices(char *texto, char *padrao, int numeroIntervalos, int intervalos[][2], FILE *arquivoSaida) {
    int tamanhoPadrao = strlen(padrao);

    int deslocamento[MAX_ALFABETO];
    preprocessarDeslocamento(padrao, tamanhoPadrao, deslocamento);

    // Processa cada intervalo especificado
    for (int i = 0; i < numeroIntervalos; i++) {
        int inicio = intervalos[i][0] - 1;
        int fim = intervalos[i][1] - 1;

        int encontrado = 0;
        int j = inicio + tamanhoPadrao - 1;

        // Executa a busca no intervalo
        while (j <= fim) {
            int k = j;
            int l = tamanhoPadrao - 1;
            // Compara o padrão com o texto de trás para frente
            while (l >= 0 && texto[k] == padrao[l]) {
                k--;
                l--;
            }
            // Se o padrão foi encontrado, interrompe a busca
            if (l < 0) {
                encontrado = 1;
                break;
            } else {
                // Desloca o índice de acordo com a tabela de deslocamento
                j += deslocamento[(unsigned char)texto[j]];
            }
        }

        // Escreve o resultado no arquivo de saída
        if (encontrado) {
            fprintf(arquivoSaida, "sim\n");
        } else {
            fprintf(arquivoSaida, "nao\n");
        }
    }
}
