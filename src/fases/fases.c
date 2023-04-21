#include <stdio.h>
#include <stdlib.h>
#include "fases.h"
#include "../nave/nave.h"
#include "../inimigos/inimigos.h"
#include "../backgrounds/backgrounds.h"
#include "../../dep/include/raylib.h"
#define FPS 60
#define ESCALA1 5
#define ESCALA2 6
#define ALT_JANELA 600
#define LARG_JANELA 1000
#define ALT_YW 27 * ESCALA2
#define LARG_YW 43 * ESCALA2
#define ALT_GO 28 * ESCALA2
#define LARG_GO 44 * ESCALA2
#define TEMPO_FASE 10 // segundos

void youWon()
{
    Texture2D win = LoadTexture("../res/interface/you_won.png");

    while (!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(BLACK);
            DrawTextureEx(win, (Vector2) {LARG_JANELA / 2 - LARG_YW / 2, ALT_JANELA / 2 - ALT_YW / 2}, 0, ESCALA2, WHITE);
        EndDrawing();
    }

    UnloadTexture(win);
}

void gameOver()
{
    Texture2D over = LoadTexture("../res/interface/game_over.png");

    while (!WindowShouldClose())
    {
        BeginDrawing();

            ClearBackground(BLACK);
            DrawTextureEx(over, (Vector2) {LARG_JANELA / 2 - LARG_GO / 2, ALT_JANELA / 2 - ALT_GO / 2}, 0, ESCALA2, WHITE);

        EndDrawing();
    }

    UnloadTexture(over);
}

void terceiraFase()
{
    
}

void segundaFase()
{
    // Inicialização
    int frames = 0;
    int divisao = 0;
    Texture2D background = LoadTexture("../res/backgrounds/background_espaco.png");

    Nave nave;
    inicializarNave(&nave);

    int numInimigos = 0;
    Inimigo *inimigo = NULL;

    int numProjetilInimigo = 0;
    ProjetilInimigo *projetilInimigo = NULL;

    // Fade-in
    int play = 1;
    int transparency = 255;

    while (transparency >= 0 && play)
    {
        BeginDrawing();

            DrawStaticBackground(background);
            DrawTextureEx(nave.sprite, nave.posicao, 0, ESCALA1, WHITE);
            DrawRectangle(0, 0, 1000, 600, (Color) {0, 0, 0, transparency});

        EndDrawing();

        transparency -= 2;
        if (WindowShouldClose()) play = 0;
    }

    while (nave.hp > 0 && frames < TEMPO_FASE * FPS && play)
    {
        // Atualização
        atualizarNave(&nave, frames);
        atualizarBackground(&divisao);
        atualizarInimigos(&inimigo, &numInimigos, frames);
        atualizarProjetilInimigo(inimigo, numInimigos, nave, &projetilInimigo, &numProjetilInimigo, frames);
            
        // Draw
        BeginDrawing();
                
            DrawScrollingBackground(background, divisao); 
                
            DrawShip(nave);
            DrawShipProjectile(nave);

            DrawEnemy(inimigo, numInimigos);
            DrawEnemyProjectile(projetilInimigo, numProjetilInimigo);
            
        EndDrawing();

        frames++;
        if (WindowShouldClose()) play = 0;
    }

    // Fade-out
    transparency = 0;

    while (transparency <= 255 && play)
    {
        atualizarNave(&nave, frames);
        atualizarBackground(&divisao);

        BeginDrawing();

            DrawScrollingBackground(background, divisao); 
            DrawShip(nave);
            DrawShipProjectile(nave);
            DrawRectangle(0, 0, 1000, 600, (Color) {0, 0, 0, transparency});

        EndDrawing();

        frames++;
        transparency += 2;
        if (WindowShouldClose()) play = 0;
    }

    // Unload
    UnloadTexture(background);

    UnloadTexture(nave.sprite);
    for (int i = 0; i < 3; i++) UnloadTexture(nave.spritesheet[i]);

    for (int i = 0; i < 2; i++)
    {
        UnloadTexture(nave.propulsor[i].sprite);

        for (int j = 0; j < 4; j++) UnloadTexture(nave.propulsor[i].spritesheet[j]);
    }

    for (int i = 0; i < numInimigos; i++)
    {
        UnloadTexture(inimigo[i].sprite);

        for (int j = 0; j < 2; j++) UnloadTexture(inimigo[i].spritesheet[j]);
    }

    for (int i = 0; i < numProjetilInimigo; i++) UnloadTexture(projetilInimigo[i].sprite);

    // Free
    free(nave.projetil);
    free(inimigo);
    free(projetilInimigo);

    if (nave.hp <= 0)
    {
        // GAME OVER
        gameOver();
    }
    else if (frames >= TEMPO_FASE * FPS)
    {
        // Continuar para segunda fase
        // terceiraFase();
    }
}

