#include <stdio.h>
#include <stdlib.h>
#include "../../dep/include/raylib.h"
#include "../inimigos/inimigos.h"
#include "../efeitos/efeitos.h"
#define FPS 60
#define ALT_SPRITE 8
#define LARG_SPRITE 8
#define ESCALA 5
#define ESCALA_B 15

Texture2D spritesheetExplosao1[4];
Texture2D spritesheetExplosao2[4];

void loadEfeitos()
{
    // Explosão 1
    Image img0 = LoadImage("../res/animacoes/explosao1.png");

    for (int i = 0; i < 4; i++)
    {
        Image img1 = ImageFromImage(img0, (Rectangle) {i * LARG_SPRITE, 0, LARG_SPRITE, ALT_SPRITE});
        spritesheetExplosao1[i] = LoadTextureFromImage(img1);
        UnloadImage(img1);
    }
    
    UnloadImage(img0);

    // Explosão 2
    Image img2 = LoadImage("../res/animacoes/explosao2.png");

    for (int i = 0; i < 4; i++)
    {
        Image img3 = ImageFromImage(img2, (Rectangle) {i * LARG_SPRITE, 0, LARG_SPRITE, ALT_SPRITE});
        spritesheetExplosao2[i] = LoadTextureFromImage(img3);
        UnloadImage(img3);
    }

    UnloadImage(img2);
}

void unloadEfeitos()
{
    // Unload
    for (int i = 0; i < 4; i++)
    {
        UnloadTexture(spritesheetExplosao1[i]);
        UnloadTexture(spritesheetExplosao2[2]);
    }
}

void inicializarExplosoes(Explosao **explosao, int *numExplosoes, Vector2 posicao, int tipo)
{
    Explosao *aux = (Explosao *) realloc(*explosao, (*numExplosoes + 1) * sizeof(Explosao));

    if (aux == NULL)
    {
        printf("Erro ao alocar a memória.\n");
        free(explosao);
        exit(1);
    }
    
    *explosao = aux;

    ((*explosao)[*numExplosoes]).dimensoes = (Rectangle) {posicao.x, posicao.y, LARG_SPRITE * ESCALA, ALT_SPRITE * ESCALA};
    ((*explosao)[*numExplosoes]).centro = (Vector2) {LARG_SPRITE * ESCALA * 0.5, ALT_SPRITE * ESCALA * 0.5};
    ((*explosao)[*numExplosoes]).tipo = tipo;
    ((*explosao)[*numExplosoes]).tempo = 0;

    if (tipo == 1)
        ((*explosao)[*numExplosoes]).sprite = spritesheetExplosao1[0];
    else if (tipo == 2)
        ((*explosao)[*numExplosoes]).sprite = spritesheetExplosao2[0];

    *numExplosoes += 1;
}

void atualizarExplosoes(Explosao **explosao, int *numExplosoes)
{
    for (int i = 0; i < *numExplosoes; i++)
    {
        // Tempo
        ((*explosao)[i]).tempo = ((*explosao)[i]).tempo + GetFrameTime();

        // Sprite
        int frame = (((*explosao)[i]).tempo) / 0.100;

        if (((*explosao)[i]).tipo == 1)
            ((*explosao)[i]).sprite = spritesheetExplosao1[frame];
        else if (((*explosao)[i]).tipo == 2)
            ((*explosao)[i]).sprite = spritesheetExplosao2[frame];

        // Deletar explosões
        if (((*explosao)[i]).tempo > 0.400)
        {
            for (int j = 0; j < *numExplosoes - 1; j++)
            {
                (*explosao)[j] = (*explosao)[j+1];
            }

            if (*numExplosoes <= 1)
            {
                *explosao = NULL;
            }
            else
            {
                Explosao *aux = (Explosao*) realloc(*explosao, (*numExplosoes - 1) * sizeof(Explosao));

                if (aux == NULL)
                {
                    printf("Erro ao alocar a memória.\n");
                    free(explosao);
                    exit(1);
                }

                *explosao = aux;
            }

            (*numExplosoes)--;
        }
    }
}

void DrawExplosoes(Explosao *explosoes, int numExplosoes)
{
    // Explosões
    for (int i = 0; i < numExplosoes; i++)
    {
        DrawTextureEx(explosoes[i].sprite, (Vector2) {explosoes[i].dimensoes.x - LARG_SPRITE / 2, explosoes[i].dimensoes.y - ALT_SPRITE / 2}, 0, ESCALA, WHITE);
    }
}

void inicializarExplosaoBoss(Vector2 posicao, Explosao *explosao)
{
    Image img;
    img = LoadImage("../res/animacoes/explosao2.png");

    explosao->dimensoes = (Rectangle) {posicao.x, posicao.y, LARG_SPRITE * ESCALA, ALT_SPRITE * ESCALA};
    explosao->centro = (Vector2) {LARG_SPRITE * ESCALA * 0.5, ALT_SPRITE * ESCALA * 0.5};
    explosao->sprite = spritesheetExplosao2[0];
    explosao->tempo = 0;
}

void atualizarExplosaoBoss (Explosao *explosao)
{
    // Tempo
    explosao->tempo = explosao->tempo + GetFrameTime();

    // Sprite
    int frame = explosao->tempo / 0.100;
    explosao->sprite = spritesheetExplosao2[frame];
}

void DrawExplosaoBoss(Explosao explosao)
{
    if (explosao.tempo <= 0.400)
    {
        DrawTextureEx(explosao.sprite, (Vector2) {explosao.dimensoes.x - LARG_SPRITE / 2, explosao.dimensoes.y - ALT_SPRITE / 2}, 0, ESCALA_B, WHITE);
    }
}
