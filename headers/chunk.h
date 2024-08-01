#ifndef CHUNK_H
#define CHUNK_H

#include <vector>
#include "raylib.h"
#include "raymath.h"

class Chunk
{
    private:
        RAYLIB_H::Vector3 position;
        RAYLIB_H::Vector3 dimensions;
        // RAYLIB_H::BoundingBox bounds;
        short *blocks;
        RAYLIB_H::Vector3 up;
        Mesh mesh = { 0 };
        Model model = { 0 };
        Texture2D texture;
        bool current;
        static RAYLIB_H::Vector3 points[8];
        static RAYLIB_H::Vector3 tris[12];
        static RAYLIB_H::Vector3 faceNormals[6];
        static RAYLIB_H::Vector2 texturecoords[12][3];
        // static RAYLIB_H::Vector2 texturecoords[6];
        // static RAYLIB_H::Vector2 texfacecoords[4];

        int getBlock(int index);
        int traverse(RAYLIB_H::Vector3 coord, RAYLIB_H::Vector3 offset);
        int traverse(RAYLIB_H::Vector3 coord);
        void generateMesh();

    public:
        Chunk(RAYLIB_H::Vector3 position);
        Chunk(RAYLIB_H::Vector3 position = {0, 0, 0}, RAYLIB_H::Vector3 dimensions = {32, 32, 32});
        ~Chunk();
        void populate();
        void rebuild();
        void innitMesh();

        void setPosition(RAYLIB_H::Vector3 position);
        RAYLIB_H::Vector3 getPosition();

        void setRotation(RAYLIB_H::Vector3 up);
        // void rotate(RAYLIB_H::Vector3 rotate);
        RAYLIB_H::Vector3 getRotation();

        RAYLIB_H::Vector3 getDimensions();

        void draw_Mesh();

        void dig(Ray hit);
        void place(Ray hit);

        void test();
        void meshTest();

        int testing = 0;
};

extern std::vector<Chunk *> chunks;

#endif