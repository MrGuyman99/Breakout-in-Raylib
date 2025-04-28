#include "BlockBreaker.hpp"
#include<cmath>
#include<numbers>
#include<iostream>
#include<string>

//Constructer Script
Paddle::Paddle(const char *imagePath, Vector2 imagePosition){

    PaddleTexture = LoadTexture(imagePath);
    PaddlePosition = imagePosition;
    
}

//Deconstructer
Paddle::~Paddle(){

    UnloadTexture(PaddleTexture);

}

void Paddle::Draw(){

    DrawTextureV(PaddleTexture, PaddlePosition, WHITE);
    
}

void Paddle::Update(){

    //Speed Variable (Powerups/adjustabilty)
    int speed = 8;

    /*Character Controller*/
    if(IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)){
        
        PaddlePosition.x = PaddlePosition.x - speed;

    }

    if(IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)){
        
        PaddlePosition.x = PaddlePosition.x + speed;

    }

    //Right Side Escape Prevention
    if(PaddlePosition.x <= 10){

        PaddlePosition.x = 10;

    }

    //Left Side (Significantly More Complicated lol)
    if(PaddlePosition.x + 256 >= GetScreenWidth() - 10){

        PaddlePosition.x = GetScreenWidth() - 10 - 256;

    }

}

Ball::Ball(const char *imagePath, Vector2 imagePosition){

    BallTexture = LoadTexture(imagePath);
    BallPosition = imagePosition;

}

Ball::~Ball() {

    UnloadTexture(BallTexture);
    UnloadSound(HitSound2);
}

void Ball::Draw(){

    DrawTextureV(BallTexture, BallPosition, WHITE);
    DrawCircle(BallPosition.x + 24, BallPosition.y + 24, 2, BLACK);
}

void Ball::Update(){

    BallPosition.x = BallPosition.x + speed_x;
    BallPosition.y = BallPosition.y + speed_y;

    //(48 x 48 is the dimensions of the Ball image)
    if(BallPosition.y <= 0){

        speed_y = speed_y * -1;
        PlaySound(HitSound2);

    }

    if(BallPosition.x >= GetScreenWidth() - 48 || BallPosition.x <= 0){

        speed_x = speed_x * -1;
        PlaySound(HitSound2);
    }

    if(BallPosition.y > GetScreenHeight()){

        //TODO: Put Game Over Stuff Here
        BallPosition.x = 640;
        BallPosition.y = 400;

    }
    if(IsKeyDown(KEY_R)){

        speed_x = 0;
        BallPosition.x = 640;

    }
}

Blocks::Blocks(std::string imagePath, Vector2 imagePosition){

    BlockPosition = imagePosition;
    BlockTexture = LoadTexture(imagePath.c_str());

}

Blocks::~Blocks(){

    UnloadTexture(BlockTexture);

}

void Blocks::Draw(){

    if(Destroyed == false){

        DrawTextureV(BlockTexture, BlockPosition, WHITE);

    }
}

void Blocks::Update(Ball& ball){

    if(Destroyed == false){
        
        if(CheckCollisionCircleRec(Vector2{ball.BallPosition.x + 24, ball.BallPosition.y + 24}, 24, 
            Rectangle{BlockPosition.x, BlockPosition.y, 70, 112})){

            ball.speed_y = ball.speed_y * -1;
        
            if(ball.speed_y > 0){
            
                ball.BallPosition.y = ball.BallPosition.y + 5;

            }
            else{
            
                ball.BallPosition.y = ball.BallPosition.y - 5;

            }
            
            PlaySound(ball.HitSound2);
            Destroyed = true;

        }
    }
}