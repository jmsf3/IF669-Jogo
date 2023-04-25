#include <stdio.h>
#include <stdlib.h>
#include "colisoes.h"
#include "../../dep/include/raylib.h"
#define ESCALA 5
#define ALT_NAVE 8 * ESCALA
#define LARG_NAVE 8 * ESCALA 
#define ALT_PROJETIL_NV 6 * ESCALA 
#define LARG_PROJETIL_NV 3 * ESCALA 
#define ALT_INIMIGO 8 * ESCALA
#define LARG_INIMIGO 8 * ESCALA
#define ALT_PROJETIL_INMG 2 * ESCALA 
#define LARG_PROJETIL_INMG 2 * ESCALA

void checarColisoes(Nave *nave, Inimigo **inimigo, ProjetilInimigo **projetil, int *numInimigos, int *numProjetil)
{
    // Colisão Nave-Projétil
    if (GetTime() > nave->tInvencivel)
    {
        Rectangle hitboxNave = {nave->posicao.x, nave->posicao.y, LARG_INIMIGO, ALT_INIMIGO};
        int colisao = 0;
        
        for (int i = 0; i < *numProjetil && !colisao; i++)
        {
            Rectangle hitboxProjetil= {(*projetil)[i].posicao.x, (*projetil)[i].posicao.y, LARG_PROJETIL_INMG, ALT_PROJETIL_INMG};
            colisao = CheckCollisionRecs(hitboxNave, hitboxProjetil);

            if (colisao)
            {
                // Som
                PlaySound(nave->hit);

                // Invencibilidade e HP
                nave->tInvencivel = GetTime() + 1;
                nave->hp -= 1;

                // Remover projétil
                UnloadTexture((*projetil)[i].sprite);
            
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

    // Colisão Inimigo-Projétil
    for (int i = 0; i < *numInimigos; i++)
    {
        Rectangle hitboxInimigo = {(*inimigo)[i].posicao.x, (*inimigo)[i].posicao.y, LARG_INIMIGO, ALT_INIMIGO};
        int colisao = 0;

        for (int j = 0; j < nave->numProjetil && !colisao; j++)
        {
            Rectangle hitboxProjetil= {nave->projetil[j].posicao.x, nave->projetil[j].posicao.y, LARG_PROJETIL_NV, ALT_PROJETIL_NV};
            colisao = CheckCollisionRecs(hitboxInimigo, hitboxProjetil);

            if (colisao)
            {
                // Som de morte
                PlaySound((*inimigo)[i].morte);
                
                // Remover inimigo
                UnloadTexture(((*inimigo)[i]).sprite);

                for (int k = i; k < *numInimigos - 1; k++)
                {
                    (*inimigo)[k] = (*inimigo)[k + 1];
                }

                if (*numInimigos > 1)
                {
                    Inimigo *aux = (Inimigo *) realloc(*inimigo, (*numInimigos - 1) * sizeof(Inimigo));

                    if (aux == NULL)
                    {
                        printf("Erro ao alocar a memória.\n");
                        free(*inimigo);
                        exit(1);
                    }

                    *inimigo = aux;
                }
                else
                {
                    *inimigo = NULL;
                }

                (*numInimigos)--;
                
                // Remover projétil
                UnloadTexture(nave->projetil[j].sprite);
            
                for (int k = j; k < nave->numProjetil - 1; k++)
                {
                    nave->projetil[k] = nave->projetil[k + 1];
                }

                printf("opa\n"); 

                if (nave->numProjetil > 1)
                {
                    printf("epa1\n");
                    ProjetilNave *aux = (ProjetilNave *) realloc(nave->projetil, (nave->numProjetil - 1) * sizeof(ProjetilNave));
                    printf("epa2\n");
                    if (aux == NULL)
                    {
                        printf("Erro ao alocar a memória.\n");
                        free(nave->projetil);
                        exit(1);
                    }

                    nave->projetil = aux;
                }
                else
                {
                    nave->projetil = NULL;
                }

                (nave->numProjetil)--;
            }
        }
    }

    // Colisão Nave-Inimigo
    if (GetTime() > nave->tInvencivel)
    {
        Rectangle hitboxNave = {nave->posicao.x, nave->posicao.y, LARG_INIMIGO, ALT_INIMIGO};
        int colisao = 0;

        for (int i = 0; i < *numInimigos && !colisao; i++)
        {
            Rectangle hitboxInimigo = {(*inimigo)[i].posicao.x, (*inimigo)[i].posicao.y, LARG_INIMIGO, ALT_INIMIGO};
            colisao = CheckCollisionRecs(hitboxNave, hitboxInimigo);

            if (colisao)
            {
                // Som
                PlaySound(nave->hit);

                // Invencibilidade e HP
                nave->tInvencivel = GetTime() + 1;
                nave->hp -= 1;
            }
        }
    }
}

void checarColisoesBoss(Nave *nave, Boss *boss, ProjetilInimigo **projetil, int *numProjetil)
{

}
