#include<iostream>
#include<raylib.h>
#include "BlockBreaker.hpp"
#include<vector>

/*
TODO:
 - Fix Weird Black Block Glitch Thing
 - Spawn Blocks properly
 - Animate Block Destruction
 - Infinte/Repeating Level System
 - Death System
 - Main Menu
*/

int main(){

    SetConfigFlags(FLAG_VSYNC_HINT);
    InitWindow(1280, 800, "Block Breaker");
    InitAudioDevice();
    SetTargetFPS(60);

    std::vector<Blocks> blocks{};

    float BlockX, BlockY = 100;
    int Spacing = 122;
    std::string Path = "Graphics/BlueBlock.png";

    Paddle PlayerPaddle{"Graphics/Paddle.png", {640, 725}};
    Ball GameBall{"Graphics/Ball.png", {1200, 5}};

    //TODO: Green / Blue Block switching is working 
    //but it doesn't appear to be displaying properly
    for(int i = 0; i < 10; i++){

        blocks.emplace_back(Path, Vector2{BlockX, BlockY});
        BlockX = BlockX + Spacing;

        if(Path == "Graphics/BlueBlock.png"){

            Path = "Graphics/GreenBlock.png";
            std::cout << "Switched! Equals GreenBlock!\n";

        }
        else{

            Path = "Graphics/BlueBlock.png";
            std::cout << "Switched! Equals BlueBlock!\n";

        }

    }

    while(WindowShouldClose() == false){

        BeginDrawing();
        PlayerPaddle.Update();
        GameBall.Update();

        for(auto& block : blocks){

            block.Update(GameBall);
            block.Draw();

        }

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
        EndDrawing();

    }

    CloseWindow();
    return 0;
}