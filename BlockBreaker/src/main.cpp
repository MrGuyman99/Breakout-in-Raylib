#include<iostream>
#include<raylib.h>
#include "BlockBreaker.hpp"

int main(){

    SetConfigFlags(FLAG_VSYNC_HINT);
    InitWindow(1280, 800, "Block Breaker");
    InitAudioDevice();
    SetTargetFPS(60);

    Paddle PlayerPaddle{"Graphics/Paddle.png", {640, 725}};
    Ball GameBall{"Graphics/Ball.png", {1200, 5}};
    Blocks Test_Block{"Graphics/BlueBlock.png", {640, 45}};
    
    while(WindowShouldClose() == false){

        BeginDrawing();
        PlayerPaddle.Update();
        GameBall.Update();
        Test_Block.Update(GameBall);

        //Ball & Paddle collision
        if(CheckCollisionCircleRec(Vector2{GameBall.BallPosition.x + 24, GameBall.BallPosition.y + 24}, 8, 
            Rectangle{PlayerPaddle.PaddlePosition.x, PlayerPaddle.PaddlePosition.y, 256, 64})){
                
            GameBall.speed_y = GameBall.speed_y * -1;
            GameBall.BallPosition.y = GameBall.BallPosition.y - 5;
            
            //Ball & Side Paddle Collisions
            if(GameBall.BallPosition.y + 24 > PlayerPaddle.PaddlePosition.y && 
            GameBall.BallPosition.x + 24 < PlayerPaddle.PaddlePosition.x + 128){

                GameBall.BallPosition.x = GameBall.BallPosition.x - 16;
                GameBall.speed_x = GameBall.speed_x * -1;

            }
            else if(GameBall.BallPosition.y + 24 > PlayerPaddle.PaddlePosition.y && 
                GameBall.BallPosition.x + 24 > PlayerPaddle.PaddlePosition.x + 128){

                GameBall.BallPosition.x = GameBall.BallPosition.x + 16;
                GameBall.speed_x = GameBall.speed_x * -1;

            }

            PlaySound(GameBall.HitSound2);

        }

        ClearBackground(DARKGRAY);
        GameBall.Draw();
        PlayerPaddle.Draw();
        Test_Block.Draw();
        EndDrawing();

    }

    CloseWindow();
    return 0;
}