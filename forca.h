/**
 * @brief Opções de menu para o The Hangman
 */
typedef enum {
    MENU,
    JOGAR,
    ADD_PALAVRA,
    SAIR
} opMenu;

/**
 * @brief Opções do sub-menu para o The Hangman
 */
typedef enum {
    UM_JOGADOR,
    DOIS_JOGADORES,
    VOLTAR_MENU_PRINCIPAL
} opJogar;

/**
 * @brief Opções para variavel verifica
 */
typedef enum{
    NAOEXISTE,
    EXISTE,
}verifica;

/**
* @brief Limpa a tela do console/terminal
*/
void limparTela();

/**
 * @brief Desenha uma linha com uma quantidade de caracteres '*'.
 *
 * @param x Número de caracteres na linha.
 */
void linha(int x);

/**
 * @brief Converte uma palavra string para minúsculas.
 *
 * @param letra Palavra a ser convertida.
 */
void minuscula(char *letra);

/**
 * @brief Confere se uma palavra já existe no banco de palavras.
 *
 * @param banco_Palavras Ponteiro para o arquivo banco_Palavras.txt.
 * @param palavraNova A palavra a ser conferida.
 * @return 1 se a palavra já existe e 0 caso contrário.
 */
verifica repeticao(FILE *banco_Palavras, char *palavraNova);

/**
 * @brief Exibe o menu principal e obtém a opção selecionada pelo usuário.
 *
 * @return A opção de menu selecionada.
 */
opMenu menu();

/**
 * @brief Conta a quantidade de palavras no banco de palavras.
 *
 * @param banco_Palavras Ponteiro para o arquivo banco_Palavras.txt.
 * @return A quantidade de palavras no banco_Palavras.txt.
 */
int contarCod(FILE *banco_Palavras);

/**
 *
 * @param caminho Localização do arquivo
 * @return arquivo aberto
 */
FILE *abrirArquivo(char *caminho);

/**
 * @brief Adiciona uma nova palavra ao banco de palavras.
 */
void addPalavra();

/**
 * @brief Exibe o sub-menu principal e obtém a opção selecionada pelo usuário.
 *
 * @return A opção de menu selecionada.
 */
opJogar submenu();

/**
 * @brief Executa o modo de jogo para um jogador.
 */
void single();

/**
 * @brief Desenha o estado da forca baseado no número de erros.
 *
 * @param caso O número de tentativas (caso) para desenhar a forca correspondente.
 */
void forca(int tentativas);

/**
 * @brief Executa o modo de jogo para dois jogadores.
 */
void mult();

/**
 * @brief Executa a lógica do submenu para o jogo.
 *
 * @return A próxima opção de menu.
 */
void exeJogo();


