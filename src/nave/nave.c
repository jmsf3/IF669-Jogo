#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "nave.h"
#include "../../dep/include/raylib.h"
#define FPS 60
#define ESCALA 5
#define ALT_NAVE 8 * ESCALA
#define LARG_NAVE 8 * ESCALA 
#define ALT_PROJETIL 10 * ESCALA 
#define LARG_PROJETIL 3 * ESCALA 
#define ALT_PROPULSOR 3 * ESCALA
#define LARG_PROPULSOR 1 * ESCALA
#define ALT_JANELA 600 
#define LARG_JANELA 1000 
#define VEL_NAVE 4
#define VEL_PROJETIL 5 
#define INTERVALO_DISPARO 0.25

void inicializarPropulsor(Propulsor *propulsor)
{
    Image img = LoadImage("../res/nave/propulsores.png");

    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            Image sprite = ImageFromImage(img, (Rectangle) {j, 0, 1, 3});
            propulsor[i].spritesheet[j] = LoadTextureFromImage(sprite);
            UnloadImage(sprite);
        }
    }

    UnloadImage(img);
}

void atualizarPropulsor(Nave *nave, int frames, char sprite)
{
    // Animação
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 4; j ++)
        {        
            if (frames % (4 * (FPS / 10)) == j * (FPS / 10))
            {
                nave->propulsor[i].sprite = nave->propulsor[i].spritesheet[j];
            }
        }
    }

    // Posição
    if (sprite == 'l')
    {
        nave->propulsor[0].posicao.x = nave->posicao.x + 2 * ESCALA;
        nave->propulsor[1].posicao.x = nave->posicao.x + 4 * ESCALA;
       
    }
    else if (sprite == 'r')
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
    nave->projetil[nave->numProjetil].tDisparo = GetTime();
    nave->projetil[nave->numProjetil].sprite = LoadTexture("../res/nave/projetil_nave.png");
    nave->projetil[nave->numProjetil].posicao = (Vector2) {nave->posicao.x, nave->posicao.y - 2 * ESCALA};

    nave->projetil[nave->numProjetil + 1].tDisparo = GetTime();
    nave->projetil[nave->numProjetil + 1].sprite = LoadTexture("../res/nave/projetil_nave.png");
    nave->projetil[nave->numProjetil + 1].posicao = (Vector2) {nave->posicao.x + 5 * 5, nave->posicao.y - 2 * ESCALA};
}

void atualizarProjetilNave(Nave *nave)
{
    // Disparar
    if (IsKeyPressed(KEY_SPACE))
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
            PlaySound(nave->disparo);

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
            UnloadTexture(nave->projetil[i].sprite);
            
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

void inicializarNave(Nave *nave)
{
    inicializarPropulsor(nave->propulsor);

    nave->posicao = (Vector2) {(LARG_JANELA - LARG_NAVE) / 2, ALT_JANELA - 2 * ALT_NAVE};

    Image img = LoadImage("../res/nave/nave.png");
    Image left = ImageFromImage(img, (Rectangle) {0, 0, 8, 8});
    Image middle = ImageFromImage(img, (Rectangle) {8, 0, 8, 8});
    Image right = ImageFromImage(img, (Rectangle) {16, 0, 8, 8});

    nave->spritesheet[0] = LoadTextureFromImage(left);
    nave->spritesheet[1] = LoadTextureFromImage(middle);
    nave->spritesheet[2] = LoadTextureFromImage(right);
    nave->sprite = nave->spritesheet[1];

    nave->numProjetil = 0;
    nave->projetil = NULL;
    
    nave->disparo = LoadSound("../res/sounds/disparo_nave.ogg");
    nave->hit = LoadSound("../res/sounds/hit_nave.ogg");
    
    nave->tInvencivel = GetTime();
    nave->hp = 1;
    nave->pontos = 0;

    UnloadImage(img);
    UnloadImage(left);
    UnloadImage(middle);
    UnloadImage(right);
}

void inicializarNave2(Nave *nave, int pontos)
{
    inicializarPropulsor(nave->propulsor);

    nave->posicao = (Vector2) {(LARG_JANELA - LARG_NAVE) / 2, ALT_JANELA - 2 * ALT_NAVE};

    Image img = LoadImage("../res/nave/nave.png");
    Image left = ImageFromImage(img, (Rectangle) {0, 0, 8, 8});
    Image middle = ImageFromImage(img, (Rectangle) {8, 0, 8, 8});
    Image right = ImageFromImage(img, (Rectangle) {16, 0, 8, 8});

    nave->spritesheet[0] = LoadTextureFromImage(left);
    nave->spritesheet[1] = LoadTextureFromImage(middle);
    nave->spritesheet[2] = LoadTextureFromImage(right);
    nave->sprite = nave->spritesheet[1];

    nave->numProjetil = 0;
    nave->projetil = NULL;
    
    nave->disparo = LoadSound("../res/sounds/disparo_nave.ogg");
    nave->hit = LoadSound("../res/sounds/hit_nave.ogg");
    
    nave->tInvencivel = GetTime();
    nave->hp = 3;
    nave->pontos = pontos;

    UnloadImage(img);
    UnloadImage(left);
    UnloadImage(middle);
    UnloadImage(right);
}

void atualizarNave(Nave *nave, int frames)
{
    char sprite;
    
    // Animação da nave
    if (IsKeyDown(KEY_LEFT))
    {
        nave->sprite = nave->spritesheet[0];
        sprite = 'l';
    }
    else if (IsKeyDown(KEY_RIGHT))
    {
        nave->sprite = nave->spritesheet[2];
        sprite = 'r';
    }
    else 
    {
        nave->sprite = nave->spritesheet[1];
        sprite = 'm';
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
    atualizarPropulsor(nave, frames, sprite);

    // Projéteis
    atualizarProjetilNave(nave);
}

void DrawShip(Nave nave)
{
    // Nave
    DrawTextureEx(nave.sprite, nave.posicao, 0, ESCALA, WHITE);
    DrawText(TextFormat("Score: %04i", nave.pontos), 10, 10, 20, WHITE);

    // Propulsores da nave
    for (int i = 0; i < 2; i++)
    {
        DrawTextureEx(nave.propulsor[i].sprite, nave.propulsor[i].posicao, 0, ESCALA, WHITE);
    }
}

void DrawShipProjectile(Nave nave)
{
    for (int i = 0; i < nave.numProjetil; i++)
    {
        DrawTextureEx(nave.projetil[i].sprite, nave.projetil[i].posicao, 0, ESCALA, WHITE); 
    }
}
