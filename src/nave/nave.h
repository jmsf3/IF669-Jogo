#ifndef _NAVE_H
#define _NAVE_H
#include "../../dep/include/raylib.h"

typedef struct
{
    int hp; // Vida da nave
    Vector2 posicao; // Posição da nave na tela
    Rectangle source; // Sprite da nave que está sendo usado no momento
    Texture2D textura; // Textura da nave
} Nave;

typedef struct 
{
    Vector2 posicao; // Posição do propulsor na tela
    Rectangle source; // Sprite do propulsor que está sendo usado no momento
    Texture2D textura; // Textura do propulsor
} Propulsor;

typedef struct
{
    double GetTime; // Instante que o projétil foi disparado
    Vector2 posicao; // Posição do projétil na tela
    Texture2D textura; // Textura do projétil
} ProjetilNave;

void inicializarNave(Nave *nave);
void atualizarNave(Nave *nave);
void inicializarPropulsor(Propulsor **propulsor);
void atualizarPropulsor(Propulsor *propulsor, Nave nave, int frames);
void inicializarProjetilNave(Nave nave, ProjetilNave *projetilEsquerda, ProjetilNave *projetilDireita);
void atualizarProjetilNave(Nave nave, ProjetilNave **projetil, int *numProjetil);

#endif