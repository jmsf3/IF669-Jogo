#include "backgrounds.h"
#include "../../dep/include/raylib.h"
#define ALT_JANELA 600
#define LARG_JANELA 1000
#define VEL_BACKGROUND 3

void DrawStaticBackground(Texture2D background)
{
    DrawTexture(background, 0, 0, WHITE);
}

void DrawScrollingBackground(Texture2D background, int divisaoBackground)
{
    Rectangle inferior = {0, 0, LARG_JANELA, ALT_JANELA - divisaoBackground};
    Rectangle superior = {0, ALT_JANELA - divisaoBackground, LARG_JANELA, divisaoBackground};
    Vector2 posInferior = {0, divisaoBackground};
    Vector2 posSuperior = {0, 0};

    DrawTextureRec(background, inferior, posInferior, WHITE);
    DrawTextureRec(background, superior, posSuperior, WHITE);
}

void atualizarBackground(int *divisao)
{
        if (*divisao > ALT_JANELA)
            *divisao = 0;
        else
            *divisao += VEL_BACKGROUND;
}