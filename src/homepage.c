#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <raylib.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


#define RAYGUI_IMPLEMENTATION
#include<raygui.h>

// Constants
#define SCREEN_WIDTH  1200
#define SCREEN_HEIGHT 800

struct DOB {
    int day,month,year;
};

struct SignUpCSV {
    long long accno;
    long long aadhaarno;
    char name[100];
    struct DOB dateofbirth;
    long long mobileno;
    char password[50];
};

int main(){
    
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Creast Banking");
    SetTargetFPS(60);

    Texture2D Logo = LoadTexture("image/logo.png");

    Logo.width /= 1.5;
    Logo.height /= 1.5;

    Font customFont = LoadFontEx("resources/Roboto-Regular.ttf", 64, 0, 0);
    GenTextureMipmaps(&customFont.texture);
    SetTextureFilter(customFont.texture, TEXTURE_FILTER_BILINEAR);

    if (customFont.texture.id == 0) {
        printf("Failed to load font!\n");
        CloseWindow();
        return -1;
    }

    // data of user 
    struct SignUpCSV userinfo;

    // input fields
    long long accno;
    


    while (!WindowShouldClose()) {

        Color peach = { 255, 218, 185, 255 };  // Peach color (Soft warm tone)

        BeginDrawing();
        ClearBackground(peach);

        Vector2 mouse = GetMousePosition();

        const char* intro = "Home Page";
        Vector2 intro_textsize = MeasureTextEx(customFont, intro, 50, 2);
        Vector2 intro_position = {(SCREEN_WIDTH - intro_textsize.x)/2,(225 - intro_textsize.y)/2};

        // text of intro

        DrawTextEx(customFont, intro, intro_position, 50, 2, BLACK);

        // logo of the app

        DrawTexture(Logo, 10, 0, WHITE);



        EndDrawing();
    }
    UnloadTexture(Logo);
    UnloadFont(customFont);

    CloseWindow();
    return 0;
}

