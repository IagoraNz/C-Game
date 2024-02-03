#include <stdio.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "windows.h"

#define WIDTH 20
#define HEIGHT 10

bool gameover;
int score;
int x, y;          // posição da cabeça da cobra
int fruitX, fruitY; // posição da fruta
int tailX[100], tailY[100]; // posição do corpo da cobra
int nTail;         // tamanho da cobra

enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };
enum Direction dir;

void setup() {
    gameover = false;
    score = 0;
    dir = STOP;
    x = WIDTH / 2;
    y = HEIGHT / 2;
    fruitX = rand() % WIDTH;
    fruitY = rand() % HEIGHT;
    nTail = 0;
}

void draw() {
    system("cls"); // Limpar a tela (funciona no Windows)

    for (int i = 0; i < WIDTH + 2; i++)
        printf("#");
    printf("\n");

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (j == 0)
                printf("#"); // Parede da esquerda

            if (i == y && j == x)
                printf("O"); // Cabeça da cobra
            else if (i == fruitY && j == fruitX)
                printf("F"); // Fruta
            else {
                bool printTail = false;
                for (int k = 0; k < nTail; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        printf("o"); // Corpo da cobra
                        printTail = true;
                    }
                }

                if (!printTail)
                    printf(" ");
            }

            if (j == WIDTH - 1)
                printf("#"); // Parede da direita
        }
        printf("\n");
    }

    for (int i = 0; i < WIDTH + 2; i++)
        printf("#");
    printf("\n");

    printf("Score:%d\n", score);
}

void input() {
    if (_kbhit()) {
        switch (_getch()) {
            case 'a':
                dir = LEFT;
                break;
            case 'd':
                dir = RIGHT;
                break;
            case 'w':
                dir = UP;
                break;
            case 's':
                dir = DOWN;
                break;
            case 'x':
                gameover = true;
                break;
        }
    }
}

void algorithm() {
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;

    for (int i = 1; i < nTail; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (dir) {
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
        case UP:
            y--;
            break;
        case DOWN:
            y++;
            break;
        default:
            break;
    }

    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
        gameover = true; // A cobra atingiu a parede

    for (int i = 0; i < nTail; i++) {
        if (tailX[i] == x && tailY[i] == y)
            gameover = true; // A cobra colidiu com o próprio corpo
    }

    if (x == fruitX && y == fruitY) {
        score += 10;
        fruitX = rand() % WIDTH;
        fruitY = rand() % HEIGHT;
        nTail++;
    }
}

int main() {
    setup();

    while (!gameover) {
        draw();
        input();
        algorithm();
        Sleep(100);  // Adiciona um delay de 100 milissegundos (0.1 segundos)
    }

    return 0;
}
