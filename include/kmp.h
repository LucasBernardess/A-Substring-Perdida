#ifndef KMP_H
#define KMP_H

void kmpComIndices(char *texto, char *padrao, int numeroIntervalos, int intervalos[][2], FILE *arquivoSaida);
void construirTabelaFalhas(char *padrao, int tamanhoPadrao, int *tabelaFalhas);


#endif