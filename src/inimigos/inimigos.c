#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "inimigos.h"
#include "../../dep/include/raylib.h"
#define LARG_INIMIGO 32 // Largura do sprite do inimigo
#define ALT_INIMIGO 32 // Altura do sprite do inimigo
#define LARG_JANELA 1000 // Largura da janela
#define ALT_JANELA 600 // Altura da janela
#define VEL_INIMIGO 3 // Velocidade do inimigo
#define ESPACO 3 * LARG_INIMIGO // Espaço entre os inimigos durante a inicialização
#define PORCENTAGEM_SPAWN 5 // Porcentagem de spawnar um grupo de inimigos

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

    // Dar load nas texturas dos inimigos
    for (int i = *numInimigos; i < *numInimigos + 8; i++)
    {
        ((*inimigos)[i]).textura = LoadTexture("../res/inimigo.png");
    }

    // Escolher aleatóriamente o padrão de ataque dos inimigos que serão incialiazados
    int pdr = GetRandomValue(0, 1);
    
    // Setar as posições iniciais dos inimigos
    for (int i = 0; i < 4; i++)
    {
        int j = *numInimigos + i;
        ((*inimigos)[j]).id = pdr;

        if (pdr == 0)
            ((*inimigos)[j]).posicao.x = (LARG_JANELA / 2 + i * ESPACO) - LARG_INIMIGO / 2; 
        else if (pdr == 1)
            ((*inimigos)[j]).posicao.x = (LARG_JANELA + i * ESPACO) - LARG_INIMIGO / 2; 
    }

    for (int i = 4; i < 8; i++)
    {
        int j = *numInimigos + i;
        ((*inimigos)[j]).id = pdr + 2;

        if (pdr == 0)
            ((*inimigos)[j]).posicao.x = (LARG_JANELA / 2 - (i - 4) * ESPACO) - LARG_INIMIGO / 2; 
        else if (pdr == 1)
            ((*inimigos)[j]).posicao.x = (0 - (i - 4) * ESPACO) - LARG_INIMIGO / 2; 
    }

    *numInimigos += 8;
}

void atualizarInimigos(Inimigo **inimigos, int *numInimigos)
{
    // Spawnar aleatoriamente grupos de inimigos 
    if (IsKeyPressed(KEY_S))
        inicializarInimigos(inimigos, numInimigos);

    // Movimentação
    for (int i = 0; i < *numInimigos; i++)
    {
        if (((*inimigos)[i]).id == 0)
        {
            ((*inimigos)[i]).posicao.x += -VEL_INIMIGO;

            int x = ((*inimigos)[i]).posicao.x + LARG_INIMIGO / 2;
            int y = 400 - pow(x, 2) / 350;

            ((*inimigos)[i]).posicao.x = x - LARG_INIMIGO / 2;
            ((*inimigos)[i]).posicao.y = y - ALT_INIMIGO / 2;
        }
        else if (((*inimigos)[i]).id == 1)
        {
            ((*inimigos)[i]).posicao.x += -VEL_INIMIGO;

            int x = ((*inimigos)[i]).posicao.x + LARG_INIMIGO / 2;
            int y = 300 - pow(x - 500, 3) / 130000;

            ((*inimigos)[i]).posicao.x = x - LARG_INIMIGO / 2;
            ((*inimigos)[i]).posicao.y = y - ALT_INIMIGO / 2;
        }
        else if (((*inimigos)[i]).id == 2)
        {
            ((*inimigos)[i]).posicao.x += VEL_INIMIGO;

            int x = ((*inimigos)[i]).posicao.x + LARG_INIMIGO / 2;
            int y = 400 - pow(x - 1000, 2) / 350;

            ((*inimigos)[i]).posicao.x = x - LARG_INIMIGO / 2;
            ((*inimigos)[i]).posicao.y = y - ALT_INIMIGO / 2;
        }
        else if (((*inimigos)[i]).id == 3)
        {
            ((*inimigos)[i]).posicao.x += VEL_INIMIGO;

            int x = ((*inimigos)[i]).posicao.x + LARG_INIMIGO / 2;
            int y = 300 + pow(x - 500, 3) / 130000;

            ((*inimigos)[i]).posicao.x = x - LARG_INIMIGO / 2;
            ((*inimigos)[i]).posicao.y = y - ALT_INIMIGO / 2;
        }
    }

    // Apagar inimigos que estão fora da tela
    for (int i = 0; i < *numInimigos; i++)
    {
        int c0 = ((*inimigos)[i]).id == 0 && ((*inimigos)[i]).posicao.x > LARG_JANELA;
        int c1 = ((*inimigos)[i]).id == 1 && ((*inimigos)[i]).posicao.y > ALT_JANELA;
        int c2 = ((*inimigos)[i]).id == 2 && ((*inimigos)[i]).posicao.x < -LARG_INIMIGO;
        int c3 = ((*inimigos)[i]).id == 3 && ((*inimigos)[i]).posicao.y > ALT_JANELA;

        if (c0 || c1 || c2 || c3)
        {
            UnloadTexture(((*inimigos)[i]).textura);

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

void inicializarBoss(Boss *boss)
{

}

void atualizarBoss(Boss *boss)
{

}