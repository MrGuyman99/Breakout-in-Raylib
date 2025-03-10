#include "BlockBreaker.hpp"

Paddle::Paddle(const char *imagePath, Vector2 imagePosition){

    PaddleTexture = LoadTexture(imagePath);
    PaddlePosition = imagePosition;

}

Paddle::~Paddle(){

    UnloadTexture(PaddleTexture);

}

void Paddle::Draw(){

    DrawTextureV(PaddleTexture, PaddlePosition, WHITE);
    
}

void Paddle::Update(){

    int speed = 8;

    if(IsKeyDown(KEY_LEFT)){
        
        PaddlePosition.x = PaddlePosition.x - speed;

    }

    if(IsKeyDown(KEY_RIGHT)){
        
        PaddlePosition.x = PaddlePosition.x + speed;

    }


}