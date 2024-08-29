#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> // Para a função isdigit

#define MAX_PESSOAS 100 // Define uma taxa máxima de 100 pessoas para a Agenda





/* [ ESTRUTURA DE DADOS — STRUCTS ] */
typedef struct Telefone {
    char numero[12]; // 11 caracteres + 1 para o terminador
    struct Telefone* proximo; // Ponteiro para o próximo telefone
} Telefone;

typedef struct Pessoa {
    char nome[31]; // 30 caracteres + 1 para o terminador
    Telefone* telefones; // Lista de telefones
    char email[31]; // 30 caracteres + 1 para o terminador
    char cpf[12]; // 11 caracteres + 1 para o terminador
    char nascimento[11]; // 10 caracteres + 1 para o terminador
    int id; // ID da pessoa
} Pessoa;

Pessoa agenda[MAX_PESSOAS]; // Criação da Agenda
int contador_de_pessoas = 0; // Contador de pessoas para o ID





/* [ PROTÓTIPOS DE FUNÇÕES ]*/
int validarNome(char* nome);
int validarTelefone(char* telefone);
int validarEmail(char* email);
int validarCPF(char* cpf);
int validarData(char* data);
int nomeJaCadastrado(char* nome);

void exibirMenuCadastro();
void exibirMenuCadastrarTelefone();

void exibirMenuEdicao();
void exibirMenuEditarPessoa();
void exibirMenuEdicaoTelefone();
void editarPessoaPorNome();
void editarPessoaPorID();

void exibirMenuExclusao();
void exibirMenuExcluirPessoa();
void excluirPessoaPorNome();
void excluirPessoaPorID();
void exibirMenuExcluirTelefone();
void excluirTelefonePorNome();
void excluirTelefonePorID();

void exibirMenuConsulta();
void exibirMenuConsultaPessoa();
void consultarPessoaPorNome();
void consultarPessoaPorID();
void exibirMenuConsultaTelefone();
void consultarTelefonePorNome();
void consultarTelefonePorID();

void exibirMenu();
void salvarDados(); // Prototipo da função para salvar dados





/* [ FUNÇÕES DE VALIDAÇÃO E VERIFICAÇÃO (Nome, Nascimento, CPF, Email, Telefone) ]*/
int validarNome(char* nome) {
    return strlen(nome) > 2;
}

int validarTelefone(char* telefone) {
    if ((strlen(telefone) == 10 || strlen(telefone) == 11)) {
        for (int i = 0; i < strlen(telefone); i++) {
            if (!isdigit(telefone[i])) {
                return 0; // Retorna 0 se não for numérico
            }
        }
        return 1; // Retorna 1 se válido
    }
    return 0; // Retorna 0 se não tiver 10 ou 11 caracteres
}

int validarEmail(char* email) {
    return strlen(email) > 10; // Implementar validação de e-mail
}

int validarCPF(char* cpf) {
    // Remove caracteres não numéricos
    char cpf_numeros[12];
    int j = 0;
    for (int i = 0; i < strlen(cpf); i++) {
        if (isdigit(cpf[i])) {
            cpf_numeros[j++] = cpf[i];
        }
    }
    cpf_numeros[j] = '\0'; // Adiciona o terminador de string

    // Verifica se o CPF tem 11 dígitos
    if (strlen(cpf_numeros) != 11) {
        return 0; // CPF inválido
    }

    // Verifica se o CPF é um número repetido
    if (strcmp(cpf_numeros, "00000000000") == 0 || 
        strcmp(cpf_numeros, "11111111111") == 0 || 
        strcmp(cpf_numeros, "22222222222") == 0 || 
        strcmp(cpf_numeros, "33333333333") == 0 || 
        strcmp(cpf_numeros, "44444444444") == 0 || 
        strcmp(cpf_numeros, "55555555555") == 0 || 
        strcmp(cpf_numeros, "66666666666") == 0 || 
        strcmp(cpf_numeros, "77777777777") == 0 || 
        strcmp(cpf_numeros, "88888888888") == 0 || 
        strcmp(cpf_numeros, "99999999999") == 0) {
        return 0; // CPF inválido
    }

    // Validação do primeiro dígito
    int soma = 0;
    for (int i = 0; i < 9; i++) {
        soma += (cpf_numeros[i] - '0') * (10 - i);
    }
    int resto = (soma * 10) % 11;
    if (resto == 10) resto = 0; // Se o resto for 10, consideramos 0
    if (resto != (cpf_numeros[9] - '0')) {
        return 0; // Primeiro dígito verificador inválido
    }

    // Validação do segundo dígito
    soma = 0;
    for (int i = 0; i < 10; i++) {
        soma += (cpf_numeros[i] - '0') * (11 - i);
    }
    resto = (soma * 10) % 11;
    if (resto == 10) resto = 0; // Se o resto for 10, consideramos 0
    if (resto != (cpf_numeros[10] - '0')) {
        return 0; // Segundo dígito verificador inválido
    }

    return 1; // CPF válido
}

