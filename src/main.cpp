// Raylib
#include "raylib.h"

#include "entities.h"
#include <vector>

#include "loguru.hpp"

#include "box2d/box2d.h"

int main(void)
{
    loguru::add_file("console.log", loguru::Truncate, loguru::Verbosity_MAX);

    const int screenWidth = 800;
    const int screenHeight = 416; // 416 fits in a 16x16 grid

    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(screenWidth, screenHeight, "Platforrmer");

    SetTargetFPS(60);

    // Camera
    Camera2D Camera = Camera2D();

    Camera.target = Vector2({0,0});
    Camera.offset = Vector2({screenWidth/2, screenHeight/2});
    Camera.zoom = 1.5f;

    EntityWorld daWorld;

    EntityPlayer *player = daWorld.NewEntity<EntityPlayer>();
    assert(player != nullptr);
    
    // Main game loop
    while (!WindowShouldClose())
    {
        float delta = GetFrameTime();

        daWorld.Update(delta);
        Camera.target = player->GetPosition();

        BeginDrawing();
            ClearBackground(SKYBLUE);

            BeginMode2D(Camera);

                daWorld.Render();

                DrawCircle(800/2, 416/2, 100, RED);
                DrawRectangle(-50,112,100,32,RED);

            EndMode2D();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}

