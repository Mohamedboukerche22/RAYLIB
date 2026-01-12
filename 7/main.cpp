#include<raylib.h>
#include<iostream>

void move_camera(Camera3D &camera){
  if (IsKeyDown(KEY_W)) camera.position.z -= 0.2f;
  if (IsKeyDown(KEY_S)) camera.position.z += 0.2f;
  if (IsKeyDown(KEY_A)) camera.position.x -= 0.2f;
  if (IsKeyDown(KEY_D)) camera.position.x += 0.2f;
  if (IsKeyDown(KEY_Q)) camera.position.y -= 0.2f;
  if (IsKeyDown(KEY_E)) camera.position.y += 0.2f;
}



using namespace std ;

int main(){
  InitWindow(1024,800,"app");
  SetTargetFPS(60);

   Model model = LoadModel("assets/robot.glb");
   Camera3D camera = { {3,3,3}, {0,0,0}, {0,1,0}, 45, 0 };
   if (model.meshCount == 0) {
        model = LoadModelFromMesh(GenMeshCube(1.0f, 2.0f, 1.0f));
    }
   DisableCursor();
   //CameraMode(camera, CAMERA_FREE);
   // wont work 
  // SetCameraMode(camera, CAMERA_FREE);
   while(!WindowShouldClose()){
     BeginDrawing();
      move_camera(camera);
      ClearBackground(RAYWHITE);
        BeginMode3D(camera);
           DrawModel(model, (Vector3){0, 0, 0}, 1.0f, WHITE);
           DrawGrid(10, 1.0f);
        EndMode3D();
      EndDrawing();
   }
   UnloadModel(model);

  CloseWindow();
}
