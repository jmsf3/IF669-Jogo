#include <stdio.h>
#include <stdlib.h>
#include "fases.h"
#include "../nave/nave.h"
#include "../efeitos/efeitos.h"
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
#define TEMPO_FASE 30 // segundos
#define N_GPTS_P_FASE 10

int score = 0;

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

void bossFight(int* play)
{
    char *text[3] = {
        "OH NAO!!! PARECE Q A OPEN.AI NAO GOSTOU DO ESTRAGO NOS GPTS!!!",
        "*UM SUPER GPT FOI ENVIADO PARA DESTRUIR A TERRA*",
        "PRESSIONE ENTER PARA IMPEDIR Q A TERRA SEJA DESTRUIDA."
    };

    Font font = LoadFont("../res/fonts/alpha_beta.png");
    Vector2 position[3];

    int totalWidth = 0;
    int centerX = LARG_JANELA / 2;  // Centro da janela
    int centerY = ALT_JANELA / 2; // Centro da janela em relacao ao eixo y

    for (int i = 0; i < 3; i++)
    {
        int textHeight = font.baseSize * 2; 
        totalWidth = MeasureTextEx(font, text[i], font.baseSize * 2, 4).x;
        position[i].x = centerX - totalWidth / 2;  // Centralizar o texto
        position[i].y = centerY - (textHeight * 1.5) + (i * textHeight);
    }

    while (!IsKeyPressed(KEY_ENTER) && *play)
    {
        BeginDrawing();

            ClearBackground(BLACK);
            for (int i = 0; i < 3; i++) DrawTextEx(font, text[i], position[i], font.baseSize * 2, 4, RAYWHITE);

        EndDrawing();

        if (WindowShouldClose()) *play = 0;
    }

    UnloadFont(font);
}

void gptIsDead()
{
    char *text[4] = {
        "MISSAO CUMPRIDA.",
        "",
        "VOCE DEFENDEU EFETIVAMENTE A TERRA DE UMA DESTRUICAO EM MASSA!",
        "TUDO ESTA DE VOLTA AOS CONFORMES!"
    };
    Font font = LoadFont("../res/fonts/alpha_beta.png");
    Vector2 position[4];

    int totalWidth = 0;
    int centerX = LARG_JANELA / 2;  // Centro da janela
    int centerY = ALT_JANELA / 2; // centro da janela em relacao ao eixo y

    for (int i = 0; i < 4; i++)
    {
        totalWidth = MeasureTextEx(font, text[i], font.baseSize * 2, 4).x;
        int textHeight = font.baseSize * 2; 
        position[i].x = centerX - totalWidth / 2;  // Centralizar o texto
        position[i].y = centerY - (textHeight * 1.5) + (i * textHeight);
    }

    while (!IsKeyPressed(KEY_ENTER))
    {
        BeginDrawing();
            ClearBackground(BLACK);
            for (int i = 0; i < 4; i++) DrawTextEx(font, text[i], position[i], font.baseSize * 2, 4, RAYWHITE);
        EndDrawing();
    }

    UnloadFont(font);
    youWon();
}

void gptKilledYou()
{
        char *text[5] = {
        "MORREU NA PRAIA.",
        "",
        "GRACAS A SUA INCOPETENCIA O PLANETA FOI DESTRUIDO",
        "TRIED SO HARD, GOT SO FAR, BUT IN THE END..",
        "OS GPTS VENCERAM."
    };
    Font font = LoadFont("../res/fonts/alpha_beta.png");
    Vector2 position[5];

    int totalWidth = 0;
    int centerX = LARG_JANELA / 2;  // Centro da janela
    int centerY = ALT_JANELA / 2; // centro da janela em relacao ao eixo y

    for (int i = 0; i < 5; i++)
    {
        totalWidth = MeasureTextEx(font, text[i], font.baseSize * 2, 4).x;
        int textHeight = font.baseSize * 2; 
        position[i].x = centerX - totalWidth / 2;  // Centralizar o texto
        position[i].y = centerY - (textHeight * 1.5) + (i * textHeight);
    }

    while (!IsKeyPressed(KEY_ENTER))
    {
        BeginDrawing();
            ClearBackground(BLACK);
            for (int i = 0; i < 5; i++) DrawTextEx(font, text[i], position[i], font.baseSize * 2, 4, RAYWHITE);
        EndDrawing();
    }

    UnloadFont(font);
    gameOver();
}

