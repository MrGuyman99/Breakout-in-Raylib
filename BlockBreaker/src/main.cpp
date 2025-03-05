#include<iostream>
#include<raylib.h>

int main(){

    SetConfigFlags(FLAG_VSYNC_HINT);
    InitWindow(1920, 1080, "Block Breaker");
    SetTargetFPS(60);

    Texture2D background = LoadTexture("Graphics/background_test.png");

    while(WindowShouldClose() == false){

        BeginDrawing();
        ClearBackground(DARKBLUE);
        DrawTexture(background, 0, 0, WHITE);
        EndDrawing();

    
    }

    CloseWindow();
    return 0;
}