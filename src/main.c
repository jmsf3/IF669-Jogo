#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "./nave/nave.h"
#include "./inimigos/inimigos.h"
#include "./backgrounds/backgrounds.h"
#include "../dep/include/raylib.h"
#define FPS 60
#define ESCALA 5
#define ALT_JANELA 600
#define LARG_JANELA 1000

void UnloadTextures(Nave *nave, Inimigo *inimigo, ProjetilInimigo *projetil, int numInimigos, int numProjetil, Texture2D background);

int main()
{
    // Inicialização
    InitWindow(LARG_JANELA, ALT_JANELA, "ACM vs. C-GPT669");
    SetTargetFPS(FPS);
    int frames = 0;

    int divisaoBackground = 0;
    Texture2D backgroundEspaco = LoadTexture("../res/backgrounds/background_espaco.png");

    Nave naveACM;
    inicializarNave(&naveACM);

    int numInimigos = 0;
    Inimigo *inimigo = NULL;

    int numProjetilInimigo = 0;
    ProjetilInimigo *projetilInimigo = NULL;

    while (!WindowShouldClose())
    {   
        // Atualização
        atualizarNave(&naveACM, frames);
        atualizarBackground(&divisaoBackground);
        atualizarInimigos(&inimigo, &numInimigos, frames);
        atualizarProjetilInimigo(inimigo, numInimigos, naveACM, &projetilInimigo, &numProjetilInimigo, frames);
        
        // Draw
        BeginDrawing();

            DrawScrollingBackground(backgroundEspaco, divisaoBackground); 
            DrawEnemy(inimigo, numInimigos);
            DrawShip(naveACM);
            DrawShipProjectile(naveACM);
            DrawEnemyProjectile(projetilInimigo, numProjetilInimigo);

        EndDrawing();

        frames++;
    }

    // Dar unload nas texturas
    UnloadTextures(&naveACM, inimigo, projetilInimigo, numInimigos, numProjetilInimigo, backgroundEspaco);

    // Liberar memória alocada
    free(inimigo);
    free(projetilInimigo);
    free(naveACM.projetil);

    CloseWindow();
    return 0;
}

void UnloadTextures(Nave *nave, Inimigo *inimigo, ProjetilInimigo *projetil, int numInimigos, int numProjetil, Texture2D background)
{
    // Nave
    UnloadTexture(nave->sprite);
    for (int i = 0; i < 3; i++) UnloadTexture(nave->spritesheet[i]);
    for (int i = 0; i < nave->numProjetil; i++) UnloadTexture(nave->projetil[i].sprite);

    // Propulsores
    for (int i = 0; i < 2; i++)
    {
        UnloadTexture(nave->polpulsor[i].sprite);

        for (int j = 0; j < 4; j++) UnloadTexture(nave->polpulsor[i].spritesheet[j]);
    }

    // Inimigos
    for (int i = 0; i < 2; i++)
    {
        UnloadTexture(inimigo[i].sprite);

        for (int j = 0; j < 2; j++) UnloadTexture(inimigo[i].spritesheet[j]);
    }

    // Projéteis
    for (int i = 0; i < numProjetil; i++) UnloadTexture(projetil[i].sprite);

    // Background
    UnloadTexture(background);
}