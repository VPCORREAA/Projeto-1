#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 100
#define MAX_TRANS 50

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

int main() {
    char cpf[12], senha[20];
    carregarDados();

    printf("Digite seu CPF: ");
    scanf("%s", cpf);
    printf("Digite sua senha: ");
    scanf("%s", senha);

    Usuario *usuario = buscarUsuario(cpf, senha);

    if (usuario != NULL) {
        printf("Login bem-sucedido!\n");
        exibirUsuario(usuario);
    } else {
        printf("CPF ou senha inválidos!\n");
    }

    salvarDados();
    return 0;
}
