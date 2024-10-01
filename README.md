# Simulação de Venda de Criptomoedas

Este projeto em C simula um sistema básico de gerenciamento de vendas e compras de criptomoedas, além de permitir operações de adicionar e sacar fundos. O sistema realiza as seguintes operações:

## Funcionalidades Implementadas:
- **Cadastro e Autenticação**: O usuário se autentica por meio de CPF e senha.
- **Saldo e Histórico**: O saldo em reais e em criptomoedas é exibido, assim como o histórico de transações.
- **Transações**:
  - **Adicionar fundos**: Adiciona valor ao saldo do usuário.
  - **Sacar fundos**: Permite sacar um valor do saldo do usuário, se houver saldo suficiente.
  - **Comprar criptomoedas**: Permite comprar Bitcoin, Ethereum ou Ripple, descontando uma taxa específica:
    - Bitcoin: 2% de taxa sobre o valor investido.
    - Ethereum: 1% de taxa sobre o valor investido.
    - Ripple: 1% de taxa sobre o valor investido.
  - **Vender criptomoedas**: Permite vender Bitcoin, Ethereum ou Ripple, descontando uma taxa específica:
    - Bitcoin: 3% de taxa sobre o valor vendido.
    - Ethereum: 2% de taxa sobre o valor vendido.
    - Ripple: 1% de taxa sobre o valor vendido.
- **Histórico de Transações**: Cada operação realizada é registrada no histórico do usuário, permitindo rastrear todas as movimentações.

## Dependências
Nenhuma dependência externa. O código foi implementado em C puro.

## Estrutura do Arquivo `dados_usuarios.txt`:
O arquivo `dados_usuarios.txt` armazena as informações dos usuários, incluindo:
- CPF e senha.
- Saldo em reais (R$).
- Quantidade de Bitcoin, Ethereum e Ripple.
- Histórico de transações.

Cada linha representa um usuário, seguido por suas transações.

### Exemplo de estrutura:
```
12345678901 senha123 5000.00 0.00050000 0.01000000 0.20000000 2
Compra de 0.0001 Bitcoin
Venda de 0.001 Ethereum
```


## Como Usar:
*******######MUDAR####*************
   ```
3. O programa solicitará o CPF e senha. Se o login for bem-sucedido, será exibido o saldo e o histórico de transações. A seguir, o usuário poderá realizar operações de adicionar, sacar, comprar e vender criptomoedas.
