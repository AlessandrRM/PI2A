#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//Código obtem os dados do csv e armazena os 1000 ids em um arquivo .txt.
//Fiz a escolha de ser 300 do começo, 400 do meio e 300 no final. 
//Decidi fazer em programa separado por questão de não misturar duas funções e modificarem os ids já selecionados
int main() {
    FILE *file = fopen("dataset4.csv", "r");
    FILE *saida = fopen("ids_extraidos.txt", "w");

    if (!file || !saida) {
        printf("Erro ao abrir arquivos.\n");
        return 1;
    }

    char buffer[1024];
    int total_dados = 0;

    while (fgets(buffer, sizeof(buffer), file)) {
        int temp_id;
        if (sscanf(buffer, "%d,", &temp_id) == 1) {
            total_dados++;
        }
    }

    if (total_dados < 1000) {
        printf("Aviso: O arquivo só possui %d registros válidos.\n", total_dados);
    }

    int meio_start = (total_dados / 2) - 200;
    int meio_end   = meio_start + 400;
    int fim_start  = total_dados - 300;

    rewind(file);

    int indice_valido = 0;
    int gravados = 0;

    while (fgets(buffer, sizeof(buffer), file)) {
        int id;
       
        if (sscanf(buffer, "%d,", &id) == 1) {
            

            int no_comeco = (indice_valido < 300);
            int no_meio   = (indice_valido >= meio_start && indice_valido < meio_end);
            int no_fim    = (indice_valido >= fim_start);

            if (no_comeco || no_meio || no_fim) {
                fprintf(saida, "%d\n", id);
                gravados++;
            }
            
            indice_valido++;
        }
    }

    fclose(file);
    fclose(saida);

    printf("Finalizado!\n");
    printf("Total de registros validos encontrados: %d\n", total_dados);
    printf("Total de IDs gravados: %d\n", gravados);

    return 0;
}