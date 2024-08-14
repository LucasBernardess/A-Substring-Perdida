#include <stdio.h>
#include <string.h>

#define MAX_ALFABETO 256

void preprocessarDeslocamento(char *padrao, int tamanhoPadrao, int deslocamento[MAX_ALFABETO]) {
    for (int i = 0; i < MAX_ALFABETO; i++) {
        deslocamento[i] = tamanhoPadrao;
    }
    for (int i = 0; i < tamanhoPadrao - 1; i++) {
        deslocamento[(unsigned char)padrao[i]] = tamanhoPadrao - 1 - i;
    }
}

void bmhComIndices(char *texto, char *padrao, int numeroIntervalos, int intervalos[][2], FILE *arquivoSaida) {
    int tamanhoPadrao = strlen(padrao);

    int deslocamento[MAX_ALFABETO];
    preprocessarDeslocamento(padrao, tamanhoPadrao, deslocamento);

    for (int i = 0; i < numeroIntervalos; i++) {
        int inicio = intervalos[i][0] - 1;
        int fim = intervalos[i][1] - 1;

        int encontrado = 0;
        int j = inicio + tamanhoPadrao - 1;

        while (j <= fim) {
            int k = j;
            int l = tamanhoPadrao - 1;
            while (l >= 0 && texto[k] == padrao[l]) {
                k--;
                l--;
            }
            if (l < 0) {
                encontrado = 1;
                break;
            } else {
                j += deslocamento[(unsigned char)texto[j]];
            }
        }

        if (encontrado) {
            fprintf(arquivoSaida, "sim\n");
        } else {
            fprintf(arquivoSaida, "nao\n");
        }
    }
}