#pragma once
#include<raylib.h>

class player
{
private:
 Texture2D image;
 Vector2 position;
 int speed;   
 int health;
public:
    player();
    ~player();
    void Draw();
    void Update();
    Rectangle GetRect();
    int GetHealth();
    void Damage();
    void Reset();
};

