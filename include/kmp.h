#ifndef KMP_H
#define KMP_H

void kmpWithIndices(char *texto, char *padrao, int numeroIntervalos, int intervalos[][2], FILE *arquivoSaida);
void buildFaultTable(char *padrao, int tamanhoPadrao, int *tabelaFalhas);


#endif