#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "inimigos.h"
#include "../nave/nave.h"
#include "../../dep/include/raylib.h"
#include "../../dep/include/raymath.h"
#define FPS 60
#define ESCALA 5
#define ESCALA_B 10
#define ALT_BOSS 16 * ESCALA_B 
#define LARG_BOSS 16 * ESCALA_B
#define ALT_INIMIGO 8 * ESCALA
#define LARG_INIMIGO 8 * ESCALA
#define ALT_PROJETIL 4 * ESCALA 
#define LARG_PROJETIL 4 * ESCALA
#define ALT_JANELA 600
#define LARG_JANELA 1000
#define VEL_BOSS 3 
#define VEL_INIMIGO 3 
#define VEL_PROJETIL 4
#define ESPACO 3 * LARG_INIMIGO

Sound disparoInimigo;
Texture2D spriteBoss;
Texture2D spriteProjetilInimigo;
Texture2D spritesheetInimigo[2];

void loadInimigos()
{
    // Sprites do inimigo
    Image img0 = LoadImage("../res/inimigos/inimigo.png");

    for (int i = 0; i < 2; i++)
    {
        Image spriteInimigo = ImageFromImage(img0, (Rectangle) {0, i * 8, 8, 8});
        spritesheetInimigo[i] = LoadTextureFromImage(spriteInimigo);
        UnloadImage(spriteInimigo);
    }

    // Sprite do projétil do inimigo
    spriteProjetilInimigo = LoadTexture("../res/inimigos/projetil_inimigo.png");

    // Disparo do inimigo
    disparoInimigo = LoadSound("../res/sounds/disparo_inimigo.ogg");
}

void unloadInimigos()
{
    // Sprites do inimigo
    for (int i = 0; i < 2; i++)
    {
        UnloadTexture(spritesheetInimigo[i]);
    }

    // Sprite do projétil do inimigo
    UnloadTexture(spriteProjetilInimigo);

    // Disparo do inimigo
    UnloadSound(disparoInimigo);
}

void loadBoss()
{
    // Sprite do boss
    spriteBoss = LoadTexture("../res/inimigos/boss.png");

    // Sprite do projétil do inimigo
    spriteProjetilInimigo = LoadTexture("../res/inimigos/projetil_inimigo.png");

    // Disparo do inimigo
    disparoInimigo = LoadSound("../res/sounds/disparo_inimigo.ogg");
}

void unloadBoss()
{
    // Sprite do boss
    UnloadTexture(spriteBoss);

    // Sprite do projétil do inimigo
    UnloadTexture(spriteProjetilInimigo);

    // Disparo do inimigo
    UnloadSound(disparoInimigo);
}

void inicializarInimigos(Inimigo **inimigos, int *numInimigos)
{
    // Alocar memória dinamicamente
    Inimigo *aux = (Inimigo *) realloc(*inimigos, (*numInimigos + 8) * sizeof(Inimigo));

    if (aux == NULL)
    {
        printf("Erro ao alocar a memória.\n");
        free(*inimigos);
        exit(1);
    }

    *inimigos = aux;

    // Setar sprite inicial dos inimigos
    for (int i = *numInimigos; i < *numInimigos + 8; i++)
    {
        ((*inimigos)[i]).sprite = spritesheetInimigo[0];
    }

    // Escolher aleatóriamente o padrão de ataque dos inimigos
    int pdr = GetRandomValue(0, 1);
    
    // Setar as posições iniciais dos inimigos
    for (int i = 0; i < 4; i++)
    {
        int j = *numInimigos + i; ((*inimigos)[j]).pdrAtq = pdr;

        if (pdr == 0)
            ((*inimigos)[j]).posicao.x = (LARG_JANELA / 2 + i * ESPACO) - LARG_INIMIGO / 2; 
        else if (pdr == 1)
            ((*inimigos)[j]).posicao.x = (LARG_JANELA + i * ESPACO) - LARG_INIMIGO / 2; 
    }

    for (int i = 4; i < 8; i++)
    {
        int j = *numInimigos + i; ((*inimigos)[j]).pdrAtq = pdr + 2;

        if (pdr == 0)
            ((*inimigos)[j]).posicao.x = (LARG_JANELA / 2 - (i - 4) * ESPACO) - LARG_INIMIGO / 2; 
        else if (pdr == 1)
            ((*inimigos)[j]).posicao.x = (0 - (i - 4) * ESPACO) - LARG_INIMIGO / 2; 
    }

    *numInimigos += 8;
}

