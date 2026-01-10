#define RAYGUI_IMPLEMENTATION
#include<raylib.h>
#include<iostream>
#include"raygui.h"
using namespace std;

//#define FRAMERATE 60
//change it into a varibale 
#define WIDTH 720
#define HEIGHT 1080

enum  Status{
  HOMEPAGE,
  MAIN,
  SETTINGS,
};

void show_fps_in_screen()
{
    DrawText(TextFormat("FPS: %d", GetFPS()), 10, 10, 20, RED);
}
//float FRAMERATE = 60.0;

Vector2 mouse_position = {0};
int main(){
 
int  FRAMERATE = 60;
int screen_w = GetScreenWidth();
int screen_h = GetScreenHeight();

  InitWindow(screen_w,screen_h ,"moha app");
  SetTargetFPS(FRAMERATE);

  bool clicked =  false ;
  Status status = HOMEPAGE;

while (!WindowShouldClose())
{
    BeginDrawing();
    ClearBackground(RAYWHITE);

    if (status == HOMEPAGE)
    {
        if (GuiButton({(screen_w - 120)/ 2.0f, (screen_h - 30 ) / 2.0f, 120, 30}, "Start"))
        {
            status = MAIN;
        }
        if(GuiButton({100,777 ,120,30},"SETTINGS")){
          status = SETTINGS;
        }
     }
    else if(status == MAIN)
    {
      if(GuiButton({WIDTH/2,HEIGHT/2 -240,120,30}, "return")){
        status = HOMEPAGE;
      }
        DrawText("MAIN SCREEN", 50, 100, 30, GREEN);
    }
    else if(status == SETTINGS)
    {
      if(GuiButton({100,100,120,30},"60 fps")){
        FRAMERATE = 60;
      }
      else if(GuiButton({100,150,120,30},"120 fps")){
        FRAMERATE = 120;
        
      }
      else if (GuiButton({100,200,120,30},"240 fps")){
        FRAMERATE = 240;
      }
      SetTargetFPS(FRAMERATE);
      show_fps_in_screen();
      
    }

    EndDrawing();
}
  CloseWindow();

  return 0;
}
