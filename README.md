# Agenda de Contatos em C

Este projeto implementa uma Agenda de Contatos utilizando a linguagem C no padrão C99. O programa oferece funcionalidades de CRUD (Create, Read, Update, Delete) para gerenciar contatos, permitindo o armazenamento de múltiplos números de telefone por contato.

## Funcionalidades

- **Adicionar Contato:** Cadastra um novo contato com nome, e-mail, CPF, data de nascimento e telefones.
- **Editar Contato:** Permite editar as informações de um contato existente, buscando-o pelo nome ou ID.
- **Excluir Contato:** Exclui um contato da agenda, podendo a busca ser feita pelo nome ou ID.
- **Consultar Contato:** Consulta as informações de um contato específico pelo nome ou ID.
- **Gerenciamento de Telefones:** Suporte para adicionar, editar ou remover múltiplos telefones por contato.

## Estrutura de Dados

- **Telefone:** Estrutura que armazena um número de telefone e um ponteiro para o próximo telefone, implementando uma lista encadeada.
- **Pessoa:** Estrutura que armazena as informações de um contato, incluindo uma lista de telefones.

## Validações

O programa implementa diversas funções de validação para garantir a integridade dos dados inseridos, incluindo:

- Validação de Nome
- Validação de Telefone
- Validação de E-mail
- Validação de CPF
- Validação de Data de Nascimento

## Estrutura do Código

O código é organizado em diversas funções para manter a modularidade:

- **Funções de Validação:** Garantem a integridade dos dados.
- **Funções de Gerenciamento de Contatos:** Para adicionar, editar, excluir e consultar contatos.
- **Funções de Menu:** Facilita a interação do usuário com o sistema por meio de uma interface de texto.

## Compilação e Execução

Para compilar e executar o programa, utilize um compilador que suporte C99. Exemplo com `gcc`:

```bash
gcc -o agenda Trabalho-2.c
./agenda