void atualizarInimigos(Inimigo **inimigos, int *numInimigos, int frames)
{
    // Spawnar grupos de inimigos a cada 10 segundos
    if (frames % (10 * FPS) == 0) inicializarInimigos(inimigos, numInimigos);

    // Animação
    for (int i = 0; i < *numInimigos; i++)
    {
        for (int j = 0; j < 2; j ++)
        {        
            if (frames % (2 * (FPS / 2)) == j * (FPS / 2))
            {
                ((*inimigos)[i]).sprite = spritesheetInimigo[j];
            }
        }
    }

    // Movimentação
    for (int i = 0; i < *numInimigos; i++)
    {
        if (((*inimigos)[i]).pdrAtq == 0)
        {
            ((*inimigos)[i]).posicao.x += -VEL_INIMIGO;

            int x = ((*inimigos)[i]).posicao.x + LARG_INIMIGO / 2;
            int y = 400 - pow(x, 2) / 350;

            ((*inimigos)[i]).posicao = (Vector2) {x - LARG_INIMIGO / 2, y - ALT_INIMIGO / 2};
        }
        else if (((*inimigos)[i]).pdrAtq == 1)
        {
            ((*inimigos)[i]).posicao.x += -VEL_INIMIGO;

            int x = ((*inimigos)[i]).posicao.x + LARG_INIMIGO / 2;
            int y = 300 - pow(x - 500, 3) / 130000;

            ((*inimigos)[i]).posicao = (Vector2) {x - LARG_INIMIGO / 2, y - ALT_INIMIGO / 2};
        }
        else if (((*inimigos)[i]).pdrAtq == 2)
        {
            ((*inimigos)[i]).posicao.x += VEL_INIMIGO;

            int x = ((*inimigos)[i]).posicao.x + LARG_INIMIGO / 2;
            int y = 400 - pow(x - 1000, 2) / 350;

            ((*inimigos)[i]).posicao = (Vector2) {x - LARG_INIMIGO / 2, y - ALT_INIMIGO / 2};
        }
        else if (((*inimigos)[i]).pdrAtq == 3)
        {
            ((*inimigos)[i]).posicao.x += VEL_INIMIGO;

            int x = ((*inimigos)[i]).posicao.x + LARG_INIMIGO / 2;
            int y = 300 + pow(x - 500, 3) / 130000;
            
            ((*inimigos)[i]).posicao = (Vector2) {x - LARG_INIMIGO / 2, y - ALT_INIMIGO / 2};
        }
    }

    // Apagar inimigos que estão fora da tela
    for (int i = 0; i < *numInimigos; i++)
    {
        int c0 = ((*inimigos)[i]).pdrAtq == 0 && ((*inimigos)[i]).posicao.x < -LARG_INIMIGO;
        int c1 = ((*inimigos)[i]).pdrAtq == 1 && ((*inimigos)[i]).posicao.y > ALT_JANELA;
        int c2 = ((*inimigos)[i]).pdrAtq == 2 && ((*inimigos)[i]).posicao.x > LARG_JANELA;
        int c3 = ((*inimigos)[i]).pdrAtq == 3 && ((*inimigos)[i]).posicao.y > ALT_JANELA;

        if (c0 || c1 || c2 || c3)
        {
            for (int j = i; j < *numInimigos - 1; j++)
            {
                (*inimigos)[j] = (*inimigos)[j + 1];
            }

            if (*numInimigos > 1)
            {
                Inimigo *aux = (Inimigo *) realloc(*inimigos, (*numInimigos - 1) * sizeof(Inimigo));

                if (aux == NULL)
                {
                    printf("Erro ao alocar a memória.\n");
                    free(*inimigos);
                    exit(1);
                }
                
                *inimigos = aux;
            }
            else
            {
                *inimigos = NULL;
            }

            (*numInimigos)--;
        }
    }
}

