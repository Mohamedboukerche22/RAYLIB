#include "player.hpp"

player::player()
{
    image = LoadTexture("assets/3abda9a.png");
    position.x = 100;
    position.y = 100;
    speed = 10;
    health = 100;
}
player::~player()
{
    UnloadTexture(image);
}

void player::Draw()
{
    DrawTextureV(image, position, WHITE);
}

void player::Update()
{
    if (IsKeyDown(KEY_DOWN))
    {
        position.y += speed;
    }
    if (IsKeyDown(KEY_UP))
    {
        position.y -= speed;
    }
    if (IsKeyDown(KEY_LEFT))
    {
        position.x -= speed;
    }
    if (IsKeyDown(KEY_RIGHT))
    {
        position.x += speed;
    }
}

Rectangle player::GetRect()
{

    return Rectangle{position.x,position.y,float(image.width),float(image.height)};
}

int player::GetHealth()
{
    return health;
}

void player::Damage()
{
    health -= 15;
    if (health < 0) health = 0;
}
void player::Reset(){
    health = 100;
}
