#include <stdio.h>
#include <string.h>
#include <windows.h>    // Configurar console para UTF-8 no Windows

// Constante que define o tamanho máximo do acervo
#define TAMANHO_ACERVO 20

// Estrutura que representa um livro
typedef struct {
    int codigo;          // Código único do livro (identificador)
    char titulo[50];     // Título do livro
    char autor[30];      // Nome do autor
    char area[30];       // Área de conhecimento (ex: Literatura, Matemática)
    int ano;             // Ano de publicação
    char editora[30];    // Nome da editora
} Livro;

// Assinaturas das funções (declaração antecipada)
void carregarAcervo(Livro acervo[], int tamanho);                 // Lê os dados do arquivo TXT
void salvarAcervo(Livro acervo[], int tamanho);                   // Salva os dados no arquivo TXT
void cadastrarLivro(Livro acervo[], int tamanho);                 // Cadastra um novo livro
void imprimirLivros(Livro acervo[], int tamanho);                 // Imprime todos os livros cadastrados
void pesquisarLivro(Livro acervo[], int tamanho, int codigoBusca);// Pesquisa livro por código
void ordenarPorAno(Livro acervo[], int tamanho);                  // Ordena livros por ano (BubbleSort robusto)
void ordenarPorCodigo(Livro acervo[], int tamanho);               // Ordena livros por código (BubbleSort robusto)

int main() {
    // Configura o console para UTF-82
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    // Declara o vetor de structs que guarda os livros
    Livro acervo[TAMANHO_ACERVO];
    int opcao, codigoBusca;

    // Inicializa o acervo vazio (código = 0 significa posição livre)
    for (int i = 0; i < TAMANHO_ACERVO; i++) {
        acervo[i].codigo = 0;
    }

    // Carrega dados do arquivo TXT (se existir)
    carregarAcervo(acervo, TAMANHO_ACERVO);

    // Loop principal do menu
    do {
        // Exibe o menu de opções
        printf("\n=== MENU BIBLIOTECA ===\n");
        printf("1 - Cadastrar livro\n");
        printf("2 - Imprimir todos os livros\n");
        printf("3 - Pesquisar livro por código\n");
        printf("4 - Ordenar livros por ano\n");
        printf("5 - Ordenar livros por código\n");
        printf("6 - Sair\n");
        printf("Escolha: ");
        if (scanf("%d", &opcao) != 1) { // Valida entrada numérica
            printf("⚠️ Entrada inválida. Tente novamente.\n");
            // Limpa qualquer lixo no buffer
            int c; while ((c = getchar()) != '\n' && c != EOF) {}
            continue;
        }
        getchar(); // limpa o '\n' após o número

        // Estrutura condicional para escolher a opção
        switch (opcao) {
            case 1:
                cadastrarLivro(acervo, TAMANHO_ACERVO);   // Cadastra novo livro
                salvarAcervo(acervo, TAMANHO_ACERVO);     // Salva no arquivo
                break;
            case 2:
                imprimirLivros(acervo, TAMANHO_ACERVO);   // Imprime todos os livros
                break;
            case 3:
                printf("Digite o código: ");
                if (scanf("%d", &codigoBusca) != 1) {
                    printf("⚠️ Código inválido.\n");
                    int c; while ((c = getchar()) != '\n' && c != EOF) {}
                    break;
                }
                getchar(); // limpa buffer
                pesquisarLivro(acervo, TAMANHO_ACERVO, codigoBusca); // Pesquisa livro
                break;
            case 4:
                ordenarPorAno(acervo, TAMANHO_ACERVO);    // Ordena por ano
                salvarAcervo(acervo, TAMANHO_ACERVO);     // Atualiza arquivo
                printf("📖 Livros ordenados por ano!\n");
                break;
            case 5:
                ordenarPorCodigo(acervo, TAMANHO_ACERVO); // Ordena por código
                salvarAcervo(acervo, TAMANHO_ACERVO);     // Atualiza arquivo
                printf("📖 Livros ordenados por código!\n");
                break;
            case 6:
                salvarAcervo(acervo, TAMANHO_ACERVO);     // Salva antes de sair
                printf("Encerrando... Dados salvos em acervo.txt!\n");
                break;
            default:
                printf("⚠️ Opção inválida!\n");
        }
    } while (opcao != 6); // Repete até escolher sair

    return 0;
}

// Função que carrega o acervo de um arquivo TXT.
// Formato esperado por linha: codigo;titulo;autor;area;ano;editora
void carregarAcervo(Livro acervo[], int tamanho) {
    FILE *f = fopen("acervo.txt", "r"); // Abre arquivo para leitura
    if (f == NULL) return; // Se não existir, apenas retorna

    int i = 0;
    // Lê cada linha do arquivo no formato separado por ";"
    while (i < tamanho && fscanf(
                 f,
                 "%d;%49[^;];%29[^;];%29[^;];%d;%29[^\n]\n",
                 &acervo[i].codigo,
                 acervo[i].titulo,
                 acervo[i].autor,
                 acervo[i].area,
                 &acervo[i].ano,
                 acervo[i].editora
             ) == 6) {
        // Remove eventuais espaços extras nas extremidades
        i++;
    }
    fclose(f); // Fecha arquivo
}

// Função que salva o acervo em arquivo TXT.

