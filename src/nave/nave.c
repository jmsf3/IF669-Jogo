#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "nave.h"
#include "../../dep/include/raylib.h"
#define LARG_NAVE 40 // Largura do sprite da nave
#define ALT_NAVE 40 // Altura do sprite da nave
#define LARG_PROJETIL 15 // Largura do sprite do projétil
#define ALT_PROJETIL 30 // Altura do sprite do projétil
#define LARG_JANELA 1000 // Largura da janela
#define ALT_JANELA 600 // Altura da janela
#define VEL_NAVE 3 // Velocidade da nave
#define VEL_PROJETIL 5 // Velocidade do projétil
#define INTERVALO_DISPARO 0.25 // Tempo mínimo entre um disparo e outro em segundos

void inicializarNave(Nave *nave)
{
    nave->textura = LoadTexture("../res/nave.png");
    nave->posicao.x = (LARG_JANELA - LARG_NAVE) / 2; nave->posicao.y = ALT_JANELA - 2 * ALT_NAVE;
    nave->source.x = LARG_NAVE; nave->source.y = 0; nave->source.width = LARG_NAVE; nave->source.height = ALT_NAVE;
}

void atualizarNave(Nave *nave)
{
    // Sprite
    if (IsKeyDown(KEY_LEFT))
        nave->source.x = 0;
    else if (IsKeyDown(KEY_RIGHT))
        nave->source.x = 2 * LARG_NAVE;
    else 
        nave->source.x = LARG_NAVE;

    // Movimentação
    if (IsKeyDown(KEY_LEFT) && nave->posicao.x > 0) 
        nave->posicao.x -= VEL_NAVE;
    if (IsKeyDown(KEY_RIGHT) && nave->posicao.x < LARG_JANELA - LARG_NAVE)
        nave->posicao.x += VEL_NAVE;
    if (IsKeyDown(KEY_UP) && nave->posicao.y > 0)
        nave->posicao.y -= VEL_NAVE;
    if (IsKeyDown(KEY_DOWN) && nave->posicao.y < ALT_JANELA - ALT_NAVE)
        nave->posicao.y += VEL_NAVE;
}

void inicializarProjetil(Nave nave, ProjetilNave *projetil)
{
    projetil->GetTime = GetTime();
    projetil->textura = LoadTexture("../res/projetil_nave.png");
    projetil->posicao.x = nave.posicao.x + (LARG_NAVE - LARG_PROJETIL) / 2; projetil->posicao.y = nave.posicao.y - ALT_PROJETIL;
}

void atualizarProjetil(Nave nave, ProjetilNave **projetil, int *numProjetil)
{
    // Disparo
    if (IsKeyPressed(KEY_SPACE))
    {
        // Calcular o intervalo de tempo percorrido desde o último disparo
        double dt;
        
        if (*numProjetil == 0)
        {
            dt = INFINITY;
        }
        else
        {
            int i = *numProjetil - 1;
            dt = GetTime() - ((*projetil)[i]).GetTime;
        }
        
        // Se o disparo for realizado
        if (dt > INTERVALO_DISPARO)
        {
            ProjetilNave *aux = (ProjetilNave *) realloc(*projetil, (*numProjetil + 1) * sizeof(ProjetilNave));

            if (aux == NULL)
            {
                printf("Erro ao alocar a memória.\n");
                free(*projetil);
                exit(1);
            }

            *projetil = aux;
            inicializarProjetil(nave, &((*projetil)[*numProjetil]));

            (*numProjetil)++;
        }
    }

    // Movimentação
    for (int i = 0; i < *numProjetil; i++)  
    {   
        if (((*projetil)[i]).posicao.y > -ALT_PROJETIL)
        {
            ((*projetil)[i]).posicao.y -= VEL_PROJETIL;
        }
    }

    // Apagar projéteis que estão fora da tela
    for (int i = 0; i < *numProjetil; i++)  
    {
        if (((*projetil)[i]).posicao.y <= -ALT_PROJETIL)
        {
            UnloadTexture(((*projetil)[i]).textura);
            
            for (int j = i; j < *numProjetil - 1; j++)
            {
                (*projetil)[j] = (*projetil)[j + 1];
            }

            if (*numProjetil > 1)
            {
                ProjetilNave *aux = (ProjetilNave *) realloc(*projetil, (*numProjetil - 1) * sizeof(ProjetilNave));

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