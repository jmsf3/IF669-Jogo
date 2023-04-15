#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "nave.h"
#include "../../dep/include/raylib.h"
#define LARG_NAVE 40 // Largura do sprite da nave
#define ALT_NAVE 40 // Altura do sprite da nave
#define LARG_PROJETIL 15 // Largura do sprite do projétil
#define ALT_PROJETIL 30 // Altura do sprite do projétil
#define LARG_PROPULSOR 5 // Largura do sprite do propulsor
#define ALT_PROPULSOR 15 // Altura do sprite do propulsor
#define LARG_JANELA 1000 // Largura da janela
#define ALT_JANELA 600 // Altura da janela
#define VEL_NAVE 4 // Velocidade da nave
#define VEL_PROJETIL 5 // Velocidade do projétil
#define INTERVALO_DISPARO 0.25 // Tempo mínimo entre um disparo e outro em segundos
#define FPS 60

void inicializarNave(Nave *nave)
{
    nave->textura = LoadTexture("../res/nave.png");
    nave->posicao = (Vector2) {(LARG_JANELA - LARG_NAVE) / 2, ALT_JANELA - 2 * ALT_NAVE};
    nave->source = (Rectangle) {LARG_NAVE, 0, LARG_NAVE, ALT_NAVE};
}

void atualizarNave(Nave *nave)
{
    // Animação
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

void inicializarPropulsor(Propulsor **propulsor)
{
    Propulsor *aux = (Propulsor *) malloc(2 * sizeof(Propulsor));

    if (aux == NULL)
    {
        printf("Erro ao alocar memória.\n");
        free(*propulsor);
        exit(1);
    }

    *propulsor = aux;

    for (int i = 0; i < 2; i++)
    {
        ((*propulsor)[i]).textura = LoadTexture("../res/propulsores.png");
        ((*propulsor)[i]).source = (Rectangle) {0, 0, LARG_PROPULSOR, ALT_PROPULSOR};
    }
}

void atualizarPropulsor(Propulsor *propulsor, Nave nave, int frames)
{
    // Animação
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 4; j ++)
        {        
            if (frames % (4 * (FPS / 10)) == j * (FPS / 10))
            {
                propulsor[i].source.x = j * LARG_PROPULSOR;
            }
        }
    }

    // Posição
    if (nave.source.x == LARG_NAVE)
    {
        propulsor[0].posicao.x = nave.posicao.x + 2 * 5;
        propulsor[1].posicao.x = nave.posicao.x + 5 * 5;
    }
    else if (nave.source.x == 2 * LARG_NAVE)
    {
        propulsor[0].posicao.x = nave.posicao.x + 3 * 5;
        propulsor[1].posicao.x = nave.posicao.x + 5 * 5;
    }
    else
    {
        propulsor[0].posicao.x = nave.posicao.x + 2 * 5;
        propulsor[1].posicao.x = nave.posicao.x + 4 * 5;
    }

    propulsor[0].posicao.y = propulsor[1].posicao.y = nave.posicao.y + ALT_NAVE;
}

void inicializarProjetilNave(Nave nave, ProjetilNave *projetilEsquerda, ProjetilNave *projetilDireita)
{
    projetilEsquerda->GetTime = GetTime();
    projetilEsquerda->textura = LoadTexture("../res/projetil_nave.png");
    projetilEsquerda->posicao = (Vector2) {nave.posicao.x, nave.posicao.y - 2 * 5};

    projetilDireita->GetTime = GetTime();
    projetilDireita->textura = LoadTexture("../res/projetil_nave.png");
    projetilDireita->posicao = (Vector2) {nave.posicao.x + 5 * 5, nave.posicao.y - 2 * 5};
}

void atualizarProjetilNave(Nave nave, ProjetilNave **projetil, int *numProjetil)
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
            ProjetilNave *aux = (ProjetilNave *) realloc(*projetil, (*numProjetil + 2) * sizeof(ProjetilNave));

            if (aux == NULL)
            {
                printf("Erro ao alocar a memória.\n");
                free(*projetil);
                exit(1);
            }

            *projetil = aux;
            inicializarProjetilNave(nave, &((*projetil)[*numProjetil]), &((*projetil)[*numProjetil + 1]));

            *numProjetil += 2;
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