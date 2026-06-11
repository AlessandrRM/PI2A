#include <stdio.h>
#include <stdlib.h>
#include "tabela_hash.h"

static int funcaoHash(int id, int tamanho) {
    return id % tamanho;
}

HashTable* criarTabelaHash(int tamanho) {

    HashTable *tabela = malloc(sizeof(HashTable));

    tabela->tamanho = tamanho;
    tabela->colisoes = 0;

    tabela->itens = calloc(tamanho, sizeof(Node*));

    return tabela;
}

void inserirHash(HashTable *tabela, Produto produto) {

    int indice = funcaoHash(produto.id, tabela->tamanho);

    if (tabela->itens[indice] != NULL) {
        tabela->colisoes++;
    }

    Node *novo = malloc(sizeof(Node));

    novo->produto = produto;

    novo->prox = tabela->itens[indice];

    tabela->itens[indice] = novo;
}

Produto* buscarHash(HashTable *tabela, int id) {

    int indice = funcaoHash(id, tabela->tamanho);

    Node *atual = tabela->itens[indice];

    while (atual != NULL) {

        if (atual->produto.id == id) {
            return &atual->produto;
        }

        atual = atual->prox;
    }

    return NULL;
}

void liberarHash(HashTable *tabela) {

    for (int i = 0; i < tabela->tamanho; i++) {

        Node *atual = tabela->itens[i];

        while (atual != NULL) {

            Node *temp = atual;

            atual = atual->prox;

            free(temp);
        }
    }

    free(tabela->itens);
    free(tabela);
}