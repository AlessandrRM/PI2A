#include <stdio.h>
#include <stdlib.h>
//Essa parte do sistema é responsável por pegar os dados .txt e transforma em um array.
//Com o objetivo de deixar o sistema moldável para cada dataset, foi necessário criar essa função separada do sistema.
int main() {
    FILE *file = fopen("ids_extraidos.txt", "r");
    if (file == NULL) {
        printf("Erro ao abrir ids_extraidos.txt\n");
        return 1;
    }

    int id;
    int primeiro = 1;

    printf("int ids_teste[] = {");

    
    while (fscanf(file, "%d", &id) == 1) {
        if (!primeiro) {
            printf(", ");
        }
        printf("%d", id);
        primeiro = 0;
    }

    printf("};\n");

    fclose(file);
    return 0;
}