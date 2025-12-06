#include<raylib.h>
#include<bits/stdc++.h>
using namespace std;
/*
** Authour : Mohamed boukerche 
** Date : 6 December 
** Code : Pong game using raylib 
*/


void move(int Y,int X){
        if(IsKeyDown(KEY_W)){
        Y-=3;
        }
        if(IsKeyDown(KEY_S)){
            Y+=3;
        }
        if(IsKeyDown(KEY_D)){
            X+=3;
        }
        if(IsKeyDown(KEY_A)){
            X-=3;
        }
}

int player_score = 0;
int IA_score = 0;

class Ball
{

public:
float x,y;
int speed_x , speed_y;
int raduis;

void Draw(){
   DrawCircle(x,y,raduis,WHITE);
}

void update(){
    x += speed_x;
    y += speed_y;
    if(y + raduis >= GetScreenHeight() || y-raduis <= 0){
        speed_y *= -1;
    }
    if(x + raduis >= GetScreenWidth()){
        IA_score ++;
        speed_x *= -1;
    } 
    if(x-raduis <= 0){
        player_score++;
        speed_x *= -1;
    }
}

};

class Paddle {
protected:
 
void limitMovement(){
    if(y <= 0){
        y=0;
    }
    if(y+height >= GetScreenHeight()){
        y = GetScreenHeight() - height;
    }


}
 public :
 float x,y;
 float width , height;
 int speed;

 void Draw(){
     DrawRectangle(x,y,width,height,WHITE);
 }
 void Update(){
    if(IsKeyDown(KEY_UP) ){
        y -= 3;
   }
    if(IsKeyDown(KEY_DOWN)){
        y += 3;
  }
  limitMovement();
 }
};

class PaddleIA : public Paddle {
    public :

    void Update(int ball_y){
        if(y+height/2 > ball_y){
            y -= speed; 
        }
        if(y+height/2 <= ball_y){
            y += speed;
        }
        limitMovement();
    }

};


int main(){
    // CALLING CLASSES
    Ball ball;
    Paddle player;
    PaddleIA IA;


    Color blue = {25, 55, 204, 1};

    // SCREEN
    int screen_w = 1024;
    int screen_h = 800;

    //BALL 
    ball.x  = screen_w/2;
    ball.y = screen_h/2;
    ball.raduis = 20;
    ball.speed_x = 7;
    ball.speed_y = 7;


     // PLAYER 
    player.width = 25;
    player.height = 120;
    player.x =  screen_w - player.width -10 ;
    player.y = screen_h /2 - player.height/2;
    player.speed  = 10;

    // IA 
    IA.width = 25;
    IA.height = 120;
    IA.x =  10;
    IA.y = screen_h /2 - IA.height/2;
    IA.speed  = 4;

    
    InitWindow(screen_w,screen_h,"moha's game");
    SetTargetFPS(60);

    while(!WindowShouldClose()){
        


       BeginDrawing();
       ball.update();
       DrawLine(screen_w/2, 0 ,screen_h/2 +110 , screen_h, WHITE);

       bool isPlayer  = CheckCollisionCircleRec(Vector2{ball.x,ball.y},ball.raduis,Rectangle{player.x,player.y,player.width,player.height});
       if(isPlayer){
        ball.speed_x *= -1;
       
        }
        bool isIA  = CheckCollisionCircleRec(Vector2{ball.x,ball.y},ball.raduis,Rectangle{IA.x,IA.y,IA.width,IA.height});
       if(isIA){
        ball.speed_x *= -1;
       }


       ClearBackground(blue);
       ball.Draw();
       player.Draw();
       player.Update();
       IA.Draw();
       IA.Update(ball.y);
       DrawText(TextFormat("%i vs %i",player_score,IA_score),screen_w/2 -50  , 50,30,RED);

      
       
       EndDrawing();
    }
  
    CloseWindow();
    return 0;
}
