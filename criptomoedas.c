#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 10
#define MAX_TRANS 100

typedef struct {
    char descricao[100];
} Transacao;

typedef struct {
    char nome[20];
    double taxa;
    double saldo;
} TaxaCripto;

typedef struct {
    char cpf[12];
    char senha[20];
    float saldoRS;
    Transacao historico[MAX_TRANS];
    int numTransacoes;
    TaxaCripto saldoCripto[5];  // Array para armazenar saldos das criptos
} Usuario;



Usuario usuarios[MAX_USERS];
TaxaCripto taxas[5];
int numUsuarios = 0;
int numTaxas = 0;

// Função para carregar dados dos usuários de um arquivo
void carregarDados() {
    FILE *arquivo = fopen("dados_usuarios.txt", "r");
    if (arquivo == NULL) {
        printf("Nenhum dado de usuário encontrado.\n");
        return;
    }

    numUsuarios = 0;
    while (fscanf(arquivo, "%s %s %f %d", 
                  usuarios[numUsuarios].cpf, 
                  usuarios[numUsuarios].senha,
                  &usuarios[numUsuarios].saldoRS,
                  &usuarios[numUsuarios].numTransacoes) != EOF) {

        // Carregar saldos de criptomoedas
        for (int i = 0; i < numTaxas; i++) {
            fscanf(arquivo, "%s %lf", taxas[i].nome, &taxas[i].saldo);
            // Associa o saldo de criptomoeda ao usuário (armazenando no array de taxas de cada usuário)
            for (int j = 0; j < numTaxas; j++) {
                if (strcmp(usuarios[numUsuarios].cpf, usuarios[numUsuarios].cpf) == 0) {
                    // Salva o saldo de cada criptomoeda
                    strcpy(usuarios[numUsuarios].saldoCripto[i].nome, taxas[i].nome);
                    usuarios[numUsuarios].saldoCripto[i].saldo = taxas[i].saldo;
                }
            }
        }

        // Agora, ler o histórico de transações do usuário
        for (int i = 0; i < usuarios[numUsuarios].numTransacoes; i++) {
            fscanf(arquivo, " %[^\n]", usuarios[numUsuarios].historico[i].descricao);
        }
        numUsuarios++;
    }

    fclose(arquivo);
}


// Função para carregar as taxas de criptomoedas de um arquivo
void carregarTaxas() {
    FILE *arquivo = fopen("taxas.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao carregar taxas de criptomoedas.\n");
        return;
    }

    numTaxas = 0;
    while (fscanf(arquivo, "%s %lf %lf", 
                  taxas[numTaxas].nome, 
                  &taxas[numTaxas].taxa, 
                  &taxas[numTaxas].saldo) != EOF) {

        // Exibe as informações carregadas
        printf("Nome cripto: %s\n", taxas[numTaxas].nome);
        printf("Taxa cripto: %lf\n", taxas[numTaxas].taxa);
        printf("Saldo cripto: %lf\n", taxas[numTaxas].saldo);

        numTaxas++;
    }

    fclose(arquivo);
}


// Função para salvar os dados dos usuários em um arquivo
void salvarDados() {
    FILE *arquivo = fopen("dados_usuarios.txt", "w");

    // Verifica se o arquivo foi aberto corretamente
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para salvar os dados!\n");
        return;
    }

    // Para cada usuário, vamos gravar seus dados no arquivo
    for (int i = 0; i < numUsuarios; i++) {
        // Primeiro, salva as informações básicas do usuário
        fprintf(arquivo, "%s %s %.2f %d\n", 
                usuarios[i].cpf, 
                usuarios[i].senha, 
                usuarios[i].saldoRS, 
                usuarios[i].numTransacoes);

        // Agora, para cada criptomoeda registrada, salva o saldo correspondente
        for (int j = 0; j < numTaxas; j++) {
            // Salva o saldo de cada criptomoeda diretamente do array `taxas`
            fprintf(arquivo, "%s %.8f\n", taxas[j].nome, taxas[j].saldo);
            printf("%s %.8f\n", taxas[j].nome, taxas[j].saldo);
        }

        // Salva o histórico de transações
        for (int j = 0; j < usuarios[i].numTransacoes; j++) {
            fprintf(arquivo, "%s\n", usuarios[i].historico[j].descricao);
        }
    }
    printf("AAAA");
    // Fecha o arquivo após salvar
    fclose(arquivo);
}


