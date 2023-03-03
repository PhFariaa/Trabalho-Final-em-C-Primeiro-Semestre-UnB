// Inclusão das bibliotecas
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include "222007086.h"

/* funções e procedimentos */
void menu();
void cadastar_pessoa();
void consultar_pessoa();
void listar_pessoas_por_cidade();
void gerar_o_relatorio();
void excluir_pessoa();
int verificacao_cpf(char vetor_cpf[]);
int verificacao_data(int dia, int mes, int ano);
int verificacao_sexo(char sexo);

int main()
{
    // Declarações de variáveis
    int escolha_opcao;

    do
    {

        // Impressão do menu e leitura da opção escolhida pelo usuário
        menu();
        scanf("%d", &escolha_opcao);

        // O switch case que irá executar o comando escolhido pelo usuário
        switch (escolha_opcao)
        {
        case CADASTRAR_PESSOA:
            cadastar_pessoa();
            break;
        case CONSULTAR_PESSOA:
            consultar_pessoa();
            break;
        case LISTAR_PESSOAS_CIDADE:
            listar_pessoas_por_cidade();
            break;
        case GERAR_RELATORIO:
            gerar_o_relatorio();
            break;
        case EXCLUIR_PESSOA:
            excluir_pessoa();
            break;
        case SAIR:
            printf("Programa finalizado!\n");
            /*código*/
            break;
        default:
            printf("Numero invalido!\n");
        }
    } while (escolha_opcao != SAIR);
}

// DEFINIÇÃO DAS FUNÇÕES/PROCEDIMENTOS

void cadastar_pessoa()
{
    // Declaração de variaveis
    FILE *arquivo;
    USUARIO pessoa1;
    CIDADE cidade1;

    // printf pra ler o cpf do usuario
    limpar_tela();
    printf("Informe o CPF da pessoa a ser cadastrada (com pontos e hifen): \n");
    limpar_buffer();
    scanf("%[^\n]s", pessoa1.cpf);

    if (verificacao_cpf(pessoa1.cpf) == 0)
    {
        printf("Cpf invalido\n");
    }
    else
    {
        printf("Informe o Nome completo da pessoa a ser cadastrada: \n");
        limpar_buffer();
        scanf("%[^\n]s", pessoa1.nome);

        // if pra ver se o nome é valido
        if (strlen(pessoa1.nome) < 3)
        {
            printf("Nome inválido\n");
        }
        else
        {
            // ler o sexo do usuario
            printf("Informe o sexo da pessoa a ser cadastrada: \n");
            limpar_buffer();
            scanf("%c", &pessoa1.sexo);

            // if pra ver se o sexo é valido
            if (verificacao_sexo(pessoa1.sexo) == 0)
            {
                printf("Sexo invalido\n");
            }
            else
            {
                // printf que le o dia, o mes e o ano
                printf("Informe o dia do nascimento do usuario: \n");
                scanf("%d", &pessoa1.data_nasc);
                printf("Informe o mes de nascimento: \n");
                scanf("%d", &pessoa1.mes_nasc);
                printf("Informe o ano de nascimento: \n");
                scanf("%d", &pessoa1.ano_nasc);

                // if que verifica o dia do nascimento
                if (verificacao_data(pessoa1.data_nasc, pessoa1.mes_nasc, pessoa1.ano_nasc) == 0)
                {
                    printf("Data de nascimento invalida\n");
                }
                else
                {
                    // leitura da cidade da pessoa
                    printf("Informe a cidade a ser cadastrada: \n");
                    limpar_buffer();
                    scanf("%[^\n]s", cidade1.nome_cidade);
                    printf("Informe a UF da cidade: \n");
                    limpar_buffer();
                    scanf("%[^\n]s", cidade1.uf);

                    // condicional pra ver se a cidade existe
                    if (achar_cidade(cidade1.nome_cidade, cidade1.uf) == 0)
                    {
                        printf("Cidade nao esta registrada no nosso banco de dados\n");
                    }
                    else
                    {
                        // if pra ver se o cpf existe
                        if (achar_cpf(pessoa1.cpf) == 1)
                        {
                            arquivo = fopen("cadastro.txt", "a");
                            if (arquivo != NULL)
                            {
                                fprintf(arquivo, "%s\n", pessoa1.cpf);
                                fprintf(arquivo, "%s\n", pessoa1.nome);
                                fprintf(arquivo, "%c\n", pessoa1.sexo);
                                fprintf(arquivo, "%d\n", pessoa1.data_nasc);
                                fprintf(arquivo, "%d\n", pessoa1.mes_nasc);
                                fprintf(arquivo, "%d\n", pessoa1.ano_nasc);
                                fprintf(arquivo, "%s\n", cidade1.nome_cidade);
                                fprintf(arquivo, "%s\n", cidade1.uf);

                                printf("Usuario cadastrado com sucesso\n");

                                fclose(arquivo);
                            }
                        }
                        else
                        {
                            printf("Nao e possivel cadastrar o usuario, pois o CPF ja esta cadastrado\n");
                        }
                    }
                }
            }
        }
    }
}

