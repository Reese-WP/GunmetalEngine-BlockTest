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

    Chunk chunk1(Vector3{0, 0, 0}, Vector3{32, 32, 32});

    chunks.push_back(&chunk1);

    chunk1.populate();

    Chunk chunk2(Vector3{32, 0, 0}, Vector3{32, 32, 32});

    chunks.push_back(&chunk2);

    chunk2.populate();

    Chunk chunk3(Vector3{0, 0, 32}, Vector3{32, 32, 32});

    chunks.push_back(&chunk3);

    chunk3.populate();

    Chunk chunk4(Vector3{32, 0, 32}, Vector3{32, 32, 32});

    chunks.push_back(&chunk4);

    chunk4.populate();

    Player player((Vector3){ 16.0f, 18.0f, 16.0f }, 45.0f);
    //, (Vector3){ 31.0f, 34.0f, 32.0f }

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())
    {
        player.update();
        
        BeginDrawing();
            ClearBackground(RAYWHITE);
            BeginMode3D(*(player.get_Camera()));



                chunk1.draw_Mesh();
                chunk2.draw_Mesh();
                chunk3.draw_Mesh();
                chunk4.draw_Mesh();
                // DrawCube(Vector3{0,0,0}, 1, 1, 1, RED);
                // chunk1.test();
                // chunk1.meshTest();


            EndMode3D();

            DrawFPS(10, 10);
            DrawText("x", 600, 450, 20, BLACK);
        EndDrawing();

    }

    CloseWindow();
    return 0;
}