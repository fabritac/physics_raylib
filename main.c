#include "include/raylib.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SCREEN_WIDTH 500
#define SCREEN_HEIGHT 500

int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Physics");

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(WHITE);

        EndDrawing();
    }
    CloseWindow();
    return 0;
}