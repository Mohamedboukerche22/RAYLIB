#include <raylib.h>

/*
** Authour : Mohamed boukerche 
** Date : 15 December 
** Code : 3d simple game with c++ using raylib 
*/


struct Player
{
    Vector3 position;
    Vector3 velocity;
    bool grounded;
};

int main()
{
    InitWindow(800, 800, "3D GAME");

    Camera3D camera = {0};
    camera.position = {5.0f, 5.0f, 5.0f};
    camera.target = {0.0f, 1.0f, 0.0f};
    camera.up = {0.0f, 1.0f, 0.0f};
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    Player player;
    player.position = {0, 1, 0};
    player.velocity = {0, 0, 0};
    player.grounded = false;

    const float speed = 5.0f;
    const float gravity = 20.f;
    const float jumpForce = 8.0f;
    const float groundy = 1.0f;

    SetTargetFPS(120);

    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();

        if (IsKeyDown(KEY_W))
        {
            player.position.z -= speed * dt;
        }
        if (IsKeyDown(KEY_S))
        {
            player.position.z += speed * dt;
        }
        if (IsKeyDown(KEY_D))
        {
            player.position.x += speed * dt;
        }
        if (IsKeyDown(KEY_A))
        {
            player.position.x -= speed * dt;
        }

        if (IsKeyPressed(KEY_SPACE) && player.grounded)
        {
            player.velocity.y = jumpForce;
            player.grounded = false;
        }

        camera.target = player.position;

        camera.position = {
            player.position.x + 5,
            player.position.y + 5,
            player.position.z + 5

        };

        player.velocity.y -= gravity * dt;
        player.position.y += player.velocity.y * dt;
        if (player.position.y <= groundy)
        {
            player.position.y = groundy;
            player.velocity.y = 0;
            player.grounded = true;
        }

        BeginDrawing();

        ClearBackground(SKYBLUE);

        BeginMode3D(camera);
        DrawPlane({0, 0, 0}, {20, 20}, GRAY);
        // DrawCube(player.position, 1, 2, 1, RED);
        Vector3 bottom = {player.position.x, player.position.y - 1, player.position.z};
        Vector3 top = {player.position.x, player.position.y + 1, player.position.z};

        DrawCapsule(bottom, top, 0.5f, 8, 8, WHITE);

        EndMode3D();
        DrawText("WASD to move | SPACE to jump", 10, 10, 20, BLACK);
        DrawText(TextFormat("FPS: %i", GetFPS()), 10, 40, 20, RED);

        EndDrawing();
    }

    CloseWindow();
}
