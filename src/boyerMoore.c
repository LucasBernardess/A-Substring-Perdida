#include <stdio.h>
#include <string.h>
#include "boyerMoore.h"

#define NO_OF_CHARS 256 

void calcularBadCharShift(char *padrao, int tamanhoPadrao, int badCharShift[NO_OF_CHARS]) {
    for (int i = 0; i < NO_OF_CHARS; i++) {
        badCharShift[i] = tamanhoPadrao;
    }
    for (int i = 0; i < tamanhoPadrao - 1; i++) {
        badCharShift[(int)padrao[i]] = tamanhoPadrao - 1 - i;
    }
}

void boyer_moore_horspool(char *texto, char *padrao, int numeroIntervalos, int intervalos[][2], FILE *arquivoSaida) {
    int tamanhoPadrao = strlen(padrao);
    int tamanhoTexto = strlen(texto);
    int badCharShift[NO_OF_CHARS];

    calcularBadCharShift(padrao, tamanhoPadrao, badCharShift);
    
    int posicoesCasamento[tamanhoTexto];
    int quantidadeCasamentos = 0;

    int posicao = 0; 
    while (posicao <= (tamanhoTexto - tamanhoPadrao)) {
        int j = tamanhoPadrao - 1;

        while (j >= 0 && padrao[j] == texto[posicao + j]) {
            j--;
        }

        if (j < 0) {
            posicoesCasamento[quantidadeCasamentos++] = posicao;
            posicao += (posicao + tamanhoPadrao < tamanhoTexto) ? badCharShift[(unsigned char)texto[posicao + tamanhoPadrao]] : 1;
        } else {
            posicao += badCharShift[(unsigned char)texto[posicao + j]];
        }
    }

    for (int i = 0; i < numeroIntervalos; i++) {
        int inicio = intervalos[i][0] - 1;
        int fim = intervalos[i][1] - 1;
        int encontrado = 0;
        for (int j = 0; j < quantidadeCasamentos; j++) {
            if (posicoesCasamento[j] >= inicio && posicoesCasamento[j] <= fim - tamanhoPadrao + 1) {
                encontrado = 1;
                break;
            }
        }
        if (encontrado) {
            fprintf(arquivoSaida, "sim\n");
        } else {
            fprintf(arquivoSaida, "nao\n");
        }
    }
}
