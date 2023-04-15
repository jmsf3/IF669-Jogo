#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "./nave/nave.h"
#include "./inimigos/inimigos.h"
#include "./backgrounds/backgrounds.h"
#include "../dep/include/raylib.h"
#define LARG_JANELA 1000
#define ALT_JANELA 600
#define VEL_BACKGROUND 3
#define FPS 60

int main()
{
    // Inicialização
    InitWindow(LARG_JANELA, ALT_JANELA, "ACM vs. C-GPT669");
    SetTargetFPS(FPS);
    int frames = 0;

    int divisaoBackground = 0;
    Texture2D backgroundEspaco = LoadTexture("../res/background_espaco.png");

    Nave naveACM;
    inicializarNave(&naveACM);
    
    Propulsor *propulsor = NULL;
    inicializarPropulsor(&propulsor);

    int numProjetilNave = 0;
    ProjetilNave *projetilNave = NULL;

    int numInimigos = 0;
    Inimigo *inimigos = NULL;

    int numProjetilInimigo = 0;
    ProjetilInimigo *projetilInimigo = NULL;

    while (!WindowShouldClose())
    {   
        // Atualização
        atualizarNave(&naveACM);
        atualizarPropulsor(propulsor, naveACM, frames);
        atualizarInimigos(&inimigos, &numInimigos, frames);
        atualizarProjetilNave(naveACM, &projetilNave, &numProjetilNave);
        atualizarProjetilInimigo(inimigos, numInimigos, naveACM, &projetilInimigo, &numProjetilInimigo, frames);
        
        if (divisaoBackground > ALT_JANELA)
            divisaoBackground = 0;
        else
            divisaoBackground += VEL_BACKGROUND;

        // Draw
        BeginDrawing();

            // Background
            DrawScrollingBackground(backgroundEspaco, divisaoBackground); 
            
            // Inimigos
            for (int i = 0; i < numInimigos; i++)
            {
                DrawTextureRec(inimigos[i].textura, inimigos[i].source, inimigos[i].posicao, WHITE); 
            }

            // Propulsores da nave
            for (int i = 0; i < 2; i++)
            {
                DrawTextureRec(propulsor[i].textura, propulsor[i].source, propulsor[i].posicao, WHITE); 
            }

            // Nave
            DrawTextureRec(naveACM.textura, naveACM.source, naveACM.posicao, WHITE);

            // Projéteis da nave
            for (int i = 0; i < numProjetilNave; i++)
            {
                DrawTextureV(projetilNave[i].textura, projetilNave[i].posicao, WHITE); 
            }

            // Projéteis do inimigo
            for (int i = 0; i < numProjetilInimigo; i++)
            {
                DrawTextureV(projetilInimigo[i].textura, projetilInimigo[i].posicao, WHITE); 
            }

        EndDrawing();

        frames++;
    }

    // Dar unload nas texturas
    UnloadTexture(naveACM.textura);
    for (int i = 0; i < 2; i++) UnloadTexture(propulsor[i].textura);
    for (int i = 0; i < numInimigos; i++) UnloadTexture(inimigos[i].textura);
    for (int i = 0; i < numProjetilNave; i++) UnloadTexture(projetilNave[i].textura);
    for (int i = 0; i < numProjetilInimigo; i++) UnloadTexture(projetilInimigo[i].textura);
    UnloadTexture(backgroundEspaco);

    // Liberar memória alocada
    free(inimigos);
    free(propulsor);
    free(projetilNave);
    free(projetilInimigo);

    CloseWindow();

    return 0;
}