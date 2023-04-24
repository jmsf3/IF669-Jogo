#include <stdio.h>
#include <stdlib.h>
#include "fases.h"
#include "../nave/nave.h"
#include "../inimigos/inimigos.h"
#include "../colisoes/colisoes.h"
#include "../backgrounds/backgrounds.h"
#include "../../dep/include/raylib.h"
#define FPS 60
#define ESCALA1 5
#define ESCALA2 6
#define ALT_NAVE 8 * ESCALA1
#define LARG_NAVE 8 * ESCALA1
#define VEL_NAVE 1
#define ALT_JANELA 600
#define LARG_JANELA 1000
#define ALT_YW 27 * ESCALA2
#define LARG_YW 43 * ESCALA2
#define ALT_GO 28 * ESCALA2
#define LARG_GO 44 * ESCALA2
#define TEMPO_FASE 60 // segundos

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

void faseCompleta(int *play)
{
    char *text[3] = {"FASE COMPLETA!", "PRESSIONE ENTER PARA CONTINUAR"};
    Font font = LoadFont("../res/fonts/alpha_beta.png");
    Vector2 position[2];

    for (int i = 0; i < 2; i++)
    {
        position[i].x = LARG_JANELA / 2 - MeasureTextEx(font, text[i], font.baseSize * 2, 4).x / 2;
        position[i].y = ALT_JANELA / 2 - font.baseSize + 45 * i;
    }

    while (!IsKeyPressed(KEY_ENTER) && *play)
    {
        BeginDrawing();

            ClearBackground(BLACK);
            for (int i = 0; i < 2; i++) DrawTextEx(font, text[i], position[i], font.baseSize * 2, 4, RAYWHITE);

        EndDrawing();

        if (WindowShouldClose()) *play = 0;
    }
    
    UnloadFont(font);
}

void terceiraFase()
{
    // Inicialização
    int frames = 0;
    Texture2D background = LoadTexture("../res/backgrounds/background_terra.png");

    Music music = LoadMusicStream("../res/sounds/musica_fase.ogg");
    PlayMusicStream(music);

    Nave nave;
    inicializarNave(&nave);
    nave.posicao.y = ALT_JANELA;

    Boss boss;
    inicializarBoss(&boss);

    int numProjetilBoss = 0;
    ProjetilInimigo *projetilBoss = NULL;

    // Fade-in / Cutscene
    int play = 1;
    float volume = 0.0;
    int transparency = 255;

    while (transparency >= 0 && play)
    {
        // Atualização
        SetMusicVolume(music, volume);
        UpdateMusicStream(music);

        atualizarPropulsor(&nave, frames, 'm');
        
        // Draw
        BeginDrawing();

            DrawStaticBackground(background);
            DrawShip(nave);
            DrawBoss(boss);
            DrawRectangle(0, 0, 1000, 600, (Color) {0, 0, 0, transparency});

        EndDrawing();

        frames++;
        transparency -= 2;
        volume += 1.0 / 255;
        if (nave.posicao.y > ALT_JANELA - 2 * ALT_NAVE) nave.posicao.y -= VEL_NAVE;
        if (WindowShouldClose()) play = 0;
    }

    // Reset nos frames
    frames = 0;

    // Iniciar fase
    while (nave.hp > 0 && boss.hp > 0 && play)
    {
        // Atualização
        UpdateMusicStream(music);
        atualizarNave(&nave, frames);
        atualizarBoss(&boss, &projetilBoss, &numProjetilBoss, frames);
        atualizarProjetilBoss(&projetilBoss, &numProjetilBoss);

        // Colisões
             
        // Draw
        BeginDrawing();
                
            DrawStaticBackground(background); 
                
            DrawShip(nave);
            DrawShipProjectile(nave);

            DrawBoss(boss);
            DrawEnemyProjectile(projetilBoss, numProjetilBoss);
            
        EndDrawing();

        frames++;
        if (WindowShouldClose()) play = 0;
    }

    // Unload
    UnloadTexture(background);
    UnloadMusicStream(music);

    UnloadSound(nave.hit);
    UnloadSound(nave.disparo);
    UnloadTexture(nave.sprite);
    for (int i = 0; i < 3; i++) UnloadTexture(nave.spritesheet[i]);

    for (int i = 0; i < 2; i++)
    {
        UnloadTexture(nave.propulsor[i].sprite);

        for (int j = 0; j < 4; j++) UnloadTexture(nave.propulsor[i].spritesheet[j]);
    }
    
    for (int i = 0; i < numProjetilBoss; i++) UnloadTexture(projetilBoss[i].sprite);

    // Free
    free(projetilBoss);
    free(nave.projetil);
}

