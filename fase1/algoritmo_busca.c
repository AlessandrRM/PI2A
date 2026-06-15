#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    int id;
    char nome[51];
    char categoria[31];
    float valor;
} Produto;

int buscaSequencial(Produto *vetor, int tamanho, int id) {
    for (int i = 0; i < tamanho; i++) {
        if (vetor[i].id == id) {
            return i; 
        }
    }
    return -1; 
}


double calcularDiferencaMs(struct timespec start, struct timespec end) {
    return (end.tv_sec - start.tv_sec) * 1000.0 + (end.tv_nsec - start.tv_nsec) / 1000000.0;
}

int carregarIdsDoArquivo(const char *nomeArquivo, int *ids) {
    FILE *file = fopen(nomeArquivo, "r");
    if (!file) {
        printf("Erro ao abrir arquivo de IDs: %s\n", nomeArquivo);
        return 0;
    }
    int i = 0;
    while (fscanf(file, "%d", &ids[i]) == 1 && i < 1000) {
        i++;
    }
    fclose(file);
    return i;
}

int main() {
    int ids_teste[1000];
    int total_ids_carregados = carregarIdsDoArquivo("../fase1/ids_extraidos.txt", ids_teste);
    
    if (total_ids_carregados < 1000) {
        printf("Aviso: Foram carregados apenas %d IDs do arquivo txt.\n", total_ids_carregados);
    }

    FILE *file = fopen("../dataset4.csv", "r");
    if (!file) {
        printf("Erro ao abrir arquivo dataset4.csv!\n");
        return 1;
    }

    int n = 0;
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), file)) n++;
    rewind(file);

    Produto *vetor = (Produto *)malloc(n * sizeof(Produto));
    int total_carregado = 0;
    fgets(buffer, sizeof(buffer), file); // Pula cabeçalho

    while (fgets(buffer, sizeof(buffer), file)) {
        if (sscanf(buffer, "%d , %50[^,] , %30[^,] , %f", 
            &vetor[total_carregado].id, vetor[total_carregado].nome, 
            vetor[total_carregado].categoria, &vetor[total_carregado].valor) >= 1) {
            total_carregado++;
        }
    }
    fclose(file);

    printf("Dataset carregado: %d registros.\n", total_carregado);
    printf("Iniciando experimento de Busca Sequencial via arquivo TXT (3 rodadas)...\n");

    struct timespec start, end;
    
    double seqInicioAcumulado = 0.0;
    double seqMeioAcumulado = 0.0;
    double seqFimAcumulado = 0.0;

    for (int r = 1; r <= 3; r++) {

        clock_gettime(CLOCK_MONOTONIC, &start);
        for (int i = 0; i < 300; i++) {
            buscaSequencial(vetor, total_carregado, ids_teste[i]);
        }
        clock_gettime(CLOCK_MONOTONIC, &end);
        seqInicioAcumulado += calcularDiferencaMs(start, end);

        clock_gettime(CLOCK_MONOTONIC, &start);
        for (int i = 300; i < 700; i++) {
            buscaSequencial(vetor, total_carregado, ids_teste[i]);
        }
        clock_gettime(CLOCK_MONOTONIC, &end);
        seqMeioAcumulado += calcularDiferencaMs(start, end);

        clock_gettime(CLOCK_MONOTONIC, &start);
        for (int i = 700; i < 1000; i++) {
            buscaSequencial(vetor, total_carregado, ids_teste[i]);
        }
        clock_gettime(CLOCK_MONOTONIC, &end);
        seqFimAcumulado += calcularDiferencaMs(start, end);
    }

    double medSeqInicio = seqInicioAcumulado / 3.0;
    double medSeqMeio   = seqMeioAcumulado / 3.0;
    double medSeqFim    = seqFimAcumulado / 3.0;
    double totalMediaSeq = medSeqInicio + medSeqMeio + medSeqFim;

    printf("\n=================================================================\n");
    printf("            BUSCA SEQUENCIAL             \n");
    printf("=================================================================\n");
    printf("Quantidade total de registros carregados : %d\n", total_carregado);
    printf("Número total de chaves lidas do TXT      : %d\n", total_ids_carregados);
    printf("-----------------------------------------------------------------\n");
    printf("DETALHAMENTO DOS TEMPOS MÉDIOS DA BUSCA SEQUENCIAL (3 Rodadas):\n\n");
    
    printf("  Trecho Início (300 buscas) : %10.4f ms  (Média/busca: %.6f ms)\n", medSeqInicio, medSeqInicio / 300.0);
    printf("  Trecho Meio   (400 buscas) : %10.4f ms  (Média/busca: %.6f ms)\n", medSeqMeio, medSeqMeio / 400.0);
    printf("  Trecho Fim    (300 buscas) : %10.4f ms  (Média/busca: %.6f ms)\n", medSeqFim, medSeqFim / 300.0);
    printf("-----------------------------------------------------------------\n");
    printf("TEMPO MÉDIO ACUMULADO (1.000 buscas)     : %.4f ms\n", totalMediaSeq);
    printf("TEMPO MÉDIO GERAL POR BUSCA              : %.6f ms\n", totalMediaSeq / 1000.0);
    printf("=================================================================\n");

    free(vetor);
    return 0;
}