#include "include/raylib.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SCREEN_WIDTH 800 
#define SCREEN_HEIGHT 450 

typedef struct {
    Vector2 pos;
    Vector2 speed;
    int radius;
    Color color;
} Ball;

void initBalls(Ball balls[], int numberOfBalls);
void collisionBalls(Ball balls[], int numberOfBalls);
void drawBalls(Ball balls[], int numberOfBalls);
void moveBalls(Ball balls[], int numberOfBalls);
void moveBall(Ball *ball);
void collisionTwoBalls(Ball *ball_A, Ball *ball_B);

int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Physics");

    int numberOfBalls = 20;
    Ball balls[numberOfBalls];
    initBalls(balls, numberOfBalls);

    SetTargetFPS(60);

    while (!WindowShouldClose()) {

        moveBalls(balls, numberOfBalls);
        collisionBalls(balls, numberOfBalls);

        BeginDrawing();

            ClearBackground(RAYWHITE);

            drawBalls(balls, numberOfBalls);

        EndDrawing();
    }
    CloseWindow();
    return 0;
}

void initBalls(Ball balls[], int numberOfBalls) {
    for (int i = 0; i < numberOfBalls; i++) {
        Ball ball = {
            (Vector2){(float)GetRandomValue(0, SCREEN_WIDTH), (float)GetRandomValue(0, SCREEN_HEIGHT)},
            (Vector2){(float)GetRandomValue(-5.0, 5.0), (float)GetRandomValue(-5.0, 5.0)},
            GetRandomValue(20, 30),
            (Color){
                GetRandomValue(0, 255),
                GetRandomValue(0, 255),
                GetRandomValue(0, 255),
                255,
            }};

        balls[i] = ball;
    }
}

void moveBalls(Ball balls[], int numberOfBalls)
{
    for (int i = 0; i < numberOfBalls; i++)
    {       
        moveBall(&balls[i]);   
    }
}

void drawBalls(Ball balls[], int numberOfBalls) {
    for (int i = 0; i < numberOfBalls; i++) {
        DrawCircleV(balls[i].pos, balls[i].radius, balls[i].color);
    }
}

void moveBall(Ball *ball) {
    ball->pos.x += ball->speed.x;
    ball->pos.y += ball->speed.y;

    if (ball->pos.x + ball->radius >= SCREEN_WIDTH) {
        if (ball->speed.x > 0) {
            ball->speed.x *= -1.0f;
        }
    }
    if (ball->pos.x - ball->radius <= 0) {
        if (ball->speed.x < 0) {
            ball->speed.x *= -1.0f;
        }
    }
    if (ball->pos.y + ball->radius >= SCREEN_HEIGHT) {
        if (ball->speed.y > 0) {
            ball->speed.y *= -1.0f;
        }
    }
    if (ball->pos.y - ball->radius <= 0) {
        if (ball->speed.y < 0) {
            ball->speed.y *= -1.0f;
        }
    }
}

void collisionBalls(Ball balls[], int numberOfBalls) {
    for (int i = 0; i < numberOfBalls; i++) {
        for (int j = i + 1; j < numberOfBalls; j++) {
            collisionTwoBalls(&balls[i], &balls[j]);
        }
    }
}

void collisionTwoBalls(Ball *ball_A, Ball *ball_B) {
    float dx = ball_A->pos.x - ball_B->pos.x;
    float dy = ball_A->pos.y - ball_B->pos.y;
    float distance = sqrtf(dx*dx + dy*dy);

    if (distance < (ball_A->radius + ball_B->radius)) {
        Vector2 temp = ball_A->speed;
        ball_A->speed = ball_B->speed;
        ball_B->speed = temp;
    } 
}