#ifndef _EFEITOS_H
#define _EFEITOS_H
#include "../inimigos/inimigos.h"
#include "../../dep/include/raylib.h"

typedef struct
{
    Texture2D spritesheet[4]; // Spritesheet
    Rectangle dimensoes;
    Vector2 centroSprite;
    double tempo;
} Explosao;

void inicializarExplosao (Vector2 posicao, int *numExplosoes, Explosao **explosoes, int tipo);
void atualizarExplosao (int *numExplosoes, Explosao **explosoes);
void DrawExplosoes(Explosao *explosoes, int numExplosoes);

#endif