void primeiraFase()
{
    // Inicialização
    int frames = 0;
    Texture2D background = LoadTexture("../res/backgrounds/background_espaco.png");

    Nave nave;
    inicializarNave(&nave);

    int numInimigos = 0;
    Inimigo *inimigo = NULL;

    int numProjetilInimigo = 0;
    ProjetilInimigo *projetilInimigo = NULL;

    // Fade-in
    int play = 1;
    int transparency = 255;

    while (transparency >= 0 && play)
    {
        BeginDrawing();

            DrawStaticBackground(background);
            DrawTextureEx(nave.sprite, nave.posicao, 0, ESCALA1, WHITE);
            DrawRectangle(0, 0, 1000, 600, (Color) {0, 0, 0, transparency});

        EndDrawing();

        transparency -= 2;
        if (WindowShouldClose()) play = 0;
    }

    // Instruções
    char *text[3] = {"SETAS - MOVIMENTAR", "ESPACO - DISPARAR", "ENTER PARA INICIAR"};
    Font font = LoadFont("../res/fonts/alpha_beta.png");
    Vector2 position[3];

    for (int i = 0; i < 3; i++)
    {
        position[i].x = LARG_JANELA / 2 - MeasureTextEx(font, text[i], font.baseSize * 2, 4).x / 2;
        position[i].y = 60 + font.baseSize + 45 * i;
    }

    while (!IsKeyPressed(KEY_ENTER) && play)
    {
        // Atualização
        atualizarNave(&nave, frames);

        // Draw
        BeginDrawing();

            DrawStaticBackground(background);
            DrawShip(nave);
            DrawShipProjectile(nave);
            for (int i = 0; i < 3; i++) DrawTextEx(font, text[i], position[i], font.baseSize * 2, 4, RAYWHITE);
        
        EndDrawing();

        frames++;
        if (WindowShouldClose()) play = 0;
    }

    frames = 0;
    UnloadFont(font);

    while (nave.hp > 0 && frames < TEMPO_FASE * FPS && play)
    {
        // Atualização
        atualizarNave(&nave, frames);
        atualizarInimigos(&inimigo, &numInimigos, frames);
        atualizarProjetilInimigo(inimigo, numInimigos, nave, &projetilInimigo, &numProjetilInimigo, frames);
            
        // Draw
        BeginDrawing();
                
            DrawStaticBackground(background); 
                
            DrawShip(nave);
            DrawShipProjectile(nave);

            DrawEnemy(inimigo, numInimigos);
            DrawEnemyProjectile(projetilInimigo, numProjetilInimigo);
            
        EndDrawing();

        frames++;
        if (WindowShouldClose()) play = 0;
    }

    // Fade-out
    transparency = 0;

    while (transparency <= 255 && play)
    {
        atualizarNave(&nave, frames);

        BeginDrawing();

            DrawStaticBackground(background);
            DrawShip(nave);
            DrawShipProjectile(nave);
            DrawRectangle(0, 0, 1000, 600, (Color) {0, 0, 0, transparency});

        EndDrawing();

        frames++;
        transparency += 2;
        if (WindowShouldClose()) play = 0;
    }

    // Unload
    UnloadTexture(background);

    UnloadTexture(nave.sprite);
    for (int i = 0; i < 3; i++) UnloadTexture(nave.spritesheet[i]);

    for (int i = 0; i < 2; i++)
    {
        UnloadTexture(nave.propulsor[i].sprite);

        for (int j = 0; j < 4; j++) UnloadTexture(nave.propulsor[i].spritesheet[j]);
    }

    for (int i = 0; i < numInimigos; i++)
    {
        UnloadTexture(inimigo[i].sprite);

        for (int j = 0; j < 2; j++) UnloadTexture(inimigo[i].spritesheet[j]);
    }

    for (int i = 0; i < numProjetilInimigo; i++) UnloadTexture(projetilInimigo[i].sprite);

    // Free
    free(nave.projetil);
    free(inimigo);
    free(projetilInimigo);

    if (nave.hp <= 0)
    {
        // GAME OVER
        gameOver();
    }
    else if (frames >= TEMPO_FASE * FPS)
    {
        // Continuar para segunda fase
        segundaFase();
    }
}

void start()
{
    primeiraFase();
}