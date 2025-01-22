#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char nome[50];
    float valor;
} Registro;

void adicionar_registro() {
    FILE *arquivo = fopen("registros.txt", "a");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    Registro registro;
    printf("Digite o ID: ");
    scanf("%d", &registro.id);
    printf("Digite o nome: ");
    scanf(" %[^\n]", registro.nome);
    printf("Digite o valor: ");
    scanf("%f", &registro.valor);

    fprintf(arquivo, "%d,%s,%.2f\n", registro.id, registro.nome, registro.valor);
    fclose(arquivo);
    printf("Registro adicionado com sucesso!\n");
}

void listar_registros() {
    FILE *arquivo = fopen("registros.txt", "r");
    if (arquivo == NULL) {
        printf("Nenhum registro encontrado.\n");
        return;
    }

    Registro registro;
    printf("\nRegistros:\n");
    printf("ID\tNome\t\tValor\n");
    printf("----------------------------\n");

    while (fscanf(arquivo, "%d,%49[^,],%f\n", &registro.id, registro.nome, &registro.valor) != EOF) {
        printf("%d\t%-15s\t%.2f\n", registro.id, registro.nome, registro.valor);
    }

    fclose(arquivo);
}

void buscar_registro() {
    FILE *arquivo = fopen("registros.txt", "r");
    if (arquivo == NULL) {
        printf("Nenhum registro encontrado.\n");
        return;
    }

    int id_procurado;
    printf("Digite o ID a buscar: ");
    scanf("%d", &id_procurado);

    Registro registro;
    int encontrado = 0;

    while (fscanf(arquivo, "%d,%49[^,],%f\n", &registro.id, registro.nome, &registro.valor) != EOF) {
        if (registro.id == id_procurado) {
            printf("\nRegistro encontrado:\n");
            printf("ID: %d\nNome: %s\nValor: %.2f\n", registro.id, registro.nome, registro.valor);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("Registro com ID %d nao encontrado.\n", id_procurado);
    }

    fclose(arquivo);
}

void excluir_registro() {
    FILE *arquivo = fopen("registros.txt", "r");
    if (arquivo == NULL) {
        printf("Nenhum registro encontrado.\n");
        return;
    }

    FILE *temp = fopen("temp.txt", "w");
    if (temp == NULL) {
        printf("Erro ao criar arquivo temporario.\n");
        fclose(arquivo);
        return;
    }

    int id_procurado;
    printf("Digite o ID a excluir: ");
    scanf("%d", &id_procurado);

    Registro registro;
    int encontrado = 0;

    while (fscanf(arquivo, "%d,%49[^,],%f\n", &registro.id, registro.nome, &registro.valor) != EOF) {
        if (registro.id == id_procurado) {
            encontrado = 1;
        } else {
            fprintf(temp, "%d,%s,%.2f\n", registro.id, registro.nome, registro.valor);
        }
    }

    fclose(arquivo);
    fclose(temp);

    remove("registros.txt");
    rename("temp.txt", "registros.txt");

    if (encontrado) {
        printf("Registro com ID %d excluido com sucesso!\n", id_procurado);
    } else {
        printf("Registro com ID %d nao encontrado.\n", id_procurado);
    }
}

int main() {
    int opcao;

    do {
        printf("\nMenu de Gerenciamento de Registros\n");
        printf("1. Adicionar Registro\n");
        printf("2. Listar Registros\n");
        printf("3. Buscar Registro\n");
        printf("4. Excluir Registro\n");
        printf("5. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                adicionar_registro();
                break;
            case 2:
                listar_registros();
                break;
            case 3:
                buscar_registro();
                break;
            case 4:
                excluir_registro();
                break;
            case 5:
                printf("Encerrando o programa...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 5);

    return 0;
}