void segundaFase()
{
    // Inicialização
    int frames = 0;
    int divisao = 0;
    Texture2D background = LoadTexture("../res/backgrounds/background_espaco.png");

    Music music = LoadMusicStream("../res/sounds/musica_fase.ogg");
    PlayMusicStream(music);

    Nave nave;
    inicializarNave(&nave);

    int numInimigos = 0;
    Inimigo *inimigo = NULL;

    int numProjetilInimigo = 0;
    ProjetilInimigo *projetilInimigo = NULL;

    // Fade-in
    int play = 1;
    float volume = 0.0;
    int transparency = 255;

    while (transparency >= 0 && play)
    {
        // Atualização
        SetMusicVolume(music, volume);
        UpdateMusicStream(music);
        atualizarPropulsor(&nave, frames, 'm');

        // Draw
        BeginDrawing();

            DrawStaticBackground(background);
            DrawShip(nave);
            DrawRectangle(0, 0, 1000, 600, (Color) {0, 0, 0, transparency});

        EndDrawing();

        frames++;
        transparency -= 2;
        volume += 1.0 / 255;
        if (WindowShouldClose()) play = 0;
    }

    // Reset dos frames
    frames = 0;

    // Iniciar fase
    while (nave.hp > 0 && frames < TEMPO_FASE * FPS && play)
    {
        // Atualização
        UpdateMusicStream(music);
        atualizarNave(&nave, frames);
        atualizarBackground(&divisao);
        atualizarInimigos(&inimigo, &numInimigos, frames);
        atualizarProjetilInimigo(inimigo, numInimigos, nave, &projetilInimigo, &numProjetilInimigo, frames);

        // Colisões
        checarColisoes(&nave, &inimigo, &projetilInimigo, &numInimigos, &numProjetilInimigo);
            
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
        // Atualização
        SetMusicVolume(music, volume);
        UpdateMusicStream(music);
        atualizarNave(&nave, frames);
        atualizarBackground(&divisao);

        // Draw
        BeginDrawing();

            DrawScrollingBackground(background, divisao); 
            DrawShip(nave);
            DrawShipProjectile(nave);
            DrawRectangle(0, 0, 1000, 600, (Color) {0, 0, 0, transparency});

        EndDrawing();

        frames++;
        transparency += 2;
        volume -= 1.0 / 255;
        if (WindowShouldClose()) play = 0;
    }

    // Unload
    UnloadTexture(background);
    UnloadMusicStream(music);

    UnloadSound(nave.hit);
    UnloadSound(nave.disparo);
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
        UnloadSound(inimigo[i].disparo);
        UnloadSound(inimigo[i].morte);

        for (int j = 0; j < 2; j++) UnloadTexture(inimigo[i].spritesheet[j]);
    }

    for (int i = 0; i < numProjetilInimigo; i++) UnloadTexture(projetilInimigo[i].sprite);

    // Free
    free(nave.projetil);
    free(inimigo);
    free(projetilInimigo);

    if (nave.hp == 0 && play)
    {
        // GAME OVER
        gameOver();
    }
    else if (frames >= TEMPO_FASE * FPS && play)
    {
        // Continuar para terceira fase
        faseCompleta(&play);
        if (play) terceiraFase();
    }
}

void primeiraFase()
{
    // Inicialização
    int frames = 0;
    Texture2D background = LoadTexture("../res/backgrounds/background_espaco.png");

    Music music = LoadMusicStream("../res/sounds/musica_fase.ogg");
    PlayMusicStream(music);

    Nave nave;
    inicializarNave(&nave);

    int numInimigos = 0;
    Inimigo *inimigo = NULL;

    int numProjetilInimigo = 0;
    ProjetilInimigo *projetilInimigo = NULL;

    // Fade-in
    int play = 1;
    float volume = 0.0;
    int transparency = 255;

    while (transparency >= 0 && play)
    {
        // Atualização
        SetMusicVolume(music, volume);
        UpdateMusicStream(music);
        
        // Draw
        BeginDrawing();

            DrawStaticBackground(background);
            DrawTextureEx(nave.sprite, nave.posicao, 0, ESCALA1, WHITE);
            DrawRectangle(0, 0, 1000, 600, (Color) {0, 0, 0, transparency});

        EndDrawing();

        transparency -= 2;
        volume += 1.0 / 255;
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
        UpdateMusicStream(music);
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

    // Dar reset nos frames
    frames = 0;
    UnloadFont(font);

    // Iniciar fase
    while (nave.hp > 0 && frames < TEMPO_FASE * FPS && play)
    {
        // Atualização
        UpdateMusicStream(music);
        atualizarNave(&nave, frames);
        atualizarInimigos(&inimigo, &numInimigos, frames);
        atualizarProjetilInimigo(inimigo, numInimigos, nave, &projetilInimigo, &numProjetilInimigo, frames);
 
        // Colisões
        checarColisoes(&nave, &inimigo, &projetilInimigo, &numInimigos, &numProjetilInimigo);
            
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
        // Atualização
        SetMusicVolume(music, volume);
        UpdateMusicStream(music);
        atualizarNave(&nave, frames);

        // Draw
        BeginDrawing();

            DrawStaticBackground(background);
            DrawShip(nave);
            DrawShipProjectile(nave);
            DrawRectangle(0, 0, 1000, 600, (Color) {0, 0, 0, transparency});

        EndDrawing();

        frames++;
        transparency += 2;
        volume -= 1.0 / 255;
        if (WindowShouldClose()) play = 0;
    }

    // Unload
    UnloadTexture(background);
    UnloadMusicStream(music);
    
    UnloadSound(nave.hit);
    UnloadSound(nave.disparo);
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
        UnloadSound(inimigo[i].disparo);
        UnloadSound(inimigo[i].morte);

        for (int j = 0; j < 2; j++) UnloadTexture(inimigo[i].spritesheet[j]);
    }

    for (int i = 0; i < numProjetilInimigo; i++) UnloadTexture(projetilInimigo[i].sprite);

    // Free
    free(nave.projetil);
    free(inimigo);
    free(projetilInimigo);

    if (nave.hp == 0 && play)
    {
        // GAME OVER
        gameOver();
    }
    else if (frames >= TEMPO_FASE * FPS && play)
    {
        // Continuar para segunda fase
        faseCompleta(&play);
        if (play) segundaFase();
    }
}

void start()
{
    primeiraFase();
}