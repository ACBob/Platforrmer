// Raylib
#include "raylib.h"

#include "entities.h"


#include <vector>

#define PHYSAC_IMPLEMENTATION
#include "physac.h"

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 416; // 416 fits in a 16x16 grid

    InitWindow(screenWidth, screenHeight, "Platforrmer");

    // Camera
    Camera2D Camera = Camera2D();

    Camera.target = Vector2({0,0});
    Camera.offset = Vector2({screenWidth/2, screenHeight/2});
    Camera.zoom = 1.0f;

    InitPhysics();
    SetPhysicsTimeStep(2);

    std::vector<EntityBase*> entities;

    // Create the player
    EntityPlayer player = EntityPlayer(Vector2({0,0}));
    entities.push_back(&player);


    // Test floor, purely defined in physics
    PhysicsBody floor = CreatePhysicsBodyRectangle(Vector2({0,128}), 100, 32, 1);
    floor->enabled = false;

    // Main game loop
    while (!WindowShouldClose())
    {
        float delta = GetFrameTime();
        for (auto entity : entities)
        {
            entity->PreThink(delta);
        }

        PhysicsStep();

        Camera.target = player.GetPosition();

        for (auto entity : entities)
        {
            entity->Think(delta);
        }

        BeginDrawing();
            ClearBackground(SKYBLUE);

            BeginMode2D(Camera);

                for (auto entity : entities)
                {
                    entity->Render();
                }

                DrawCircle(800/2, 416/2, 100, RED);
                DrawRectangle(-50,112,100,32,RED);

            EndMode2D();

        EndDrawing();

        for (auto entity : entities)
        {
            entity->PostThink(delta);
        }
    }

    ClosePhysics();
    CloseWindow();

    return 0;
}