// Função para exibir o saldo e histórico do usuário
void exibirUsuario(Usuario *usuario) {
    printf("Saldo em Reais: R$%.2f\n", usuario->saldoRS);
    for(int i = 0; i < numTaxas; i++){
        printf("Saldo em %s: %lf\n", taxas[i].nome, taxas[i].saldo);
    }

    printf("\nHistórico de transações:\n");
    for (int i = 0; i < usuario->numTransacoes; i++) {
        printf("%d. %s\n", i + 1, usuario->historico[i].descricao);
    }
}

// Função para procurar usuário por CPF e senha
Usuario* buscarUsuario(char *cpf, char *senha) {
    for (int i = 0; i < numUsuarios; i++) {
        if (strcmp(usuarios[i].cpf, cpf) == 0 && strcmp(usuarios[i].senha, senha) == 0) {
            return &usuarios[i];
        }
    }
    return NULL;
}

// Função para adicionar transação ao histórico
void adicionarTransacao(Usuario *usuario, char *descricao) {
    if (usuario->numTransacoes < MAX_TRANS) {
        strcpy(usuario->historico[usuario->numTransacoes].descricao, descricao);
        usuario->numTransacoes++;
    }
}

// Função para adicionar fundos
void adicionarFundos(Usuario *usuario, float valor) {
    usuario->saldoRS += valor;
    char descricao[100];
    sprintf(descricao, "Adicionado R$%.2f ao saldo", valor);
    adicionarTransacao(usuario, descricao);
    printf("%s\n", descricao);
}

// Função para solicitar senha
int solicitarSenha(char *senhaCorreta) {
    char senha[20];
    printf("Digite sua senha novamente: ");
    scanf("%s", senha);
    return strcmp(senha, senhaCorreta) == 0;
}

// Função para sacar fundos
void sacarFundos(Usuario *usuario) {
    float valor;
    if (solicitarSenha(usuario->senha)) {
        printf("Digite o valor para sacar: ");
        scanf("%f", &valor);
        if (usuario->saldoRS >= valor) {
            usuario->saldoRS -= valor;
            char descricao[100];
            sprintf(descricao, "Sacado R$%.2f do saldo", valor);
            adicionarTransacao(usuario, descricao);
            printf("%s\n", descricao);
        } else {
            printf("Saldo insuficiente!\n");
        }
    } else {
        printf("Senha incorreta!\n");
    }
}

// Função para comprar criptomoeda
void comprarCriptomoeda(Usuario *usuario) {
    char tipo[20];
    float valor;

    if (solicitarSenha(usuario->senha)) {
        for(int i=0; i<numTaxas; i++){
            printf("Nome cripto: %s\n", taxas[i].nome);
            printf("Taxa cripto: %lf\n", taxas[i].taxa);
        }
        printf("Digite o tipo de criptomoeda: ");
        scanf("%s", tipo);
        printf("Digite o valor a ser investido: ");
        scanf("%f", &valor);

        float taxa = 0;
        float quantidade = 0;
        int criptomoedaEncontrada = 0;

        // Buscar a taxa e nome da criptomoeda
        for (int i = 0; i < numTaxas; i++) {
            if (strcmp(taxas[i].nome, tipo) == 0) {
                taxa = taxas[i].taxa;  // Obtém a taxa da criptomoeda cadastrada
                criptomoedaEncontrada = 1;
                quantidade = valor / (1 + taxa); // valor sem a taxa
                break;
            }
        }

        // Se a criptomoeda não foi encontrada, retorna erro
        if (!criptomoedaEncontrada) {
            printf("Tipo de criptomoeda inválido!\n");
            return;
        }

        // Verifica se o saldo é suficiente para comprar a criptomoeda
        if (usuario->saldoRS >= valor) {
            // Adiciona a quantidade comprada ao saldo da criptomoeda
            for (int i = 0; i < numTaxas; i++) {
                if (strcmp(taxas[i].nome, tipo) == 0) {
                    taxas[i].saldo += quantidade; // Atualiza o saldo da criptomoeda
                    break;
                }
            }

            // Subtrai o valor gasto do saldo do usuário
            usuario->saldoRS -= valor;

            // Registra a transação
            char descricao[100];
            sprintf(descricao, "Comprado %.8f %s", quantidade, tipo);
            adicionarTransacao(usuario, descricao);

            printf("%s\n", descricao);
        } else {
            printf("Saldo insuficiente!\n");
        }
    } else {
        printf("Senha incorreta!\n");
    }
}


