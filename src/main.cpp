#include "raylib.h"
#include "player.h"
#include "chunk.h"


int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1200;
    const int screenHeight = 900;

    InitWindow(screenWidth, screenHeight, "Block Game Test - C++");

    Player player((Vector3){ 32.0f, 34.0f, 32.0f }, 45.0f);
    //, (Vector3){ 31.0f, 34.0f, 32.0f }

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    Chunk chunk1(Vector3{0, 0, 0}, Vector3{64, 64, 64});

    chunk1.populate();

    // chunk1.innitMesh();

    // Main game loop
    while (!WindowShouldClose())
    {
        player.update();

        if(IsKeyDown(KEY_R)) { chunk1.rebuild(); }
        
        BeginDrawing();
            ClearBackground(RAYWHITE);
            BeginMode3D(player.camera);



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