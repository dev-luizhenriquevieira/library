# 📚 Sistema de Gerenciamento de Biblioteca (library)

Este é um sistema de linha de comando simples e eficiente para gerenciamento de acervo de livros, desenvolvido inteiramente em **Linguagem C**. O projeto foi estruturado de forma modular para exercitar boas práticas de programação e manipulação de arquivos em disco.

## 🛠️ Tecnologias Utilizadas

*   **Linguagem C** (98%)
*   **CMake** (Para automação da compilação)

## 📁 Estrutura do Projeto

O código foi dividido seguindo o princípio da modularização:
*   `main.c`: Ponto de entrada do programa e controle do menu principal.
*   `library.c`: Implementação de toda a lógica de negócios (cadastro, listagem, etc.).
*   `library.h`: Arquivo de cabeçalho contendo as estruturas de dados e protótipos de funções.
*   `acervo.txt`: Banco de dados em texto puro onde as informações dos livros ficam salvas permanentemente.

## 🚀 Como Executar o Projeto

Certifique-se de ter um compilador C (como o GCC) instalado em sua máquina.

### Passo 1: Clonar o repositório
```bash
git clone https://github.com
cd library
```

### Passo 2: Compilar o código
Você pode compilar direto usando o GCC no terminal:
```bash
gcc main.c library.c -o library
```

### Passo 3: Rodar o programa
*   **No Windows:**
    ```bash
    library.exe
    ```
*   **No Linux/Mac:**
    ```bash
    ./library
    ```

## 📝 Licença

Este projeto é aberto e serve para fins de estudo. Sinta-se à vontade para clonar e fazer melhorias!
