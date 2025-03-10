#pragma once
#include<raylib.h>

class Paddle{

    public:
        Paddle(const char* imagePath, Vector2 imagePosition);
        ~Paddle();
        void Draw();
        void Update();
        Vector2 PaddlePosition;

    private:
        Texture2D PaddleTexture;
        

    
    
};