void incializarProjetilInimigo(ProjetilInimigo *projetil, Inimigo inimigo, Nave nave)
{
    projetil->sprite = spriteProjetilInimigo;
    projetil->direcao = Vector2Normalize(Vector2Subtract(nave.posicao, inimigo.posicao));
    projetil->posicao = Vector2Add(inimigo.posicao, Vector2Scale(projetil->direcao, VEL_PROJETIL));
}

void atualizarProjetilInimigo(Inimigo *inimigos, int numInimigos, Nave nave, ProjetilInimigo **projetil, int *numProjetil, int frames)
{
    // Disparar a cada 3 segundos
    if (frames != 0 && frames % (3 * FPS) == 0)
    {
        for (int i = 0; i < numInimigos; i++)
        {
            if (GetRandomValue(0, 1) && inimigos[i].posicao.y > 0)
            {
                if (frames != 0) PlaySound(disparoInimigo);
                
                ProjetilInimigo *aux = (ProjetilInimigo *) realloc(*projetil, (*numProjetil + 1) * sizeof(ProjetilInimigo));

                if (aux == NULL)
                {
                    free(*projetil);
                    free(inimigos);
                    exit(1);
                }

                *projetil = aux;
                incializarProjetilInimigo(&((*projetil)[*numProjetil]), inimigos[i], nave);
                (*numProjetil)++;
            }
        }
    }

    // Movimentação
    for (int i = 0; i < *numProjetil; i++)
    {
        ((*projetil)[i]).posicao = Vector2Add(((*projetil)[i]).posicao, Vector2Scale(((*projetil)[i]).direcao, VEL_PROJETIL));
    }

    // Remover projéteis que estão fora da tela
    for (int i = 0; i < *numProjetil; i++)
    {
        int c0 = ((*projetil)[i]).posicao.x < -LARG_PROJETIL;
        int c1 = ((*projetil)[i]).posicao.x > LARG_JANELA;
        int c2 = ((*projetil)[i]).posicao.y > ALT_JANELA;

        if (c0 || c1 || c2)
        {
            for (int j = i; j < *numProjetil - 1; j++)
            {
                (*projetil)[j] = (*projetil)[j + 1];
            }

            if (*numProjetil > 1)
            {
                ProjetilInimigo *aux = (ProjetilInimigo *) realloc(*projetil, (*numProjetil - 1) * sizeof(ProjetilInimigo));

                if (aux == NULL)
                {
                    printf("Erro ao alocar a memória.\n");
                    free(*projetil);
                    free(inimigos);
                    exit(1);
                }
                
                *projetil = aux;
            }
            else
            {
                *projetil = NULL;
            }

            (*numProjetil)--;
        }        
    }
}

void inicializarBoss(Boss *boss)
{
    boss->hp = 300;
    boss->velocidade = VEL_BOSS;
    boss->direcao = (Vector2) {1,1};
    boss->posicao = (Vector2) {LARG_JANELA / 2 - LARG_BOSS / 2, ALT_JANELA / 4 - ALT_BOSS / 2};
}

void atualizarBoss(Boss *boss, ProjetilInimigo **projetil, int *numProjetil, int frames)
{
    boss->posicao.x += boss->velocidade * boss->direcao.x;
    boss->posicao.y += boss->velocidade * boss->direcao.y;

    // Inverter direção do movimento do chefão se ele atingir a borda da tela
    if (boss->posicao.x >= LARG_JANELA - 200 || boss->posicao.x <= 100)
        boss->direcao.x *= -1;
    if (boss->posicao.y <= 0 || boss->posicao.y >= ALT_JANELA*2/3 - 100)
        boss->direcao.y *= -1;
}

