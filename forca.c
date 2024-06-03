#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include "forca.h"

#define MAX_LETRAS 51
#define MAX_TENTATIVAS 6

void limparTela() {
    #ifdef _WIN32 // Verifica se é Windows
        system("cls");              // Comando para limpar a tela no Windows
    #else
        system("clear");   // Comando para limpar a tela em Unix/Linux
    #endif
}

void linha(int x){

    putchar(' ');
    for(int i = 1 ;i <= x ; i++){
        putchar('*');
    }
    putchar('\n');
}

void minuscula (char *letra){               //Função para deixar todas letras minusculas.

    int i = 0;

    while(letra[i]){                        //Passa de letra em letra
        letra[i] = tolower(letra[i]);
        i++;
    }
}

verifica repeticao(FILE *banco_Palavras, char *palavraNova){

    int cod;
    char dica[MAX_LETRAS];
    char palavra[MAX_LETRAS];
    verifica repeticao = NAOEXISTE;

    rewind(banco_Palavras);
    while(fscanf(banco_Palavras, "%d %s %s", &cod, dica, palavra) != EOF) {

        if(strcmp(palavra, palavraNova) == 0){
            repeticao = EXISTE;
            break;
        }
    }
    rewind(banco_Palavras);

    return repeticao;
}

opMenu menu() {
    int escolha;
    printf("\n ******** Menu *******\n");
    printf("|1. Jogar               |\n");
    printf("|2. Adicionar Palavra   |\n");
    printf("|3. Sair                |\n");
    linha(23);
    printf("Escolha uma opcao: ");
    scanf("%d", &escolha);

    switch(escolha) {
        case 1:
            return JOGAR;
        case 2:
            return ADD_PALAVRA;
        case 3:
            return SAIR;
        default:
            printf("Opcao inválida!\n");
            return MENU;
    }
}

int contarCod(FILE *banco_Palavras){

    int cod;
    int contador = 0;
    char dica[MAX_LETRAS];
    char palavra[MAX_LETRAS];

    // Loop para ler o arquivo ate o final
    while(fscanf(banco_Palavras, "%d %s %s", &cod, dica, palavra) != EOF){
        contador++;
    }

    return contador;
}

FILE *abrirArquivo(char *caminho){

        FILE *banco_Palavras = fopen(caminho, "a+");

/*
    if (banco_Palavras == NULL) {
        printf("Arquivo %s nao existe ou nao pode ser aberto.\n", caminho);
        exit(1);
    } else {
        printf("Arquivo %s foi aberto.\n\n", caminho);
    }
*/

    return banco_Palavras;
}

void addPalavra() {

    //Abrindo arquivo
    FILE *banco_Palavras = abrirArquivo("C:\\Forca\\docs\\banco_Palavras.txt");

    //Iniciando variaveis

    int cod;
    char palavraNova[MAX_LETRAS];
    char dica[MAX_LETRAS];

    // Pedindo nova dica e palavra

    fflush(stdin);
    printf("\nInsira a dica: ");
    gets(dica);
    printf("\n-Use palavras sem acentuacao-\n");
    printf("Insira a palavra: ");
    gets(palavraNova);
    minuscula(palavraNova);

    // Conferindo se palavra existe, caso nao, ela é adicionada ao arquivo.

    if (repeticao(banco_Palavras, palavraNova) == EXISTE) {                       //Função que verifica se palavra existe
        limparTela();
        printf("\nA palavra ja existe no banco de palavras.\n");
        printf("Pressione ENTER para continuar..");
        getchar();
    } else {
        cod = contarCod(banco_Palavras) + 1;

        fflush(stdin);
        fprintf(banco_Palavras,"\n%d", cod);
        fprintf(banco_Palavras," %s", dica);
        fflush(stdin);
        fprintf(banco_Palavras," %s", palavraNova);
        fflush(stdin);

        printf("\nPalavra adicionada.\n");
        printf("Pressione ENTER para continuar..");
        getchar();
    }

    //Fechando arquivo
    fclose(banco_Palavras);

}

void exeJogo() {
    opJogar opcaoJogar;
    do {
        limparTela();
        opcaoJogar = submenu();
        if(opcaoJogar == UM_JOGADOR) {
            limparTela();
            single();
        } else if(opcaoJogar == DOIS_JOGADORES) {
            limparTela();
            mult();
        }
    } while(opcaoJogar != VOLTAR_MENU_PRINCIPAL);
}

