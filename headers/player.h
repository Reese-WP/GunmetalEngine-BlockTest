#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "raylib.h"
#include "raymath.h"

class Player
{
    private:
    Camera camera  = { 0 };
    Ray hit_ray;
    Ray feet;

    int nearest_Chunk();


    public:
    Player(Vector3 position = (Vector3){ 32.0f, 34.0f, 32.0f }, Vector3 target = (Vector3){ 0.0f, 34.0f, 32.0f }, float fov = 45.0f);
    Player(Vector3 position, float fov);
    ~Player();

    void update();
    Camera* get_Camera();
    Ray get_Hit_Ray();

};

#endif