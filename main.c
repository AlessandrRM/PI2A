#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "dataset_record.h"


Produto* carregarDataset(const char *nomeArquivo, int *total);

int colisoesTotais = 0;

int funcaoHash(int id, int m) {
    unsigned long hash = (unsigned long)id * 31;
    return (int)(hash % m);
}

void inserirHash(Node **tabela, int m, Produto prod) {
    int idx = funcaoHash(prod.id, m);
    Node *novo = malloc(sizeof(Node));
    novo->dado = prod;
    novo->proximo = NULL;
    
    if (tabela[idx] == NULL) {
        tabela[idx] = novo;
    } else {
        colisoesTotais++; 
        novo->proximo = tabela[idx]; 
        tabela[idx] = novo;
    }
}

Produto* buscaHash(Node **tabela, int m, int idAlvo) {
    int idx = funcaoHash(idAlvo, m);
    Node *atual = tabela[idx];
    while (atual != NULL) {
        if (atual->dado.id == idAlvo) return &(atual->dado);
        atual = atual->proximo;
    }
    return NULL; 
}


int carregarIdsBusca(const char *nomeArquivo, int *ids) {
    FILE *file = fopen(nomeArquivo, "r");
    if (!file) return 0;
    int i = 0;
    while (fscanf(file, "%d", &ids[i]) == 1 && i < 1000) {
        i++;
    }
    fclose(file);
    return i;
}

double calcularDiferencaMs(struct timespec start, struct timespec end) {
    return (end.tv_sec - start.tv_sec) * 1000.0 + (end.tv_nsec - start.tv_nsec) / 1000000.0;
}

void liberarTabela(Node **tabela, int m) {
    for (int i = 0; i < m; i++) {
        Node *atual = tabela[i];
        while (atual != NULL) {
            Node *aux = atual;
            atual = atual->proximo;
            free(aux);
        }
    }
    free(tabela);
}

int main() {
    int totalRegistros = 0;
    
    printf("Carregando dataset4.csv...\n");
    Produto *datasetVetor = carregarDataset("dataset4.csv", &totalRegistros);
    if (!datasetVetor) return 1;

    int m = totalRegistros; 
    Node **tabelaHash = calloc(m, sizeof(Node*));
    
    printf("Estruturando dados na Tabela Hash...\n");
    for (int i = 0; i < totalRegistros; i++) {
        inserirHash(tabelaHash, m, datasetVetor[i]);
    }

    int idsBusca[1000];
    int totalIds = carregarIdsBusca("fase1/ids_extraidos.txt", idsBusca);
    if (totalIds < 1000) {
        printf("Aviso: Apenas %d IDs carregados do arquivo.\n", totalIds);
    }

    struct timespec start, end;
    
    double hashInicioAcumulado = 0.0;
    double hashMeioAcumulado = 0.0;
    double hashFimAcumulado = 0.0;


    for (int rodada = 1; rodada <= 3; rodada++) {
        clock_gettime(CLOCK_MONOTONIC, &start);
        for (int i = 0; i < 300; i++) {
            buscaHash(tabelaHash, m, idsBusca[i]);
        }
        clock_gettime(CLOCK_MONOTONIC, &end);
        hashInicioAcumulado += calcularDiferencaMs(start, end);

        clock_gettime(CLOCK_MONOTONIC, &start);
        for (int i = 300; i < 700; i++) {
            buscaHash(tabelaHash, m, idsBusca[i]);
        }
        clock_gettime(CLOCK_MONOTONIC, &end);
        hashMeioAcumulado += calcularDiferencaMs(start, end);

        clock_gettime(CLOCK_MONOTONIC, &start);
        for (int i = 700; i < 1000; i++) {
            buscaHash(tabelaHash, m, idsBusca[i]);
        }
        clock_gettime(CLOCK_MONOTONIC, &end);
        hashFimAcumulado += calcularDiferencaMs(start, end);
    }

    double medHashInicio = hashInicioAcumulado / 3.0;
    double medHashMeio   = hashMeioAcumulado / 3.0;
    double medHashFim    = hashFimAcumulado / 3.0;
    double totalMediaHash = medHashInicio + medHashMeio + medHashFim;


    printf("=================================================================\n");
    printf("Quantidade total de registros carregados : %d\n", totalRegistros);
    printf("Número total de colisões detectadas      : %d\n", colisoesTotais);
    printf("-----------------------------------------------------------------\n");
    printf("DETALHAMENTO DOS TEMPOS MÉDIOS DA TABELA HASH (3 Rodadas):\n\n");
    
    printf("  Trecho Início (300 buscas) : %10.4f ms  (Média/busca: %.6f ms)\n", medHashInicio, medHashInicio / 300.0);
    printf("  Trecho Meio   (400 buscas) : %10.4f ms  (Média/busca: %.6f ms)\n", medHashMeio, medHashMeio / 400.0);
    printf("  Trecho Fim    (300 buscas) : %10.4f ms  (Média/busca: %.6f ms)\n", medHashFim, medHashFim / 300.0);
    printf("-----------------------------------------------------------------\n");
    printf("TEMPO MÉDIO ACUMULADO (1.000 buscas)     : %.4f ms\n", totalMediaHash);
    printf("TEMPO MÉDIO GERAL POR BUSCA              : %.6f ms\n", totalMediaHash / 1000.0);
    printf("=================================================================\n");

    liberarTabela(tabelaHash, m);
    free(datasetVetor);
    return 0;
}