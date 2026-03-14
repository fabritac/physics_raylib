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

void moveBall(Ball *ball);
void collisionBalls(Ball **balls, int numberOfBalls);
void collisionTwoBalls(Ball *ball_A, Ball *ball_B);

// TODO: Refactorizar la manera de crear pelotas, manejar su movimiento y dibujarlas.

int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Physics");

    Ball redBall = {
        (Vector2){(float)SCREEN_WIDTH/3, (float)SCREEN_HEIGHT/2},
        (Vector2){ 5.0f, 10.0f },
        30,
        MAROON
    };

    Ball blueBall = {
        (Vector2){(float)SCREEN_WIDTH*2/3, (float)SCREEN_HEIGHT/2},
        (Vector2){ -5.0f, -10.0f },
        30,
        BLUE 
    };

    Ball greenBall = {
        (Vector2){(float)SCREEN_WIDTH, (float)SCREEN_HEIGHT/2},
        (Vector2){ 5.0f, -10.0f },
        30,
        GREEN 
    };

    int numberOfBalls = 3;
    Ball **balls = malloc(numberOfBalls * sizeof(Ball *));
    balls[0] = &redBall;
    balls[1] = &blueBall;
    balls[2] = &greenBall;

    SetTargetFPS(60);

    while (!WindowShouldClose()) {

        moveBall(&redBall);
        moveBall(&blueBall);
        moveBall(&greenBall);
        collisionBalls(balls, numberOfBalls);

        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawCircleV(redBall.pos, redBall.radius, redBall.color);
            DrawCircleV(blueBall.pos, blueBall.radius, blueBall.color);
            DrawCircleV(greenBall.pos, greenBall.radius, greenBall.color);

        EndDrawing();
    }
    CloseWindow();
    return 0;
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

void collisionBalls(Ball **balls, int numberOfBalls) {
    for (int i = 0; i < numberOfBalls; i++) {
        for (int j = i + 1; j < numberOfBalls; j++) {
            collisionTwoBalls(balls[i], balls[j]);
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