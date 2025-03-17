#include<iostream>
#include<raylib.h>
#include "BlockBreaker.hpp"

int main(){

    SetConfigFlags(FLAG_VSYNC_HINT);
    InitWindow(1280, 800, "Block Breaker");
    SetTargetFPS(60);

    Paddle PlayerPaddle{"Graphics/Paddle.png", {640, 725}};
    Ball GameBall{"Graphics/Ball.png", {640, 400}};

    while(WindowShouldClose() == false){

        BeginDrawing();
        PlayerPaddle.Update();
        GameBall.Update();
        ClearBackground(DARKGRAY);
        PlayerPaddle.Draw();
        GameBall.Draw();
        EndDrawing();

    }

    CloseWindow();
    return 0;
}