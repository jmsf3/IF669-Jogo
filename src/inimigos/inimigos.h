#ifndef _INIMIGOS_H
#define _INIMIGOS_H
#include "../nave/nave.h"
#include "../../dep/include/raylib.h"

typedef struct 
{
    int hp; // Vida do inimigo
    int id; // Identificação do tipo de padrão de ataque que o inimigo segue
    Vector2 posicao; // Posição do inimigo na tela
    Rectangle source; // Indica qual sprite está sendo usado no momento
    Texture2D textura; // Textura do inimigo
} Inimigo;

typedef struct
{
    Vector2 posicao; // Posição do projétil na tela
    Vector2 direcao; // Direção do projétil
    Texture2D textura; // Textura do projétil
} ProjetilInimigo;

typedef struct 
{
    int hp; // Vida do boss
    int id; // Identificação do tipo de padrão de ataque que o boss segue
    Vector2 posicao; // Posição do inimigo na tela
    Texture2D textura; // Textura do inimigo
} Boss;

void inicializarInimigos(Inimigo **inimigos, int *numInimigos);
void atualizarInimigos(Inimigo **inimigos, int *numInimigos, int frames);
void incializarProjetilInimigo(ProjetilInimigo *projetil, Inimigo inimigo, Nave nave);
void atualizarProjetilInimigo(Inimigo *inimigos, int numInimigos, Nave nave, ProjetilInimigo **projetil, int *numProjetil, int frames);
void inicializarBoss(Boss *boss);
void atualizarBoss(Boss *boss);

#endif