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

    Texture2D Logo = LoadTexture("image/logosignup.png");

    Logo.width /= 1.1;
    Logo.height /= 1.1;

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
    char accno[12] = "";
    char input_aadhaar[12] = "";
    char input_name[100] = "";
    char input_dob[10] = "";
    struct DOB input_dateofbirth;
    char input_mobileno[10] = "";
    char input_password[50] = "";
    char input_con_password[50] = "";    

    // Boolean Values
    bool accnoActive = false;
    bool aadhaarActive = false;
    bool nameActive = false;
    bool dobActive = false;
    bool mobilenoActive = false;
    bool passActive = false;
    bool conpassActive = false;
    bool accnoActive_ph = true;
    bool aadhaarActive_ph = true;
    bool nameActive_ph = true;
    bool dobActive_ph = true;
    bool mobilenoActive_ph = true;
    bool passActive_ph = true;
    bool conpassActive_ph = true;

    while (!WindowShouldClose()) {

        Color peach = { 255, 218, 185, 255 };  // Peach color (Soft warm tone)

        BeginDrawing();
        ClearBackground(peach);

        Vector2 mouse = GetMousePosition();

        const char* intro = "SignUp";
        Vector2 intro_textsize = MeasureTextEx(customFont, intro, 64, 4);
        Vector2 intro_position = {(SCREEN_WIDTH - Logo.width - intro_textsize.x)/2 + Logo.width - 20,(Logo.height - intro_textsize.y)/2};

        // text of intro

        DrawTextEx(customFont, intro, intro_position, 64, 4, BLACK);

        // logo of the app

        DrawTexture(Logo, 100, 0, WHITE);

        int txtboxheight = 60;
        int txtboxwidth = 600;

        // text box for name

        Rectangle namebox = { SCREEN_WIDTH/3, Logo.height + 20, txtboxwidth, txtboxheight };
        DrawRectangleRounded(namebox, 0.3, 10, LIGHTGRAY);

        DrawRectangleRoundedLinesEx(namebox, 0.3, 10, 0.2, nameActive ? BLACK : LIGHTGRAY);

        const char *namelabel = "Name:";
        Vector2 namelabel_textsize = MeasureTextEx(customFont, namelabel, 30, 1);
        Vector2 namelabel_position = {namebox.x - namelabel_textsize.x - 20, namebox.y + (namebox.height - namelabel_textsize.y)/2};

        DrawTextEx(customFont, namelabel, namelabel_position, 30, 1, BLACK);

        const char *name_ph = "Enter your Name";
        Vector2 nameph_textsize = MeasureTextEx(customFont, name_ph, 25, 1);
        Vector2 nameph_position = {namebox.x + (namebox.width - nameph_textsize.x)/2,namebox.y + (namebox.height - nameph_textsize.y)/2};

        DrawTextEx(customFont, name_ph, nameph_position, 25, 1, nameActive_ph ? BLACK : LIGHTGRAY);

        if (CheckCollisionPointRec(mouse, namebox) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            accnoActive = false;
		    aadhaarActive = false;
		    nameActive = true;
		    dobActive = false;
		    mobilenoActive = false;
		    passActive = false;
		    conpassActive = false;
        }

        if (strlen(input_name) != 0 ) {
            nameActive_ph = false;
        }

        if ( !nameActive && strlen(input_name) == 0 ){
            nameActive_ph = true;
        }

        Vector2 name_textsize = MeasureTextEx(customFont, input_name, 25, 1);
        Vector2 name_position = {(SCREEN_WIDTH - name_textsize.x)/2,namebox.y + (namebox.height - name_textsize.y)/2};

        if (strlen(input_name)!=0){
            DrawTextEx(customFont, input_name, name_position, 25, 1, BLACK );
        }
        
        // text box for DOB

        Rectangle dobbox = { SCREEN_WIDTH/3, namebox.y + namebox.height + 20, txtboxwidth, txtboxheight };
        DrawRectangleRounded(dobbox, 0.3, 10, LIGHTGRAY);

        DrawRectangleRoundedLinesEx(dobbox, 0.3, 10, 0.2, dobActive ? BLACK : LIGHTGRAY);

        const char *doblabel = "Date of Birth:";
        Vector2 doblabel_textsize = MeasureTextEx(customFont, doblabel, 30, 1);
        Vector2 doblabel_position = {dobbox.x - doblabel_textsize.x - 20, dobbox.y + (dobbox.height - doblabel_textsize.y)/2};

        DrawTextEx(customFont, doblabel, doblabel_position, 30, 1, BLACK);

        const char *dob_ph = "Enter your DOB (dd-mm-yyyy)";
        Vector2 dobph_textsize = MeasureTextEx(customFont, dob_ph, 25, 1);
        Vector2 dobph_position = {dobbox.x + (dobbox.width - dobph_textsize.x)/2,dobbox.y + (dobbox.height - dobph_textsize.y)/2};

        DrawTextEx(customFont, dob_ph, dobph_position, 25, 1, dobActive_ph ? BLACK : LIGHTGRAY);

        if (CheckCollisionPointRec(mouse, dobbox) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            accnoActive = false;
		    aadhaarActive = false;
		    nameActive = false;
		    dobActive = true;
		    mobilenoActive = false;
		    passActive = false;
		    conpassActive = false;
        }

        if (strlen(input_dob) != 0 ) {
            dobActive_ph = false;
        }

        if ( !dobActive && strlen(input_dob) == 0 ){
            dobActive_ph = true;
        }

        Vector2 dob_textsize = MeasureTextEx(customFont, input_dob, 25, 1);
        Vector2 dob_position = {(SCREEN_WIDTH - dob_textsize.x)/2,dobbox.y + (dobbox.height - dob_textsize.y)/2};

        if (strlen(input_dob)!=0){
            DrawTextEx(customFont, input_dob, dob_position, 25, 1, BLACK );
        }

        // textbox for Aadhaar Number

		Rectangle aadhaarbox = { SCREEN_WIDTH/3, dobbox.y + dobbox.height + 20, txtboxwidth, txtboxheight };
        DrawRectangleRounded(aadhaarbox, 0.3, 10, LIGHTGRAY);

        DrawRectangleRoundedLinesEx(aadhaarbox, 0.3, 10, 0.2, aadhaarActive ? BLACK : LIGHTGRAY);

        const char *aadhaarlabel = "Aadhaar Number:";
        Vector2 aadhaarlabel_textsize = MeasureTextEx(customFont, aadhaarlabel, 30, 1);
        Vector2 aadhaarlabel_position = {aadhaarbox.x - aadhaarlabel_textsize.x - 20, aadhaarbox.y + (aadhaarbox.height - aadhaarlabel_textsize.y)/2};

        DrawTextEx(customFont, aadhaarlabel, aadhaarlabel_position, 30, 1, BLACK);

        const char *aadhaar_ph = "Enter your Aadhaar Number";
        Vector2 aadhaarph_textsize = MeasureTextEx(customFont, aadhaar_ph, 25, 1);
        Vector2 aadhaarph_position = {aadhaarbox.x + (aadhaarbox.width - aadhaarph_textsize.x)/2,aadhaarbox.y + (aadhaarbox.height - aadhaarph_textsize.y)/2};

        DrawTextEx(customFont, aadhaar_ph, aadhaarph_position, 25, 1, aadhaarActive_ph ? BLACK : LIGHTGRAY);

        if (CheckCollisionPointRec(mouse, aadhaarbox) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            accnoActive = false;
		    aadhaarActive = true;
		    nameActive = false;
		    dobActive = false;
		    mobilenoActive = false;
		    passActive = false;
		    conpassActive = false;
        }

        if (strlen(input_aadhaar) != 0 ) {
            aadhaarActive_ph = false;
        }

        if ( !aadhaarActive && strlen(input_aadhaar) == 0 ){
            aadhaarActive_ph = true;
        }

        Vector2 aadhaar_textsize = MeasureTextEx(customFont, input_aadhaar, 25, 1);
        Vector2 aadhaar_position = {(SCREEN_WIDTH - aadhaar_textsize.x)/2,aadhaarbox.y + (aadhaarbox.height - aadhaar_textsize.y)/2};

        if (strlen(input_aadhaar)!=0){
            DrawTextEx(customFont, input_aadhaar, aadhaar_position, 25, 1, BLACK );
        }

        // textbox for Mobile Number

        Rectangle mobilenobox = { SCREEN_WIDTH/3, aadhaarbox.y + aadhaarbox.height + 20, txtboxwidth, txtboxheight };
        DrawRectangleRounded(mobilenobox, 0.3, 10, LIGHTGRAY);

        DrawRectangleRoundedLinesEx(mobilenobox, 0.3, 10, 0.2, mobilenoActive ? BLACK : LIGHTGRAY);

        const char *mobilenolabel = "Mobile Number:";
        Vector2 mobilenolabel_textsize = MeasureTextEx(customFont, mobilenolabel, 30, 1);
        Vector2 mobilenolabel_position = {mobilenobox.x - mobilenolabel_textsize.x - 20, mobilenobox.y + (mobilenobox.height - mobilenolabel_textsize.y)/2};

        DrawTextEx(customFont, mobilenolabel, mobilenolabel_position, 30, 1, BLACK);

        const char *mobileno_ph = "Enter your Mobile Number";
        Vector2 mobilenoph_textsize = MeasureTextEx(customFont, aadhaar_ph, 25, 1);
        Vector2 mobilenoph_position = {mobilenobox.x + (mobilenobox.width - mobilenoph_textsize.x)/2,mobilenobox.y + (mobilenobox.height - mobilenoph_textsize.y)/2};

        DrawTextEx(customFont, mobileno_ph, mobilenoph_position, 25, 1, mobilenoActive_ph ? BLACK : LIGHTGRAY);

        if (CheckCollisionPointRec(mouse, mobilenobox) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            accnoActive = false;
            aadhaarActive = false;
            nameActive = false;
            dobActive = false;
            mobilenoActive = true;
            passActive = false;
            conpassActive = false;
        }

        if (strlen(input_mobileno) != 0 ) {
            mobilenoActive_ph = false;
        }

        if ( !mobilenoActive && strlen(input_mobileno) == 0 ){
            mobilenoActive_ph = true;
        }

        Vector2 mobileno_textsize = MeasureTextEx(customFont, input_mobileno, 25, 1);
        Vector2 mobileno_position = {(SCREEN_WIDTH - mobileno_textsize.x)/2,mobilenobox.y + (mobilenobox.height - mobileno_textsize.y)/2};

        if (strlen(input_mobileno)!=0){
            DrawTextEx(customFont, input_mobileno, mobileno_position, 25, 1, BLACK );
        }

        // text box for password
        
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
        EndDrawing();
    }

    UnloadTexture(Logo);
    UnloadFont(customFont);

    CloseWindow();
    return 0;
}

