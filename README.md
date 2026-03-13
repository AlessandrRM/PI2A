# Projeto Integrador 2A

Fase 1

🎯 Objetivo Geral
Desenvolver uma base experimental para análise de desempenho de algoritmos de busca, por meio da:
Leitura e estruturação de dados reais;
Implementação da busca sequencial;
Medição de tempo de execução;
Construção de um relatório técnico inicial com análise dos resultados.
Esta fase tem como foco estabelecer um ponto de comparação (baseline), que será utilizado como referência comparativa na implementação da Tabela Hash na Fase II.

📦 Dataset
Será disponibilizado um arquivo CSV contendo a seguinte estrutura lógica:
```C
typedef struct {
int id;
char nome[51];
char categoria[31];
float valor;
} Produto;
```
O volume de dados poderá variar para permitir testes com diferentes tamanhos de entrada.

🧩 Requisitos Funcionais
O programa deve atender integralmente aos seguintes requisitos:
a) Leitura do arquivo CSV com verificação de erros (arquivo inexistente, formato inválido, etc.);
b) Armazenamento dos registros em vetor dinâmico;
c) Implementação da função de busca sequencial por id;
d) Implementação de função para medição do tempo de busca (utilizando mecanismo adequado da linguagem);
e) Execução de múltiplos testes para cálculo do tempo médio de busca.

🔬 Protocolo Experimental
Para garantir padronização entre os grupos, os testes devem seguir o seguinte protocolo:
1. O vetor deve estar completamente carregado antes do início das medições.
2. Devem ser realizadas no mínimo 1.000 buscas consecutivas para cálculo do tempo médio.
3. As buscas devem contemplar:
Elementos no início do vetor;
Elementos no meio;
Elementos no final;
Elementos inexistentes.
4. O tempo total deve ser medido e dividido pelo número de execuções para obtenção do tempo médio de busca.
5. Os testes devem ser repetidos ao menos 3 vezes, apresentando-se a média final.

Não serão aceitas medições isoladas ou testes manuais.

📋 Resultados Esperados
O relatório técnico deve apresentar, obrigatoriamente:
1. Quantidade total de registros carregados.
2. Tempo total das execuções de busca.
3. Tempo médio por busca.
4. Tabela com os resultados obtidos.
5. Breve análise interpretativa dos dados, discutindo:
Comportamento observado;
Relação entre tamanho do vetor e tempo de busca;
Limitações da busca sequencial.
A ausência de qualquer uma dessas medições comprometerá a avaliação.

👥 Trabalho em Grupo
O trabalho poderá ser realizado em grupo de até 3 integrantes. A participação de todos deve ser comprovável por commits. Cada integrante deve submeter o link do repositório. O projeto deve compilar e executar corretamente no momento da avaliação.

📂 Entrega do Projeto
O projeto deve conter:
Repositório no GitHub;
Commits organizados e coerentes com a evolução do projeto;
Aplicação executável localmente;
Relatório técnico parcial contendo descrição do problema, caracterização do dataset, metodologia de testes (seguindo o protocolo), resultados obtidos e análise preliminar do desempenho.
📊 Critérios de Avaliação
A avaliação será realizada com base na rubrica disponibilizada na atividade, a qual estabelece os critérios e os níveis de desempenho considerados na correção.

Fase 2 

🎯 Objetivo Geral
Desenvolver uma estrutura de busca otimizada para análise de desempenho de algoritmos, por meio da:
Leitura e estruturação de dados reais;
Implementação da Tabela Hash com tratamento de colisões;
Medição controlada do tempo de execução;
Análise comparativa entre busca sequencial (Fase I) e Tabela Hash;
Produção de artigo científico com análise experimental completa.
Esta fase tem como foco validar experimentalmente a eficiência da Tabela Hash em comparação ao baseline estabelecido na Fase I.

🧩 Requisitos Funcionais
O programa deve atender integralmente aos seguintes requisitos:
a) Implementação da Tabela Hash com encadeamento;
b) Utilização da função hash definida para o grupo;
c) Tamanho da tabela hash deverá ser igual ao volume de dados do dataset testado;
d) Implementação de mecanismo para contabilizar colisões;
e) Execução automatizada de múltiplos testes para cálculo do tempo médio de busca.

🔬 Protocolo Experimental
Para garantir padronização entre os grupos, os testes devem seguir o seguinte protocolo:
1. A Tabela Hash deve estar completamente carregada antes do início das medições.
2. Devem ser realizadas no mínimo 1.000 buscas consecutivas para cálculo do tempo médio.
3. As buscas devem contemplar:
Elementos existentes;
Elementos inexistentes.
4. O tempo total deve ser medido e dividido pelo número de execuções para obtenção do tempo médio.
5. Os testes devem ser repetidos ao menos 3 vezes, apresentando-se a média final.
6. Deve ser contabilizado o número total de colisões.

Não serão aceitas medições isoladas ou testes manuais.

📋 Resultados Esperados
O relatório técnico deve apresentar, obrigatoriamente:
1. Quantidade total de registros carregados.
2. Número total de colisões.
3. Tempo total das execuções de busca.
4. Tempo médio por busca.
5. Tabela comparativa:
Métrica  |  Busca Sequencial  |  Tabela Hash
Tempo médio        
Complexidade teórica        
Observações experimentais        
8. Análise interpretativa discutindo:
Diferença entre desempenho teórico e prático;
Eficiência da função hash;
Vantagens e limitações observadas.
A ausência de qualquer uma dessas medições comprometerá a avaliação.

👥 Trabalho em Grupo
Deve ser mantido o mesmo grupo da Fase I. A participação de todos deve ser comprovável por commits. Cada integrante deve submeter o link do repositório. O projeto deve compilar e executar corretamente no momento da avaliação.

📂 Entrega do Projeto
O projeto deve conter:
Repositório no GitHub;
Commits organizados e coerentes com a evolução do projeto;
Aplicação executável localmente;
Artigo científico final contendo introdução teórica fundamentada em Estrutura de Dados, fundamentação sobre Tabelas Hash, metodologia experimental, resultados da Fase I, resultados da Fase II, comparação formal, discussão crítica e conclusão.
📊 Critérios de Avaliação
A avaliação será realizada com base na rubrica disponibilizada na atividade, a qual estabelece os critérios e os níveis de desempenho considerados na correção.
