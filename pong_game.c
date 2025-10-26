#include "raylib.h"
#include <stdio.h>
#include <math.h>
#define MAX_VEL 10.0f

typedef struct raquete {
    Rectangle rect;
    float velY;
}raquete;

typedef struct circulo {
    Vector2 pos;
    float raio;
    float velX;
    float velY;
}circulo;

void resetarBola(circulo* circ, const int screenWidth, const int screenHeight, float velBase) {
    //reposiciona a bola pro centro da tela
    circ->pos = (Vector2){(float)screenWidth / 2, (float) screenHeight / 2};

    //randomiza a posicao que ela vai ir
    int inicX = (GetRandomValue(0, 1) == 0) ? -1 : 1;
    int inicY = (GetRandomValue(0, 1) == 0) ? -1 : 1;

     //velocidade da bola, mantendo o valor base
    circ->velX = velBase * inicX;
    circ->velY = velBase * inicY;
}

void aumentarVelBola(circulo* circ) { 
    circ->velX *= 1.05f;
    circ->velY *= 1.05f;

    //limita a velocidade no eixo X
    if(fabsf(circ->velX) > MAX_VEL) {
        circ->velX = (circ->velX > 0) ? MAX_VEL : -MAX_VEL;
    }
    //limita a velocidade no eixo Y
    if(fabsf(circ->velY) > MAX_VEL) {
        circ->velY = (circ->velY > 0) ? MAX_VEL : -MAX_VEL;
    }
}


int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;
    int p1 = 0, p2 = 0;
    float vel = 6.0f;
    float velB = 5.0f;
    float velocidade = velB;

    //x, y, largura, altura
    raquete r1 = {{20, (float)(screenHeight / 2) - 100, 10, 150}, vel};
    raquete r2 = {{770, (float)(screenHeight / 2) - 100, 10, 150}, vel};
    circulo circ = {{screenWidth / 2, screenHeight / 2}, 25.0f, velB, velB};

    resetarBola(&circ, screenWidth, screenHeight, velB);

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60);

    // Main game loop
    while (!WindowShouldClose()) 
    {
        //Update your variables here

        //velocidade da bola pra mostrar na tela
        velocidade = sqrtf(circ.velX * circ.velX + circ.velY * circ.velY);
        
        //mover a raquete da esquerda
        if (IsKeyDown(KEY_W)) r1.rect.y -= r1.velY;
        if (IsKeyDown(KEY_S)) r1.rect.y += r1.velY;

        //mover a raquete da direita
        if (IsKeyDown(KEY_O)) r2.rect.y -= r2.velY;
        if (IsKeyDown(KEY_L)) r2.rect.y += r2.velY;


        //limitar para nao sair da tela
        //travar para nao passar por cima
        if (r1.rect.y < 0) r1.rect.y = 0;
        if (r2.rect.y < 0) r2.rect.y = 0;

        //travar pra nao passar por baixo
        if (r1.rect.y + r1.rect.height > screenHeight) r1.rect.y = screenHeight - r1.rect.height;
        if (r2.rect.y + r2.rect.height > screenHeight) r2.rect.y = screenHeight - r2.rect.height;

        //fazer a bola andar
        circ.pos.x += circ.velX;
        circ.pos.y += circ.velY;

        // colisao da bola no eixo Y (cima e baixo)
        if(circ.pos.y - circ.raio <= 0 || circ.pos.y + circ.raio >= screenHeight) {
            circ.velY = -circ.velY;
        }
        
        //colisao no eixo X (ponto)
        if(circ.pos.x - circ.raio <=  0) {
            //bola saiu na esquerda
            p2++;
            //reinicia a bola pro centro da tela
            resetarBola(&circ, screenWidth, screenHeight, velB);
        } else if(circ.pos.x + circ.raio >= screenWidth){
            //bola saiu na direita
            p1++;
            //reinicia a bola pro centro da tela
            resetarBola(&circ, screenWidth, screenHeight, velB);
        }

        //colisao com as raquetes
        //raquete da esquerda
        if(CheckCollisionCircleRec(circ.pos, circ.raio, r1.rect))  {
            //para bola nao grudar na tela
            circ.pos.x = r1.rect.x + r1.rect.width + circ.raio;

            //calcular o ponto de impacto da bola (-1 no topo, 1 na base)
            //o valor resultante (fator saida) sera entre -0.5 e 0.5
            float pontoImpacto = circ.pos.y - (r1.rect.y + r1.rect.height / 2.0f);
            float pontoSaida = pontoImpacto / (r1.rect.height / 2.0f);
            pontoSaida = fmaxf(-1.0f, fminf(pontoSaida, 1.0f));
            
            //pega a velocidade base atual (magnitude)
            float velTotal = sqrtf(circ.velX * circ.velX + circ.velY * circ.velY);
            
            //aumentar a velocidade da bola
            aumentarVelBola(&circ);

            //pega a nova velocidade da bola
            float velNova = sqrtf(circ.velX * circ.velX + circ.velY * circ.velY);

            //aplica o novo angulo
            circ.velX = velNova * sqrtf(1.0f - (pontoSaida * 0.5f) * (pontoSaida * 0.5f)); //valor positivo (bola vai pra direita)
            circ.velY = velNova * (pontoSaida * 0.5f);
            //garante que va para a direita
            circ.velX = fabsf(circ.velX);
        }

        //raquete da direita
        if(CheckCollisionCircleRec(circ.pos, circ.raio, r2.rect)) {
            //para bola nao grudar na tela
            circ.pos.x = r2.rect.x - circ.raio;
 
            //calcular o ponto de impacto
            float pontoImpacto = circ.pos.y - (r2.rect.y + r2.rect.height / 2.0f);
            float pontoSaida = pontoImpacto / (r2.rect.height / 2.0f);
            pontoSaida = fmaxf(-1.0f, fminf(pontoSaida, 1.0f));
            float velTotal = sqrtf(circ.velX * circ.velX + circ.velY * circ.velY);

            //aumentar velocidade da bola
            aumentarVelBola(&circ);

            //pega a nova velocidade da bola
            float velNova = sqrtf(circ.velX * circ.velX + circ.velY * circ.velY);

            //aplica o novo angulo
            circ.velX = velNova * sqrtf(1.0f - (pontoSaida * 0.5f) * (pontoSaida * 0.5f)); //valor negativo (bola vai pra esquerda)
            circ.velY = velNova * (pontoSaida * 0.5f);

            //garante que va para a esquerda(negativo)
            circ.velX = -fabsf(circ.velX);
        }


        BeginDrawing();
            ClearBackground(RAYWHITE);

            int fontSize = 50;
            char pontuacao[32];
            char textveloc[30];
            sprintf(pontuacao, "%d  |  %d", p1, p2);
            sprintf(textveloc, "Velocidade: %.2f", velocidade);

            int larguraTexto = MeasureText(pontuacao, fontSize);
            int posX = (screenWidth - larguraTexto) / 2;
            int larguraTexto2 = MeasureText(textveloc, fontSize);
            int posX2 = (screenWidth - larguraTexto2) / 2;

            DrawText(pontuacao, posX, 20, fontSize, LIGHTGRAY);
            DrawText(textveloc, posX2, 80, fontSize, LIGHTGRAY);

            DrawRectangleRec(r1.rect, BLUE);
            DrawRectangleRec(r2.rect, RED);
            DrawCircle(circ.pos.x, circ.pos.y, circ.raio, RED);

        EndDrawing();
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}