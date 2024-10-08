#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 10
#define MAX_TRANS 100

typedef struct {
    char descricao[100];
} Transacao;

typedef struct {
    char cpf[12];
    char senha[20];
    float saldoRS;
    float bitcoin;
    float ethereum;
    float ripple;
    Transacao historico[MAX_TRANS];
    int numTransacoes;
} Usuario;

Usuario usuarios[MAX_USERS];
int numUsuarios = 0;

// Função para carregar dados dos usuários de um arquivo
void carregarDados() {
    FILE *arquivo = fopen("dados_usuarios.txt", "r");
    if (arquivo == NULL) {
        printf("Nenhum dado de usuário encontrado.\n");
        return;
    }

    numUsuarios = 0;
    while (fscanf(arquivo, "%s %s %f %f %f %f %d", 
                  usuarios[numUsuarios].cpf, 
                  usuarios[numUsuarios].senha,
                  &usuarios[numUsuarios].saldoRS,
                  &usuarios[numUsuarios].bitcoin,
                  &usuarios[numUsuarios].ethereum,
                  &usuarios[numUsuarios].ripple,
                  &usuarios[numUsuarios].numTransacoes) != EOF) {
        for (int i = 0; i < usuarios[numUsuarios].numTransacoes; i++) {
            fscanf(arquivo, " %[^\n]", usuarios[numUsuarios].historico[i].descricao);
        }
        numUsuarios++;
    }

    fclose(arquivo);
}

// Função para salvar os dados dos usuários em um arquivo
void salvarDados() {
    FILE *arquivo = fopen("dados_usuarios.txt", "w");

    for (int i = 0; i < numUsuarios; i++) {
        fprintf(arquivo, "%s %s %.2f %.8f %.8f %.8f %d\n", 
                usuarios[i].cpf, 
                usuarios[i].senha, 
                usuarios[i].saldoRS, 
                usuarios[i].bitcoin,
                usuarios[i].ethereum, 
                usuarios[i].ripple, 
                usuarios[i].numTransacoes);

        for (int j = 0; j < usuarios[i].numTransacoes; j++) {
            fprintf(arquivo, "%s\n", usuarios[i].historico[j].descricao);
        }
    }

    fclose(arquivo);
}

// Função para exibir o saldo e histórico do usuário
void exibirUsuario(Usuario *usuario) {
    printf("Saldo em Reais: R$%.2f\n", usuario->saldoRS);
    printf("Bitcoin: %.8f\n", usuario->bitcoin);
    printf("Ethereum: %.8f\n", usuario->ethereum);
    printf("Ripple: %.8f\n", usuario->ripple);

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

// Função para comprar criptomoedas
void comprarCriptomoeda(Usuario *usuario) {
    char tipo[10];
    float valor;
    if (solicitarSenha(usuario->senha)) {
        printf("Digite o tipo de criptomoeda (bitcoin, ethereum, ripple): ");
        scanf("%s", tipo);
        printf("Digite o valor a ser investido: ");
        scanf("%f", &valor);

        float taxa, quantidade;
        if (strcmp(tipo, "bitcoin") == 0) {
            taxa = 0.02;
            quantidade = valor / (1 + taxa); // valor sem a taxa
            if (usuario->saldoRS >= valor) {
                usuario->bitcoin += quantidade;
                usuario->saldoRS -= valor;
                char descricao[100];
                sprintf(descricao, "Comprado %.8f Bitcoin", quantidade);
                adicionarTransacao(usuario, descricao);
                printf("%s\n", descricao);
            } else {
                printf("Saldo insuficiente!\n");
            }
        } else if (strcmp(tipo, "ethereum") == 0) {
            taxa = 0.01;
            quantidade = valor / (1 + taxa);
            if (usuario->saldoRS >= valor) {
                usuario->ethereum += quantidade;
                usuario->saldoRS -= valor;
                char descricao[100];
                sprintf(descricao, "Comprado %.8f Ethereum", quantidade);
                adicionarTransacao(usuario, descricao);
                printf("%s\n", descricao);
            } else {
                printf("Saldo insuficiente!\n");
            }
        } else if (strcmp(tipo, "ripple") == 0) {
            taxa = 0.01;
            quantidade = valor / (1 + taxa);
            if (usuario->saldoRS >= valor) {
                usuario->ripple += quantidade;
                usuario->saldoRS -= valor;
                char descricao[100];
                sprintf(descricao, "Comprado %.8f Ripple", quantidade);
                adicionarTransacao(usuario, descricao);
                printf("%s\n", descricao);
            } else {
                printf("Saldo insuficiente!\n");
            }
        } else {
            printf("Tipo de criptomoeda inválido!\n");
        }
    } else {
        printf("Senha incorreta!\n");
    }
}

// Função para vender criptomoedas
void venderCriptomoeda(Usuario *usuario) {
    char tipo[10];
    float quantidade;
    if (solicitarSenha(usuario->senha)) {
        printf("Digite o tipo de criptomoeda (bitcoin, ethereum, ripple): ");
        scanf("%s", tipo);
        printf("Digite a quantidade a ser vendida: ");
        scanf("%f", &quantidade);

        float valor, taxa;
        if (strcmp(tipo, "bitcoin") == 0) {
            taxa = 0.03;
            valor = quantidade * (1 - taxa);
            if (usuario->bitcoin >= quantidade) {
                usuario->bitcoin -= quantidade;
                usuario->saldoRS += valor;
                char descricao[100];
                sprintf(descricao, "Vendido %.8f Bitcoin", quantidade);
                adicionarTransacao(usuario, descricao);
                printf("%s\n", descricao);
            } else {
                printf("Quantidade de Bitcoin insuficiente!\n");
            }
        } else if (strcmp(tipo, "ethereum") == 0) {
            taxa = 0.02;
            valor = quantidade * (1 - taxa);
            if (usuario->ethereum >= quantidade) {
                usuario->ethereum -= quantidade;
                usuario->saldoRS += valor;
                char descricao[100];
                sprintf(descricao, "Vendido %.8f Ethereum", quantidade);
                adicionarTransacao(usuario, descricao);
                printf("%s\n", descricao);
            } else {
                printf("Quantidade de Ethereum insuficiente!\n");
            }
        } else if (strcmp(tipo, "ripple") == 0) {
            taxa = 0.01;
            valor = quantidade * (1 - taxa);
            if (usuario->ripple >= quantidade) {
                usuario->ripple -= quantidade;
                usuario->saldoRS += valor;
                char descricao[100];
                sprintf(descricao, "Vendido %.8f Ripple", quantidade);
                adicionarTransacao(usuario, descricao);
                printf("%s\n", descricao);
            } else {
                printf("Quantidade de Ripple insuficiente!\n");
            }
        } else {
            printf("Tipo de criptomoeda inválido!\n");
        }
    } else {
        printf("Senha incorreta!\n");
    }
}

int main() {
    char cpf[12], senha[20];
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
