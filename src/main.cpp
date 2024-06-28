#include "raylib-cpp.hpp"
#include "raylib.hpp"
#include "raymath.hpp"

int main()
{
    const int screenwidth = 1200;
    const int screenheight = 900;

    raylib::Window window(screenwidth, screenheight, "Test Window");

    raylib::Camera camera(
        raylib::Vector3(10.0f, 10.0f, 10.0f),
        raylib::Vector3(0.0f, 10.0f, 0.0f),
        raylib::Vector3(0.0f, 1.0f, 0.0f),
        45.0f,
        CAMERA_PERSPECTIVE);
    
    SetTargetFPS(60);

    while(!window.ShouldClose())
    {
        camera.Update(
            raylib::Vector3{
                (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))*0.1f - (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))*0.1f,                                  // Move forward-backward
                (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))*0.1f - (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))*0.1f,                               // Move right-left
                (IsKeyDown(KEY_SPACE) || IsKeyDown(KEY_RIGHT_SHIFT))*0.1f - (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_CONTROL))*0.1f    // Move up-down
            },
            raylib::Vector3{
                GetMouseDelta().x * 0.05f,                            // Rotation: yaw
                GetMouseDelta().y * 0.05f,                            // Rotation: pitch
                0.0f                                                // Rotation: roll
            });

        BeginDrawing();

            window.ClearBackground(RAYWHITE);

            camera.BeginMode();

            DrawCubeV(raylib::Vector3(0, 0, 0), raylib::Vector3(1.0, 1.0, 1.0), RED);

            camera.EndMode();
    }

    return 0;
}