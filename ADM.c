#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 512
#define ADMIN_FILE "admins.txt"
#define DADOS_USUARIOS_FILE "dados_usuarios.txt"

typedef struct {
    char cpf[12];
    char senha[20];
    double saldo;
    double bitcoin;
    double ethereum;
    double outra_criptomoeda;
    int num_transacoes;
    char historico[100][MAX_LINE_LENGTH];  // Armazenando até 100 transações
} Usuario;

int verificarLogin(const char *cpf, const char *senha);
void exibirMenu();
void cadastrarUsuario();
void excluirUsuario();
void exibirUsuarios();
int gravarUsuarios(Usuario usuarios[], int numUsuarios);
int carregarUsuarios(Usuario usuarios[]);

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
    char cpfArquivo[12], senhaArquivo[20];

    while (fgets(linha, sizeof(linha), file)) {
        // Remover o caractere de nova linha
        linha[strcspn(linha, "\n")] = 0;

        // Separar CPF e senha com base no caractere ':'
        sscanf(linha, "%11s:%19s", cpfArquivo, senhaArquivo);

        // Verificar se o CPF e a senha correspondem
        if (strcmp(cpfArquivo, cpf) == 0 && strcmp(senhaArquivo, senha) == 0) {
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
        printf("3. Exibir lista de investidores\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                cadastrarUsuario();
                break;
            case 2:
                excluirUsuario();
                break;
            case 3:
                exibirUsuarios();
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    } while(opcao != 0);
}

// Função para cadastrar um novo usuário
void cadastrarUsuario() {
    Usuario novoUsuario;

    // Solicitar os dados do usuário
    printf("Digite o CPF do novo investidor (11 dígitos): ");
    scanf("%s", novoUsuario.cpf);
    printf("Digite a senha: ");
    scanf("%s", novoUsuario.senha);
    printf("Digite o saldo inicial: ");
    scanf("%lf", &novoUsuario.saldo);
    printf("Digite o saldo de Bitcoin: ");
    scanf("%lf", &novoUsuario.bitcoin);
    printf("Digite o saldo de Ethereum: ");
    scanf("%lf", &novoUsuario.ethereum);
    printf("Digite o saldo de outra criptomoeda: ");
    scanf("%lf", &novoUsuario.outra_criptomoeda);
    novoUsuario.num_transacoes = 0;

    // Carregar os usuários existentes e adicionar o novo
    Usuario usuarios[100];
    int numUsuarios = carregarUsuarios(usuarios);
    usuarios[numUsuarios] = novoUsuario;
    numUsuarios++;

    // Gravar de volta no arquivo
    if (gravarUsuarios(usuarios, numUsuarios)) {
        printf("Investidor cadastrado com sucesso!\n");
    } else {
        printf("Erro ao cadastrar investidor.\n");
    }
}

// Função para excluir um usuário
void excluirUsuario() {
    char cpf[12];
    printf("Digite o CPF do investidor a ser excluído: ");
    scanf("%s", cpf);

    Usuario usuarios[100];
    int numUsuarios = carregarUsuarios(usuarios);
    int i, j;
    int excluido = 0;

    // Buscar o usuário e removê-lo
    for (i = 0; i < numUsuarios; i++) {
        if (strcmp(usuarios[i].cpf, cpf) == 0) {
            // Excluir o usuário
            for (j = i; j < numUsuarios - 1; j++) {
                usuarios[j] = usuarios[j + 1];
            }
            numUsuarios--;
            excluido = 1;
            break;
        }
    }

    if (excluido) {
        if (gravarUsuarios(usuarios, numUsuarios)) {
            printf("Investidor excluído com sucesso!\n");
        } else {
            printf("Erro ao excluir investidor.\n");
        }
    } else {
        printf("Usuário não encontrado.\n");
    }
}

// Função para exibir todos os usuários
void exibirUsuarios() {
    Usuario usuarios[100];
    int numUsuarios = carregarUsuarios(usuarios);

    for (int i = 0; i < numUsuarios; i++) {
        printf("\nCPF: %s\n", usuarios[i].cpf);
        printf("Saldo: R$%.2f\n", usuarios[i].saldo);
        printf("Bitcoin: %.8f\n", usuarios[i].bitcoin);
        printf("Ethereum: %.8f\n", usuarios[i].ethereum);
        printf("Outra criptomoeda: %.8f\n", usuarios[i].outra_criptomoeda);
        printf("Número de transações: %d\n", usuarios[i].num_transacoes);
        printf("Histórico de transações:\n");
        for (int j = 0; j < usuarios[i].num_transacoes; j++) {
            printf("  %s\n", usuarios[i].historico[j]);
        }
    }
}

// Função para gravar os dados dos usuários no arquivo
int gravarUsuarios(Usuario usuarios[], int numUsuarios) {
    FILE *file = fopen(DADOS_USUARIOS_FILE, "w");
    if (file == NULL) {
        return 0;
    }

    for (int i = 0; i < numUsuarios; i++) {
        fprintf(file, "%s %s %.2f %.8f %.8f %.8f %d\n", usuarios[i].cpf, usuarios[i].senha,
                usuarios[i].saldo, usuarios[i].bitcoin, usuarios[i].ethereum, usuarios[i].outra_criptomoeda, usuarios[i].num_transacoes);
        for (int j = 0; j < usuarios[i].num_transacoes; j++) {
            fprintf(file, "%s\n", usuarios[i].historico[j]);
        }
    }

    fclose(file);
    return 1;
}

// Função para carregar os dados dos usuários do arquivo
int carregarUsuarios(Usuario usuarios[]) {
    FILE *file = fopen(DADOS_USUARIOS_FILE, "r");
    if (file == NULL) {
        return 0;
    }

    int numUsuarios = 0;
    while (fscanf(file, "%11s %19s %lf %lf %lf %lf %d\n", usuarios[numUsuarios].cpf, usuarios[numUsuarios].senha,
                  &usuarios[numUsuarios].saldo, &usuarios[numUsuarios].bitcoin, &usuarios[numUsuarios].ethereum,
                  &usuarios[numUsuarios].outra_criptomoeda, &usuarios[numUsuarios].num_transacoes) != EOF) {
        for (int i = 0; i < usuarios[numUsuarios].num_transacoes; i++) {
            fgets(usuarios[numUsuarios].historico[i], MAX_LINE_LENGTH, file);
            usuarios[numUsuarios].historico[i][strcspn(usuarios[numUsuarios].historico[i], "\n")] = 0;
        }
        numUsuarios++;
    }

    fclose(file);
    return numUsuarios;
}