int validarData(char* data) {
    int dia, mes, ano;
    if (sscanf(data, "%d/%d/%d", &dia, &mes, &ano) != 3) {
        return 0; // Retorna 0 se não estiver no formato correto
    }
    if (ano < 1900 || mes < 1 || mes > 12 || dia < 1 || dia > 31) {
        return 0; // Retorna 0 se ano, mês ou dia forem inválidos
    }
    if ((mes == 4 || mes == 6 || mes == 9 || mes == 11) && dia > 30) {
        return 0; // Meses com 30 dias
    }
    if (mes == 2) {
        int bissexto = (ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0);
        if ((bissexto && dia > 29) || (!bissexto && dia > 28)) {
            return 0; // Fevereiro
        }
    }

    // Data atual fixa (exemplo: 15/10/2023)
    int dia_atual = 15;
    int mes_atual = 10;
    int ano_atual = 2023;

    // Verifica se a data é menor ou igual à data atual
    if (ano > ano_atual || 
        (ano == ano_atual && mes > mes_atual) || 
        (ano == ano_atual && mes == mes_atual && dia > dia_atual)) {
        return 0; // Data de nascimento não pode ser futura
    }

    return 1; // Retorna 1 se a data for válida
}





/* [ FUNÇÃO VERIFICA SE O NOME JA ESTÁ CADASTRADO ] */
int nomeJaCadastrado(char* nome) {
    for (int i = 0; i < contador_de_pessoas; i++) {
        if (strcmp(agenda[i].nome, nome) == 0) {
            return 1; // Retorna 1 se o nome já estiver cadastrado
        }
    }
    return 0; // Retorna 0 se o nome não estiver cadastrado
}





/* [ FUNÇÕES DO SISTEMA ] {
    CADASTRO {
        cadastrarPessoa()
    }
    EDIÇÃO {
        editarPessoaPorNome()
        editarPessoaPorID()
        editarTelefonePorNome()
        editarTelefonePorID()
    }
    EXCLUSÃO {
        confirmarExclusaoPessoa()
        excluirPessoaPorNome()
        excluirPessoaPorID()
        excluirTelefonePorNome()
        excluirTelefonePorID()
    }
    CONSULTA {
        consultarPessoaPorNome()
        consultarPessoaPorID()
        consultarTelefonePorNome()
        consultarTelefonePorID()
    }
    SAIR E SALVAR {
        salvarDados()
    }
} */

/* CADASTRO */
void cadastrarPessoa() {
    if (contador_de_pessoas < MAX_PESSOAS) {
        Pessoa nova_pessoa;
        nova_pessoa.id = contador_de_pessoas + 1;

        do {
            printf("Nome: ");
            scanf(" %[^\n]", nova_pessoa.nome);
            if (nomeJaCadastrado(nova_pessoa.nome)) {
                printf("Nome ja cadastrado. Digite um novo nome.\n");
            }
        } while (!validarNome(nova_pessoa.nome) || nomeJaCadastrado(nova_pessoa.nome));

        do {
            printf("Data de Nascimento (dd/mm/aaaa): ");
            scanf("%s", nova_pessoa.nascimento);
        } while (!validarData(nova_pessoa.nascimento));

        do {
            printf("CPF: ");
            scanf("%s", nova_pessoa.cpf);
        } while (!validarCPF(nova_pessoa.cpf));

        do {
            printf("E-mail: ");
            scanf("%s", nova_pessoa.email);
        } while (!validarEmail(nova_pessoa.email));

        Telefone* novo_telefone = (Telefone*)malloc(sizeof(Telefone));
        do {
            printf("Telefone: ");
            scanf("%s", novo_telefone->numero);
        } while (!validarTelefone(novo_telefone->numero));

        novo_telefone->proximo = NULL;
        nova_pessoa.telefones = novo_telefone;

        agenda[contador_de_pessoas] = nova_pessoa;
        contador_de_pessoas++;

        char resposta;
        do {
            printf("Deseja adicionar um novo telefone? (S/N): ");
            scanf(" %c", &resposta);
            if (resposta == 'S' || resposta == 's') {
                Telefone* novo_telefone = (Telefone*)malloc(sizeof(Telefone));
                do {
                    printf("Telefone: ");
                    scanf("%s", novo_telefone->numero);
                } while (!validarTelefone(novo_telefone->numero));
                novo_telefone->proximo = nova_pessoa.telefones; // Adiciona no início da lista
                nova_pessoa.telefones = novo_telefone;
            }
        } while (resposta == 'S' || resposta == 's');

        printf("Cadastro concluído com sucesso!\n");
    } else {
        printf("Agenda cheia!\n");
    }
}

