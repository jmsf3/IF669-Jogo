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

    int divisaoBackground = 0;
    Texture2D backgroundTerra = LoadTexture("../res/background_terra.png");
    Texture2D backgroundEspaco = LoadTexture("../res/background_espaco.png");

    Nave naveACM;
    inicializarNave(&naveACM);

    int numProjetilNave = 0;
    ProjetilNave *projetilNave = NULL;

    while (!WindowShouldClose())
    {   
        // Atualização
        atualizarNave(&naveACM);
        atualizarProjetil(naveACM, &projetilNave, &numProjetilNave);

        divisaoBackground += VEL_BACKGROUND;
        if (divisaoBackground > ALT_JANELA) divisaoBackground = 0;

        // Draw
        BeginDrawing();

            DrawScrollingBackground(backgroundEspaco, divisaoBackground); // Background

            DrawTextureRec(naveACM.textura, naveACM.source, naveACM.posicao, WHITE); // Nave

            for (int i = 0; i < numProjetilNave; i++)
            {
                DrawTextureV(projetilNave[i].textura, projetilNave[i].posicao, WHITE); // Projéteis da nave
            }

        EndDrawing();
    }

    // Dar unload nas texturas
    UnloadTexture(naveACM.textura);
    for (int i = 0; i < numProjetilNave; i++) UnloadTexture(projetilNave[i].textura);
    UnloadTexture(backgroundTerra);
    UnloadTexture(backgroundEspaco);

    // Liberar memória alocada
    free(projetilNave);

    CloseWindow();

    return 0;
}