    // DEFINES
#define TAM_MAX 101
#define TAM_CPF 15
#define CADASTRAR_PESSOA 1
#define CONSULTAR_PESSOA 2
#define LISTAR_PESSOAS_CIDADE 3
#define GERAR_RELATORIO 4
#define EXCLUIR_PESSOA 5
#define SAIR 6
#define TAM_UF 4
#define TAM_MAX_CIDADE 200
#define QTD_PESSOAS 1000

// DEFINIÇÃO DOS STRUCTS
typedef struct Pessoa
{
    char cpf[TAM_CPF];
    char nome[TAM_MAX];
    char sexo;
    int data_nasc, mes_nasc, ano_nasc;

} USUARIO;

typedef struct Cidades
{
    char uf[TAM_UF];
    char nome_cidade[TAM_MAX_CIDADE];
    char nome_com_acento[TAM_MAX_CIDADE];
    char nome_sem_acento[TAM_MAX_CIDADE];
    int cod_municipio;

} CIDADE;

// Função utilizada para limpar o buffer
void limpar_buffer()
{
    char ch;
    while ((ch = getchar()) != '\n' && ch != EOF)
        ;
}

// Função utilizada para limpar o terminal
void limpar_tela()
{
#if defined(linux) || defined(unix) || defined(APPLE)
    system("clear");
#endif

#if defined(_WIN32) || defined(_WIN64)
    system("cls");
#endif
}

// Procedimento que irá imprimir o menu do SGBS
void menu()
{
    printf("....... MENU DE OPCOES .......\n");
    printf(" \n");
    printf(" \n");
    printf("1) Cadastrar Pessoa\n");
    printf("2) Consultar Pessoa\n");
    printf("3) Listar pessoa por Cidade\n");
    printf("4) Gerar Relatorio\n");
    printf("5) Excluir Pessoa\n");
    printf("6) Encerrar Programa\n\n");
}

// Procedimento que converte string para letras maiúsculas
void maiuscula(char str1[])
{
    int i = 0;

    while (str1[i] != '\0')
    {
        str1[i] = toupper(str1[i]);
        i++;
    }
    printf("%s\n", str1);
}

// Função que irá validar o CPF informado
int verificacao_cpf(char vetor_cpf[])
{
    // Declaração de variáveis
    int cpf_numero[TAM_CPF], f = 0, soma1, ver1, soma2, ver2;

    // Condicional que verifica se o CPF é válido
    if (strlen(vetor_cpf) != TAM_CPF - 1)
    {
        return 0;
    }
    else
    {
        if (vetor_cpf[0] >= '0' && vetor_cpf[0] <= '9' &&
            vetor_cpf[1] >= '0' && vetor_cpf[1] <= '9' &&
            vetor_cpf[2] >= '0' && vetor_cpf[2] <= '9' &&
            vetor_cpf[3] == '.' &&
            vetor_cpf[4] >= '0' && vetor_cpf[4] <= '9' &&
            vetor_cpf[5] >= '0' && vetor_cpf[5] <= '9' &&
            vetor_cpf[6] >= '0' && vetor_cpf[6] <= '9' &&
            vetor_cpf[7] == '.' &&
            vetor_cpf[8] >= '0' && vetor_cpf[8] <= '9' &&
            vetor_cpf[9] >= '0' && vetor_cpf[9] <= '9' &&
            vetor_cpf[10] >= '0' && vetor_cpf[10] <= '9' &&
            vetor_cpf[11] == '-' &&
            vetor_cpf[12] >= '0' && vetor_cpf[12] <= '9' &&
            vetor_cpf[13] >= '0' && vetor_cpf[13] <= '9')
        {

            // Converter CPF de string para numero inteiro
            for (int i = 0; i < 14; i++)
            {
                if (vetor_cpf[i] == '1')
                {
                    cpf_numero[i] = 1;
                }
                else if (vetor_cpf[i] == '2')
                {
                    cpf_numero[i] = 2;
                }
                else if (vetor_cpf[i] == '3')
                {
                    cpf_numero[i] = 3;
                }
                else if (vetor_cpf[i] == '4')
                {
                    cpf_numero[i] = 4;
                }
                else if (vetor_cpf[i] == '5')
                {
                    cpf_numero[i] = 5;
                }
                else if (vetor_cpf[i] == '6')
                {
                    cpf_numero[i] = 6;
                }
                else if (vetor_cpf[i] == '7')
                {
                    cpf_numero[i] = 7;
                }
                else if (vetor_cpf[i] == '8')
                {
                    cpf_numero[i] = 8;
                }
                else if (vetor_cpf[i] == '9')
                {
                    cpf_numero[i] = 9;
                }
                else if (vetor_cpf[i] == '0')
                {
                    cpf_numero[i] = 0;
                }
            }

            // Condicional que verifica se os numeros do CPF são repetidos
            if (cpf_numero[0] == cpf_numero[1] && cpf_numero[1] == cpf_numero[2])
            {
                f = 1;
            }
            else
            {
                f = 0;
            }

            // Se f seja igual a 0 vai para a condicional que faz o calculo de validação do CPF
            if (f == 0)
            {
                // Calculo que verifica o primeiro digito após o hífen
                soma1 = (cpf_numero[0] * 10) + (cpf_numero[1] * 9) + (cpf_numero[2] * 8) + (cpf_numero[4] * 7) + (cpf_numero[5] * 6) + (cpf_numero[6] * 5) +
                        (cpf_numero[8] * 4) + (cpf_numero[9] * 3) + (cpf_numero[10] * 2);
                ver1 = (soma1 * 10) % 11;

                if (ver1 == 10)
                {
                    ver1 = 0;
                }

                // Calculo que verifica o segundo digito após o hífen
                soma2 = (cpf_numero[0] * 11) + (cpf_numero[1] * 10) + (cpf_numero[2] * 9) + (cpf_numero[4] * 8) + (cpf_numero[5] * 7) + (cpf_numero[6] * 6) +
                        (cpf_numero[8] * 5) + (cpf_numero[9] * 4) + (cpf_numero[10] * 3) + (cpf_numero[12] * 2);
                ver2 = (soma2 * 10) % 11;

                if (ver2 == 10)
                {
                    ver2 = 0;
                }

                // Se o res1 for igual ao primeiro digito e o res2 for igual ao segundo digito, o CPF é válido
                if (ver1 == cpf_numero[12] && ver2 == cpf_numero[13])
                {
                    return 1;
                }
                else
                {
                    return 0;
                }
            }
            else
            {
                return 0;
            }
        }
        else
        {
            return 0;
        }
    }
}

