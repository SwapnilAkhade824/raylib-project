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


struct Account {
    long long accno;
    char username[10];
    char password[10];
};


int main(int argc, char const *argv[]) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Creast Banking");
    SetTargetFPS(60);

    Texture2D Logo = LoadTexture("image/logo.png");

    Font customFont = LoadFontEx("resources/Roboto-Regular.ttf", 64, 0, 0);
    GenTextureMipmaps(&customFont.texture);
    SetTextureFilter(customFont.texture, TEXTURE_FILTER_BILINEAR);

    if (customFont.texture.id == 0) {
        printf("Failed to load font!\n");
        CloseWindow();
        return -1;
    }

    const char* intro = "Welcome to the CREST Bank";

    while (!WindowShouldClose()) {

        Color peach = { 255, 218, 185, 255 };  // Peach color (Soft warm tone)

        BeginDrawing();
        ClearBackground(peach);

        // data of user
        struct Account userdata;

        // input fields
        char input_username[11] = "";
        char input_password[11] = "";
        bool isPasswordHidden = true;
        bool accno_placeholderActive = true;
        bool password_placeholderActive = true;
        bool usernameActive = false;
        bool passwordActive = false;

        // input values
        char inputaccno[13]="";
        char inputpassword[11]="";

        Vector2 intro_textsize = MeasureTextEx(customFont, intro, 50, 2);
        Vector2 intro_position = {(SCREEN_WIDTH - intro_textsize.x)/2,(225 - intro_textsize.y)/2};

        // text of intro

        DrawTextEx(customFont, intro, intro_position, 50, 2, BLACK);

        // logo of the app

        DrawTexture(Logo, (SCREEN_WIDTH - Logo.width) / 2, 125, WHITE);

        // text or input box

        Rectangle accno = { (SCREEN_WIDTH - 600)/2, SCREEN_HEIGHT/8*5, 600, 60 };
        DrawRectangleRounded(accno, 0.3, 10, WHITE);

        char *accno_placeholder = "Enter the Account no or Username";
        Vector2 accno_textsize = MeasureTextEx(customFont, accno_placeholder, 25, 2);
        Vector2 accno_position = {(SCREEN_WIDTH - accno_textsize.x)/2,accno.y + (accno.height - accno_textsize.y)/2};

        DrawTextEx(customFont, accno_placeholder, accno_position, 25, 2, accno_placeholderActive ? BLACK : WHITE);

        Rectangle password = { (SCREEN_WIDTH - 600)/2, SCREEN_HEIGHT/8*5 + 70, 600, 60 };
        DrawRectangleRounded(password, 0.3, 10, WHITE);

        char *password_placeholder = "Enter your Password";
        Vector2 password_textsize = MeasureTextEx(customFont, password_placeholder, 25, 2);
        Vector2 password_position = {(SCREEN_WIDTH - password_textsize.x)/2,password.y + (password.height - password_textsize.y)/2};

        DrawTextEx(customFont, password_placeholder, password_position, 25, 2, password_placeholderActive ? BLACK : WHITE);

        Vector2 center = { password.x + 570, password.y + 30 };
        DrawCircleV(center, 20, isPasswordHidden ? GREEN : RED);



        EndDrawing();
    }

    UnloadTexture(Logo);
    UnloadFont(customFont);

    CloseWindow();
    return 0;
}


