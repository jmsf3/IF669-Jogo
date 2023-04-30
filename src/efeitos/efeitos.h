#ifndef _EFEITOS_H
#define _EFEITOS_H
#include "../inimigos/inimigos.h"
#include "../../dep/include/raylib.h"

typedef struct
{
    int tipo;
    double tempo;
    Vector2 centro;
    Texture2D sprite;
    Rectangle dimensoes;
} Explosao;

void loadEfeitos();
void unloadEfeitos();

void inicializarExplosoes(Explosao **explosao, int *numExplosoes, Vector2 posicao, int tipo);
void atualizarExplosoes(Explosao **explosao, int *numExplosoes);
void DrawExplosoes(Explosao *explosoes, int numExplosoes);

void inicializarExplosaoBoss(Vector2 posicao, Explosao *explosao);
void atualizarExplosaoBoss(Explosao *explosao);
void DrawExplosaoBoss(Explosao explosao);

#endif