/* EDIÇÃO */
void editarPessoaPorNome() {
    char nome[31];
    printf("Digite o nome da pessoa: ");
    scanf(" %[^\n]", nome);
    
    for (int i = 0; i < contador_de_pessoas; i++) {
        if (strcmp(agenda[i].nome, nome) == 0) { // Se o nome estiver na agenda
            int opcao;
            do {
                printf("Menu Editar Pessoa:\n");
                printf("1. Editar Nome\n");
                printf("2. Editar Data de Nascimento\n");
                printf("3. Editar CPF\n");
                printf("4. Editar E-mail\n");
                printf("5. Retornar ao Menu de Edição\n");
                printf("Escolha uma opcao: ");
                scanf("%d", &opcao);

                switch (opcao) {
                    case 1:
                        do {
                            printf("Novo Nome: ");
                            scanf(" %[^\n]", agenda[i].nome);
                        } while (!validarNome(agenda[i].nome));
                        printf("Nome atualizado com sucesso!\n");
                        break;
                    case 2:
                        do {
                            printf("Nova Data de Nascimento (dd/mm/aaaa): ");
                            scanf("%s", agenda[i].nascimento);
                        } while (!validarData(agenda[i].nascimento));
                        printf("Data de Nascimento atualizada com sucesso!\n");
                        break;
                    case 3:
                        do {
                            printf("Novo CPF: ");
                            scanf("%s", agenda[i].cpf);
                        } while (!validarCPF(agenda[i].cpf));
                        printf("CPF atualizado com sucesso!\n");
                        break;
                    case 4:
                        do {
                            printf("Novo E-mail: ");
                            scanf("%s", agenda[i].email);
                        } while (!validarEmail(agenda[i].email));
                        printf("E-mail atualizado com sucesso!\n");
                        break;
                    case 5:
                        printf("Retornando ao Menu de Edição...\n");
                        break;
                    default:
                        printf("Opcao invalida! Tente novamente.\n");
                }
            } while (opcao != 5);
            return; // Sai da função após editar
        }
    }
    printf("Nome não encontrado na agenda.\n");
}

void editarPessoaPorID() {
    int id;
    printf("Digite o ID da pessoa: ");
    scanf("%d", &id);
    
    if (id > 0 && id <= contador_de_pessoas) { // Se o ID estiver na agenda
        int opcao;
        do {
            printf("Menu Editar Pessoa:\n");
            printf("1. Editar Nome\n");
            printf("2. Editar Data de Nascimento\n");
            printf("3. Editar CPF\n");
            printf("4. Editar E-mail\n");
            printf("5. Retornar ao Menu de Edição\n");
            printf("Escolha uma opcao: ");
            scanf("%d", &opcao);

            switch (opcao) {
                case 1:
                    do {
                        printf("Novo Nome: ");
                        scanf(" %[^\n]", agenda[id - 1].nome);
                    } while (!validarNome(agenda[id - 1].nome));
                    printf("Nome atualizado com sucesso!\n");
                    break;
                case 2:
                    do {
                        printf("Nova Data de Nascimento (dd/mm/aaaa): ");
                        scanf("%s", agenda[id - 1].nascimento);
                    } while (!validarData(agenda[id - 1].nascimento));
                    printf("Data de Nascimento atualizada com sucesso!\n");
                    break;
                case 3:
                    do {
                        printf("Novo CPF: ");
                        scanf("%s", agenda[id - 1].cpf);
                    } while (!validarCPF(agenda[id - 1].cpf));
                    printf("CPF atualizado com sucesso!\n");
                    break;
                case 4:
                    do {
                        printf("Novo E-mail: ");
                        scanf("%s", agenda[id - 1].email);
                    } while (!validarEmail(agenda[id - 1].email));
                    printf("E-mail atualizado com sucesso!\n");
                    break;
                case 5:
                    printf("Retornando ao Menu de Edição...\n");
                    break;
                default:
                    printf("Opcao invalida! Tente novamente.\n");
            }
        } while (opcao != 5);
    } else {
        printf("ID inválido!\n");
    }
}

