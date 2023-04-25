#include "menu.h"
#include "../fases/fases.h"
#include "../backgrounds/backgrounds.h"
#include "../../dep/include/raylib.h"
#define FPS
#define ESCALA1 4
#define ESCALA2 6 
#define ALT_JANELA 600
#define LARG_JANELA 1000
#define ALT_START 18 * ESCALA1
#define LARG_START 52 * ESCALA1
#define ALT_SAIR 18 * ESCALA1
#define LARG_SAIR 39 * ESCALA1
#define ALT_LOGO 44 * ESCALA2
#define LARG_LOGO 82 * ESCALA2
 
int mouseStart()
{
    return GetMouseX() > LARG_JANELA / 2 - LARG_START / 2 && GetMouseX() < LARG_JANELA / 2 + LARG_START / 2 && GetMouseY() > ALT_JANELA - ALT_START - 150 && GetMouseY() < ALT_JANELA - 150;
}

int mouseSair()
{
    return GetMouseX() > LARG_JANELA / 2 - LARG_SAIR / 2 && GetMouseX() < LARG_JANELA / 2 + LARG_SAIR / 2 && GetMouseY() > ALT_JANELA - ALT_SAIR - 50 && GetMouseY() < ALT_JANELA - 50;
}

int cliqueStart()
{
    return mouseStart() && IsMouseButtonDown(0);
}

int cliqueSair()
{
    return mouseSair() && IsMouseButtonDown(0);
}

void DrawStart(Texture2D *start)
{
    Vector2 posicao = {LARG_JANELA / 2 - LARG_START / 2, ALT_JANELA - ALT_START - 150};

    if (cliqueStart())
        DrawTextureEx(start[2], posicao, 0, ESCALA1, WHITE);
    else if (mouseStart())
        DrawTextureEx(start[1], posicao, 0, ESCALA1, WHITE);
    else
        DrawTextureEx(start[0], posicao, 0, ESCALA1, WHITE);
}

void DrawExit(Texture2D *sair)
{
    Vector2 posicao = {LARG_JANELA / 2 - LARG_SAIR / 2, ALT_JANELA - ALT_SAIR - 50};

    if (cliqueSair())
        DrawTextureEx(sair[2], posicao, 0, ESCALA1, WHITE);
    else if (mouseSair())
        DrawTextureEx(sair[1], posicao, 0, ESCALA1, WHITE);
    else
        DrawTextureEx(sair[0], posicao, 0, ESCALA1, WHITE);
}

void DrawLogo(Texture2D logo)
{
    Vector2 posicao = {LARG_JANELA / 2 - LARG_LOGO / 2, ALT_JANELA - ALT_LOGO - 265};
    DrawTextureEx(logo, posicao, 0, ESCALA2, WHITE);
}

void menu(int *play)
{
    // Inicialização
    Music music = LoadMusicStream("../res/sounds/musica_menu.ogg");
    PlayMusicStream(music);

    Texture2D logo = LoadTexture("../res/interface/logo_acm.png");
    Texture2D background = LoadTexture("../res/backgrounds/background_espaco.png");

    Image imgStart = LoadImage("../res/interface/botao_start.png");
    Texture2D start[3] = {LoadTextureFromImage(ImageFromImage(imgStart, (Rectangle) {0, 0, 52, 18})),
                          LoadTextureFromImage(ImageFromImage(imgStart, (Rectangle) {52, 0, 52, 18})),
                          LoadTextureFromImage(ImageFromImage(imgStart, (Rectangle) {104, 0, 52, 18}))};

    Image imgSair = LoadImage("../res/interface/botao_sair.png");
    Texture2D sair[3] = {LoadTextureFromImage(ImageFromImage(imgSair, (Rectangle) {0, 0, 39, 18})),
                         LoadTextureFromImage(ImageFromImage(imgSair, (Rectangle) {39, 0, 39, 18})),
                         LoadTextureFromImage(ImageFromImage(imgSair, (Rectangle) {78, 0, 39, 18}))}; 

    while (!cliqueStart() && !cliqueSair() && !WindowShouldClose())
    {
        // Atualização
        UpdateMusicStream(music);

        // Draw
        BeginDrawing();

            DrawStaticBackground(background);
            DrawLogo(logo);
            DrawStart(start);
            DrawExit(sair);

        EndDrawing();
    }

    if (cliqueStart()) 
    {
        *play = 1;

        // Fade-out
        float volume = 1.0;
        int transparency = 0;

        while (transparency <= 255 && *play)
        {
            // Atualização
            SetMusicVolume(music, volume);
            UpdateMusicStream(music);

            // Draw
            BeginDrawing();

                DrawRectangle(0, 0, 1000, 600, (Color) {0, 0, 0, transparency});
                
            EndDrawing();
            
            transparency += 3;
            volume -= 1.0 / 255;
            if (WindowShouldClose()) *play = 0;
        }
    }

    // Unload
    UnloadMusicStream(music);

    UnloadTexture(logo);
    UnloadTexture(background);

    UnloadImage(imgStart);
    for (int i = 0; i < 3; i++) UnloadTexture(start[i]);

    UnloadImage(imgSair);
    for (int i = 0; i < 3; i++) UnloadTexture(sair[i]);
}