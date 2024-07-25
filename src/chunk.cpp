#include <vector>
#include "raylib.h"
#include "raymath.h"
#include "chunk.h"


//public
Chunk::Chunk(Vector3 position, Vector3 dimensions)
{
    this->position = position;
    this->dimensions = dimensions;
    up = Vector3{0.0, 1.0, 0.0};
    current = false;

    Image uvimage = LoadImage("../assets/textures/texture.png");
    texture = LoadTextureFromImage(uvimage);
    UnloadImage(uvimage);
}



Chunk::Chunk(Vector3 position) { Chunk(position, Vector3{32, 32, 32}); }

Chunk::~Chunk()
{
    //chunk destructor
}

void Chunk::test()
{
    DrawCube(Vector3{1,1,1}, 1, 1, 1, BLUE);
}

void Chunk::meshTest()
{
    Mesh test = { 0 };

    test.triangleCount = 2;
    test.vertexCount = test.triangleCount * 3;
    test.vertices = (float *)MemAlloc(test.vertexCount*3*sizeof(float));
    test.texcoords = (float *)MemAlloc(test.vertexCount*2*sizeof(float));
    test.normals = (float *)MemAlloc(test.vertexCount*3*sizeof(float));

    test.vertices[0] = 0;
    test.vertices[1] = 0;
    test.vertices[2] = 0;
    test.vertices[3] = 0;
    test.vertices[4] = 0;
    test.vertices[5] = -1;
    test.vertices[6] = -1;
    test.vertices[7] = 0;
    test.vertices[8] = 0;

    test.normals[0] = 0;
    test.normals[1] = 1;
    test.normals[2] = 0;
    test.normals[3] = 0;
    test.normals[4] = 1;
    test.normals[5] = 0;
    test.normals[6] = 0;
    test.normals[7] = 1;
    test.normals[8] = 0;

    test.texcoords[0] = 1;
    test.texcoords[1] = 1;
    test.texcoords[2] = 1;
    test.texcoords[3] = 0;
    test.texcoords[4] = 0;
    test.texcoords[5] = 1;

    test.vertices[9]  = -1;
    test.vertices[10] = 0;
    test.vertices[11] = -1;
    test.vertices[12] = -1;
    test.vertices[13] = 0;
    test.vertices[14] = 0;
    test.vertices[15] = 0;
    test.vertices[16] = 0;
    test.vertices[17] = -1;

    test.normals[9]  = 0;
    test.normals[10] = 1;
    test.normals[11] = 0;
    test.normals[12] = 0;
    test.normals[13] = 1;
    test.normals[14] = 0;
    test.normals[15] = 0;
    test.normals[16] = 1;
    test.normals[17] = 0;

    test.texcoords[6] = 0;
    test.texcoords[7] = 0;
    test.texcoords[8] = 0;
    test.texcoords[9] = 1;
    test.texcoords[10] = 1;
    test.texcoords[11] = 0;

    UploadMesh(&test, false);

    Model ter = LoadModelFromMesh(test);

    ter.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;

    DrawModel(ter, Vector3{0, 0, 0}, 1.0f, RAYWHITE);

}



void Chunk::populate()
{
    blocks = (short*)MemAlloc(dimensions.x * dimensions.y * dimensions.z * sizeof(short));

    for(int i = 0; i < ((dimensions.x * dimensions.y * dimensions.z / 2) - 1); i++)
    {
        blocks[i] = (short)1;
    }
    for(int i = (dimensions.x * dimensions.y * dimensions.z / 2); i < (dimensions.x * dimensions.y * dimensions.z); i++)
    {
        blocks[i] = (short)0;
    }
}



void Chunk::setPosition(Vector3 position) { this->position = position; }

Vector3 Chunk::getPosition() { return position; }

void Chunk::setRotation(Vector3 up) { this->up = up; }



// void Chunk::rotate(Vector3 rotate)
// {
//     rotate = Vector3Normalize(rotate);
//     up = Vector3Add(Vector3Scale(rotate, up.x),)
// }



Vector3 Chunk::getRotation() { return up; }

void Chunk::draw_Mesh() {
    if (!current) {
        UnloadMesh(mesh);
        generateMesh();
        current = true;
        
        // UnloadModel(model);
        UploadMesh(&mesh, false);
        model = LoadModelFromMesh(mesh);
        model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;
    }

    RAYLIB_H::DrawModel(model, this->position, 1.0f, RAYWHITE);
}

