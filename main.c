#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

#define TAMTABULEIROX 300
#define TAMTABULEIROY 2
#define MAXTAM 1000

#define VERDE 10
#define VERMELHO 12
#define BRANCO 15

struct Jogo{
    int tabuleiro[TAMTABULEIROX][TAMTABULEIROY];
    int pontuacao;
    int tabx;
    int taby;
    int maca[2];
    int speed;
    char direcao; // Nova variável para armazenar a direção atual da cobra
} jogo = {
    .pontuacao = 1,
    .tabx = 2,
    .taby = 2,
    .speed = 150
};

void antiglitch(int x, int y){
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), (COORD){x, y});
}

void cobrinha(struct Jogo *jogo){
    int i;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), VERDE);
    for(i = 0; i < jogo->pontuacao; i++){
        antiglitch(jogo->tabuleiro[i][0], jogo->tabuleiro[i][1]);
        printf("%c", 219);
    }
}

int bateuemsi(struct Jogo *jogo){
    int aux = 0, i;
    for(i = 1; i < jogo->pontuacao; i++){
        if(jogo->tabx == jogo->tabuleiro[i][0] && jogo->taby == jogo->tabuleiro[i][1])
            aux = 1;
    }
    return aux;
}

void atualizar(struct Jogo *jogo) {
    int i;
    antiglitch(jogo->tabuleiro[jogo->pontuacao][0], jogo->tabuleiro[jogo->pontuacao][1]);
    printf(" ");
    for(i = jogo->pontuacao; i >= 0; i--){
        jogo->tabuleiro[i + 1][0] = jogo->tabuleiro[i][0];
        jogo->tabuleiro[i + 1][1] = jogo->tabuleiro[i][1];
    }
}

void fruta(struct Jogo *jogo){
    int preenchido = 0;

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), VERMELHO);

    antiglitch(jogo->maca[0], jogo->maca[1]);
    printf(" ");

    srand(time(NULL));

    while(1){
        jogo->maca[0] = (rand() % 46) + 2;
        jogo->maca[1] = (rand() % 17) + 2;

        preenchido = 0;
        
        for(int i = 0; i < jogo->pontuacao; i++){
            if(jogo->maca[0] == jogo->tabuleiro[i][0] && jogo->maca[1] == jogo->tabuleiro[i][1]){
                preenchido = 1;
                break;
            }
        }

        if(!preenchido)
            break;
    }

    antiglitch(jogo->maca[0], jogo->maca[1]);
    printf("%c", 254);
}

int stringparaint(char *string){
    int i, num = 0;
    for(i = 0; string[i] != '\0'; i++){
        num = num * 10 + string[i] - '0';
    }
    return num;
}

int main(){
    char menus[5][MAXTAM] = {
        "1 - Jogar",
        "2 - Tutorial",
        "3 - Niveis de dificuldade",
        "4 - Ranking de pontos",
        "0 - Sair"
    };

    int i, j, gameover = 0, opcao = 0;
    char clicar;

    system("cls");

    antiglitch(10,1);
    printf("%s","S N A K E  G A M E");

    for(i = 0; i < 5; i++){
        antiglitch(10, 3 + i);
        printf("%s", menus[i]);
    }

    antiglitch(10,9);

    printf("%s","Digite a opcao desejada: ");
    scanf("%d", &opcao);

    switch (opcao)
    {
    case 1:
        system("cls");
        srand(time(NULL));

        for(i = 1; i < 49; i++){
            for(j = 1; j < 20; j++){
                if(i == 1 || i == 48 || j == 1 || j == 19){
                    antiglitch(i, j);
                    printf("%c", 219);
                }
            }
        }

        fruta(&jogo);
        cobrinha(&jogo);

        jogo.direcao = 'd'; // Comece com uma direção inicial

        while(!gameover){

            jogo.tabuleiro[0][0] = jogo.tabx;
            jogo.tabuleiro[0][1] = jogo.taby;

            if (kbhit()) {
                clicar = getch();
                if (clicar == 'w' || clicar == 'W' || clicar == 72) {
                    if (jogo.direcao != 's' && jogo.direcao != 'S') {
                        jogo.direcao = 'w';
                    }
                }
                else if (clicar == 'a' || clicar == 'A' || clicar == 75) {
                    if (jogo.direcao != 'd' && jogo.direcao != 'D') {
                        jogo.direcao = 'a';
                    }
                }
                else if (clicar == 's' || clicar == 'S' || clicar == 80) {
                    if (jogo.direcao != 'w' && jogo.direcao != 'W') {
                        jogo.direcao = 's';
                    }
                }
                else if (clicar == 'd' || clicar == 'D' || clicar == 77) {
                    if (jogo.direcao != 'a' && jogo.direcao != 'A') {
                        jogo.direcao = 'd';
                    }
                }
            }

            if (jogo.tabx == jogo.maca[0] && jogo.taby == jogo.maca[1]) {
                jogo.pontuacao++;
                fruta(&jogo);
            }

            if((jogo.direcao == 'w' || jogo.direcao == 'W') && (jogo.taby > 2 || jogo.pontuacao >= 1))
                jogo.taby--;

            if((jogo.direcao == 'a' || jogo.direcao == 'A') && (jogo.tabx > 2 || jogo.pontuacao >= 1))
                jogo.tabx--;

            if((jogo.direcao == 's' || jogo.direcao == 'S') && (jogo.taby < 18 || jogo.pontuacao >= 1))
                jogo.taby++;

            if((jogo.direcao == 'd' || jogo.direcao == 'D') && (jogo.tabx < 47 || jogo.pontuacao >= 1))
                jogo.tabx++;

            gameover = bateuemsi(&jogo);

            if(jogo.tabx == 1 || jogo.tabx == 48 || jogo.taby == 1 || jogo.taby == 19){
                gameover = 1;
            }

            atualizar(&jogo);
            cobrinha(&jogo);
            antiglitch(49, 19);
            Sleep(jogo.speed);
        }
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BRANCO);
        antiglitch(17, 9);
        printf("G A M E  O V E R\n");
        antiglitch(19, 10);
        printf("Pontuacao: %d\n", jogo.pontuacao);
        antiglitch(1, 21);
        printf("Deseja jogar novamente? ('1' para voltar ao menu / '0' para sair do jogo): ");
        char input[1];
        scanf("%s", input);
        int opc;
        opc = stringparaint(input);
        if(opc == 1){
            jogo.pontuacao = 1;
            jogo.tabx = 2;
            jogo.taby = 2;
            jogo.speed = 150;
            gameover = 0;
            main();
        }
        else if(opc == 0){
            exit(EXIT_FAILURE);
        }
        else if(opc != 0 || opc != 1){
            antiglitch(1, 22);
            printf("Opcao invalida, voltando ao menu...");
            Sleep(2000);
            main();
        }
        
        break;
    
    default:
        break;
    }

    return 0;
}