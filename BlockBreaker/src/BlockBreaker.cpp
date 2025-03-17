#include "BlockBreaker.hpp"

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

    //Debug
    if(IsKeyDown(KEY_R)){

        PaddlePosition.x = 640;

    }

    /*Side Detection/Prevention*/

    //Right Side
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

}

void Ball::Draw(){

    DrawTextureV(BallTexture, BallPosition, WHITE);

}

void Ball::Update(){

    

}