void Chunk::rebuild()
{
    this->current = false;
    blocks[(int)(dimensions.x * dimensions.y * dimensions.z / 2 - 1) + testing] = (short)1;
    testing++;
}

void Chunk::innitMesh() { 
    generateMesh();
    UploadMesh(&mesh, false);
    model = LoadModelFromMesh(mesh);
    model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;

}

void Chunk::dig()
{
    //dig
}

void Chunk::place()
{
    //place
}



//private
RAYLIB_H::Vector3 Chunk::points[8] =
{
    RAYLIB_H::Vector3{0.5, 0.5, 0.5}, RAYLIB_H::Vector3{-0.5, 0.5, 0.5}, RAYLIB_H::Vector3{-0.5, 0.5, -0.5}, RAYLIB_H::Vector3{0.5, 0.5, -0.5},
    RAYLIB_H::Vector3{0.5, -0.5, -0.5}, RAYLIB_H::Vector3{-0.5, -0.5, -0.5}, RAYLIB_H::Vector3{-0.5, -0.5, 0.5}, RAYLIB_H::Vector3{0.5, -0.5, 0.5}
};

RAYLIB_H::Vector3 Chunk::tris[12] =
{
    RAYLIB_H::Vector3{3, 1, 0}, RAYLIB_H::Vector3{3, 2, 1},
    RAYLIB_H::Vector3{7, 6, 5}, RAYLIB_H::Vector3{7, 5, 4},
    RAYLIB_H::Vector3{7, 4, 0}, RAYLIB_H::Vector3{0, 4, 3},
    RAYLIB_H::Vector3{2, 6, 1}, RAYLIB_H::Vector3{5, 6, 2},
    RAYLIB_H::Vector3{1, 7, 0}, RAYLIB_H::Vector3{7, 1, 6},
    RAYLIB_H::Vector3{5, 2, 3}, RAYLIB_H::Vector3{5, 3, 4},
};

// Normals for each face direction
RAYLIB_H::Vector3 Chunk::faceNormals[6] = {
    RAYLIB_H::Vector3{0, 1, 0},  // Up
    RAYLIB_H::Vector3{0, -1, 0}, // Down
    RAYLIB_H::Vector3{1, 0, 0},  // Right
    RAYLIB_H::Vector3{-1, 0, 0}, // Left
    RAYLIB_H::Vector3{0, 0, 1},  // Front
    RAYLIB_H::Vector3{0, 0, -1}  // Back
};

RAYLIB_H::Vector2 Chunk::texturecoords[12][3] =
{
    {RAYLIB_H::Vector2{1, 0}, RAYLIB_H::Vector2{0, 1}, RAYLIB_H::Vector2{1, 1}},
    {RAYLIB_H::Vector2{1, 0}, RAYLIB_H::Vector2{0, 0}, RAYLIB_H::Vector2{0, 1}},
    
    {RAYLIB_H::Vector2{1, 0}, RAYLIB_H::Vector2{0, 0}, RAYLIB_H::Vector2{0, 1}},
    {RAYLIB_H::Vector2{1, 0}, RAYLIB_H::Vector2{0, 1}, RAYLIB_H::Vector2{1, 1}},
    
    {RAYLIB_H::Vector2{0, 1}, RAYLIB_H::Vector2{1, 1}, RAYLIB_H::Vector2{0, 0}},
    {RAYLIB_H::Vector2{0, 0}, RAYLIB_H::Vector2{1, 1}, RAYLIB_H::Vector2{1, 0}},
    
    {RAYLIB_H::Vector2{0, 0}, RAYLIB_H::Vector2{1, 1}, RAYLIB_H::Vector2{1, 0}},
    {RAYLIB_H::Vector2{0, 1}, RAYLIB_H::Vector2{1, 1}, RAYLIB_H::Vector2{0, 0}},
    
    {RAYLIB_H::Vector2{0, 0}, RAYLIB_H::Vector2{1, 1}, RAYLIB_H::Vector2{1, 0}},
    {RAYLIB_H::Vector2{1, 1}, RAYLIB_H::Vector2{0, 0}, RAYLIB_H::Vector2{0, 1}},
    
    {RAYLIB_H::Vector2{1, 1}, RAYLIB_H::Vector2{1, 0}, RAYLIB_H::Vector2{0, 0}},
    {RAYLIB_H::Vector2{1, 1}, RAYLIB_H::Vector2{0, 0}, RAYLIB_H::Vector2{0, 1}}
};

