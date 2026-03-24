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
        // Mantida para uso futuro
    }

    void selecionarArquivoDentroIntervalo(){
        // Mantida para uso futuro
    }

    int main() {

        FILE *file = fopen("dataset4.csv", "r");

        if (file == NULL) {
            printf("Erro ao abrir o arquivo!\n");
            return 1;
        }

        int total_linhas = contarLinhas("dataset4.csv");

        int read = 0;
        int records = 0;

        Produto *produto = (Produto *) malloc(total_linhas * sizeof(Produto));
        char line[1024];

        // ignora cabecalho
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
        printf("Total de linhas do arquivo eh: %d\n", total_linhas);

        printf("------------------------------------EXECUCAO DAS BUSCAS--------------------------------------------\n");
        printf("Foram realizadas 1000 buscas por IDs aleatorios.\n");
        printf("Divididas em tres regioes: INICIO, MEIO e FIM.\n\n");

        srand(time(NULL));

        int total_buscas = 1000;
        int buscas_por_regiao = total_buscas / 3;

        clock_t inicio, fim;
        double tempo_gasto;

        double tempo_inicio = 0.0;
        double tempo_meio = 0.0;
        double tempo_fim = 0.0;

        int confirmador;

        for (int j = 0; j < total_buscas; j++) {

            int indice_aleatorio;
            char *regiao;

            if (j < buscas_por_regiao) {
                indice_aleatorio = rand() % (records / 3);
                regiao = "INICIO";
            } 
            else if (j < 2 * buscas_por_regiao) {
                indice_aleatorio = (records / 3) + rand() % (records / 3);
                regiao = "MEIO";
            } 
            else {
                indice_aleatorio = (2 * records / 3) + rand() % (records / 3);
                regiao = "FIM";
            }

            int id_procurar = produto[indice_aleatorio].id;
            confirmador = 0;

            // inicio da contagem de tempo
            inicio = clock();

            for (int i = 0; i < records; i++) {
                if (id_procurar == produto[i].id) {
                    confirmador = 1;
                    break;
                }
            }

            // fim da contagem de tempo
            fim = clock();

            tempo_gasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC;

            // acumula tempo por regiao
            if (j < buscas_por_regiao) {
                tempo_inicio += tempo_gasto;
            } 
            else if (j < 2 * buscas_por_regiao) {
                tempo_meio += tempo_gasto;
            } 
            else {
                tempo_fim += tempo_gasto;
            }

            // MOSTRAR buscas de INICIO, MEIO e FIM
            if (
                j < 2 || 
                (j >= buscas_por_regiao && j < buscas_por_regiao + 2) || 
                j >= total_buscas - 2
            ) {
                printf("Busca %d | Regiao: %s | ID: %d | Tempo: %f segundos\n",
                    j + 1, regiao, id_procurar, tempo_gasto);
            }
        }

        double media_inicio = tempo_inicio / buscas_por_regiao;
        double media_meio = tempo_meio / buscas_por_regiao;
        double media_fim = tempo_fim / buscas_por_regiao;

        double tempo_total = tempo_inicio + tempo_meio + tempo_fim;
        double media_geral = tempo_total / total_buscas;

        printf("\n------------------------------------RESULTADO FINAL--------------------------------------------\n");

        printf("Total de buscas realizadas: %d\n\n", total_buscas);

        printf("Tempo medio - INICIO: %f segundos\n", media_inicio);
        printf("Tempo medio - MEIO:   %f segundos\n", media_meio);
        printf("Tempo medio - FIM:    %f segundos\n\n", media_fim);

        printf("Tempo medio GERAL:    %f segundos\n");

        printf("---------------------------------------------------------------------------------------------\n");

        free(produto);
        return 0;
    }