#ifndef _COLISOES_H
#define _COLISOES_H
#include "../nave/nave.h"
#include "../inimigos/inimigos.h"
#include "../efeitos/efeitos.h"
#include "../../dep/include/raylib.h"

void checarColisoes(Nave *nave, Inimigo **inimigo, ProjetilInimigo **projetil, int *numInimigos, int *numProjetil, Explosao **explosoes, int *numExplosoes);
void checarColisoesBoss(Nave *nave, Boss *boss, ProjetilInimigo **projetil, int *numProjetil);

#endif