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
    int numProjetil; // Número de projéteis
    double tInvencivel; // Tempo de invencibilidade
    Sound hit; // Som de hit
    Sound disparo; // Som de disparo
    Vector2 posicao; // Posição
    Texture2D sprite; // Sprite
    Texture2D spritesheet[3]; // Spritesheet
    Propulsor propulsor[2]; // Propulsores
    ProjetilNave *projetil; // Projéteis
} Nave;

void inicializarPropulsor(Propulsor *propulsor);
void atualizarPropulsor(Nave *nave, int frames, char sprite);

void inicializarProjetilNave(Nave *nave);
void atualizarProjetilNave(Nave *nave);

void inicializarNave(Nave *nave);
void atualizarNave(Nave *nave, int frames);

void DrawShip(Nave nave);
void DrawShipProjectile(Nave nave);

#endif