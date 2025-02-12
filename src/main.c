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


struct LoginCSV {
    long long accno;
    char username[50];
    char password[50];
};


int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Creast Banking");
    SetTargetFPS(60);

    Texture2D Logo = LoadTexture("image/logo.png");

    // surabhi check
    
    Font customFont = LoadFontEx("resources/Roboto-Regular.ttf", 64, 0, 0);
    GenTextureMipmaps(&customFont.texture);
    SetTextureFilter(customFont.texture, TEXTURE_FILTER_BILINEAR);

    if (customFont.texture.id == 0) {
        printf("Failed to load font!\n");
        CloseWindow();
        return -1;
    }

    // data of user
    struct LoginCSV userdata;

    // input fields
    char input_username[50] = "";
    char input_password[50] = "";
    char hidden_password[50] = "";
    bool isPasswordHidden = true;
    bool accno_placeholderActive = true;
    bool password_placeholderActive = true;
    bool usernameActive = false;
    bool passwordActive = false;
    bool loginbuttonActive = false;
    bool signupbuttonActive = false;

    while (!WindowShouldClose()) {

        Color peach = { 255, 218, 185, 255 };  // Peach color (Soft warm tone)

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

        // text or input box

        Rectangle accno = { (SCREEN_WIDTH - 600)/2, SCREEN_HEIGHT/8*5, 600, 60 };
        DrawRectangleRounded(accno, 0.3, 10, LIGHTGRAY);

        DrawRectangleRoundedLinesEx(accno, 0.3, 10, 0.2, usernameActive ? BLACK : LIGHTGRAY);

        const char *accno_placeholder = "Enter the Account no or Username";
        Vector2 accno_textsize = MeasureTextEx(customFont, accno_placeholder, 25, 2);
        Vector2 accno_position = {(SCREEN_WIDTH - accno_textsize.x)/2,accno.y + (accno.height - accno_textsize.y)/2};

        DrawTextEx(customFont, accno_placeholder, accno_position, 25, 2, accno_placeholderActive ? BLACK : LIGHTGRAY);

        if (CheckCollisionPointRec(mouse, accno) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            usernameActive = true;
            passwordActive = false;
        }

        if (strlen(input_username) != 0 ) {
            accno_placeholderActive = false;
        }

        if ( !usernameActive && strlen(input_username) == 0 ){
            accno_placeholderActive = true;
        }

        Vector2 username_textsize = MeasureTextEx(customFont, input_username, 25, 2);
        Vector2 username_position = {(SCREEN_WIDTH - username_textsize.x)/2,accno.y + (accno.height - username_textsize.y)/2};

        if (strlen(input_username)!=0){
            DrawTextEx(customFont, input_username, username_position, 25, 2, BLACK );
        }

        Rectangle password = { (SCREEN_WIDTH - 600)/2, SCREEN_HEIGHT/8*5 + 70, 600, 60 };
        DrawRectangleRounded(password, 0.3, 10, LIGHTGRAY);

        DrawRectangleRoundedLinesEx(password, 0.3, 10, 0.2, passwordActive ? BLACK : LIGHTGRAY);

        const char *password_placeholder = "Enter your Password";
        Vector2 password_textsize = MeasureTextEx(customFont, password_placeholder, 25, 2);
        Vector2 password_position = {(SCREEN_WIDTH - password_textsize.x)/2,password.y + (password.height - password_textsize.y)/2};

        DrawTextEx(customFont, password_placeholder, password_position, 25, 2, password_placeholderActive ? BLACK : LIGHTGRAY);

        Vector2 center = { password.x + 570, password.y + 30 };
        DrawCircleV(center, 20, isPasswordHidden ? GREEN : RED);

        if (CheckCollisionPointCircle(mouse, center, 20) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            isPasswordHidden = !isPasswordHidden;
        } 

        if (CheckCollisionPointRec(mouse, password) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            passwordActive = true;
            usernameActive = false;
        }

        if (strlen(input_password) != 0 ) {
            password_placeholderActive = false;
        }

        if ( !passwordActive && strlen(input_password) == 0 ){
            password_placeholderActive = true;
        }

        Vector2 input_password_textsize = MeasureTextEx(customFont, input_password, 25, 2);
        Vector2 input_password_position = {(SCREEN_WIDTH - input_password_textsize.x)/2,password.y + (password.height - input_password_textsize.y)/2};

        if (strlen(input_password)!=0){
            if (isPasswordHidden){
                DrawTextEx(customFont, hidden_password, input_password_position, 25, 2, BLACK );
            }else{
                DrawTextEx(customFont, input_password, input_password_position, 25, 2, BLACK );
            }
        }  

        // Keyboard Interaction

        int key = GetCharPressed();

        if (usernameActive) {
            if (key >= 32 && key <= 126 && strlen(input_username) < 50) {
                input_username[strlen(input_username)] = (char)key;
                input_username[strlen(input_username) + 1] = '\0';
            }

            if (IsKeyPressed(KEY_BACKSPACE) && strlen(input_username) > 0) {
                input_username[strlen(input_username) - 1] = '\0';
            }
        } else if (passwordActive) {
            if (key >= 32 && key <= 126 && strlen(input_password) < 50) {
                input_password[strlen(input_password)] = (char)key;
                input_password[strlen(input_password) + 1] = '\0';
            }

            if (IsKeyPressed(KEY_BACKSPACE) && strlen(input_password) > 0) {
                input_password[strlen(input_password) - 1] = '\0';
            }
        }

        // code to hide the password
        if (isPasswordHidden) {
            memset(hidden_password, '*', strlen(input_password));
            hidden_password[strlen(input_password)] = '\0';
        }

        // login and signup buttons

        Rectangle loginbutton = {SCREEN_WIDTH/2 - 150 -(password.width/2-150)/2, password.y + password.height + 25, 150, password.height - 10};
        DrawRectangleRounded(loginbutton, 0.3, 10, loginbuttonActive ? GRAY : LIGHTGRAY);

        const char* logintext = "Login";
        Vector2 login_textsize = MeasureTextEx(customFont, logintext, 20, 1);
        Vector2 logintext_position = {loginbutton.x + (loginbutton.width - login_textsize.x)/2,loginbutton.y + (loginbutton.height - login_textsize.y)/2};

        DrawTextEx(customFont, logintext, logintext_position, 20, 1, BLACK );

        Rectangle signupbutton = {SCREEN_WIDTH/2 + (password.width/2-150)/2, password.y + password.height + 25, 150, password.height - 10};
        DrawRectangleRounded(signupbutton, 0.3, 10, signupbuttonActive ? GRAY : LIGHTGRAY);

        const char* signuptext = "SignUp";
        Vector2 signup_textsize = MeasureTextEx(customFont, logintext, 20, 1);
        Vector2 signuptext_position = {signupbutton.x + (signupbutton.width - signup_textsize.x)/2,signupbutton.y + (signupbutton.height - signup_textsize.y)/2};

        DrawTextEx(customFont, signuptext, signuptext_position, 20, 1, BLACK );

        if (CheckCollisionPointRec(mouse, loginbutton)){
            loginbuttonActive = true;
        }else{
            loginbuttonActive = false;
        }

        if (CheckCollisionPointRec(mouse, signupbutton)){
            signupbuttonActive = true;
        }else{
            signupbuttonActive = false;
        }

        // line between buttons
        Vector2 startline = {SCREEN_WIDTH/2, password.y + password.height + 20};
        Vector2 endline = {SCREEN_WIDTH/2, password.y + password.height*2 + 20};
        DrawLineEx(startline, endline, 2, GRAY);

        // status showing

        char *statusmessage = "";

        if (CheckCollisionPointRec(mouse,loginbutton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            // check for username correction and password correction
            // and add the username add password to the structure for accessing it again again for all the pages
            // if found correct redirect to the homepage
        }
        else if (CheckCollisionPointRec(mouse,signupbutton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            // redirect the user to the signup page
        }

        EndDrawing();
    }

    UnloadTexture(Logo);
    UnloadFont(customFont);

    CloseWindow();
    return 0;
}