void editarTelefonePorNome() {
    char nome[31];
    printf("Digite o nome da pessoa: ");
    scanf(" %[^\n]", nome);
    
    for (int i = 0; i < contador_de_pessoas; i++) {
        if (strcmp(agenda[i].nome, nome) == 0) { // Se o nome estiver na agenda
            Telefone* telefone_atual = agenda[i].telefones;
            if (telefone_atual == NULL) {
                printf("Nenhum telefone cadastrado para esta pessoa.\n");
                return;
            }

            int opcao;
            do {
                printf("Telefones cadastrados:\n");
                int j = 1;
                while (telefone_atual != NULL) {
                    printf("%d. %s\n", j++, telefone_atual->numero);
                    telefone_atual = telefone_atual->proximo;
                }

                printf("Escolha o telefone para editar (ou 0 para retornar): ");
                scanf("%d", &opcao);

                if (opcao > 0 && opcao < j) {
                    telefone_atual = agenda[i].telefones;
                    for (int k = 1; k < opcao; k++) {
                        telefone_atual = telefone_atual->proximo; // Navega até o telefone escolhido
                    }
                    do {
                        printf("Novo Telefone: ");
                        scanf("%s", telefone_atual->numero);
                    } while (!validarTelefone(telefone_atual->numero));
                    printf("Telefone atualizado com sucesso!\n");
                } else if (opcao != 0) {
                    printf("Opcao invalida! Tente novamente.\n");
                }
            } while (opcao != 0);
            return; // Sai da função após editar
        }
    }
    printf("Nome não encontrado na agenda.\n");
}

void editarTelefonePorID() {
    int id;
    printf("Digite o ID da pessoa: ");
    scanf("%d", &id);
    
    if (id > 0 && id <= contador_de_pessoas) { // Se o ID estiver na agenda
        Telefone* telefone_atual = agenda[id - 1].telefones;
        if (telefone_atual == NULL) {
            printf("Nenhum telefone cadastrado para esta pessoa.\n");
            return;
        }

        int opcao;
        do {
            printf("Telefones cadastrados:\n");
            int j = 1;
            while (telefone_atual != NULL) {
                printf("%d. %s\n", j++, telefone_atual->numero);
                telefone_atual = telefone_atual->proximo;
            }

            printf("Escolha o telefone para editar (ou 0 para retornar): ");
            scanf("%d", &opcao);

            if (opcao > 0 && opcao < j) {
                telefone_atual = agenda[id - 1].telefones;
                for (int k = 1; k < opcao; k++) {
                    telefone_atual = telefone_atual->proximo; // Navega até o telefone escolhido
                }
                do {
                    printf("Novo Telefone: ");
                    scanf("%s", telefone_atual->numero);
                } while (!validarTelefone(telefone_atual->numero));
                printf("Telefone atualizado com sucesso!\n");
            } else if (opcao != 0) {
                printf("Opcao invalida! Tente novamente.\n");
            }
        } while (opcao != 0);
    } else {
        printf("ID inválido!\n");
    }
}

/* EXCLUSÃO */
void confirmarExclusaoPessoa(int index) {
    char resposta;
    printf("Tem certeza que deseja excluir a pessoa '%s'? (S/N): ", agenda[index].nome);
    scanf(" %c", &resposta);
    if (resposta == 'S' || resposta == 's') {
        // Lógica para remover a pessoa da agenda
        for (int j = index; j < contador_de_pessoas - 1; j++) {
            agenda[j] = agenda[j + 1]; // Move as pessoas para preencher o espaço
        }
        contador_de_pessoas--; // Decrementa o contador de pessoas
        printf("Pessoa excluída com sucesso!\n");
    } else {
        printf("Exclusão cancelada.\n");
    }
}