opJogar submenu() {
    int escolha;
    printf(" ******** Jogar ********\n");
    printf("|1. Um Jogador          |\n");
    printf("|2. Dois Jogadores      |\n");
    printf("|3. Voltar ao Menu      |\n");
    linha(23);
    printf("Escolha uma opcao: ");
    scanf("%d", &escolha);

    switch(escolha) {
        case 1:
            return UM_JOGADOR;
        case 2:
            return DOIS_JOGADORES;
        case 3:
            return VOLTAR_MENU_PRINCIPAL;
        default:
            printf("Opção inválida!\n");
            return VOLTAR_MENU_PRINCIPAL;
    }
}

void single() {

    typedef enum{
        ERRADO,
        CERTO,
    };

    // Declarando variaveis
    int numPalavras = 0;
    int codigo = 0;
    char dica[MAX_LETRAS];
    char palavra[MAX_LETRAS];

    // abre o arquivo

    FILE * banco_Palavras = NULL;
    banco_Palavras = fopen("C:\\Forca\\docs\\banco_Palavras.txt", "r");

    // contando grupos
    numPalavras = contarCod(banco_Palavras);
    fclose(banco_Palavras);

    // semente aleatoria

    srand(time(NULL));
    int numAleatorio = (rand() % numPalavras + 1);

    // definir palavra aleatoria

    banco_Palavras = fopen("C:\\Forca\\docs\\banco_Palavras.txt", "r");

    while(codigo != numAleatorio + 1){
        fscanf(banco_Palavras, "%d %s %s", &codigo, dica, palavra);
        codigo++;
    }
    fclose(banco_Palavras);

    // iniciando jogo com mensagem, e aguardo enter

    printf("Boa Sorte!\n");
    printf("Precione Enter para comecar...\n");
    fflush(stdin);
    getchar();

    // logica jogo

    int lenPalavra = strlen(palavra);
    char corretas[lenPalavra];
    char erradas[MAX_TENTATIVAS];
    int tentativas = 0;
    int acertos = 0;

    for(int i = 0; i < lenPalavra; i++){        // Definindo o vetor corretas como '_'
        corretas[i] = '_';
    }
+
    while(tentativas < MAX_TENTATIVAS && acertos < lenPalavra){

        limparTela();
        printf("\nLetras erradas: ");

        for(int i = 0; i < tentativas; i++){                // vetor para letras erradas
            printf("%c ", erradas[i]);
        }

        printf("\nDica: %s", dica);                 // imprimir dica
        forca(tentativas);

        for (int i = 0; i < lenPalavra; i++) {             // Troca dos "_" pela letra correta
            printf("%c ", corretas[i]);
        }

        char letra;
        printf("\nDigite uma letra: ");             // Entrada da nova letra
        scanf(" %c", &letra);
        letra = tolower(letra);

        int chute = ERRADO;                                 // Troca de letras erradas ou certas
        for(int i =0; i < lenPalavra; i++){                 // e verificacao de acerto ou erro

            if(palavra[i] == letra){
                corretas[i] = letra;
                chute = CERTO;
                acertos++;
            }
        }

        if(!chute){
            erradas[tentativas] = letra;
            tentativas++;
        }
    }
    //fim while

    if(acertos == lenPalavra){
        limparTela();
        forca(tentativas);
        printf("%s", palavra);
        printf("\nParabens, voce venceu!\n");
        putchar('\n');
        printf("Pressione ENTER para continuar...");
        fflush(stdin);
        getchar();
    }else{
        limparTela();
        forca(6);
        printf("\nVoce perdeu! \nA palavra era: %s\n", palavra);
        putchar('\n');
        printf("Pressione ENTER para continuar...");
        fflush(stdin);
        getchar();
    }
}