void incializarProjetilBoss(ProjetilInimigo *projetil, Boss boss, Nave nave, char side)
{
    projetil->sprite = spriteProjetilInimigo;
    projetil->direcao = Vector2Normalize(Vector2Subtract(nave.posicao, boss.posicao));

    if (side == 'l')
        projetil->posicao = Vector2Add(boss.posicao, (Vector2) {3 * ESCALA_B, 12 * ESCALA_B});
    else if (side == 'r')
        projetil->posicao = Vector2Add(boss.posicao, (Vector2) {14 * ESCALA_B, 12 * ESCALA_B});
}

void atualizarProjetilBoss(Boss boss,ProjetilInimigo **projetil, int *numProjetil, Nave nave, int frames)
{
    // Disparar a cada 2 segundos
    if (frames != 0 && frames % (2 * FPS) == 0 && boss.hp > 0)
    {
        if (frames != 0) PlaySound(disparoInimigo);
        
        ProjetilInimigo *aux = (ProjetilInimigo *) realloc(*projetil, (*numProjetil + 2) * sizeof(ProjetilInimigo));

        if (aux == NULL)
        {
            free(*projetil);
            exit(1);
        }

        *projetil = aux;
        incializarProjetilBoss(&((*projetil)[*numProjetil]), boss, nave, 'l');
        incializarProjetilBoss(&((*projetil)[*numProjetil + 1]), boss, nave, 'r');
        *numProjetil += 2;
    }

    // Movimentação
    for (int i = 0; i < *numProjetil; i++)
    {
        ((*projetil)[i]).posicao = Vector2Add(((*projetil)[i]).posicao, Vector2Scale(((*projetil)[i]).direcao, VEL_PROJETIL));
    }

    // Remover projéteis que estão fora da tela
    for (int i = 0; i < *numProjetil; i++)
    {
        int c0 = ((*projetil)[i]).posicao.x < -LARG_PROJETIL;
        int c1 = ((*projetil)[i]).posicao.x > LARG_JANELA;
        int c2 = ((*projetil)[i]).posicao.y > ALT_JANELA;

        if (c0 || c1 || c2)
        {
            for (int j = i; j < *numProjetil - 1; j++)
            {
                (*projetil)[j] = (*projetil)[j + 1];
            }

            if (*numProjetil > 1)
            {
                ProjetilInimigo *aux = (ProjetilInimigo *) realloc(*projetil, (*numProjetil - 1) * sizeof(ProjetilInimigo));

                if (aux == NULL)
                {
                    printf("Erro ao alocar a memória.\n");
                    free(*projetil);
                    exit(1);
                }
                
                *projetil = aux;
            }
            else
            {
                *projetil = NULL;
            }

            (*numProjetil)--;
        }        
    }  
}

void DrawBoss(Boss boss)
{
    // Sprite Boss
    if (boss.hp > 0) DrawTextureEx(spriteBoss, boss.posicao, 0, ESCALA_B, WHITE); 

    // Barra de HP
    Color backgroundColor = GRAY;
    Color foregroundColor = RED;
    Rectangle background = {LARG_JANELA - 200 - 10, 10, 200, 30};
    Rectangle foreground = {LARG_JANELA - 200 - 10, 10, 200 * (boss.hp / 300.0), 30};

    DrawRectangleRec(background, backgroundColor);
    DrawRectangleRec(foreground, foregroundColor);
}

void DrawEnemy(Inimigo *inimigos, int numInimigos)
{
    // Inimigos
    for (int i = 0; i < numInimigos; i++)
    {
        DrawTextureEx(inimigos[i].sprite, inimigos[i].posicao, 0, ESCALA, WHITE); 
    }
}

void DrawEnemyProjectile(ProjetilInimigo *projetil, int numProjetil)
{
    // Projéteis do inimigo
    for (int i = 0; i < numProjetil; i++)
    {
        DrawTextureEx(projetil[i].sprite, projetil[i].posicao, 0, ESCALA, WHITE); 
    }
}