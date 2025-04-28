#pragma once
#include<raylib.h>
#include<iostream>
#include<string>

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
        int speed_y = -8;
        int speed_x = 8;
        Sound HitSound2 = LoadSound("Audio/BlockBreakerHit.wav");

    private:
        Texture2D BallTexture;
};

class Blocks{

    public:
        Blocks(std::string imagePath, Vector2 imagePosition);
        ~Blocks();
        void Draw();
        void Update(Ball& ball);
        Vector2 BlockPosition;

    private:
        Texture2D BlockTexture;
        bool Destroyed = false;
        int Block_Type; 
};  