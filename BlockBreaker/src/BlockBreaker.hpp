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

class Ball{

    public:
        Ball(const char* imagePath, Vector2 imagePosition);
        ~Ball();
        void Draw();
        void Update();
        Vector2 BallPosition;

    private:
        Texture2D BallTexture;

};



class Blocks{

    public:
        Blocks(const char* imagePath, Vector2 imagePosition);
        ~Blocks();
        void Draw();
        void Update();
        Vector2 BlockPosition;

    private:
        Texture2D BlockTexture;

};