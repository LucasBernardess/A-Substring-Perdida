#ifndef BOYERMOORE_H
#define BOYERMOORE_H

#define MAX_ALFABETO 256

void preprocessarDeslocamento(char *padrao, int tamanhoPadrao, int deslocamento[MAX_ALFABETO]);
void bmhComIndices(char *texto, char *padrao, int numeroIntervalos, int intervalos[][2], FILE *arquivoSaida);

#endif