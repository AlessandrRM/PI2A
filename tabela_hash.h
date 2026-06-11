#ifndef TABELA_HASH_H
#define TABELA_HASH_H
#include "produto.h"


typedef struct Node {
    Produto produto;
    struct Node *prox;
} Node;

typedef struct {
    Node **itens;
    int tamanho;
    int colisoes;
} HashTable;

HashTable* criarTabelaHash(int tamanho);

void inserirHash(HashTable *tabela, Produto produto);

Produto* buscarHash(HashTable *tabela, int id);

void liberarHash(HashTable *tabela);

#endif