void salvarAcervo(Livro acervo[], int tamanho) {
    FILE *f = fopen("acervo.txt", "w"); // Abre arquivo para escrita (sobrescreve)
    if (f == NULL) {
        printf("Erro ao salvar arquivo!\n");
        return;
    }
    // Percorre o vetor e grava cada livro em uma linha
    for (int i = 0; i < tamanho; i++) {
        if (acervo[i].codigo != 0) { // Só grava se posição estiver ocupada
            fprintf(
                f,
                "%d;%s;%s;%s;%d;%s\n",
                acervo[i].codigo,
                acervo[i].titulo,
                acervo[i].autor,
                acervo[i].area,
                acervo[i].ano,
                acervo[i].editora
            );
        }
    }
    fclose(f); // Fecha arquivo
}

// Função que cadastra um novo livro
// valida duplicidade de código e lê todos os campos com segurança.
void cadastrarLivro(Livro acervo[], int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        if (acervo[i].codigo == 0) { // posição livre encontrada
            int codigoTemp;
            printf("\nDigite o código do livro: ");
            if (scanf("%d", &codigoTemp) != 1) {
                printf("⚠️ Código inválido.\n");
                int c; while ((c = getchar()) != '\n' && c != EOF) {}
                return;
            }
            getchar(); // limpa '\n'

            // Verifica se já existe livro com esse código (evita duplicidade)
            for (int j = 0; j < tamanho; j++) {
                if (acervo[j].codigo == codigoTemp) {
                    printf("⚠️ Código já cadastrado!\n");
                    return;
                }
            }

            // Preenche os dados do livro
            acervo[i].codigo = codigoTemp;

            printf("Título: ");
            fgets(acervo[i].titulo, sizeof(acervo[i].titulo), stdin);
            acervo[i].titulo[strcspn(acervo[i].titulo, "\n")] = '\0'; // Remove '\n' final

            printf("Autor: ");
            fgets(acervo[i].autor, sizeof(acervo[i].autor), stdin);
            acervo[i].autor[strcspn(acervo[i].autor, "\n")] = '\0';

            printf("Área: ");
            fgets(acervo[i].area, sizeof(acervo[i].area), stdin);
            acervo[i].area[strcspn(acervo[i].area, "\n")] = '\0';

            printf("Ano: ");
            if (scanf("%d", &acervo[i].ano) != 1) {
                printf("⚠️ Ano inválido.\n");
                int c; while ((c = getchar()) != '\n' && c != EOF) {}
                // "Desfaz" cadastro da posição para evitar registro quebrado
                acervo[i].codigo = 0;
                return;
            }
            getchar(); // limpa '\n'

            printf("Editora: ");
            fgets(acervo[i].editora, sizeof(acervo[i].editora), stdin);
            acervo[i].editora[strcspn(acervo[i].editora, "\n")] = '\0';

            printf("✅ Livro cadastrado com sucesso!\n");
            return; // cadastrado, encerra a função
        }
    }
    printf("⚠️ Acervo cheio!\n");
}

// Função que imprime todos os livros cadastrados.
// Conta quantos impressos e avisa se nenhum foi encontrado.
void imprimirLivros(Livro acervo[], int tamanho) {
    printf("\n=== LISTA DE LIVROS ===\n");
    int encontrados = 0;
    for (int i = 0; i < tamanho; i++) {
        if (acervo[i].codigo != 0) {
            encontrados++;
            printf("Código: %d | Título: %s | Autor: %s | Área: %s | Ano: %d | Editora: %s\n",
                   acervo[i].codigo, acervo[i].titulo, acervo[i].autor,
                   acervo[i].area, acervo[i].ano, acervo[i].editora);
        }
    }
    if (!encontrados) printf("Nenhum livro cadastrado.\n");
}

// Função que pesquisa um livro pelo código.
// Percorre o vetor e mostra os dados se encontrar; caso contrário, informa ausência.
void pesquisarLivro(Livro acervo[], int tamanho, int codigoBusca) {
    for (int i = 0; i < tamanho; i++) {
        if (acervo[i].codigo == codigoBusca) {
            printf("\n📖 Livro encontrado:\n");
            printf("Título: %s\nAutor: %s\nÁrea: %s\nAno: %d\nEditora: %s\n",
                   acervo[i].titulo, acervo[i].autor, acervo[i].area,
                   acervo[i].ano, acervo[i].editora);
            return;
        }
    }
    printf("⚠️ Livro não encontrado.\n");
}

// Função que ordena os livros por ano de publicação (BubbleSort robusto).
// Usa 'do-while' com flag 'trocou' para garantir múltiplas passagens até ordenar.

void ordenarPorAno(Livro acervo[], int tamanho) {
    Livro temp;
    int trocou;
    if (tamanho <= 1) return; // Caso trivial

    do {
        trocou = 0;
        for (int j = 0; j < tamanho - 1; j++) {
            // Compara apenas elementos válidos
            if (acervo[j].codigo != 0 && acervo[j + 1].codigo != 0 &&
                acervo[j].ano > acervo[j + 1].ano) {
                // Troca os elementos
                temp = acervo[j];
                acervo[j] = acervo[j + 1];
                acervo[j + 1] = temp;
                trocou = 1;
            }
        }
    } while (trocou);
}

// Função que ordena os livros por código (BubbleSort robusto).
// Mesma lógica da ordenação por ano, comparando 'codigo'.
void ordenarPorCodigo(Livro acervo[], int tamanho) {
    Livro temp;
    int trocou;
    if (tamanho <= 1) return; // Caso trivial

    do {
        trocou = 0;
        for (int j = 0; j < tamanho - 1; j++) {
            // Compara apenas elementos válidos
            if (acervo[j].codigo != 0 && acervo[j + 1].codigo != 0 &&
                acervo[j].codigo > acervo[j + 1].codigo) {
                // Troca os elementos
                temp = acervo[j];
                acervo[j] = acervo[j + 1];
                acervo[j + 1] = temp;
                trocou = 1;
            }
        }
    } while (trocou);
}
