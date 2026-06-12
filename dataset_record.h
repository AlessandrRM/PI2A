#ifndef DATASET_RECORD_H
#define DATASET_RECORD_H

typedef struct {
    int id;
    char nome[51];
    char categoria[31];
    float valor;
} Produto;

typedef struct Node {
    Produto dado;
    struct Node *proximo;
} Node;

#endif