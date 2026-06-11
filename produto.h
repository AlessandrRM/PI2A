#ifndef PRODUTO_H
#define PRODUTO_H

typedef struct {
    int id;
    char nome[51];
    char categoria[31];
    float valor;
} Produto;

#endif