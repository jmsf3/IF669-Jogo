#ifndef _NAVE_H
#define _NAVE_H
#include "../../dep/include/raylib.h"

typedef struct
{
    Vector2 posicao;
    Rectangle source;
    Texture2D textura;
} Nave;

typedef struct
{
    double GetTime;
    Vector2 posicao;
    Texture2D textura;
} ProjetilNave;

void inicializarNave(Nave *nave);
void atualizarNave(Nave *nave);
void inicializarProjetil(Nave nave, ProjetilNave *projetil);
void atualizarProjetil(Nave nave, ProjetilNave **projetil, int *numProjetil);

#endif