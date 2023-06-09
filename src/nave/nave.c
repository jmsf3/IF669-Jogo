#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "nave.h"
#include "../../dep/include/raylib.h"
#define FPS 60
#define ESCALA 5
#define ALT_NAVE 8 * ESCALA
#define LARG_NAVE 8 * ESCALA
#define ALT_PILOTO 8 * ESCALA
#define LARG_PILOTO 8 * ESCALA 
#define ALT_PROJETIL 10 * ESCALA 
#define LARG_PROJETIL 3 * ESCALA 
#define ALT_PROPULSOR 3 * ESCALA
#define LARG_PROPULSOR 1 * ESCALA
#define ALT_JANELA 600 
#define LARG_JANELA 1000 
#define VEL_NAVE 4
#define VEL_PROJETIL 5 
#define INTERVALO_DISPARO 0.25 // Segundos

Texture2D spriteCoracao;
Texture2D spriteProjetil;
Texture2D spritesheetNave[3];
Texture2D spritesheetPiloto[5];
Texture2D spritesheetPropulsor[4];

Sound disparoNave;

Font alphaBeta;

void loadNave()
{
    // Sprites da nave
    Image img0 = LoadImage("../res/nave/nave.png");

    for (int i = 0; i < 3; i++)
    {
        Image spriteNave = ImageFromImage(img0, (Rectangle) {i * 8, 0, 8, 8});
        spritesheetNave[i] = LoadTextureFromImage(spriteNave);
        UnloadImage(spriteNave);
    }

    UnloadImage(img0);

    // Sprites do propulsor
    Image img1 = LoadImage("../res/nave/propulsores.png");

    for (int i = 0; i < 4; i++)
    {

        Image spritePropulsor = ImageFromImage(img1, (Rectangle) {i * 1, 0, 1, 3});
        spritesheetPropulsor[i] = LoadTextureFromImage(spritePropulsor);
        UnloadImage(spritePropulsor);
    }

    UnloadImage(img1);

    // Sprites do piloto
    Image img2 = LoadImage("../res/nave/piloto.png");

    for (int i = 0; i < 5; i++) 
    {
        Image spritePiloto = ImageFromImage(img2,  (Rectangle) {i * 8, 0, 8, 8});
        spritesheetPiloto[i] = LoadTextureFromImage(spritePiloto);
        UnloadImage(spritePiloto);
    }

    UnloadImage(img2);

    // Sprite do projétil
    spriteProjetil = LoadTexture("../res/nave/projetil_nave.png");

    // Sprite do coração
    spriteCoracao = LoadTexture("../res/interface/coracao.png");

    // Som de disparo
    disparoNave = LoadSound("../res/sounds/disparo_nave.ogg");

    // Fonte
    alphaBeta = LoadFont("../res/fonts/alpha_beta.png");
}

void unloadNave()
{
    // Sprites da nave
    for (int i = 0; i < 3; i++)
    {
        UnloadTexture(spritesheetNave[i]);
    }

    // Sprites do propulsor
    for (int i = 0; i < 4; i++)
    {
        UnloadTexture(spritesheetPropulsor[i]);
    }

    // Sprites do piloto
    for (int i = 0; i < 5; i++) 
    {
        UnloadTexture(spritesheetPiloto[i]);
    }

    // Sprite do projétil
    UnloadTexture(spriteProjetil);

    // Sprite do coração
    UnloadTexture(spriteCoracao);

    // Som de disparo
    UnloadSound(disparoNave);

    // Fonte
    UnloadFont(alphaBeta);
}

void inicializarPiloto(Nave *nave)
{
    nave->spritePiloto = spritesheetPiloto[0];
}

void atualizarPiloto(Nave *nave, int frames)
{
    // Animação
    for (int i = 0; i < 5; i ++)
    {        
        if (frames % (5 * (FPS / 5)) == i * (FPS / 5))
        {
            nave->spritePiloto = spritesheetPiloto[i];
        }
    }
}

void inicializarPropulsor(Propulsor *propulsor)
{
    for (int i = 0; i < 2; i++)
    {
        propulsor[i].sprite = spritesheetPropulsor[0];
    }
}

void atualizarPropulsor(Nave *nave, int frames, char spriteNave)
{
    // Animação
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 4; j ++)
        {        
            if (frames % (4 * (FPS / 10)) == j * (FPS / 10))
            {
                nave->propulsor[i].sprite = spritesheetPropulsor[j];
            }
        }
    }

    // Posição
    if (spriteNave == 'l')
    {
        nave->propulsor[0].posicao.x = nave->posicao.x + 2 * ESCALA;
        nave->propulsor[1].posicao.x = nave->posicao.x + 4 * ESCALA;
    }
    else if (spriteNave == 'r')
    {
        nave->propulsor[0].posicao.x = nave->posicao.x + 3 * ESCALA;
        nave->propulsor[1].posicao.x = nave->posicao.x + 5 * ESCALA;
    }
    else
    {
        nave->propulsor[0].posicao.x = nave->posicao.x + 2 * ESCALA;
        nave->propulsor[1].posicao.x = nave->posicao.x + 5 * ESCALA;
    }

    nave->propulsor[0].posicao.y = nave->propulsor[1].posicao.y = nave->posicao.y + ALT_NAVE;
}

