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

typedef struct{
	long long acc_num;
	char name[50];
	long long aadhar_no;
	char DOB[11];
	long long mob_no;
	char passwd[100];
	}Account;


 Account customer = {0};
    customer.acc_num = generateUniqueId();

    char nameBuffer[50] = "";
    char aadharBuffer[20] = "";
    char dobBuffer[11] = "";
    char mobBuffer[20] = "";
    char passwordBuffer[100] = "";

int main()
{
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

    long long accno = generateUniqueIdId();

    while(!WindowShouldClose)
    {
    	color peach = {255,218,185,255};
    	BeginDrawing();
    	ClearBackground(peach);
        Vector2 mouse = GetMousePosition();

        const char* intro = "Welcome to the CREST Bank";
        Vector2 intro_textsize = MeasureTextEx(customFont, intro, 50, 2);
        Vector2 intro_position = {(SCREEN_WIDTH - intro_textsize.x)/2,(225 - intro_textsize.y)/2};

        // text of intro

        DrawTextEx(customFont, intro, intro_position, 50, 2, BLACK);

        // logo of the app

        DrawTexture(Logo, (SCREEN_WIDTH - Logo.width) / 2, 125, WHITE);

        Rectangle accno = { (SCREEN_WIDTH - 600)/2, SCREEN_HEIGHT/8*5, 600, 60 };
        DrawRectangleRounded(accno, 0.3, 10, LIGHTGRAY);

        int yinc = 400;

        // Account Number Display
        DrawText(TextFormat("Your account number assigned is: %lld", customer.acc_num), 300, yinc, 20, DARKGRAY);
        yinc += 50;

        // Name Input
        DrawText("Name:", 300, yinc, 20, BLACK);
        GuiTextBox((Rectangle){450, yinc - 5, 300, 30}, nameBuffer, sizeof(nameBuffer), nameActive);
        yinc += 50;

        // Aadhar Input
        DrawText("Aadhar number:", 300, yinc, 20, BLACK);
        GuiTextBox((Rectangle){450, yinc - 5, 300, 30}, aadharBuffer, sizeof(aadharBuffer), aadharActive);
        yinc += 50;

        // Date of Birth Input
        DrawText("Date of Birth [yyyy-mm-dd]:", 300, yinc, 20, BLACK);
        GuiTextBox((Rectangle){450, yinc - 5, 300, 30}, dobBuffer, sizeof(dobBuffer), dobActive);
        yinc += 50;

        // Mobile Number Input
        DrawText("Mobile number:", 300, yinc, 20, BLACK);
        GuiTextBox((Rectangle){450, yinc - 5, 300, 30}, mobBuffer, sizeof(mobBuffer), mobActive);
        yinc += 50;

        // Password Input
        DrawText("Password:", 300, yinc, 20, BLACK);
        GuiTextBox((Rectangle){450, yinc - 5, 300, 30}, passwordBuffer, sizeof(passwordBuffer), passwordActive);
        yinc += 50;

        // Submit Button
        if (GuiButton((Rectangle){450, yinc, 150, 40}, "Submit")) {
            // Save input to struct
            strcpy(customer.name, nameBuffer);
            customer.aadhar_no = atoll(aadharBuffer);
            strcpy(customer.DOB, dobBuffer);
            customer.mob_no = atoll(mobBuffer);
            strcpy(customer.passwd, passwordBuffer);

        EndDrawing();
    }
    UnloadTexture(Logo);
    UnloadFont(customFont);
    CloseWindow();
}