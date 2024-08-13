#ifndef BOYERMOORE_H
#define BOYERMOORE_H

#define NO_OF_CHARS 256

void boyer_moore_horspool(char *texto, char *padrao, int numeroIntervalos, int intervalos[][2], FILE *arquivoSaida);
void calcularBadCharShift(char *padrao, int tamanhoPadrao, int badCharShift[NO_OF_CHARS]);

#endif