void inicializarProjetilNave(Nave *nave)
{
    for (int i = 0; i < 2; i++)
    {
        nave->projetil[nave->numProjetil + i].tDisparo = GetTime();
        nave->projetil[nave->numProjetil + i].sprite = spriteProjetil;
        nave->projetil[nave->numProjetil + i].posicao = (Vector2) {nave->posicao.x + 5 * ESCALA * i, nave->posicao.y - 2 * ESCALA};
    } 
}

void atualizarProjetilNave(Nave *nave)
{
    // Disparar
    if (nave->hp > 0 && IsKeyPressed(KEY_SPACE))
    {
        // Calcular o intervalo de tempo percorrido desde o último disparo
        double dt;
        
        if (nave->numProjetil == 0)
        {
            dt = INFINITY;
        }
        else
        {
            int i = nave->numProjetil - 1;
            dt = GetTime() - nave->projetil[i].tDisparo;
        }
        
        // Se o disparo for realizado
        if (dt > INTERVALO_DISPARO)
        {
            // Efeito sonoro
            PlaySound(disparoNave);

            ProjetilNave *aux = (ProjetilNave *) realloc(nave->projetil, (nave->numProjetil + 2) * sizeof(ProjetilNave));

            if (aux == NULL)
            {
                printf("Erro ao alocar a memória.\n");
                free(nave->projetil);
                exit(1);
            }

            nave->projetil = aux;
            inicializarProjetilNave(nave);

            nave->numProjetil += 2;
        }
    }

    // Movimentação
    for (int i = 0; i < nave->numProjetil; i++)  
    {   
        nave->projetil[i].posicao.y -= VEL_PROJETIL;
    }

    // Apagar projéteis que estão fora da tela
    for (int i = 0; i < nave->numProjetil; i++)  
    {
        if (nave->projetil[i].posicao.y <= -ALT_PROJETIL)
        {            
            for (int j = i; j < nave->numProjetil - 1; j++)
            {
                nave->projetil[j] = nave->projetil[j + 1];
            }

            if (nave->numProjetil > 1)
            {
                ProjetilNave *aux = (ProjetilNave *) realloc(nave->projetil, (nave->numProjetil - 1) * sizeof(ProjetilNave));

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

void inicializarNave(Nave *nave, int score)
{
    inicializarPropulsor(nave->propulsor);
    inicializarPiloto(nave);

    nave->posicao = (Vector2) {(LARG_JANELA - LARG_NAVE) / 2, ALT_JANELA - 2 * ALT_NAVE};
    nave->spriteNave = spritesheetNave[1];

    nave->numProjetil = 0;
    nave->projetil = NULL;    

    nave->tInvencivel = GetTime();
    nave->score = score;
    nave->hp = 3;
}

void atualizarNave(Nave *nave, int frames)
{
    char spriteNave;
    
    // Animação da nave
    if (IsKeyDown(KEY_LEFT))
    {
        nave->spriteNave = spritesheetNave[0];
        spriteNave = 'l';
    }
    else if (IsKeyDown(KEY_RIGHT))
    {
        nave->spriteNave = spritesheetNave[2];
        spriteNave = 'r';
    }
    else 
    {
        nave->spriteNave = spritesheetNave[1];
        spriteNave = 'm';
    }

    // Movimentação
    if (IsKeyDown(KEY_LEFT) && nave->posicao.x > 0) 
        nave->posicao.x -= VEL_NAVE;
    if (IsKeyDown(KEY_RIGHT) && nave->posicao.x < LARG_JANELA - LARG_NAVE)
        nave->posicao.x += VEL_NAVE;
    if (IsKeyDown(KEY_UP) && nave->posicao.y > 0)
        nave->posicao.y -= VEL_NAVE;
    if (IsKeyDown(KEY_DOWN) && nave->posicao.y < ALT_JANELA - ALT_NAVE)
        nave->posicao.y += VEL_NAVE;
    
     // Animação dos propulsores 
    atualizarPropulsor(nave, frames, spriteNave);
    atualizarPiloto(nave, frames);

    // Projéteis
    atualizarProjetilNave(nave);
}

void DrawShip(Nave nave)
{
    if (nave.hp > 0)
    {
        // Nave
        DrawTextureEx(nave.spriteNave, nave.posicao, 0, ESCALA, WHITE);

        // Propulsores da nave
        for (int i = 0; i < 2; i++)
        {
            DrawTextureEx(nave.propulsor[i].sprite, nave.propulsor[i].posicao, 0, ESCALA, WHITE);
        }

        // Piloto
        DrawTextureEx(nave.spritePiloto, (Vector2) {LARG_JANELA - 10 * ESCALA , ALT_JANELA - 10 * ESCALA}, 0, ESCALA, WHITE);
    }
    
    // Vidas
    for (int i = 0; i < nave.hp; i++)
    {
        DrawTextureEx(spriteCoracao, (Vector2) {10 + 8 * ESCALA * i, ALT_JANELA - 8 * ESCALA}, 0, ESCALA, WHITE);
    }

    // Score
    DrawTextEx(alphaBeta, TextFormat("SCORE: %05d", nave.score), (Vector2) {10, 10}, alphaBeta.baseSize * 2, 4, WHITE);
}

void DrawShipProjectile(Nave nave)
{
    for (int i = 0; i < nave.numProjetil; i++)
    {
        DrawTextureEx(nave.projetil[i].sprite, nave.projetil[i].posicao, 0, ESCALA, WHITE); 
    }
}
