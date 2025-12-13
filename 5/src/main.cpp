#include <raylib.h>
#include "player.hpp"


/*
** Authour : Mohamed boukerche 
** Date : 14 December 
** Code : A full game ig with c++ using raylib 
// MENU page 
// SETTINGS
// LOSS page
// VICTORY page
*/

// todo make game's better or 3d why not

typedef enum GameState
{
    PLAYING,
    VICTORY,
    LOSS
} GameState;
typedef enum Game_menu
{
    GAME,
    MENU,
    SETTINGS
} Game_menu;
// struct Health { int str_c; };

void show_fps_in_screen()
{
    DrawText(TextFormat("FPS: %d", GetFPS()), 10, 10, 20, RED);
}

int main()
{
    /*const int Monitor = GetCurrentMonitor();
    const int screen_w  = GetMonitorWidth(Monitor);
    const int screen_h = GetMonitorHeight(Monitor);*/

    InitWindow(GetMonitorHeight(GetCurrentMonitor()), GetMonitorWidth(GetCurrentMonitor()), "moha");
    int framerate = 60;
    SetTargetFPS(framerate);
    // ToggleFullscreen();

    player Player;
    Rectangle bar = Rectangle{800, 200, 200, 175};

    int health = 100;
    GameState gamestate = PLAYING;
    Game_menu gamemenu = MENU;

    while (!WindowShouldClose())
    {
        if (gamemenu == MENU)
        {
            BeginDrawing();
            ClearBackground(WHITE);
            show_fps_in_screen();
            DrawText("3ADA9A'S feet", (GetScreenWidth() / 2) - MeasureText("3ADA9A'S feet", 50), GetScreenHeight() / 2 - 200, 100, BLACK);
            DrawText("[P] - PLAY", GetScreenWidth() / 2 - 100, 600, 40, BLUE);
            DrawText("[S] - SETTINGS", GetScreenWidth() / 2 - 170, 700, 40, BLUE);
            DrawText("[E] - EXIT", GetScreenWidth() / 2 - 100, 800, 40, BLUE);
            EndDrawing();
            if (IsKeyDown(KEY_P))
            {
                gamemenu = GAME;
            }
            if (IsKeyDown(KEY_S))
            {
                gamemenu = SETTINGS;
            }
            if (IsKeyDown(KEY_E))
            {
                CloseWindow();
            }
        }
        else if (gamemenu == GAME)
        {
            Player.Update();
            bool Istoutch = CheckCollisionRecs(Player.GetRect(), bar);
            BeginDrawing();
            ClearBackground(WHITE);
            if (gamestate == PLAYING)
            {
                show_fps_in_screen();
                DrawText(TextFormat("blood %d", health), 100, 50, 50, RED);
                DrawText("do not go onto that box", 100, 600, 20, BLACK);

                if (Istoutch)
                {
                    DrawRectangleLinesEx(bar, 50, RED);
                    DrawText("get out motherfucker", 100, 300, 50, BLACK);
                    Player.Damage();
                    health--;
                    if (health < 0)
                    {
                        gamestate = LOSS;
                    }
                }
                else
                {
                    DrawRectangleLinesEx(bar, 5, BLACK);
                }

                Player.Draw();
            }
            else if (gamestate == LOSS)
            {
                show_fps_in_screen();
                DrawText("LOOSER", (GetScreenWidth() / 2) - MeasureText("LOOSER", 50), GetScreenHeight() / 2 - 200, 100, RED);
                DrawText("[R] - REPLAY", GetScreenWidth() / 2 - 130, 600, 40, BLUE);
                DrawText("[M] - MENU ", GetScreenWidth() / 2 - 130, 700, 40, BLUE);
                DrawText("[E] - EXIT", GetScreenWidth() / 2 - 100, 800, 40, BLUE);
                if (IsKeyDown(KEY_R))
                {
                    gamestate = PLAYING;

                    health = 100;
                }
                if (IsKeyDown(KEY_M))
                {

                    gamemenu = MENU;
                }
                if (IsKeyDown(KEY_E))
                {
                    CloseWindow();
                }
            }
            else if (gamestate == VICTORY)
            {
                show_fps_in_screen();
                DrawText("WINNER", (GetScreenWidth() / 2) - MeasureText("WINNER", 50), GetScreenHeight() / 2 - 200, 100, GREEN);
                DrawText("[R] - REPLAY", GetScreenWidth() / 2 - 160, 600, 40, BLUE);
                DrawText("[M] - MENU ", 100, 666, 60, BLACK);
                DrawText("[E] - EXIT", GetScreenWidth() / 2 - 100, 700, 40, BLUE);
                if (IsKeyDown(KEY_R))
                {
                    gamestate = PLAYING;
                    Player.Reset();
                    health = 100;
                }
                if (IsKeyDown(KEY_M))
                {
                    gamemenu = MENU;
                }
                if (IsKeyDown(KEY_E))
                {
                    CloseWindow();
                }
            }

            EndDrawing();
        }
        else if (gamemenu == SETTINGS)
        {
            BeginDrawing();
            ClearBackground(WHITE);
            show_fps_in_screen();

            DrawText("choose FPS:", 100, 100, 80, RED);
            DrawText("[A] - 30 FPS", 100, 200, 60, BLACK);
            DrawText("[B] - 60 FPS", 100, 300, 60, BLACK);
            DrawText("[C] - 120 FPS", 100, 400, 60, BLACK);
            DrawText("[D] - 240 FPS", 100, 500, 60, BLACK);
            if (IsKeyDown(KEY_A))
            {
                framerate = 30;
                SetTargetFPS(framerate);
            }
            if (IsKeyDown(KEY_B))
            {
                framerate = 60;
                SetTargetFPS(framerate);
            }
            if (IsKeyDown(KEY_C))
            {
                framerate = 120;
                SetTargetFPS(framerate);
            }
            if (IsKeyDown(KEY_D))
            {
                framerate = 240;
                SetTargetFPS(framerate);
            }

            DrawText("[M] - MENU ", 100, 666, 60, BLACK);
            DrawText("[E] - EXIT ", 100, 777, 60, BLACK);
            if (IsKeyDown(KEY_E))
            {
                CloseWindow();
            }
            if (IsKeyDown(KEY_M))
            {
                gamemenu = MENU;
            }

            EndDrawing();
        }
    }
    CloseWindow();
}
