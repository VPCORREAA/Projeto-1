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
    int num_transacoes;
    char historico[100][MAX_LINE_LENGTH];  // Armazenando até 100 transações
} Usuario;

typedef struct {
    char nome[20];
    double taxa;
    double saldo;
} TaxaCripto;

TaxaCripto taxas1[5];
int numUsuarios1 = 0;
int numTaxas1 = 0;
int verificarLogin(const char *cpf, const char *senha);
void exibirMenu();
void cadastrarUsuario();
void excluirUsuario();
void exibirUsuarios();
int gravarUsuarios(Usuario usuarios[], int numUsuarios);
int carregarUsuarios(Usuario usuarios[]);


// Função para carregar as taxas de criptomoedas de um arquivo
void carregarTaxas2() {
    FILE *arquivo = fopen("taxas.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao carregar taxas de criptomoedas.\n");
        return;
    }

    numTaxas1 = 0;
    while (fscanf(arquivo, "%s %lf", taxas1[numTaxas1].nome, &taxas1[numTaxas1].taxa) != EOF) {
       

        numTaxas1++;
    }

    fclose(arquivo);
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

// Função para cadastrar criptomoedas
void cadastrarCripto() {
    if (numTaxas1 >= 5) {
        printf("Limite de criptomoedas cadastradas atingido.\n");
        return;
    }

    char nome[20];
    float taxa;

    // Solicita os dados da nova criptomoeda
    printf("Digite o nome da nova Criptomoeda: ");
    scanf("%s", nome);

    printf("Digite a taxa da nova Criptomoeda (em decimal, por exemplo, 0.02 para 2%%): ");
    scanf("%f", &taxa);

    // Adiciona a nova criptomoeda na próxima posição disponível
    strcpy(taxas1[numTaxas1].nome, nome);
    taxas1[numTaxas1].taxa = taxa;
    taxas1[numTaxas1].saldo = 0.0;

    // Atualiza o contador de criptos cadastradas
    numTaxas1++;

    printf("Criptomoeda %s cadastrada com sucesso! Taxa: %.2f\n", nome, taxa);
}
// Função para excluir uma criptomoeda
void excluirCripto() {
    char nome[20];
    int encontrado = 0;

    // Solicita o nome da criptomoeda a ser excluída
    printf("Digite o nome da criptomoeda a ser excluída: ");
    scanf("%s", nome);

    // Procura a criptomoeda no array taxas1
    for (int i = 0; i < numTaxas1; i++) {
        if (strcmp(taxas1[i].nome, nome) == 0) {
            // Encontrou a criptomoeda, agora remove ela
            for (int j = i; j < numTaxas1 - 1; j++) {
                // Move as criptomoedas subsequentes para a posição anterior
                taxas1[j] = taxas1[j + 1];
            }
            numTaxas1--; // Decrementa o contador de criptomoedas
            encontrado = 1;
            printf("Criptomoeda %s excluída com sucesso!\n", nome);
            break;
        }
    }

    // Se a criptomoeda não for encontrada
    if (!encontrado) {
        printf("Criptomoeda %s não encontrada.\n", nome);
    }
}

// Função para exibir as criptomoedas cadastradas
void exibirCriptos() {
    if (numTaxas1 == 0) {
        printf("Nenhuma criptomoeda cadastrada.\n");
        return;
    }

    printf("Criptomoedas cadastradas:\n");
    for (int i = 0; i < numTaxas1; i++) {
        printf("%d. %s - Taxa: %.2f\n", i + 1, taxas1[i].nome, taxas1[i].taxa);
    }
}

// Função para salvar as criptomoedas em um arquivo txt
void salvarCriptos() {
    FILE *arquivo = fopen("taxas.txt", "w");  // Abre o arquivo para escrita
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para salvar as criptomoedas.\n");
        return;
    }

    // Grava os dados das criptomoedas no arquivo
    for (int i = 0; i < numTaxas1; i++) {
        fprintf(arquivo, "%s %.2f\n", taxas1[i].nome, taxas1[i].taxa);
    }

    fclose(arquivo);  // Fecha o arquivo
    printf("Criptomoedas salvas com sucesso no arquivo 'criptomoedas.txt'.\n");
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
        // Grava os dados do usuário, incluindo o saldo em reais e número de transações
        fprintf(file, "%s %s %.2f %d\n", usuarios[i].cpf, usuarios[i].senha,
                usuarios[i].saldo, usuarios[i].num_transacoes);

        // Grava o saldo de cada criptomoeda do usuário
        for (int j = 0; j < numTaxas1; j++) {
            fprintf(file, "%s %.8f\n", taxas1[j].nome, taxas1[j].saldo);
        }

        // Grava o histórico de transações do usuário
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
    char linha[MAX_LINE_LENGTH];

    while (fgets(linha, sizeof(linha), file)) {
        // Verificar se é a linha de cabeçalho do usuário
        if (sscanf(linha, "%11s %19s %lf %d", 
                   usuarios[numUsuarios].cpf, 
                   usuarios[numUsuarios].senha, 
                   &usuarios[numUsuarios].saldo, 
                   &usuarios[numUsuarios].num_transacoes) == 4) {
            // Lê o histórico de transações
            for (int i = 0; i < usuarios[numUsuarios].num_transacoes; i++) {
                fgets(usuarios[numUsuarios].historico[i], MAX_LINE_LENGTH, file);
                // Remover nova linha
                usuarios[numUsuarios].historico[i][strcspn(usuarios[numUsuarios].historico[i], "\n")] = 0;
            }
            numUsuarios++;
        } else {
            // Ignorar linhas não relacionadas a um usuário
            continue;
        }
    }

    fclose(file);
    return numUsuarios;
}

// Função para exibir o menu de opções
void exibirMenu() {
    int opcao;

    do {
        printf("\nMenu:\n");
        printf("1. Cadastro de novo investidor\n");
        printf("2. Excluir investidor\n");
        printf("3. Exibir lista de investidores\n");
        printf("4. Cadastrar nova criptomoeda\n");
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
            case 4:
                cadastrarCripto();
                break;
            case 5:
                excluirCripto();
            case 0:
                printf("Saindo...\n");
                salvarCriptos();
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    } while(opcao != 0);
}

int main() {
    char cpf[12], senha[20];
    carregarTaxas2();
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