void goodEnding()
{
    char *text[4] = {
        "GOOD ENDING.",
        "",
        "VOCE EH TAO RUIM RESISTINDO QUE OS ALIENS DESISTIRAM DA INVASAO!",
        "TUDO TERMINA BEM, NINGUEM SE FERIU, TODOS ESTAO FELIZES."
    };
    Font font = LoadFont("../res/fonts/alpha_beta.png");
    Vector2 position[4];

    int totalWidth = 0;
    int centerX = LARG_JANELA / 2;  // Centro da janela
    int centerY = ALT_JANELA / 2; // centro da janela em relacao ao eixo y

    for (int i = 0; i < 4; i++)
    {
        totalWidth = MeasureTextEx(font, text[i], font.baseSize * 2, 4).x;
        int textHeight = font.baseSize * 2; 
        position[i].x = centerX - totalWidth / 2;  // Centralizar o texto
        position[i].y = centerY - (textHeight * 1.5) + (i * textHeight);
    }

    while (!IsKeyPressed(KEY_ENTER))
    {
        BeginDrawing();
            ClearBackground(BLACK);
            for (int i = 0; i < 4; i++) DrawTextEx(font, text[i], position[i], font.baseSize * 2, 4, RAYWHITE);
        EndDrawing();
    }

    UnloadFont(font);
    youWon();
}

void exterminationEnding()
{
        char *text[6] = {
        "EXTERMINATION ENDING.",
        "",
        "POIS EH, VOCE EXTERMINOU TODOS OS GPTS",
        "VOCE SE ORGULHA DISSO????",
        "NEM TUDO TERMINA BEM,",
        "A TERRA ESTA SEGURA, VOCE EXTERMINOU UM POVO."
    };
    Font font = LoadFont("../res/fonts/alpha_beta.png");
    Vector2 position[6];

    int totalWidth = 0;
    int centerX = LARG_JANELA / 2;  // Centro da janela
    int centerY = ALT_JANELA / 2; // centro da janela em relacao ao eixo y

    for (int i = 0; i < 6; i++)
    {
        totalWidth = MeasureTextEx(font, text[i], font.baseSize * 2, 4).x;
        int textHeight = font.baseSize * 2; 
        position[i].x = centerX - totalWidth / 2;  // Centralizar o texto
        position[i].y = centerY - (textHeight * 1.5) + (i * textHeight);
    }

    while (!IsKeyPressed(KEY_ENTER))
    {
        BeginDrawing();
            ClearBackground(BLACK);
            for (int i = 0; i < 6; i++) DrawTextEx(font, text[i], position[i], font.baseSize * 2, 4, RAYWHITE);
        EndDrawing();
    }

    UnloadFont(font);
    youWon();
}