void mult() {

    typedef enum{
        ERRADO,
        CERTO,
    };

    char dica[MAX_LETRAS];                                                      // Abrindo variareis
    char palavraNova[MAX_LETRAS];
    int tentativas = 0;
    int acertos = 0;

    FILE *banco_Palavras = abrirArquivo("C:\\Forca\\docs\\banco_Palavras.txt");    //Abrindo arquivo
    int cod = contarCod(banco_Palavras) + 1;

    limparTela();                                                               //Pedindo palavra e dica
    fflush(stdin);
    printf("Insira a dica: ");
    gets(dica);
    printf("\n-Use palavras sem acentuacao-\n");
    printf("Insira a palavra: ");
    gets(palavraNova);
    minuscula(palavraNova);
    fflush(stdin);

    //Verificando palavra

    if (repeticao(banco_Palavras, palavraNova) == NAOEXISTE) {                // Caso a palavra nao exista na lista, ela sera adicionada ao banco_Palavras.txt
        fflush(stdin);
        fprintf(banco_Palavras,"\n%d", cod);
        fprintf(banco_Palavras," %s", dica);
        fflush(stdin);
        fprintf(banco_Palavras," %s", palavraNova);
        fflush(stdin);
    }

    fclose(banco_Palavras);                                             // Fechando arquivo

    // Iniciando o jogo com mensagem de ENTER

    limparTela();
    printf("Boa Sorte!\n");
    printf("Precione Enter para comecar...\n");
    fflush(stdin);
    getchar();


    int lenPalavra = strlen(palavraNova);
    char corretas[lenPalavra];
    char erradas[MAX_TENTATIVAS];

    for(int i = 0; i < lenPalavra; i++){        // Definindo o vetor corretas como '_'
        corretas[i] = '_';
    }

    while(tentativas < MAX_TENTATIVAS && acertos < lenPalavra){

        limparTela();
        printf("\nLetras erradas: ");

        for(int i = 0; i < tentativas; i++){                // vetor para letras erradas
            printf("%c ", erradas[i]);
        }

        printf("\nDica: %s", dica);                 // imprimir dica

        forca(tentativas);

        for (int i = 0; i < lenPalavra; i++) {             // Troca dos "_" pela letra correta
            printf("%c ", corretas[i]);
        }

        char letra;
        printf("\nDigite uma letra: ");             // Entrada da nova letra
        scanf(" %c", &letra);
        letra = tolower(letra);

        int chute = ERRADO;                                 // Troca de letras erradas ou certas
        for(int i =0; i < lenPalavra; i++){                 // e verificacao de acerto ou erro

            if(palavraNova[i] == letra){
                corretas[i] = letra;
                chute = CERTO;
                acertos++;
            }
        }

        if(!chute){
            erradas[tentativas] = letra;
            tentativas++;
        }
    }
    //fim while

    if(acertos == lenPalavra){
        limparTela();
        forca(tentativas);
        printf("%s", palavraNova);
        printf("\nParabens, voce venceu!\n");
        putchar('\n');
        printf("Pressione ENTER para continuar...");
        fflush(stdin);
        getchar();
    }else{
        limparTela();
        forca(6);
        printf("\nVoce perdeu! \nA palavra era: %s\n", palavraNova);
        putchar('\n');
        printf("Pressione ENTER para continuar...");
        fflush(stdin);
        getchar();
    }
}

void forca(int tentativas) {
    if (tentativas == 0) {
        printf("\n+------+");
        printf("\n|      |");
        printf("\n|");
        printf("\n|");
        printf("\n|");
        printf("\n|");
        printf("\n- ");
    } else if (tentativas == 1) {
        printf("\n+------+");
        printf("\n|      |");
        printf("\n|      0");
        printf("\n|");
        printf("\n|");
        printf("\n|");
        printf("\n- ");
    } else if (tentativas == 2) {
        printf("\n+------+");
        printf("\n|      |");
        printf("\n|      0");
        printf("\n|      |");
        printf("\n|");
        printf("\n|");
        printf("\n- ");
    }else if (tentativas == 3) {
        printf("\n+------+");
        printf("\n|      |");
        printf("\n|      0");
        printf("\n|     /|");
        printf("\n|");
        printf("\n|");
        printf("\n- ");
    }else if (tentativas == 4) {
        printf("\n+------+");
        printf("\n|      |");
        printf("\n|      0");
        printf("\n|     /|\\");
        printf("\n|");
        printf("\n|");
        printf("\n- ");
    }else if (tentativas == 5) {
        printf("\n+------+");
        printf("\n|      |");
        printf("\n|      0");
        printf("\n|     /|\\");
        printf("\n|     /");
        printf("\n|");
        printf("\n- ");
    }else if (tentativas == 6) {
        printf("\n+------+");
        printf("\n|      |");
        printf("\n|      0");
        printf("\n|     /|\\");
        printf("\n|     / \\");
        printf("\n|");
        printf("\n-");
    }
}
