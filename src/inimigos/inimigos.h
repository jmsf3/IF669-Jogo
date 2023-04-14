#ifndef _INIMIGOS_H
#define _INIMIGOS_H
#include "../../dep/include/raylib.h"

typedef struct 
{
    int hp; // Vida do inimigo
    int id; // Identificação do tipo de padrão de ataque que o inimigo segue
    Vector2 posicao; // Posição do inimigo na tela
    Texture2D textura; // Textura do inimigo
} Inimigo;

typedef struct
{
    Vector2 posicao; // Posição do projétil na tela
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
void atualizarInimigos(Inimigo **inimigos, int *numInimigos);
void inicializarBoss(Boss *boss);
void atualizarBoss(Boss *boss);

#endif