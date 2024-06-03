#include <stdio.h>
#include "forca.h"

int main(void) {
    opMenu opcao = MENU;

    while(1) {
        if(opcao == MENU) {
            limparTela();
            opcao = menu();
        } else if(opcao == JOGAR) {
            limparTela();
            exeJogo();
            opcao = MENU;
        } else if(opcao == ADD_PALAVRA) {
            limparTela();
            addPalavra();
            opcao = MENU;
        } else if(opcao == SAIR) {
            printf("Fechando jogo.\n");
            break;
        }
    }

    return 0;
}