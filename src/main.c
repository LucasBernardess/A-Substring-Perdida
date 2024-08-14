#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>
#include "../include/time.h"
#include "../include/file_io.h"
#include "../include/boyer_moore.h"
#include "kmp.h"

// Inicialização do projeto
int main(int argc, char *argv[]) {
    struct timeval start, end; 
    struct rusage usageStart, usageEnd; 
    char *inputFileName = NULL; 
    char strategy; 
    
    // Verificação dos argumentos
    if (argc != 3) {
        fprintf(stderr, "Use: %s <estrategia> <arquivo de entrada>\n", argv[0]);
        return EXIT_FAILURE;
    }

    strategy = argv[1][0]; 
    inputFileName = argv[2]; 

    // Validação da estratégia
    if (strategy != 'B' && strategy != 'K') {
        fprintf(stderr, "Estratégia inválida! Use 'K' para KMP ou 'B' para Boyer-Moore.\n");
        return EXIT_FAILURE;
    }

    // Início da medição do tempo de execução do programa
    gettimeofday(&start, NULL);
    getrusage(RUSAGE_SELF, &usageStart);

    // Processamento do arquivo de entrada e geração do arquivo de saída
    if (!processInputOutput(inputFileName, strategy)) {
        fprintf(stderr, "Falha no processamento dos arquivos.\n");
        return EXIT_FAILURE;
    }

    // Fim da medição do tempo e cálculo do tempo de execução
    gettimeofday(&end, NULL);
    getrusage(RUSAGE_SELF, &usageEnd);
    calculateExecutionTime(start, end, usageStart, usageEnd);

    return EXIT_SUCCESS;
}