// Função que irá verificar se o sexo dado pelo usuário é válido
int verificacao_sexo(char sexo)
{
    if (sexo == 'M' || sexo == 'm' || sexo == 'F' || sexo == 'f')
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

// Função que verifica se a data informada pelo usuário é válida
int verificacao_data(int dia, int mes, int ano)
{

    // Checagem do ano
    if (ano >= 1000 && ano <= 9999)
    {

        // Checagem do mes
        if (mes >= 1 && mes <= 12)
        {

            // Checagem do dia
            if ((dia >= 1 && dia <= 31) && (mes == 1 || mes == 3 || mes == 5 || mes == 7 || mes == 8 || mes == 10 || mes == 12))
            {
                return 1;
            }
            else if ((dia >= 1 && dia <= 30) && (mes == 4 || mes == 6 || mes == 9 || mes == 11))
            {
                return 1;
            }
            else if ((dia >= 1 && dia <= 28) && (mes == 2))
            {
                return 1;
            }
            else if (dia == 29 && mes == 2 && (ano % 400 == 0 || (ano % 4 == 0 && ano % 100 != 0)))
            {
                return 1;
            }
            else
            {
                return 0;
            }
            return 0;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        return 0;
    }
}

// Função que procura se o CPF dado já existe no arquivo com os dados de usuários
int achar_cpf(char cpf_da_pessoa[])
{
    // Declaração de variáveis
    FILE *dados;
    USUARIO pessoa2;
    CIDADE cidade2;
    int validacao=0;

    // Instrução para abrir o arquivo para leitura
    dados = fopen("cadastro.txt", "r");

    if (dados != NULL)
    {
        // Repetição que irá ler os dados do arquivo e comparar com o que foi dado
        while (!feof(dados))
        {

            fscanf(dados, "%[^\n]\n", pessoa2.cpf);
            fscanf(dados, "%[^\n]\n", pessoa2.nome);
            fscanf(dados, "%c\n", &pessoa2.sexo);
            fscanf(dados, "%d\n", &pessoa2.data_nasc);
            fscanf(dados, "%d\n", &pessoa2.mes_nasc);
            fscanf(dados, "%d\n", &pessoa2.ano_nasc);
            fscanf(dados, "%[^\n]\n", cidade2.nome_cidade);
            fscanf(dados, "%[^\n]\n", cidade2.uf);



            if (strcmp(cpf_da_pessoa, pessoa2.cpf) == 0)
            {
                // se retorna 0 tem cpf cadastrado
                validacao = 0;
                break;
            }
            else
            {
                // se ta retornando 1 nao tem cpf igual cadastrado
                validacao = validacao + 1;
            }
        }

        if(validacao == 0){
            return 0;
        }else{
            return 1;
        }
        fclose(dados);
    }
}

int achar_cidade(char cidade_pessoa[], char uf_cidade[])
{
    // Declaração de variáveis
    FILE *lista_cidades;
    char cabecalho[TAM_MAX];
    CIDADE cidade_cadastrada;
    int verifica_cidade = 0;

    // Abrir o arquivo
    lista_cidades = fopen("cidades.txt", "r");

    if (lista_cidades != NULL)
    {

        while (!feof(lista_cidades))
        {
            // leitura dos dados do arquivo
            fscanf(lista_cidades, "%d\n", &cidade_cadastrada.cod_municipio);
            fscanf(lista_cidades, "%[^\n]\n", cidade_cadastrada.uf);
            fscanf(lista_cidades, "%[^\n]\n", cidade_cadastrada.nome_com_acento);
            fscanf(lista_cidades, "%[^\n]\n", cidade_cadastrada.nome_sem_acento);
            // caso as strings sejam iguais a cidade é válida e consta no arquivo

            if ((strcmp(cidade_pessoa, cidade_cadastrada.nome_sem_acento) == 0) && (strcmp(uf_cidade, cidade_cadastrada.uf) == 0))
            {
                verifica_cidade = 1;
                return 1;
                break;
            }
            else
            {
                verifica_cidade = 0;
            }
        }
        fclose(lista_cidades);
    }
}

int calculo_idade(int dia, int mes, int ano){
    struct tm *calculo;
    time_t data;
    int idade;
    int dia_atual = 0, mes_atual = 0, ano_atual = 0;

    time(&data);
    calculo=localtime(&data);

    dia_atual = calculo->tm_mday;
    mes_atual = calculo->tm_mon+1;
    ano_atual = calculo->tm_year+1900;

    if(mes < mes_atual){
        idade = ano_atual - ano;
    }else if(mes > mes_atual){
        idade = (ano_atual - 1) - ano;
    }else if(mes == mes_atual){
        if(dia <= dia_atual){
            idade = ano_atual - ano;
        }else if(dia > dia_atual){
            idade = (ano_atual - 1) - ano;
        }
    }
    return idade;
}