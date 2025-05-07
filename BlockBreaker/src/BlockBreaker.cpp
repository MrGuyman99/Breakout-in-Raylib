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

}

void Ball::Update(Paddle& paddle){

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
    //Ball Starting Stuff
    if(Go == false){

        BallPosition.y = paddle.PaddlePosition.y - 50;
        BallPosition.x = paddle.PaddlePosition.x + 104;
        speed_x = 0;
        speed_y = 0;

    }
    if(IsKeyDown(KEY_UP) && Go == false){

        Go = true;
        speed_x = 8;
        speed_y = -8;

    }

}

Blocks::Blocks(Texture2D& texture, Vector2 imagePosition){

    BlockPosition = imagePosition;
    BlockTexture = texture;

}

Blocks::~Blocks(){

    /*
    Placeholder
    (Texture is a global texture that gets unloaded)
    */

}

void Blocks::Draw(){

    if(Destroyed == false){

        DrawTextureV(BlockTexture, BlockPosition, WHITE);

    }
}

void Blocks::Update(Ball& ball){

    if(Destroyed == false){
        
        if(CheckCollisionCircleRec(Vector2{ball.BallPosition.x + 24, ball.BallPosition.y + 24}, 24, 
            Rectangle{BlockPosition.x, BlockPosition.y, 112, 8}) || CheckCollisionCircleRec(Vector2{ball.BallPosition.x + 24, ball.BallPosition.y + 24}, 24, 
                Rectangle{BlockPosition.x, BlockPosition.y + 70, 112, 8})){

            ball.speed_y = ball.speed_y * -1;
        
            if(ball.speed_y > 0){
            
                ball.BallPosition.y = ball.BallPosition.y + 5;

            }
            else{
            
                ball.BallPosition.y = ball.BallPosition.y - 5;

            }
            
            //Side Collisions
            if(CheckCollisionCircleRec(Vector2{ball.BallPosition.x + 24, ball.BallPosition.y + 24}, 24, 
                Rectangle({BlockPosition.x, BlockPosition.y, 8, 70}))){

                ball.speed_x = ball.speed_x * -1;
                ball.BallPosition.x = ball.BallPosition.x - 5;    

            }
            else if(CheckCollisionCircleRec(Vector2{ball.BallPosition.x + 24, ball.BallPosition.y + 24}, 24, 
                Rectangle({BlockPosition.x + 111, BlockPosition.y, 8, 70}))){

                ball.speed_x = ball.speed_x * -1;
                ball.BallPosition.x = ball.BallPosition.x + 5;
            
            }
            
            PlaySound(ball.HitSound2);
            Destroyed = true;

        }
    }
}