// Função para vender criptomoedas
void venderCriptomoeda(Usuario *usuario) {
    char tipo[20];
    float valor;

    if (solicitarSenha(usuario->senha)) {
        for(int i=0; i<numTaxas; i++){
            printf("Nome cripto: %s\n", taxas[i].nome);
            printf("Taxa cripto: %lf\n", taxas[i].taxa);
        }
        printf("Digite o tipo de criptomoeda: ");
        scanf("%s", tipo);
        printf("Digite o valor a ser investido: ");
        scanf("%f", &valor);

        float taxa = 0;
        float quantidade = 0;
        int criptomoedaEncontrada = 0, nrcripto = 100;

        // Buscar a taxa e nome da criptomoeda
        for (int i = 0; i < numTaxas; i++) {
            if (strcmp(taxas[i].nome, tipo) == 0) {
                taxa = taxas[i].taxa;  // Obtém a taxa da criptomoeda cadastrada
                criptomoedaEncontrada = 1;
                nrcripto = i;
                quantidade = valor / (1 - taxa); // valor sem a taxa
                break;
            }
        }

        // Se a criptomoeda não foi encontrada, retorna erro
        if (!criptomoedaEncontrada) {
            printf("Tipo de criptomoeda inválido!\n");
            return;
        }

        // Verifica se o saldo é suficiente para comprar a criptomoeda
        if (taxas[nrcripto].saldo <= valor) {
            // Adiciona a quantidade comprada ao saldo da criptomoeda
            for (int i = 0; i < numTaxas; i++) {
                if (strcmp(taxas[i].nome, tipo) == 0) {
                    taxas[i].saldo -= quantidade; // Atualiza o saldo da criptomoeda
                    break;
                }
            }

            // Subtrai o valor gasto do saldo do usuário
            usuario->saldoRS += valor;

            // Registra a transação
            char descricao[100];
            sprintf(descricao, "Comprado %.8f %s", quantidade, tipo);
            adicionarTransacao(usuario, descricao);

            printf("%s\n", descricao);
        } else {
            printf("Saldo insuficiente!\n");
        }
    } else {
        printf("Senha incorreta!\n");
    }
}


int aa() {
    char cpf[12], senha[20];
    carregarTaxas();  // Carregar taxas de criptomoedas

    carregarDados();

    printf("Digite seu CPF: ");
    scanf("%s", cpf);
    printf("Digite sua senha: ");
    scanf("%s", senha);

    Usuario *usuario = buscarUsuario(cpf, senha);
    if (usuario == NULL) {
        printf("CPF ou senha inválidos!\n");
        return 1;
    }

    int opcao;
    do {
        printf("\nEscolha uma opção:\n");
        printf("1. Exibir saldo e histórico\n");
        printf("2. Adicionar fundos\n");
        printf("3. Sacar fundos\n");
        printf("4. Comprar criptomoeda\n");
        printf("5. Vender criptomoeda\n");
        printf("6. Sair\n");
        printf("Opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                exibirUsuario(usuario);
                break;
            case 2: {
                float valor;
                printf("Digite o valor a ser adicionado: ");
                scanf("%f", &valor);
                adicionarFundos(usuario, valor);
                break;
            }
            case 3:
                sacarFundos(usuario);
                break;
            case 4:
                comprarCriptomoeda(usuario);
                break;
            case 5:
                venderCriptomoeda(usuario);
                break;
            case 6:
                printf("Saindo...\n");
                salvarDados();
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    } while (opcao != 6);

    return 0;
}

