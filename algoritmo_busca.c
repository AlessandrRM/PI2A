#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int id;
    char nome[51];
    char categoria[31];
    float valor;
} Produto;

int contarLinhas(const char *filename) {
    FILE *file = fopen(filename, "r");
    int linhas = 0;
    char ch;
    while ((ch = fgetc(file)) != EOF) {
        if (ch == '\n') {
            linhas++;
        }
    }
    
    fclose(file);
    return linhas + 1;
}

void selecionarIntervalo(){
    //A função tem que receber o intervalo de arquivos para serem buscados
    //Por exemplo, quero selecionar os registro de (n-m), ele deve retornar esses valores
}

void selecionarArquivoDentroIntervalo(){
    //A função tem que fazer a busca de um Id pelo intervalo do registro
}



int main() {
    FILE *file;
    file = fopen("dataset4.csv", "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return 1;
    }
    int total_linhas = contarLinhas("dataset4.csv");

    int n = total_linhas;
    int read = 0;
    int records = 0;
    clock_t inicio, fim;
    double tempo_gasto;

    int id_procurar = 213256; //ID DE PROCURA

    int confirmador = 0;
    Produto *produto = (Produto *) malloc(total_linhas * sizeof(Produto));
    char line[1024]; 
fgets(line, sizeof(line), file); 

while (records < total_linhas && fgets(line, sizeof(line), file)) {
    read = sscanf(line, "%d , %50[^,] , %30[^,] , %f",
                &produto[records].id,
                produto[records].nome,
                produto[records].categoria,
                &produto[records].valor);

    if (read == 4) {
        records++;
    }
}
    fclose(file);

    printf("------------------------------------TOTAL DE LINHAS--------------------------------------------\n");
    printf("Total de linhas do arquivo e: %d\n", total_linhas);
    printf("------------------------------------RESULTADO DA BUSCA POR ID--------------------------------------------\n");
    //inicio da contagem de tempo
    inicio = clock();
    printf("ID\t| NOME\t\t\t\t| CATEGORIA\t\t| VALOR\n");
    for (int i = 0; i < records; i++) {
        if(id_procurar == produto[i].id ){
        printf("%d | %-30s | %-20s | R$ %.2f\n",
            produto[i].id,
            produto[i].nome,
            produto[i].categoria,
            produto[i].valor);
            confirmador = 1;
            break;
    }}
    if(confirmador != 1){
        printf("Valor nao encontrado\n");
    }
    //fim da contagem de tempo
    fim = clock();

    // Tempo em segundos
    tempo_gasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    printf("Tempo de execucao: %f segundos\n", tempo_gasto);
    printf("---------------------------------------------------------------------------------------------\n");
    free(produto);
    return 0;
}