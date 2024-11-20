---

## 📋 **Projeto 3: CRIPTO.PT2**

O projeto **`ADM.C`** é um sistema básico de gerenciamento de investidores e criptomoedas desenvolvido em **C**. Ele permite o cadastro e controle de investidores, gerenciamento de criptomoedas, exclusão de registros, e persistência de dados em arquivos. O sistema inclui funcionalidades de login para administradores e um menu interativo para realizar as operações.

---

## ⚙️ **Funcionalidades**

1. **Gestão de Investidores**:
   - Cadastro de novos investidores (CPF, senha e saldo inicial).
   - Exclusão de investidores existentes.
   - Listagem de todos os investidores, incluindo histórico de transações.

2. **Gestão de Criptomoedas**:
   - Cadastro de novas criptomoedas com taxas associadas.
   - Exclusão de criptomoedas existentes.
   - Listagem de criptomoedas cadastradas.

3. **Persistência de Dados**:
   - Dados de investidores armazenados em `dados_usuarios.txt`.
   - Dados de criptomoedas armazenados em `taxas.txt`.

4. **Autenticação**:
   - Login de administradores via `admins.txt`.

---

## 🗂️ **Arquivos do Projeto**

- **`ADM.C`**: Código-fonte principal do sistema.
- **`dados_usuarios.txt`**: Armazena os dados dos investidores cadastrados.
- **`taxas.txt`**: Armazena as taxas e nomes das criptomoedas cadastradas.
- **`admins.txt`**: Contém os logins e senhas dos administradores.

---

## 🛠️ **Como Executar**

1. **Pré-requisitos**:
   - Compilador GCC ou compatível.
   - Sistema operacional compatível com o padrão POSIX ou Windows.

2. **Compilação**:
   Use o comando abaixo para compilar o programa:
   ```bash
   gcc ADM.C -o adm
   ```

3. **Execução**:
   Após compilar, execute o programa com:
   ```bash
   ./adm
   ```

4. **Arquivos Necessários**:
   Certifique-se de que os arquivos `dados_usuarios.txt`, `taxas.txt`, e `admins.txt` estejam no mesmo diretório que o executável.

---

## 📑 **Estrutura dos Arquivos de Dados**

1. **`dados_usuarios.txt`**:
   - Formato:
     ```
     CPF SENHA SALDO NUMERO_DE_TRANSACOES
     NOME_CRIPTO SALDO_CRIPTO
     ...
     HISTORICO_DE_TRANSACOES
     ```
   - Exemplo:
     ```
     12345678900 12345 5000.00 2
     Bitcoin 0.00500000
     Ethereum 1.00000000
     Adicionado R$100.00 ao saldo
     Comprado 0.00500000 Bitcoin
     ```

2. **`taxas.txt`**:
   - Formato:
     ```
     NOME_CRIPTO TAXA
     ```
   - Exemplo:
     ```
     Bitcoin 0.02
     Ethereum 0.01
     ```

3. **`admins.txt`**:
   - Formato:
     ```
     CPF:SENHA
     ```
   - Exemplo:
     ```
     12345678900:admin123
     ```

---

## 🚀 **Funcionalidades do Menu**

- **Opções disponíveis**:
  ```
  Menu:
  1. Cadastro de novo investidor
  2. Excluir investidor
  3. Exibir lista de investidores
  4. Cadastrar nova criptomoeda
  5. Excluir criptomoeda
  0. Sair
  ```

- **Navegação**:
   - Digite o número correspondente à opção desejada.
   - Informe os dados solicitados durante as operações.

---

## 💾 **Detalhes Técnicos**

- **Persistência de Dados**:
  - Dados são salvos em arquivos de texto (`txt`) para fácil leitura e manutenção.
  - As alterações feitas no programa, como cadastro ou exclusão, são imediatamente refletidas nos arquivos correspondentes.

- **Limitações**:
  - Número máximo de investidores: 100.
  - Número máximo de criptomoedas: 5.
  - Número máximo de transações por investidor: 100.

---

