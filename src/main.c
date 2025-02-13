#define RAYGUI_IMPLEMENTATION
#include <raygui.h>	
#include <stdio.h>
#include "../include/signup2.h"
// #include "../include/Admin.h"
#include "../include/account.h"
// #include "../include/login_page.h"

int main()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Crest Banking");
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

	long long accno = login_page(Logo,customFont);

    UnloadTexture(Logo);
    UnloadFont(customFont);

    CloseWindow();

	return 0;
}