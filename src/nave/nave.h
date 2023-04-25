#ifndef _NAVE_H
#define _NAVE_H
#include "../../dep/include/raylib.h"

typedef struct 
{
    Vector2 posicao; // Posição
    Texture2D sprite; // Sprite
    Texture2D spritesheet[4]; // Spritesheet
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
    Font font; // Fonte
    Sound hit; // Som de hit
    Sound disparo; // Som de disparo
    Vector2 posicao; // Posição
    Texture2D sprite; // Sprite
    Texture2D spriteCoracao; // Sprite do coração
    Texture2D spritesheet[3]; // Spritesheet
    Propulsor propulsor[2]; // Propulsores
    ProjetilNave *projetil; // Projéteis
    Texture2D piloto[5];
} Nave;

void inicializarPropulsor(Propulsor *propulsor);
void atualizarPropulsor(Nave *nave, int frames, char sprite);

void inicializarProjetilNave(Nave *nave);
void atualizarProjetilNave(Nave *nave);

void inicializarNave(Nave *nave, int score);
void atualizarNave(Nave *nave, int frames);

void DrawShip(Nave nave);
void DrawShipProjectile(Nave nave);

void inicializarPiloto(Nave *nave);
void atualizarPiloto(Nave *nave, int frames);

#endif