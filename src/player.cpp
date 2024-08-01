#include <vector>
#include "raylib.h"
#include "raymath.h"
#include "player.h"
#include "chunk.h"

//Private:

int Player::nearest_Chunk()
{
    //nearest chunk index

    int maxCollisionDistance = INT_MAX;

    int chunk = -1;

    for(int i = 0; i < chunks.size(); i++)
    {
        RayCollision chunk_hit = GetRayCollisionBox(hit_ray, BoundingBox{chunks[i]->getPosition(), Vector3Add(chunks[i]->getPosition(), chunks[i]->getDimensions())});

        if(chunk_hit.hit && (chunk_hit.distance < maxCollisionDistance))
        {
            maxCollisionDistance = chunk_hit.distance;
            chunk = i;
        }

    }

    return chunk;
}

//Public:

Player::Player(Vector3 position, Vector3 target, float fov)
{
    // Define camera (position, target, up vector)
    camera.position = position;    // Camera position
    camera.target = target;      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = fov;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera projection type

    DisableCursor();
}

Player::Player(Vector3 position, float fov)
{
    // Define camera (position, target, up vector)
    camera.position = position;    // Camera position
    camera.target = (Vector3){position.x - 1, position.y, position.z};      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = fov;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera projection type

    DisableCursor();
}

Player::~Player()
{
}

void Player::update()
{
    if(IsKeyPressed(KEY_TAB))
    {
        if (IsCursorHidden()) EnableCursor();
        else DisableCursor();
    }

    if(IsCursorHidden())
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
        
        hit_ray.position = camera.position;
        hit_ray.direction = Vector3Normalize(Vector3Subtract(camera.target, camera.position));

        if(IsKeyDown(KEY_R)) { chunks[0]->rebuild(); }

        if(IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
        {
            int chunk = nearest_Chunk();
            if(chunk != -1) { chunks[chunk]->dig(hit_ray); }
        }
        else if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            int chunk = nearest_Chunk();
            if(chunk != -1) { chunks[chunk]->place(hit_ray); }
        }
    }
}

Camera* Player::get_Camera() { return &camera; }

Ray Player::get_Hit_Ray() { return hit_ray; }