void consultar_pessoa()
{
    // Declaracao de variaveis
    FILE *consulta_dados;
    USUARIO pessoa_consultada, leitura_pessoa;
    CIDADE cidade_pessoa_consultada;
    int consulta_valida = 0;

    // leitura do cpf para a consulta
    limpar_tela();
    printf("Digite o CPF a ser consultado: \n");
    printf("\n");
    limpar_buffer();
    scanf("%[^\n]s", pessoa_consultada.cpf);

    consulta_dados = fopen("cadastro.txt", "r");
    if (consulta_dados != NULL)
    {
        while (!feof(consulta_dados))
        {
            fscanf(consulta_dados, "%[^\n]\n", leitura_pessoa.cpf);
            fscanf(consulta_dados, "%[^\n]\n", leitura_pessoa.nome);
            fscanf(consulta_dados, "%c\n", &leitura_pessoa.sexo);
            fscanf(consulta_dados, "%d\n", &leitura_pessoa.data_nasc);
            fscanf(consulta_dados, "%d\n", &leitura_pessoa.mes_nasc);
            fscanf(consulta_dados, "%d\n", &leitura_pessoa.ano_nasc);
            fscanf(consulta_dados, "%[^\n]\n", cidade_pessoa_consultada.nome_cidade);
            fscanf(consulta_dados, "%[^\n]\n", cidade_pessoa_consultada.uf);

            if (strcmp(pessoa_consultada.cpf, leitura_pessoa.cpf) == 0)
            {
                consulta_valida = 1;
                break;
            }
            else
            {
                consulta_valida = 0;
            }
        }

        if (consulta_valida == 1)
        {
            printf("CPF: %s\n", leitura_pessoa.cpf);
            printf("Nome completo: %s\n", leitura_pessoa.nome);
            printf("Sexo: %c\n", leitura_pessoa.sexo);
            printf("Data de nascimento: %d/%d/%d\n", leitura_pessoa.data_nasc, leitura_pessoa.mes_nasc, leitura_pessoa.ano_nasc);
            printf("Cidade e unidade da federacao: %s - %s\n", cidade_pessoa_consultada.nome_cidade, cidade_pessoa_consultada.uf);
            printf("\n");
        }
        else
        {
            printf("Essa pessoa nao esta cadastrado em nosso sistema\n");
        }
        fclose(consulta_dados);
    }
}

void listar_pessoas_por_cidade()
{
    FILE *consultar_dados_usuarios;
    CIDADE cidade_consultada, leitura_cidade;
    USUARIO morador;
    char pessoas_por_cidade[QTD_PESSOAS][TAM_MAX], aux[TAM_MAX];
    int i, j, x, contador = 0;

    // Ler a cidade a ser consultada
    printf("Digite a cidade a ser consultada: ");
    limpar_buffer();
    scanf("%[^\n]", cidade_consultada.nome_cidade);
    // Ler a uf da cidade a ser consultada
    printf("Digite a UF da cidade a ser consultada: ");
    limpar_buffer();
    scanf("%[^\n]", cidade_consultada.uf);

    // if pra ver se a cidade está no arquivo de cidades
    if (achar_cidade(cidade_consultada.nome_cidade, cidade_consultada.uf) == 0)
    {
        printf("Essa cidade nao consta no nosso banco de cidades!\n");
    }
    else
    {
        // Comando pra abrir o arquivo do cadastro dos usuarios
        consultar_dados_usuarios = fopen("cadastro.txt", "r");
        if (consultar_dados_usuarios != NULL)
        {
            while (!feof(consultar_dados_usuarios))
            {

                fscanf(consultar_dados_usuarios, "%[^\n]\n", morador.cpf);
                fscanf(consultar_dados_usuarios, "%[^\n]\n", morador.nome);
                fscanf(consultar_dados_usuarios, "%c\n", &morador.sexo);
                fscanf(consultar_dados_usuarios, "%d\n", &morador.data_nasc);
                fscanf(consultar_dados_usuarios, "%d\n", &morador.mes_nasc);
                fscanf(consultar_dados_usuarios, "%d\n", &morador.ano_nasc);
                fscanf(consultar_dados_usuarios, "%[^\n]\n", leitura_cidade.nome_cidade);
                fscanf(consultar_dados_usuarios, "%[^\n]\n", leitura_cidade.uf);

                if ((strcmp(cidade_consultada.nome_cidade, leitura_cidade.nome_cidade) == 0) && strcmp(cidade_consultada.uf, leitura_cidade.uf) == 0)
                {
                    strcpy(pessoas_por_cidade[contador], morador.nome);
                    contador++;
                }
            }

            for (i = 0; i <= contador; i++)
            {
                for (j = i + 1; j <= contador; j++)
                {
                    x = strcmp(pessoas_por_cidade[i], pessoas_por_cidade[j]);
                    if (x > 0)
                    {
                        strcpy(aux, pessoas_por_cidade[i]);
                        strcpy(pessoas_por_cidade[i], pessoas_por_cidade[j]);
                        strcpy(pessoas_por_cidade[j], aux);
                    }
                }
            }
            for (i = 0; i <= contador; i++)
            {
                printf("%s\n", pessoas_por_cidade[i]);
            }
        }
    }
}

