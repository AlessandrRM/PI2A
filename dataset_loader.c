#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dataset_record.h"

Produto* carregarDataset(const char *nomeArquivo, int *total) {
    FILE *file = fopen(nomeArquivo, "r");
    if (!file) {
        printf("Erro ao abrir arquivo: %s\n", nomeArquivo);
        return NULL;
    }

    int n = 0;
    char buffer[1024];

    if (fgets(buffer, sizeof(buffer), file)) {
        while (fgets(buffer, sizeof(buffer), file)) {
            n++;
        }
    }
    
    rewind(file);
    fgets(buffer, sizeof(buffer), file); 

    Produto *vetor = malloc(n * sizeof(Produto));
    if (!vetor) {
        printf("Erro de memoria!\n");
        fclose(file);
        return NULL;
    }

    int i = 0;
    while (fgets(buffer, sizeof(buffer), file) && i < n) {
        if (sscanf(buffer, "%d,%50[^,],%30[^,],%f",
            &vetor[i].id,
            vetor[i].nome,
            vetor[i].categoria,
            &vetor[i].valor) == 4) {

            vetor[i].nome[strcspn(vetor[i].nome, "\r\n")] = 0;
            vetor[i].categoria[strcspn(vetor[i].categoria, "\r\n")] = 0;
            i++;
        }
    }

    fclose(file);
    *total = i;
    return vetor;
}