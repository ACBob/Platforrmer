// Raylib
#include "raylib.h"

#include "entities.h"
#include <vector>

#include "levelload.h"

#include "loguru.hpp"

#include "box2d/box2d.h"

int main(void)
{
    loguru::add_file("console.log", loguru::Truncate, loguru::Verbosity_MAX);

    const int screenWidth = 800;
    const int screenHeight = 416; // 416 fits in a 16x16 grid

    // SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(screenWidth, screenHeight, "Platforrmer");

    SetTargetFPS(60);

    // Camera
    Camera2D Camera = Camera2D();

    Camera.target = Vector2({0,0});
    Camera.offset = Vector2({screenWidth/2, screenHeight/2});
    Camera.zoom = 2.0f;

    LOG_F(INFO, "Attempt to load level file");
    
    EntityLevel world = loadLevel("level.json");
    World *entWorld = world.GetWorld();

    EntityPlayer *player = entWorld->NewEntity<EntityPlayer>();

    EntityTile *groundTest = entWorld->NewEntity<EntityTile>();

    groundTest->GetPhysicsBody()->SetTransform(b2Vec2(-13, 32), 0);
    
    // Main game loop
    while (!WindowShouldClose())
    {
        float delta = GetFrameTime();
        entWorld->FrameStart(delta);

        entWorld->Update(delta);
        Camera.target = player->GetPosition();

        BeginDrawing();
            ClearBackground(SKYBLUE);

            BeginMode2D(Camera);

                entWorld->Render(true);

                DrawCircle(800/2, 416/2, 100, RED);
                DrawRectangle(-50,112,100,32,RED);

            EndMode2D();

        EndDrawing();
        
        entWorld->FrameEnd(delta);
    }

    CloseWindow();

    return 0;
}

