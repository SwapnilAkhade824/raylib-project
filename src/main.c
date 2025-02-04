#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <raylib.h>
#include <string.h>

// Constants
#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 600

int main(int argc, char const *argv[]) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Creast Banking");
    SetTargetFPS(60);

    Texture2D Logo = LoadTexture("image\\logo.png");

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        char intro[100] = "Welcome to the CREAST Bank";
        DrawText(intro, (800 - MeasureText(intro, 30)) / 2, 50, 30, BLACK);

        DrawTexture(Logo, 80, 50, WHITE);

        EndDrawing();
    }

    UnloadTexture(Logo);

    CloseWindow();
    return 0;
}