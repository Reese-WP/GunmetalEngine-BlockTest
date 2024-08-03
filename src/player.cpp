#include <vector>
#include "raylib.h"
#include "raymath.h"
#include "player.h"
#include "chunk.h"
// #include <iostream>

float dist(Vector3 p1, Vector3 p2)
{
    return sqrt(((p1.x - p2.x) * (p1.x - p2.x)) + ((p1.y - p2.y) * (p1.y - p2.y)) + ((p1.z - p2.z) * (p1.z - p2.z)));
}


//Private:

std::vector<Chunk *> Player::nearest_Chunks()
{
    //nearest chunk index

    float maxCollisionDistance = 500.0;

    std::vector<Chunk *> chunk_batch(chunks);

    std::vector<Chunk *> chunk_list;
    std::vector<float> distances;

    for(int i = 0; i < chunk_batch.size(); i++)
    {
        if(dist(camera.position, Vector3Add(chunk_batch.at(i)->getPosition(), Vector3Scale(chunk_batch.at(i)->getDimensions(), 0.5))) > maxCollisionDistance)
        {
            chunk_batch.erase(chunk_batch.begin() + i);
            i--;
            continue;
        }

        RayCollision chunk_hit = GetRayCollisionBox(hit_ray, BoundingBox{chunk_batch.at(i)->getPosition(), Vector3Add(chunk_batch.at(i)->getPosition(), chunk_batch.at(i)->getDimensions())});

        if(chunk_hit.hit)
        {
            float distance_to_player = dist(camera.position, Vector3Add(chunk_batch.at(i)->getPosition(), Vector3Scale(chunk_batch.at(i)->getDimensions(), 0.5)));


            if(chunk_batch.size() >= 2)
            {
                if(distances.size() == 1)
                {
                    if(distance_to_player >= distances.at(0))
                    {
                        distances.insert(distances.begin(), distance_to_player);
                        chunk_list.insert(chunk_list.begin(), chunk_batch.at(i));
                        continue;
                    } else {
                        distances.push_back(distance_to_player);
                        chunk_list.push_back(chunk_batch.at(i));
                        continue;
                    }
                }
                else if(distances.size() == 0)
                {
                    // std::cout << "test" << std::endl;
                    distances.insert(distances.begin(), distance_to_player);
                    chunk_list.insert(chunk_list.begin(), chunk_batch.at(i));
                    continue;
                }

                for(int j = distances.size() - 1; j >= 0; j--)
                {
                    if(distance_to_player <= distances.at(j))
                    {
                        chunk_list.insert(chunk_list.begin() + j + 1, chunk_batch.at(i));
                        distances.insert(distances.begin() + j + 1, distance_to_player);
                        break;
                    }
                }

                if(distance_to_player > distances.at(distances.size() - 1))
                {
                    chunk_list.insert(chunk_list.begin(), chunk_batch.at(i));
                    distances.insert(distances.begin(), distance_to_player);
                }

            } else {
                chunk_list.insert(chunk_list.begin(), chunk_batch.at(0));
                break;
            }
            
        }

    }

    return chunk_list;
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
            0.0f);                              // Move to target (zoom)   GetMouseWheelMove()*2.0f
        
        hit_ray.position = camera.position;
        hit_ray.direction = Vector3Normalize(Vector3Subtract(camera.target, camera.position));

        if(IsKeyDown(KEY_R)) { chunks.at(0)->rebuild(); }

        if(IsMouseButtonPressed(MOUSE_BUTTON_RIGHT) || (IsMouseButtonDown(MOUSE_BUTTON_RIGHT) && IsKeyDown(KEY_LEFT_CONTROL)))
        {
            std::vector<Chunk *> chunk_list = nearest_Chunks();
            
            for(int i = chunk_list.size() - 1; i >= 0; i--)
            { if(chunk_list.at(i)->dig(hit_ray)) { break; } }
        }
        else if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && IsKeyDown(KEY_LEFT_CONTROL)))
        {
            std::vector<Chunk *> chunk_list = nearest_Chunks();
            
            for(int i = chunk_list.size() - 1; i >= 0; i--)
            { if(chunk_list.at(i)->place(hit_ray)) { break; } }
        }
    }
}

Camera* Player::get_Camera() { return &camera; }

Ray Player::get_Hit_Ray() { return hit_ray; }