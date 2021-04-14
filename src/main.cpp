// Raylib
#include "raylib.h"

#include "entities.h"

#define PHYSAC_IMPLEMENTATION
#include "physac.h"


int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 416; // 416 fits in a 16x16 grid

    InitWindow(screenWidth, screenHeight, "Platforrmer");

    SetTargetFPS(60);

    // Camera
    Camera2D Camera = Camera2D();

    Camera.target = Vector2({0,0});
    Camera.offset = Vector2({screenWidth/2, screenHeight/2});
    Camera.zoom = 1.0f;

    InitPhysics();

    // Create the player
    EntityPlayer player = EntityPlayer(Vector2({0,0}));


    // Test floor, purely defined in physics
    PhysicsBody floor = CreatePhysicsBodyRectangle(Vector2({0,128}), 100, 32, 1);
    floor->enabled = false;

    // Main game loop
    while (!WindowShouldClose())
    {
        PhysicsStep();

        Camera.target = player.GetPosition();

        BeginDrawing();
            ClearBackground(SKYBLUE);

            BeginMode2D(Camera);

                player.Render();

                DrawCircle(800/2, 416/2, 100, RED);

            EndMode2D();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}

