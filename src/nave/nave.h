#ifndef _NAVE_H
#define _NAVE_H
#include "../../dep/include/raylib.h"

typedef struct
{
    int hp; // Vida do inimigo
    Vector2 posicao; // Posição da nave na tela
    Rectangle source; // Sprite da nave que está sendo usada no momento
    Texture2D textura; // Textura da nave
} Nave;

typedef struct
{
    double GetTime; // Instante que o projétil foi disparado
    Vector2 posicao; // Posição do projétil na tela
    Texture2D textura; // Textura do projétil
} ProjetilNave;

void inicializarNave(Nave *nave);
void atualizarNave(Nave *nave);
void inicializarProjetilNave(Nave nave, ProjetilNave *projetil);
void atualizarProjetilNave(Nave nave, ProjetilNave **projetil, int *numProjetil);

#endif