void gerar_o_relatorio()
{
    // declarar variaveis
    USUARIO pessoa_do_cadastro1;
    CIDADE city;
    FILE *cadastro;
    int idade = 0;
    float total = 0;
    float total15 = 0, total29 = 0, total49 = 0, total60 = 0, totalmais60 = 0;
    float per15, per29, per49, per60, permais60;
    float total_masc = 0, total_fem = 0;
    float perc_masc, perc_fem;

    cadastro = fopen("cadastro.txt", "r");
    if (cadastro != NULL)
    {
        while (!feof(cadastro))
        {
            fscanf(cadastro, "%[^\n]\n", pessoa_do_cadastro1.cpf);
            fscanf(cadastro, "%[^\n]\n", pessoa_do_cadastro1.nome);
            fscanf(cadastro, "%c\n", &pessoa_do_cadastro1.sexo);
            fscanf(cadastro, "%d\n", &pessoa_do_cadastro1.data_nasc);
            fscanf(cadastro, "%d\n", &pessoa_do_cadastro1.mes_nasc);
            fscanf(cadastro, "%d\n", &pessoa_do_cadastro1.ano_nasc);
            fscanf(cadastro, "%[^\n]\n", city.nome_cidade);
            fscanf(cadastro, "%[^\n]\n", city.uf);
            // calculo da idade do usuario

            idade = calculo_idade(pessoa_do_cadastro1.data_nasc, pessoa_do_cadastro1.mes_nasc, pessoa_do_cadastro1.ano_nasc);
            total = total + 1;

            // armazenar o usuario em alguma faixa etaria
            if (idade >= 0 && idade <= 15)
            {
                total15 = total15 + 1;
            }
            else if (idade > 15 && idade < 30)
            {
                total29 = total29 + 1;
            }
            else if (idade > 29 && idade < 50)
            {
                total49 = total49 + 1;
            }
            else if (idade > 49 && idade <= 60)
            {
                total60 = total60 + 1;
            }
            else if (idade > 60)
            {
                totalmais60 = totalmais60 + 1;
            }

            if (pessoa_do_cadastro1.sexo == 'M' || pessoa_do_cadastro1.sexo == 'm')
            {
                total_masc = total_masc + 1;
            }
            else if (pessoa_do_cadastro1.sexo == 'F' || pessoa_do_cadastro1.sexo == 'f')
            {
                total_fem = total_fem + 1;
            }
        }
        fclose(cadastro);
        per15 = (total15 / total) * 100;
        per29 = (total29 / total) * 100;
        per49 = (total49 / total) * 100;
        per60 = (total60 / total) * 100;
        permais60 = (totalmais60 / total) * 100;

        perc_fem = (total_fem / total) * 100;
        perc_masc = (total_masc / total) * 100;

        printf("\n");
        printf("Total de pessoas beneficiadas:\n");
        printf("\n");
        printf("Percentual da faixa etaria: \n");
        printf("0 a 15 anos %.2f %%\n", per15);
        printf("16 a 29 anos %.2f %%\n", per29);
        printf("30 a 49 anos %.2f %%\n", per49);
        printf("50 a 60 anos %.2f %%\n", per60);
        printf("acima de 60 anos %.2f %%\n", permais60);
        printf("\n");
        printf("Percentual de pessoas por sexo: \n");
        printf("Masculino: %.2f %%\n", perc_masc);
        printf("Feminino %.2f %%\n", perc_fem);
        printf("\n");
    }
}

