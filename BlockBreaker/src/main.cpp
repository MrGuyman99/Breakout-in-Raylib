#include<iostream>
#include<raylib.h>
#include "BlockBreaker.hpp"
#include<vector>
#include<cmath>
#include<ctime>

/*
TODO (New Updates?):
 - Animate Block Destruction
 - Infinte/Repeating Level System
 - Death System
 - Main Menu
*/

int main(){

    //Raylib Stuff
    SetConfigFlags(FLAG_VSYNC_HINT);
    InitWindow(1280, 800, "Block Breaker");
    InitAudioDevice();
    SetTargetFPS(60);

    //Declaring blocks of type Blocks
    std::vector<Blocks> blocks{};

    //Variable Declaration + seed random
    float BlockX = 150; 
    float BlockY = 75;
    int Spacing = 122;
    int NumTimesBlockSpawn = 0;
    srand(std::time(0));
    //One global texture for the blocks (Fixes weird errors)
    Texture2D BlockTexture;

    //Random Number between 1 and 2, if 2 BlueBlock, if 1 GreenBlock
    if((std::rand() % 2) + 1 == 2){

        BlockTexture = LoadTexture("Graphics/BlueBlock.png");

    }
    else{

        BlockTexture = LoadTexture("Graphics/GreenBlock.png");

    }

    //Spawning Paddle and Ball
    Paddle PlayerPaddle{"Graphics/Paddle.png", {640, 725}};
    Ball GameBall{"Graphics/Ball.png", {640, 600}};

    //Spawning Block Loop
    for(int i = 0; i < 24; i++){

        //Adds a new block to the vector, increments the spacing, and increasing the counter
        blocks.emplace_back(BlockTexture, Vector2{BlockX, BlockY});
        BlockX = BlockX + Spacing;
        NumTimesBlockSpawn++;

        //If it equals 8 (i.e one full row) than we increase the Y to make a column
        if(NumTimesBlockSpawn == 8){

            BlockY = BlockY + 100;
            BlockX = 150;
            NumTimesBlockSpawn = 0;

        }

    }

    while(WindowShouldClose() == false){

        //Begin Drawing and Updating
        BeginDrawing();
        PlayerPaddle.Update();
        GameBall.Update();

        //Updates all the blocks in the vector
        for(Blocks& block : blocks){

            block.Update(GameBall);
            block.Draw();

        }

        //Ball & Paddle collision
        if(CheckCollisionCircleRec(Vector2{GameBall.BallPosition.x + 24, GameBall.BallPosition.y + 24}, 8, 
            Rectangle{PlayerPaddle.PaddlePosition.x, PlayerPaddle.PaddlePosition.y, 256, 64})){
                
            GameBall.speed_y = GameBall.speed_y * -1;
            GameBall.BallPosition.y = GameBall.BallPosition.y - 5;
            
            //Ball & Side Paddle Collisions (Looks Complicated, really isn't)
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

        //Draw Everything
        ClearBackground(DARKGRAY);
        GameBall.Draw();
        PlayerPaddle.Draw();
        EndDrawing();

    }

    //Unload and close the window
    UnloadTexture(BlockTexture);
    CloseWindow();
    return 0;
}