void excluirPessoaPorNome() {
    char nome[31];
    printf("Digite o nome da pessoa a ser excluída: ");
    scanf(" %[^\n]", nome);
    
    for (int i = 0; i < contador_de_pessoas; i++) {
        if (strcmp(agenda[i].nome, nome) == 0) { // Se o nome estiver na agenda
            confirmarExclusaoPessoa(i); // Confirma a exclusão
            return;
        }
    }
    printf("Nome não encontrado na agenda.\n");
}

void excluirPessoaPorID() {
    int id;
    printf("Digite o ID da pessoa a ser excluída: ");
    scanf("%d", &id);
    
    if (id > 0 && id <= contador_de_pessoas) { // Se o ID estiver na agenda
        confirmarExclusaoPessoa(id - 1); // Confirma a exclusão
    } else {
        printf("ID inválido!\n");
    }
}

void excluirTelefonePorNome() {
    char nome[31];
    printf("Digite o nome da pessoa para excluir o telefone: ");
    scanf(" %[^\n]", nome);
    
    for (int i = 0; i < contador_de_pessoas; i++) {
        if (strcmp(agenda[i].nome, nome) == 0) { // Se o nome estiver na agenda
            Telefone* telefone_atual = agenda[i].telefones;
            if (telefone_atual == NULL) {
                printf("Nenhum telefone cadastrado para esta pessoa.\n");
                return;
            }

            int opcao;
            do {
                printf("Telefones cadastrados:\n");
                int j = 1;
                Telefone* temp = telefone_atual;
                while (temp != NULL) {
                    printf("%d. %s\n", j++, temp->numero);
                    temp = temp->proximo;
                }

                printf("Escolha o telefone para excluir (ou 0 para retornar): ");
                scanf("%d", &opcao);

                if (opcao > 0 && opcao < j) {
                    // Lógica para excluir o telefone
                    Telefone* anterior = NULL;
                    temp = agenda[i].telefones;
                    for (int k = 1; k < opcao; k++) {
                        anterior = temp;
                        temp = temp->proximo; // Navega até o telefone escolhido
                    }
                    if (anterior == NULL) {
                        // Exclui o primeiro telefone
                        agenda[i].telefones = temp->proximo;
                    } else {
                        anterior->proximo = temp->proximo; // Remove o telefone da lista
                    }
                    free(temp); // Libera a memória
                    printf("Telefone excluído com sucesso!\n");
                } else if (opcao != 0) {
                    printf("Opcao invalida! Tente novamente.\n");
                }
            } while (opcao != 0);
            return; // Sai da função após excluir
        }
    }
    printf("Nome não encontrado na agenda.\n");
}

void excluirTelefonePorID() {
    int id;
    printf("Digite o ID da pessoa para excluir o telefone: ");
    scanf("%d", &id);
    
    if (id > 0 && id <= contador_de_pessoas) { // Se o ID estiver na agenda
        excluirTelefonePorNome(); // Chama a função para excluir por nome
    } else {
        printf("ID inválido!\n");
    }
}

/* CONSULTAR */
void consultarPessoaPorNome() {
    char nome[31];
    printf("Digite o nome da pessoa: ");
    scanf(" %[^\n]", nome);
    
    for (int i = 0; i < contador_de_pessoas; i++) {
        if (strcmp(agenda[i].nome, nome) == 0) {
            // Exibe as informações da pessoa
            printf("Nome: %s\n", agenda[i].nome);
            printf("Data de Nascimento: %s\n", agenda[i].nascimento);
            printf("CPF: %s\n", agenda[i].cpf);
            printf("E-mail: %s\n", agenda[i].email);
            // Exibir telefones se necessário
            return;
        }
    }
    printf("Nome não encontrado na agenda.\n");
}

void consultarPessoaPorID() {
    int id;
    printf("Digite o ID da pessoa: ");
    scanf("%d", &id);
    
    if (id > 0 && id <= contador_de_pessoas) {
        // Exibe as informações da pessoa
        printf("Nome: %s\n", agenda[id - 1].nome);
        printf("Data de Nascimento: %s\n", agenda[id - 1].nascimento);
        printf("CPF: %s\n", agenda[id - 1].cpf);
        printf("E-mail: %s\n", agenda[id - 1].email);
        // Exibir telefones se necessário
    } else {
        printf("ID inválido!\n");
    }
}

