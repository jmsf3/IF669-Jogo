#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "./menu/menu.h"
#include "./fases/fases.h"
#include "../dep/include/raylib.h"
#define FPS 60
#define ESCALA 5
#define ALT_JANELA 600
#define LARG_JANELA 1000

int main()
{
    // Inicialização
    InitWindow(LARG_JANELA, ALT_JANELA, "ACM vs. C-GPT669");
    SetTargetFPS(FPS);
    int play = 0;

    // Menu
    menu(&play);

    // Jogo
    if (play)
    {
        start();
    }

    CloseWindow();
    return 0;
}