/*
//texcoords for each face direction
// RAYLIB_H::Vector2 Chunk::texturecoords[6] =
// {
//     {1/(float)3, 0.5},  // Up
//     {1/(float)3, 0.0},  // Down
//     {1.0, 0.5},         // Right
//     {0.0, 0.75},        // Left
//     {1/(float)3, 0.75}, // Front
//     {1/(float)3, 0.25}  // Back
// };

//texcoords for the verticies of the face
// RAYLIB_H::Vector2 Chunk::texfacecoords[4] = {
//     {},
//     {},
//     {},
//     {}
// };
*/

int Chunk::getBlock(int index)
{
    if(index == -1)
    {
        return -1; //replace with proper chunk boundary handling later
    }
    else
    {
        return blocks[index];
    }
}

int Chunk::traverse(RAYLIB_H::Vector3 coordinate)
{
    if(coordinate.x >= dimensions.x || coordinate.x < 0 || coordinate.y >= dimensions.y || coordinate.y < 0 || coordinate.z >= dimensions.z || coordinate.z < 0)
    {
        return -1;
    }
    else
    {
        return (int)((coordinate.z) + ((coordinate.x) * dimensions.z) + ((coordinate.y) * dimensions.x * dimensions.z));
    }
}

int Chunk::traverse(RAYLIB_H::Vector3 coordinate, RAYLIB_H::Vector3 offset)
{
    return Chunk::traverse(RAYMATH_H::Vector3Add(coordinate, offset));
}

void Chunk::generateMesh() 
{
    RAYLIB_H::Vector3 current;
    int numFaces = 0;

    std::vector<float> vertices;
    std::vector<float> normals;
    std::vector<float> texcoords;

    for (int i = 0; i < (dimensions.x * dimensions.y * dimensions.z); i++) {
        if (blocks[i] != 0) {
            current = {
                (float)((i % (int)(dimensions.x * dimensions.z)) / (int)dimensions.z),
                (float)(i / (int)(dimensions.x * dimensions.z)),
                (float)(i % (int)dimensions.z)
            };
            for (int faceDir = 0; faceDir < 6; faceDir++) {
                if (!(Chunk::getBlock(Chunk::traverse(current, faceNormals[faceDir])) >= 1)) {
                    for (int j = 0; j < 6; j++) {
                        int triIndex = faceDir * 2 + j / 3;
                        RAYLIB_H::Vector3 tri = tris[triIndex];
                        int pointIndex = (j % 3 == 0) ? tri.x : ((j % 3 == 1) ? tri.y : tri.z);
                        RAYLIB_H::Vector3 vertex = points[pointIndex];

                        vertices.push_back(current.x + vertex.x);
                        vertices.push_back(current.y + vertex.y);
                        vertices.push_back(current.z + vertex.z);

                        normals.push_back(faceNormals[faceDir].x);
                        normals.push_back(faceNormals[faceDir].y);
                        normals.push_back(faceNormals[faceDir].z);

                        texcoords.push_back(texturecoords[triIndex][j % 3].x);
                        texcoords.push_back(texturecoords[triIndex][j % 3].y);
                    }
                    numFaces++;
                }
            }
        }
    }

    mesh = { 0 };

    mesh.triangleCount = numFaces * 2;
    mesh.vertexCount = numFaces * 6;

    // Allocate memory using MemAlloc and copy data from vectors
    mesh.vertices = (float *)MemAlloc(vertices.size() * sizeof(float));
    std::copy(vertices.begin(), vertices.end(), mesh.vertices);

    mesh.normals = (float *)MemAlloc(normals.size() * sizeof(float));
    std::copy(normals.begin(), normals.end(), mesh.normals);

    mesh.texcoords = (float *)MemAlloc(texcoords.size() * sizeof(float));
    std::copy(texcoords.begin(), texcoords.end(), mesh.texcoords);
}


// (float)((i % (int)(dimensions.x * dimensions.z)) / (int)dimensions.z),
// (float)(i / (int)(dimensions.x * dimensions.z)),
// (float)(i % (int)dimensions.z)

// for(int i = 0; i < dimensions.y; i++)
//     {
//         for(int j = 0; i < dimensions.z; i++)
//         {
//             for(int k = 0; i < dimensions.x; i++)
//             {
                
//             }
//         }
//     }