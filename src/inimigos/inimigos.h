#ifndef _INIMIGOS_H
#define _INIMIGOS_H
#include "../nave/nave.h"
#include "../../dep/include/raylib.h"

typedef struct 
{
    int hp; // HP
    int pdrAtq; // Padrão de ataque
    Vector2 posicao; // Posição
    Texture2D sprite; // Sprite
} Inimigo;

typedef struct
{
    Vector2 posicao; // Posição
    Vector2 direcao; // Direção de disparo
    Texture2D sprite; // Sprite
} ProjetilInimigo;

typedef struct 
{
    int hp; // HP
    int velocidade; // Velocidade
    Vector2 direcao; // Direção
    Vector2 posicao; // Posição
    Texture2D sprite; // Sprite
} Boss;

void loadInimigos();
void unloadInimigos();

void loadBoss();
void unloadBoss();

void incializarProjetilInimigo(ProjetilInimigo *projetil, Inimigo inimigo, Nave nave);
void atualizarProjetilInimigo(Inimigo *inimigo, int numInimigos, Nave nave, ProjetilInimigo **projetil, int *numProjetil, int frames);

void inicializarInimigos(Inimigo **inimigo, int *numInimigos);
void atualizarInimigos(Inimigo **inimigo, int *numInimigos, int frames);

void inicializarBoss(Boss *boss);
void atualizarBoss(Boss *boss, ProjetilInimigo **projetil, int *numProjetil, int frames);

void incializarProjetilBoss(ProjetilInimigo *projetil, Boss boss, Nave nave, char side);
void atualizarProjetilBoss(Boss boss,ProjetilInimigo **projetil, int *numProjetil, Nave nave, int frames);

void DrawBoss(Boss boss);
void DrawEnemy(Inimigo *inimigo, int numInimigos);
void DrawEnemyProjectile(ProjetilInimigo *projetil, int numProjetil);

#endif