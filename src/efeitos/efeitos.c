#include <stdio.h>
#include <stdlib.h>
#include "../../dep/include/raylib.h"
#include "../inimigos/inimigos.h"
#include "../efeitos/efeitos.h"
#define ALT_SPRITE 8
#define LARG_SPRITE 8
#define ESCALA 5

void inicializarExplosao(Vector2 posicao, int *numExplosoes, Explosao **explosoes, int tipo)
{
    Explosao *aux = (Explosao *) realloc(*explosoes, (*numExplosoes + 1) * sizeof(Explosao));

    if (aux == NULL)
    {
        printf("Erro ao alocar a memória.\n");
        free(explosoes);
        exit(1);
    }
    
    *explosoes = aux;
    
    Image img;
    if (tipo == 1)
        img = LoadImage("../res/animacoes/explosao1.png");
    else if (tipo == 2)
        img = LoadImage("../res/animacoes/explosao2.png");

    for (int j = 0; j < 4; j++)
    {
        Image sprite = ImageFromImage(img, (Rectangle) {j * 8, 0, 8, 8});
        ((*explosoes)[*numExplosoes]).spritesheet[j] = LoadTextureFromImage(sprite);
        UnloadImage(sprite);
    }

    ((*explosoes)[*numExplosoes]).dimensoes = (Rectangle) {posicao.x, posicao.y, LARG_SPRITE * ESCALA, ALT_SPRITE * ESCALA};
    ((*explosoes)[*numExplosoes]).centroSprite = (Vector2) {LARG_SPRITE * ESCALA * 0.5, ALT_SPRITE * ESCALA * 0.5};
    ((*explosoes)[*numExplosoes]).tempo = 0;

    *numExplosoes += 1;
}

void atualizarExplosao (int *numExplosoes, Explosao **explosoes)
{
    for(int i = 0; i < *numExplosoes; i++)
    {
        ((*explosoes)[i]).tempo = ((*explosoes)[i]).tempo + GetFrameTime();
    
        if (((*explosoes)[i]).tempo >= 0.240)
        {
            *numExplosoes -= 1;

            for (int j = 0; j < *numExplosoes-1; j++)
            {
                (*explosoes)[j] = (*explosoes)[j+1];
            }

            if(*numExplosoes == 0)
            {
                *explosoes = NULL;
            }
            else
            {
                Explosao *aux = (Explosao*) realloc(*explosoes, (*numExplosoes + 1) * sizeof(Explosao));

                if (aux == NULL)
                {
                    printf("Erro ao alocar a memória.\n");
                    free(explosoes);
                    exit(1);
                }

                *explosoes = aux;
            }
        }
    }
}

void DrawExplosoes(Explosao *explosoes, int numExplosoes)
{
    // Explosões
    for (int i = 0; i < numExplosoes; i++)
    {
        DrawTextureEx(explosoes[i].spritesheet[(int) ((explosoes[i].tempo)/(60*0.00125))], (Vector2) {explosoes[i].dimensoes.x - LARG_SPRITE / 2, explosoes[i].dimensoes.y - ALT_SPRITE / 2}, 0, ESCALA, WHITE);
    }
}