#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 256
#define ADMIN_FILE "admins.txt"

typedef struct {
    char cpf[12];
    char senha[20];
} Admin;

int verificarLogin(const char *cpf, const char *senha);
void exibirMenu();

int main() {
    char cpf[12], senha[20];

    // Solicitar login
    printf("Digite seu CPF (11 dígitos): ");
    scanf("%s", cpf);
    printf("Digite sua senha: ");
    scanf("%s", senha);

    // Verificar login
    if (verificarLogin(cpf, senha)) {
        printf("Login bem-sucedido!\n");
        exibirMenu();
    } else {
        printf("CPF ou senha incorretos!\n");
    }

    return 0;
}

// Função para verificar CPF e senha no arquivo admins.txt
int verificarLogin(const char *cpf, const char *senha) {
    FILE *file = fopen(ADMIN_FILE, "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo de administradores.\n");
        return 0;
    }

    char linha[MAX_LINE_LENGTH];
    Admin admin;

    while (fgets(linha, sizeof(linha), file)) {
        // Remover o caractere de nova linha
        linha[strcspn(linha, "\n")] = 0;

        // Separar CPF e senha com base no caracter ':'
        sscanf(linha, "%11s:%19s", admin.cpf, admin.senha);

        // Verificar se o CPF e a senha correspondem
        if (strcmp(admin.cpf, cpf) == 0 && strcmp(admin.senha, senha) == 0) {
            fclose(file);
            return 1; // Login válido
        }
    }

    fclose(file);
    return 0; // Login inválido
}

// Função para exibir o menu de opções
void exibirMenu() {
    int opcao;

    do {
        printf("\nMenu:\n");
        printf("1. Cadastro de novo investidor\n");
        printf("2. Excluir investidor\n");
        printf("3. Cadastro de criptomoeda\n");
        printf("4. Excluir criptomoeda\n");
        printf("5. Consultar saldo de um investidor\n");
        printf("6. Consultar extrato de um investidor\n");
        printf("7. Atualizar cotação de criptomoedas\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                printf("Cadastro de novo investidor (não implementado)\n");
                break;
            case 2:
                printf("Excluir investidor (não implementado)\n");
                break;
            case 3:
                printf("Cadastro de criptomoeda (não implementado)\n");
                break;
            case 4:
                printf("Excluir criptomoeda (não implementado)\n");
                break;
            case 5:
                printf("Consultar saldo de um investidor (não implementado)\n");
                break;
            case 6:
                printf("Consultar extrato de um investidor (não implementado)\n");
                break;
            case 7:
                printf("Atualizar cotação de criptomoedas (não implementado)\n");
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    } while(opcao != 0);
}
