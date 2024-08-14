#include <stdio.h>
#include <string.h>

// Função que constrói a tabela de falhas para o algoritmo KMP
void construirTabelaFalhas(char *padrao, int tamanhoPadrao, int *tabelaFalhas) {
    int comprimentoPrefixo = 0;
    tabelaFalhas[0] = 0;
    int indice = 1;

    // Preenche a tabela de falhas baseada nos prefixos do padrão
    while (indice < tamanhoPadrao) {
        if (padrao[indice] == padrao[comprimentoPrefixo]) {
            comprimentoPrefixo++;
            tabelaFalhas[indice] = comprimentoPrefixo;
            indice++;
        } else {
            if (comprimentoPrefixo != 0) {
                comprimentoPrefixo = tabelaFalhas[comprimentoPrefixo - 1];
            } else {
                tabelaFalhas[indice] = 0;
                indice++;
            }
        }
    }
}

// Função que executa o algoritmo KMP e verifica a ocorrência do padrão dentro dos intervalos
void kmpComIndices(char *texto, char *padrao, int numeroIntervalos, int intervalos[][2], FILE *arquivoSaida) {
    int tamanhoTexto = strlen(texto);
    int tamanhoPadrao = strlen(padrao);

    int tabelaFalhas[tamanhoPadrao]; 
    construirTabelaFalhas(padrao, tamanhoPadrao, tabelaFalhas);

    int posicoesCasamento[tamanhoTexto];
    int quantidadeCasamentos = 0;
    int indiceTexto = 0;
    int indicePadrao = 0;

    // Executa a busca do padrão no texto
    while (indiceTexto < tamanhoTexto) {
        if (padrao[indicePadrao] == texto[indiceTexto]) {
            indiceTexto++;
            indicePadrao++;
        }

        // Padrão encontrado, salva a posição e ajusta o índice do padrão usando a tabela de falhas
        if (indicePadrao == tamanhoPadrao) {
            posicoesCasamento[quantidadeCasamentos++] = indiceTexto - indicePadrao;
            indicePadrao = tabelaFalhas[indicePadrao - 1];
        } else if (indiceTexto < tamanhoTexto && padrao[indicePadrao] != texto[indiceTexto]) {
            if (indicePadrao != 0) {
                indicePadrao = tabelaFalhas[indicePadrao - 1];
            } else {
                indiceTexto++;
            }
        }
    }

    // Verifica se as posições encontradas estão dentro dos intervalos especificados
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