void consultarTelefonePorNome() {
    char nome[31];
    printf("Digite o nome da pessoa: ");
    scanf(" %[^\n]", nome);
    
    for (int i = 0; i < contador_de_pessoas; i++) {
        if (strcmp(agenda[i].nome, nome) == 0) {
            Telefone* telefone_atual = agenda[i].telefones;
            if (telefone_atual == NULL) {
                printf("Nenhum telefone cadastrado para esta pessoa.\n");
                return;
            }
            printf("Telefones cadastrados:\n");
            while (telefone_atual != NULL) {
                printf("%s\n", telefone_atual->numero);
                telefone_atual = telefone_atual->proximo;
            }
            return;
        }
    }
    printf("Nome não encontrado na agenda.\n");
}

void consultarTelefonePorID() {
    int id;
    printf("Digite o ID da pessoa: ");
    scanf("%d", &id);
    
    if (id > 0 && id <= contador_de_pessoas) {
        Telefone* telefone_atual = agenda[id - 1].telefones;
        if (telefone_atual == NULL) {
            printf("Nenhum telefone cadastrado para esta pessoa.\n");
            return;
        }
        printf("Telefones cadastrados:\n");
        while (telefone_atual != NULL) {
            printf("%s\n", telefone_atual->numero);
            telefone_atual = telefone_atual->proximo;
        }
    } else {
        printf("ID inválido!\n");
    }
}

/* SALVAR DADOS */
void salvarDados() {
    FILE* arquivo = fopen("agenda.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para salvar os dados.\n");
        return;
    }

    for (int i = 0; i < contador_de_pessoas; i++) {
        fprintf(arquivo, "ID: %d\n", agenda[i].id);
        fprintf(arquivo, "Nome: %s\n", agenda[i].nome);
        fprintf(arquivo, "Data de Nascimento: %s\n", agenda[i].nascimento);
        fprintf(arquivo, "CPF: %s\n", agenda[i].cpf);
        fprintf(arquivo, "E-mail: %s\n", agenda[i].email);
        
        Telefone* telefone_atual = agenda[i].telefones;
        fprintf(arquivo, "Telefones:\n");
        while (telefone_atual != NULL) {
            fprintf(arquivo, "  %s\n", telefone_atual->numero);
            telefone_atual = telefone_atual->proximo;
        }
        fprintf(arquivo, "\n");
    }

    fclose(arquivo);
    printf("Dados salvos com sucesso em 'agenda.txt'.\n");
}





/* [ MENUS — 1) Cadastro, 2) Edição, 3) Exclusão, 4) Consulta ] {
    exibirMenu() {
        exibirMenuCadastro() {
            exibirMenuCadastrarTelefone()
        }
        exibirMenuEdicao() {
            exibirMenuEditarPessoa()
            exibirMenuEdicaoTelefone()
        }
        exibirMenuExclusao() {
            exibirMenuExcluirPessoa
            exibirMenuExcluirTelefone()
        }
        exibirMenuConsulta() {
            exibirMenuConsultaPessoa()
            exibirMenuConsultaTelefone()
        }
    }
} */

