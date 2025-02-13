#ifndef SIGNUP_H
#define SIGNUP_H

#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <raylib.h>
#include <string.h>
#include <Admin.h>
#include <account.h>


#define RAYGUI_IMPLEMENTATION
#include <raygui.h>

// Constants
#define SCREEN_WIDTH  1200
#define SCREEN_HEIGHT 800
    
bool nameActive = false, aadharActive = false, dobActive = false;
bool mobActive = false, passwordActive = false;

account signupgui() {
    char nameBuffer[50] = "";
    char aadharBuffer[20] = "";
    char dobBuffer[11] = "";
    char mobBuffer[20] = "";
    char passwordBuffer[30] = "";

    account acc = {0};
    acc.acc_num = generateUniqueId();

    //FIX THE LOGO OVERLAP

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Creast Banking");
    SetTargetFPS(60);

    Texture2D Logo = LoadTexture("image/logo.png");

    Font customFont = LoadFontEx("resources/Roboto-Regular.ttf", 64, 0, 0);
    GenTextureMipmaps(&customFont.texture);
    SetTextureFilter(customFont.texture, TEXTURE_FILTER_BILINEAR);

    if (customFont.texture.id == 0) {
        printf("Failed to load font!\n");
        CloseWindow();
        account empty_acc = {0};
        return empty_acc;
    }

    long long accno = generateUniqueId();

    while (!WindowShouldClose()) {
        Color peach = {255, 218, 185, 255};

        BeginDrawing();
        ClearBackground(peach);
        Vector2 mouse = GetMousePosition();

        const char *intro = "Welcome to the CREST Bank";
        Vector2 intro_textsize = MeasureTextEx(customFont, intro, 50, 2);
        Vector2 intro_position = {(SCREEN_WIDTH - intro_textsize.x) / 2, (225 - intro_textsize.y) / 2};

        // Intro Text
        DrawTextEx(customFont, intro, intro_position, 50, 2, BLACK);

        // Logo
        DrawTexture(Logo, (SCREEN_WIDTH - Logo.width) / 2, 90, WHITE);

        // Rectangle box = {(SCREEN_WIDTH - 600) / 2, SCREEN_HEIGHT / 8 * 5, 600, 60};
        // DrawRectangleRounded(box, 0.3, 10, LIGHTGRAY);

        int yinc = 400;

        // Account Number Display
        DrawText(TextFormat("Your account number assigned is: %lld", acc.acc_num), 300, yinc, 20, DARKGRAY);
        yinc += 50;

        // Name Input
        Rectangle Name ={485, yinc - 5, 300, 30};
        DrawText("Name:", 300, yinc, 20, BLACK);
        GuiTextBox(Name, nameBuffer, sizeof(nameBuffer), nameActive);
        yinc += 50;

        // Aadhar Input
        Rectangle Aadhar = {485, yinc - 5, 300, 30};
        DrawText("Aadhar number:", 300, yinc , 20, BLACK);  
        GuiTextBox(Aadhar, aadharBuffer, sizeof(aadharBuffer), aadharActive);
        yinc += 50;

        // Date of Birth Input
        Rectangle DOB = {485, yinc - 5, 300, 30};
        DrawText("DOB [yyyy-mm-dd]:", 300, yinc, 20, BLACK);
        GuiTextBox(DOB, dobBuffer, sizeof(dobBuffer), dobActive);
        yinc += 50;

        // Mobile Number Input
        Rectangle Mobile = {485, yinc - 5, 300, 30};
        DrawText("Mobile number:", 300, yinc, 20, BLACK);
        GuiTextBox(Mobile, mobBuffer, sizeof(mobBuffer), mobActive);
        yinc += 50;

        // Password Input
        Rectangle pass = {485, yinc - 5, 300, 30};
        DrawText("Password:", 300, yinc, 20, BLACK);
        GuiTextBox(pass, passwordBuffer, sizeof(passwordBuffer), passwordActive);
        yinc += 50;

        Vector2 mousePos = GetMousePosition();

        Rectangle submit = {525, yinc, 150, 60};

        GuiSetStyle(DEFAULT, TEXT_SIZE, 24);

        // Submit Button
        if (GuiButton(submit, "Submit")) 
        {
            // Save input to struct
            strcpy(acc.name, nameBuffer);
            acc.aadhar_no = atoll(aadharBuffer);
            strcpy(acc.DOB, dobBuffer);
            acc.mob_no = atoll(mobBuffer);
            strcpy(acc.passwd, passwordBuffer);
            //when clicked return acc;
            
        }
        
        if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mousePos, submit)) 
        {
            return acc;
            break;
        }
            
        // Mouse Click Handling
        // FIX THE ALLIGNMENT
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            // Vector2 mousePos = GetMousePosition();
            yinc = 400;
            nameActive = CheckCollisionPointRec(mousePos, Name);
            yinc += 50;
            aadharActive = CheckCollisionPointRec(mousePos, Aadhar);
            yinc += 50;
            dobActive = CheckCollisionPointRec(mousePos, DOB);
            yinc += 50;
            mobActive = CheckCollisionPointRec(mousePos, Mobile);
            yinc += 50;
            passwordActive = CheckCollisionPointRec(mousePos, pass);
        }

        EndDrawing();
    }
    printf("%lld",acc.aadhar_no);

    UnloadTexture(Logo);
    UnloadFont(customFont);
    CloseWindow();

}


#endif // SIGNUP_h