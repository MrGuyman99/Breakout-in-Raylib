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

    //Character Controller
    if(IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)){
        
        PaddlePosition.x = PaddlePosition.x - speed;

    }

    if(IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)){
        
        PaddlePosition.x = PaddlePosition.x + speed;

    }

}