#include "raylib.h"
#include "chunk.h"




int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1200;
    const int screenHeight = 900;

    InitWindow(screenWidth, screenHeight, "Block Game Test - C++");

    // Define camera (position, target, up vector)
    Camera camera = { 0 };
    camera.position = (Vector3){ 32.0f, 34.0f, 32.0f };    // Camera position
    camera.target = (Vector3){ 0.0f, 34.0f, 32.0f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera projection type

    DisableCursor();

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    Chunk chunk1(Vector3{0, 0, 0}, Vector3{64, 64, 64});

    chunk1.populate();

    chunk1.innitMesh();

    // Main game loop
    while (!WindowShouldClose())
    {
        UpdateCameraPro(&camera,
            Vector3{
                (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))*0.1f - (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))*0.1f,                                  // Move forward-backward
                (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))*0.1f - (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))*0.1f,                               // Move right-left
                (IsKeyDown(KEY_SPACE) || IsKeyDown(KEY_RIGHT_SHIFT))*0.1f - (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_CONTROL))*0.1f    // Move up-down
            },
            Vector3{
                GetMouseDelta().x * 0.05f,                            // Rotation: yaw
                GetMouseDelta().y * 0.05f,                            // Rotation: pitch
                0.0f                                                // Rotation: roll
            },
            GetMouseWheelMove()*2.0f);                              // Move to target (zoom)

        if(IsKeyPressed(KEY_R)) { chunk1.rebuild(); }
        
        BeginDrawing();
            ClearBackground(RAYWHITE);
            BeginMode3D(camera);



                chunk1.draw_Mesh();
                // DrawCube(Vector3{0,0,0}, 1, 1, 1, RED);
                // chunk1.test();
                // chunk1.meshTest();


            EndMode3D();

            DrawFPS(10, 10);
        EndDrawing();

    }

    CloseWindow();
    return 0;
}