void terceiraFase()
{
    // Inicialização
    int frames = 0;
    Texture2D background = LoadTexture("../res/backgrounds/background_terra.png");

    Music music = LoadMusicStream("../res/sounds/musica_fase.ogg");
    PlayMusicStream(music);

    Nave nave;
    inicializarNave(&nave, score);
    nave.posicao.y = ALT_JANELA;

    Boss boss;
    inicializarBoss(&boss);

    Inimigo *inimigo = NULL;

    int numProjetilBoss = 0;
    ProjetilInimigo *projetilBoss = NULL;

    int numExplosoes = 0;
    Explosao *explosoes = NULL;

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
            DrawTextureEx(boss.sprite, boss.posicao, 0, 10, WHITE);
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
        atualizarNave(&nave, frames);
        atualizarBoss(&boss, &projetilBoss, &numProjetilBoss, frames);
        atualizarProjetilBoss(boss, &projetilBoss, &numProjetilBoss, nave, frames);

        // Colisões
        checarColisoesBoss(&nave, &boss, &projetilBoss, &numProjetilBoss);

        // Draw
        BeginDrawing();
        BeginDrawing();
                
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

    // Fade-out
    transparency = 0;
    if (nave.hp == 0)
    {
        Sound explosao = LoadSound("../res/sounds/explosao.ogg");
        PlaySound(explosao);
        inicializarExplosao(nave.posicao, &numExplosoes, &explosoes, 1);
    }

    while (transparency <= 255 && play)
    {
        // Atualização
        SetMusicVolume(music, volume);
        UpdateMusicStream(music);
        atualizarNave(&nave, frames);
        atualizarExplosao(&numExplosoes, &explosoes);
        atualizarBoss(&boss, &projetilBoss, &numProjetilBoss, frames);

        // Draw
        BeginDrawing();

            DrawStaticBackground(background); 
            
            DrawBoss(boss);    
            DrawShip(nave);

            DrawShipProjectile(nave);
            DrawEnemyProjectile(projetilBoss, numProjetilBoss);
            
            DrawExplosoes(explosoes, numExplosoes);
            DrawRectangle(0, 0, 1000, 600, (Color) {0, 0, 0, transparency});

        EndDrawing();

        frames++;
        transparency += 3;
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
    
    for (int i = 0; i < numProjetilBoss; i++) UnloadTexture(projetilBoss[i].sprite);

    // Free
    free(projetilBoss);
    free(nave.projetil);

    if (nave.hp == 0 && play)
    {
        // GAME OVER
        gptKilledYou();
    }
    else if (frames >= TEMPO_FASE * FPS && play)
    {
        gptIsDead();
    }
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
    inicializarNave(&nave, score);

    int numInimigos = 0;
    Inimigo *inimigo = NULL;

    int numProjetilInimigo = 0;
    ProjetilInimigo *projetilInimigo = NULL;

    int numExplosoes = 0;
    Explosao *explosoes = NULL;

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
        transparency -= 3;
        volume += 1.0 / 255;
        if (WindowShouldClose()) play = 0;
    }

    // Dar reset nos frames
    frames = 0;

    // Iniciar fase
    while (nave.hp > 0 && frames < TEMPO_FASE * FPS && play)
    {
        // Atualização
        UpdateMusicStream(music);
        atualizarNave(&nave, frames);
        atualizarBackground(&divisao);
        atualizarExplosao(&numExplosoes, &explosoes);
        atualizarInimigos(&inimigo, &numInimigos, frames);
        atualizarProjetilInimigo(inimigo, numInimigos, nave, &projetilInimigo, &numProjetilInimigo, frames);

        // Colisões
        checarColisoes(&nave, &inimigo, &projetilInimigo, &numInimigos, &numProjetilInimigo, &explosoes, &numExplosoes);
            
        // Draw
        BeginDrawing();
                
            DrawScrollingBackground(background, divisao); 

            DrawEnemy(inimigo, numInimigos);    
            DrawShip(nave);
            
            DrawShipProjectile(nave);
            DrawEnemyProjectile(projetilInimigo, numProjetilInimigo);

            DrawExplosoes(explosoes, numExplosoes);
            
        EndDrawing();

        frames++;
        if (WindowShouldClose()) play = 0;
    }

    // Fade-out
    transparency = 0;
    if (nave.hp == 0)
    {
        Sound explosao = LoadSound("../res/sounds/explosao.ogg");
        PlaySound(explosao);
        inicializarExplosao(nave.posicao, &numExplosoes, &explosoes, 1);
    }

    while (transparency <= 255 && play)
    {
        // Atualização
        SetMusicVolume(music, volume);
        UpdateMusicStream(music);
        atualizarNave(&nave, frames);
        atualizarBackground(&divisao);
        atualizarExplosao(&numExplosoes, &explosoes);
        atualizarInimigos(&inimigo, &numInimigos, frames);
        atualizarProjetilInimigo(inimigo, numInimigos, nave, &projetilInimigo, &numProjetilInimigo, frames);

        // Draw
        BeginDrawing();

            DrawScrollingBackground(background, divisao); 
            
            DrawEnemy(inimigo, numInimigos);    
            DrawShip(nave);

            DrawShipProjectile(nave);
            DrawEnemyProjectile(projetilInimigo, numProjetilInimigo);
            
            DrawExplosoes(explosoes, numExplosoes);
            DrawRectangle(0, 0, 1000, 600, (Color) {0, 0, 0, transparency});

        EndDrawing();

        frames++;
        transparency += 3;
        volume -= 1.0 / 255;
        if (WindowShouldClose()) play = 0;
    }

    // Unload
    UnloadTexture(background);
    UnloadMusicStream(music);
    
    UnloadFont(nave.font);
    UnloadSound(nave.hit);
    UnloadSound(nave.disparo);
    UnloadTexture(nave.sprite);
    UnloadTexture(nave.spriteCoracao);
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
    free(explosoes);

    if (nave.hp == 0 && play)
    {
        // GAME OVER
        score = 0;
        gameOver();
    }
    else if (frames >= TEMPO_FASE * FPS && play)
    {
        // Continuar para terceira fase
        score = nave.score;
        // faseCompleta(&play);
        bossFight(&play);
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
    inicializarNave(&nave, score);

    int numInimigos = 0;
    Inimigo *inimigo = NULL;

    int numProjetilInimigo = 0;
    ProjetilInimigo *projetilInimigo = NULL;

    int numExplosoes = 0;
    Explosao *explosoes = NULL;

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

        transparency -= 3;
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
        atualizarExplosao(&numExplosoes, &explosoes);
        atualizarInimigos(&inimigo, &numInimigos, frames);
        atualizarProjetilInimigo(inimigo, numInimigos, nave, &projetilInimigo, &numProjetilInimigo, frames);
 
        // Colisões
        checarColisoes(&nave, &inimigo, &projetilInimigo, &numInimigos, &numProjetilInimigo, &explosoes, &numExplosoes);
            
        // Draw
        BeginDrawing();
                
            DrawStaticBackground(background); 
                
            DrawEnemy(inimigo, numInimigos);    
            DrawShip(nave);
            
            DrawShipProjectile(nave);
            DrawEnemyProjectile(projetilInimigo, numProjetilInimigo);

            DrawExplosoes(explosoes, numExplosoes);
            
        EndDrawing();

        frames++;
        if (WindowShouldClose()) play = 0;
    }

    // Fade-out
    transparency = 0;
    if (nave.hp == 0)
    {
        Sound explosao = LoadSound("../res/sounds/explosao.ogg");
        PlaySound(explosao);
        inicializarExplosao(nave.posicao, &numExplosoes, &explosoes, 1);
    }

    while (transparency <= 255 && play)
    {
        // Atualização
        SetMusicVolume(music, volume);
        UpdateMusicStream(music);
        atualizarNave(&nave, frames);
        atualizarExplosao(&numExplosoes, &explosoes);
        atualizarInimigos(&inimigo, &numInimigos, frames);
        atualizarProjetilInimigo(inimigo, numInimigos, nave, &projetilInimigo, &numProjetilInimigo, frames);

        // Draw
        BeginDrawing();

            DrawStaticBackground(background);

            DrawEnemy(inimigo, numInimigos);    
            DrawShip(nave);
            
            DrawShipProjectile(nave);
            DrawEnemyProjectile(projetilInimigo, numProjetilInimigo);

            DrawExplosoes(explosoes, numExplosoes);
            DrawRectangle(0, 0, 1000, 600, (Color) {0, 0, 0, transparency});

        EndDrawing();

        frames++;
        transparency += 3;
        volume -= 1.0 / 255;
        if (WindowShouldClose()) play = 0;
    }

    // Unload
    UnloadTexture(background);
    UnloadMusicStream(music);

    UnloadFont(nave.font);
    UnloadSound(nave.hit);
    UnloadSound(nave.disparo);
    UnloadTexture(nave.sprite);
    UnloadTexture(nave.spriteCoracao);
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
    free(explosoes);

    if (nave.hp == 0 && play)
    {
        // GAME OVER
        score = 0;
        gameOver();
    }
    else if (frames >= TEMPO_FASE * FPS && play)
    {
        // Continuar para segunda fase
        score = nave.score;
        faseCompleta(&play);
        if (play) segundaFase();
    }
}

void start()
{
    segundaFase();
}