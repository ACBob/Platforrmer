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
    SetPhysicsTimeStep(2);

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

        if(IsKeyDown(KEY_RIGHT))
            PhysicsAddForce(player.GetPhysicsBody(), Vector2({32,0}));
        if(IsKeyDown(KEY_LEFT))
            PhysicsAddForce(player.GetPhysicsBody(), Vector2({-32,0}));
        if(IsKeyDown(KEY_UP))
            PhysicsAddForce(player.GetPhysicsBody(), Vector2({0,-32}));
        if(IsKeyDown(KEY_DOWN))
            PhysicsAddForce(player.GetPhysicsBody(), Vector2({0,32}));

        BeginDrawing();
            ClearBackground(SKYBLUE);

            BeginMode2D(Camera);

                player.Render();

                DrawCircle(800/2, 416/2, 100, RED);
                DrawRectangle(-50,112,100,32,RED);

            EndMode2D();

        EndDrawing();
    }

    ClosePhysics();
    CloseWindow();

    return 0;
}

