#ifndef _NAVE_H
#define _NAVE_H
#include "../../dep/include/raylib.h"

typedef struct
{
    Vector2 posicao; // Posição
    Texture2D sprite; // Sprite
} Propulsor;

typedef struct
{
    double tDisparo; // Instante de disparo
    Vector2 posicao; // Posição
    Texture2D sprite; // Sprite
} ProjetilNave;

typedef struct
{
    int hp; // HP
    int score; // Score
    int numProjetil; // Número de projéteis
    double tInvencivel; // Tempo de invencibilidade
    Vector2 posicao; // Posição
    Texture2D spriteNave; // Sprite da nave
    Texture2D spritePiloto; // Sprite do piloto
    Propulsor propulsor[2]; // Propulsores
    ProjetilNave *projetil; // Projéteis
} Nave;

void loadNave();
void unloadNave();

void inicializarPropulsor(Propulsor *propulsor);
void atualizarPropulsor(Nave *nave, int frames, char spriteNave);

void inicializarProjetilNave(Nave *nave);
void atualizarProjetilNave(Nave *nave);

void inicializarNave(Nave *nave, int score);
void atualizarNave(Nave *nave, int frames);

void DrawShip(Nave nave);
void DrawShipProjectile(Nave nave);

void inicializarPiloto(Nave *nave);
void atualizarPiloto(Nave *nave, int frames);

#endif