// Função de excluir pessoa
void excluir_pessoa()
{
    USUARIO pessoa_excluida, pessoa_do_cadastro;
    CIDADE municipio;
    FILE *arquivo_antigo;
    FILE *arquivo_novo;
    int confirmacao;
    int conferidor_de_cpf = 0;

    printf("Digite o CPF a ser excluido: \n");
    limpar_buffer();
    scanf("%[^\n]", pessoa_excluida.cpf);

    arquivo_antigo = fopen("cadastro.txt", "r");
    arquivo_novo = fopen("pessoastemp.txt", "a");
    if (arquivo_antigo != NULL)
    {
        while (!feof(arquivo_antigo))
        {
            fscanf(arquivo_antigo, "%[^\n]\n", pessoa_do_cadastro.cpf);
            fscanf(arquivo_antigo, "%[^\n]\n", pessoa_do_cadastro.nome);
            fscanf(arquivo_antigo, "%c\n", &pessoa_do_cadastro.sexo);
            fscanf(arquivo_antigo, "%d\n", &pessoa_do_cadastro.data_nasc);
            fscanf(arquivo_antigo, "%d\n", &pessoa_do_cadastro.mes_nasc);
            fscanf(arquivo_antigo, "%d\n", &pessoa_do_cadastro.ano_nasc);
            fscanf(arquivo_antigo, "%[^\n]\n", municipio.nome_cidade);
            fscanf(arquivo_antigo, "%[^\n]\n", municipio.uf);

            if (strcmp(pessoa_excluida.cpf, pessoa_do_cadastro.cpf) == 0)
            {
                printf("CPF: %s\n", pessoa_do_cadastro.cpf);
                printf("Nome completo: %s\n", pessoa_do_cadastro.nome);
                printf("Sexo: %c\n", pessoa_do_cadastro.sexo);
                printf("Data de nascimento: %d/%d/%d\n", pessoa_do_cadastro.data_nasc, pessoa_do_cadastro.mes_nasc, pessoa_do_cadastro.ano_nasc);
                printf("Cidade e unidade da federacao: %s - %s\n", municipio.nome_cidade, municipio.uf);
                printf("\n");
                printf("Deseja mesmo excluir esse usuario? \n");
                printf("1 - SIM\n");
                printf("2 - NAO\n");
                scanf("%d", &confirmacao);
                conferidor_de_cpf = 0;
                break;
            }
            conferidor_de_cpf = conferidor_de_cpf+1;
        }
        if (conferidor_de_cpf == 0)
        {
            if (confirmacao == 1)
            {
                rewind(arquivo_antigo);
                while (!feof(arquivo_antigo))
                {
                    fscanf(arquivo_antigo, "%[^\n]\n", pessoa_do_cadastro.cpf);
                    fscanf(arquivo_antigo, "%[^\n]\n", pessoa_do_cadastro.nome);
                    fscanf(arquivo_antigo, "%c\n", &pessoa_do_cadastro.sexo);
                    fscanf(arquivo_antigo, "%d\n", &pessoa_do_cadastro.data_nasc);
                    fscanf(arquivo_antigo, "%d\n", &pessoa_do_cadastro.mes_nasc);
                    fscanf(arquivo_antigo, "%d\n", &pessoa_do_cadastro.ano_nasc);
                    fscanf(arquivo_antigo, "%[^\n]\n", municipio.nome_cidade);
                    fscanf(arquivo_antigo, "%[^\n]\n", municipio.uf);

                    if (strcmp(pessoa_excluida.cpf, pessoa_do_cadastro.cpf) != 0)
                    {

                        fprintf(arquivo_novo, "%s\n", pessoa_do_cadastro.cpf);
                        fprintf(arquivo_novo, "%s\n", pessoa_do_cadastro.nome);
                        fprintf(arquivo_novo, "%c\n", pessoa_do_cadastro.sexo);
                        fprintf(arquivo_novo, "%d\n", pessoa_do_cadastro.data_nasc);
                        fprintf(arquivo_novo, "%d\n", pessoa_do_cadastro.mes_nasc);
                        fprintf(arquivo_novo, "%d\n", pessoa_do_cadastro.ano_nasc);
                        fprintf(arquivo_novo, "%s\n", municipio.nome_cidade);
                        fprintf(arquivo_novo, "%s\n", municipio.uf);
                    }
                }
                fclose(arquivo_antigo);
                fclose(arquivo_novo);
                remove("cadastro.txt");
                rename("pessoastemp.txt", "cadastro.txt");
                printf("Usuario excluido com sucesso. \n");
            }
            else
            {
                printf("O usuario nao sera excluido. \n");
            }
        }
        else
        {
            printf("Cpf nao encontrado! Tente novamente. \n");
        }
    }
}