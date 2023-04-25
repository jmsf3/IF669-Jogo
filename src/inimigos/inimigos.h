#ifndef _INIMIGOS_H
#define _INIMIGOS_H
#include "../nave/nave.h"
#include "../../dep/include/raylib.h"

typedef struct 
{
    int hp; // HP
    int pdrAtq; // Padrão de ataque
    Sound morte; // Som de morte
    Sound disparo; // Som de disparo
    Vector2 posicao; // Posição
    Texture2D sprite; // Sprite
    Texture2D spritesheet[2]; // Spritesheet
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
    Font font; // Fonte
    Sound disparo; // Som de disparo
    Vector2 posicao; // Posição
    Texture2D sprite; // Sprite
    Vector2 direcao; // Direção do boss

} Boss;

void incializarProjetilInimigo(ProjetilInimigo *projetil, Inimigo inimigo, Nave nave);
void atualizarProjetilInimigo(Inimigo *inimigo, int numInimigos, Nave nave, ProjetilInimigo **projetil, int *numProjetil, int frames);

void inicializarInimigos(Inimigo **inimigo, int *numInimigos);
void atualizarInimigos(Inimigo **inimigo, int *numInimigos, int frames);

void inicializarBoss(Boss *boss);
void atualizarBoss(Boss *boss, ProjetilInimigo **projetil, int *numProjetil, int frames);

void incializarProjetilBoss(ProjetilInimigo *projetil, Boss boss, Nave nave);
void atualizarProjetilBoss(Boss boss,ProjetilInimigo **projetil, int *numProjetil, Nave nave, int frames);

void DrawBoss(Boss boss);
void DrawEnemy(Inimigo *inimigo, int numInimigos);
void DrawEnemyProjectile(ProjetilInimigo *projetil, int numProjetil);

#endif