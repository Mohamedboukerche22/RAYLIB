#include <iostream>
#include <math.h>
#include <raylib.h>
/*
** written by mohamed Boukerche
** github.com/mohamedboukerche22
** 21:00 14/01/2026
** 3d player movement example in raylib using c++17
** to comile use :
** g++ main.cpp -o game -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
** run : ./game
** make sure you have raylib installed
** my screen resolution is 1920x1080
** you can change it in the defines btw 
***/

using namespace std;

typedef enum GameState {
  MENU,
  PLAYING,
  /*PAUSED soon */
  SETTINGS
} GameState;

// show fps in screen function to call it in game loop
void show_fps_in_screen() {
  DrawText(TextFormat("FPS: %i", GetFPS()), 10, 40, 20, RED);
}

struct Player {
  Vector3 position;
  Vector3 velocity;
  bool grounded;
};

#define SPEED 5.0f
#define GRAVITY 20.0f
#define JUMP_FORCE 8.0f
#define GROUNDY 1.0f
#define CAM_DISTANCE 6.0f
#define WINDOW_WIDTH 1920 // chnage this  by your resolution 
#define WINDOW_HEIGHT 1080 // also this 
#define MOUSE_SENSITIVITY 0.2f
#define MODEL_FORWARD_OFFSET 180.0f

int main() {
  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "moha's 3d robot game");
  int FPS = 60;
  SetTargetFPS(FPS);
  GameState gameState = MENU;

  Model model = LoadModel("assets/robot.glb");
  Camera3D camera = {{3, 3, 3}, {0, 0, 0}, {0, 1, 0}, 45, 0};
  if (model.meshCount == 0) {
    model = LoadModelFromMesh(GenMeshCube(1.0f, 2.0f, 1.0f));
  }

  Player player;
  player.position = {0, 2, 0};
  player.velocity = {0, 0, 0};
  player.grounded = false;

  const float speed = 5.0f;
  const float gravity = 20.f;
  const float jumpForce = 8.0f;
  const float groundy = 1.0f;
  float playerAngle = 0.0f;
  float sensitivity = 0.2f;

  DisableCursor();
  // sorry for the mess
  // no mouse

  while (!WindowShouldClose()) {
    if (gameState == MENU) {
      BeginDrawing();
      ClearBackground(WHITE);
      show_fps_in_screen();
      DrawText("MOha'S game",
               (GetScreenWidth() / 2) - MeasureText("MOha'S game", 50),
               GetScreenHeight() / 2 - 200, 100, BLACK);
      DrawText("[P] - PLAY", GetScreenWidth() / 2 - 100, 600, 40, BLUE);
      DrawText("[S] - SETTINGS", GetScreenWidth() / 2 - 170, 700, 40, BLUE);
      DrawText("[E] - EXIT", GetScreenWidth() / 2 - 100, 800, 40, BLUE);
      EndDrawing();
      if (IsKeyDown(KEY_P)) {
        gameState = PLAYING;
      }
      if (IsKeyDown(KEY_S)) {
        gameState = SETTINGS;
      }
      if (IsKeyDown(KEY_E)) {
        CloseWindow();
      }
    } else if (gameState == SETTINGS) {
      BeginDrawing();
      ClearBackground(WHITE);
      show_fps_in_screen();

      DrawText("choose FPS:", 100, 100, 80, RED);
      DrawText("[A] - 30 FPS", 100, 200, 60, BLACK);
      DrawText("[B] - 60 FPS", 100, 300, 60, BLACK);
      DrawText("[C] - 120 FPS", 100, 400, 60, BLACK);
      DrawText("[D] - 240 FPS", 100, 500, 60, BLACK);
      if (IsKeyDown(KEY_A)) {
        FPS = 30;
        SetTargetFPS(FPS);
      }
      if (IsKeyDown(KEY_B)) {
        FPS = 60;
        SetTargetFPS(FPS);
      }
      if (IsKeyDown(KEY_C)) {
        FPS = 120;
        SetTargetFPS(FPS);
      }
      if (IsKeyDown(KEY_D)) {
        FPS = 240;
        SetTargetFPS(FPS);
      }

      DrawText("[M] - MENU ", 100, 666, 60, BLACK);
      DrawText("[E] - EXIT ", 100, 777, 60, BLACK);
      if (IsKeyDown(KEY_E)) {
        CloseWindow();
      }
      if (IsKeyDown(KEY_M)) {
        gameState = MENU;
      }

      EndDrawing();
    }

    if (gameState == PLAYING) {
      float dt = GetFrameTime();

      Vector2 mouseDelta = GetMouseDelta();

      playerAngle -= mouseDelta.x * MOUSE_SENSITIVITY;

      if (playerAngle > 360)
        playerAngle -= 360;
      if (playerAngle < 0)
        playerAngle += 360;

      float rad = DEG2RAD * playerAngle;

      Vector3 moveDirection = {0, 0, 0};

      if (IsKeyDown(KEY_W)) {
        player.position.x += sin(rad) * speed * dt;

        player.position.z += cos(rad) * speed * dt;
      }
      if (IsKeyDown(KEY_S)) {
        player.position.x -= sin(rad) * speed * dt;
        player.position.z -= cos(rad) * speed * dt;
      }
      if (IsKeyDown(KEY_D)) {
        player.position.x += cos(rad) * speed * dt;
        player.position.z -= sin(rad) * speed * dt;
      }
      if (IsKeyDown(KEY_A)) {
        player.position.x -= cos(rad) * speed * dt;
        player.position.z += sin(rad) * speed * dt;
      }

      if (IsKeyPressed(KEY_SPACE) && player.grounded) {
        player.velocity.y = jumpForce;
        player.grounded = false;
      }

      player.velocity.y -= GRAVITY * dt;
      player.position.y += player.velocity.y * dt;

      if (player.position.y <= GROUNDY + 0.1f) {
        player.position.y = GROUNDY;
        player.velocity.y = 0;
        player.grounded = true;
      } else {

        // player is not grounded  -*-
        player.grounded = false;
      }
      camera.target = player.position;

      float camDistance = CAM_DISTANCE;
      camera.position = {
          player.position.x - sin(DEG2RAD * playerAngle) * camDistance,
          player.position.y + 3,
          player.position.z - cos(DEG2RAD * playerAngle) * camDistance};

      BeginDrawing();

      ClearBackground(SKYBLUE);

      BeginMode3D(camera);
      DrawPlane({0, 0, 0}, {20, 20}, GRAY);

      /*Vector3 bottom = {
          player.position.x,
          player.position.y - 1,
          player.position.z
      };

      Vector3 top = {
          player.position.x,
          player.position.y + 1,
          player.position.z
      };*/

      DrawModelEx(model, player.position, (Vector3){0, 1, 0}, playerAngle,
                  (Vector3){1, 1, 1}, WHITE);

      EndMode3D();
      DrawText("WASD to move | SPACE to jump", 10, 10, 20, BLACK);

      show_fps_in_screen();

      DrawText(TextFormat("Pos: (%.1f, %.1f, %.1f)", player.position.x,
                          player.position.y, player.position.z),
               10, 70, 20, BLUE);
      // you know like minecraft

      EndDrawing();
    }
  }
  UnloadModel(model);
  CloseWindow();
}