// Função para exibir o menu principal
void exibirMenu() {
    int opcao;
    do {
        printf("Menu Principal\n\n");
        printf("1. Cadastrar\n");
        printf("2. Editar\n");
        printf("3. Excluir\n");
        printf("4. Consultar\n");
        printf("5. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                exibirMenuCadastro();
                break;
            case 2:
                exibirMenuEdicao();
                break;
            case 3:
                exibirMenuExclusao();
                break;
            case 4:
                exibirMenuConsulta();
                break;
            case 5:
                printf("Saindo do programa...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 5);
}

/* [ CADASTRO ] */
void exibirMenuCadastro() {
    int opcao;
    do {
        printf("Menu Principal / Menu Cadastrar\n\n");
        printf("1. Cadastrar Pessoa\n");
        printf("2. Cadastrar Telefone\n");
        printf("3. Retornar ao Menu Principal\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarPessoa();
                break;
            case 2:
                exibirMenuCadastrarTelefone(); // Chama a nova função para cadastrar telefone
                break;
            case 3:
                printf("Retornando ao Menu Principal...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 3);
}

void exibirMenuCadastrarTelefone() {
    int opcao;
    do {
        printf("Menu Principal / Menu Cadastrar / Telefone\n\n");
        printf("1. Pesquisar por Nome\n");
        printf("2. Pesquisar por IDPessoa\n");
        printf("3. Retornar ao Menu Principal\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                // Pesquisar por Nome
                {
                    char nome[31];
                    printf("Digite o nome da pessoa: ");
                    scanf(" %[^\n]", nome);
                    for (int i = 0; i < contador_de_pessoas; i++) {
                        if (strcmp(agenda[i].nome, nome) == 0) { // Se o nome estiver na agenda
                            Telefone* novo_telefone = (Telefone*)malloc(sizeof(Telefone)); // Aloca novo telefone
                            do {
                                printf("Telefone: ");
                                scanf("%s", novo_telefone->numero);
                            } while (!validarTelefone(novo_telefone->numero)); // Enquanto o telefone não for válido
                            novo_telefone->proximo = agenda[i].telefones; // Adiciona no início da lista
                            agenda[i].telefones = novo_telefone;

                            char resposta;
                            do {
                                printf("Deseja adicionar um novo telefone? (S/N): ");
                                scanf(" %c", &resposta);
                                if (resposta == 'S' || resposta == 's') {
                                    novo_telefone = (Telefone*)malloc(sizeof(Telefone));
                                    do {
                                        printf("Telefone: ");
                                        scanf("%s", novo_telefone->numero);
                                    } while (!validarTelefone(novo_telefone->numero));
                                    novo_telefone->proximo = agenda[i].telefones; // Adiciona no início da lista
                                    agenda[i].telefones = novo_telefone;
                                }
                            } while (resposta == 'S' || resposta == 's');
                            break;
                        }
                    }
                }
                break;
            case 2:
                // Pesquisar por IDPessoa
                {
                    int id;
                    printf("Digite o ID da pessoa: ");
                    scanf("%d", &id);
                    if (id > 0 && id <= contador_de_pessoas) {
                        Telefone* novo_telefone = (Telefone*)malloc(sizeof(Telefone));
                        do {
                            printf("Telefone: ");
                            scanf("%s", novo_telefone->numero);
                        } while (!validarTelefone(novo_telefone->numero));
                        novo_telefone->proximo = agenda[id - 1].telefones; // Adiciona no início da lista
                        agenda[id - 1].telefones = novo_telefone;

                        char resposta;
                        do {
                            printf("Deseja adicionar um novo telefone? (S/N): ");
                            scanf(" %c", &resposta);
                            if (resposta == 'S' || resposta == 's') {
                                novo_telefone = (Telefone*)malloc(sizeof(Telefone));
                                do {
                                    printf("Telefone: ");
                                    scanf("%s", novo_telefone->numero);
                                } while (!validarTelefone(novo_telefone->numero));
                                novo_telefone->proximo = agenda[id - 1].telefones; // Adiciona no início da lista
                                agenda[id - 1].telefones = novo_telefone;
                            }
                        } while (resposta == 'S' || resposta == 's');
                    } else {
                        printf("ID inválido!\n");
                    }
                }
                break;
            case 3:
                printf("Retornando ao Menu Principal...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 3);
}

/* [ EDIÇÃO ] */
void exibirMenuEdicao() {
    int opcao;
    do {
        printf("Menu Principal / Menu Editar\n\n");
        printf("1. Editar Pessoa\n");
        printf("2. Editar Telefone\n");
        printf("3. Retornar ao Menu Principal\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                exibirMenuEditarPessoa(); // Chama a nova função para editar pessoa
                break;
            case 2:
                exibirMenuEdicaoTelefone(); // Chama o menu de edição de telefone
                break;
            case 3:
                printf("Retornando ao Menu Principal...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 3);
}

void exibirMenuEditarPessoa() {
    int opcao;
    do {
        printf("Menu Principal / Menu Editar / Menu Editar Pessoa\n\n");
        printf("1. Editar por Nome\n");
        printf("2. Editar por IDPessoa\n");
        printf("3. Retornar ao Menu de Edição\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                editarPessoaPorNome(); // Chama a função para editar por nome
                break;
            case 2:
                editarPessoaPorID(); // Chama a função para editar por ID
                break;
            case 3:
                printf("Retornando ao Menu de Edição...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 3);
}

void exibirMenuEdicaoTelefone() {
    int opcao;
    do {
        printf("Menu Principal / Menu Editar / Menu Editar Telefone\n\n");
        printf("1. Editar Telefone por Nome\n");
        printf("2. Editar Telefone por IDPessoa\n");
        printf("3. Retornar ao Menu Principal\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                editarTelefonePorNome(); // Chama a função para editar por nome
                break;
            case 2:
                editarTelefonePorID(); // Chama a função para editar por ID
                break;
            case 3:
                printf("Retornando ao Menu Principal...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 3);
}

/* [ EXCLUSÃO ] */
void exibirMenuExclusao() {
    int opcao;
    do {
        printf("Menu Principal / Menu Excluir\n\n");
        printf("1. Excluir Pessoa\n");
        printf("2. Excluir Telefone\n");
        printf("3. Retornar ao Menu Principal\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                exibirMenuExcluirPessoa(); // Chama a nova função para excluir pessoa
                break;
            case 2:
                exibirMenuExcluirTelefone(); // Chama a nova função para excluir telefone
                break;
            case 3:
                printf("Retornando ao Menu Principal...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 3);
}

void exibirMenuExcluirPessoa() {
    int opcao;
    do {
        printf("Menu Principal / Menu Excluir / Menu Excluir Pessoa\n\n");
        printf("1. Excluir por Nome\n");
        printf("2. Excluir por IDPessoa\n");
        printf("3. Retornar ao Menu de Exclusão\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                excluirPessoaPorNome(); // Chama a função para excluir por nome
                break;
            case 2:
                excluirPessoaPorID(); // Chama a função para excluir por ID
                break;
            case 3:
                printf("Retornando ao Menu de Exclusão...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 3);
}

void exibirMenuExcluirTelefone() {
    int opcao;
    do {
        printf("Menu Principal / Menu Excluir / Menu Excluir Telefone\n\n");
        printf("1. Excluir Telefone por Nome\n");
        printf("2. Excluir Telefone por IDPessoa\n");
        printf("3. Retornar ao Menu de Exclusão\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                excluirTelefonePorNome(); // Chama a função para excluir por nome
                break;
            case 2:
                excluirTelefonePorID(); // Chama a função para excluir por ID
                break;
            case 3:
                printf("Retornando ao Menu de Exclusão...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 3);
}

/* [ CONSULTA ] */
void exibirMenuConsulta() {
    int opcao;
    do {
        printf("Menu Principal / Menu Consultar\n\n");
        printf("1. Consultar Pessoa\n");
        printf("2. Consultar Telefone\n");
        printf("3. Retornar ao Menu Principal\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                exibirMenuConsultaPessoa(); // Chama o menu de consulta de pessoa
                break;
            case 2:
                exibirMenuConsultaTelefone(); // Chama o menu de consulta de telefone
                break;
            case 3:
                printf("Retornando ao Menu Principal...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 3);
}

void exibirMenuConsultaPessoa() {
    int opcao;
    do {
        printf("Menu Principal / Menu Consultar / Consultar Pessoa\n\n");
        printf("1. Consultar por Nome\n");
        printf("2. Consultar por IDPessoa\n");
        printf("3. Retornar ao Menu de Consulta\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                consultarPessoaPorNome(); // Chama a função para consultar por nome
                break;
            case 2:
                consultarPessoaPorID(); // Chama a função para consultar por ID
                break;
            case 3:
                printf("Retornando ao Menu de Consulta...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 3);
}

void exibirMenuConsultaTelefone() {
    int opcao;
    do {
        printf("Menu Principal / Menu Consultar / Consultar Telefone\n\n");
        printf("1. Consultar Telefone por Nome\n");
        printf("2. Consultar Telefone por IDPessoa\n");
        printf("3. Retornar ao Menu de Consulta\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                consultarTelefonePorNome(); // Chama a função para consultar telefone por nome
                break;
            case 2:
                consultarTelefonePorID(); // Chama a função para consultar telefone por ID
                break;
            case 3:
                printf("Retornando ao Menu de Consulta...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 3);
}





/* [ MAIN ] */
int main() {
    exibirMenu();
    salvarDados(); // Salva os dados antes de sair
    return 0;
}