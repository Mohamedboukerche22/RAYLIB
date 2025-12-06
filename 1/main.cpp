#include<raylib.h>
#include<bits/stdc++.h>

int main(){
    int X  = 400,Y = 400;
    Color blue = {30,43,131,1};
    InitWindow(800,800,"moha");
    SetTargetFPS(60);

    while(!WindowShouldClose()){
        
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

       BeginDrawing();
       ClearBackground(blue);
       DrawCircle(X,Y,20,WHITE);
       EndDrawing();
    }
  
    CloseWindow();
    return 0;
}
