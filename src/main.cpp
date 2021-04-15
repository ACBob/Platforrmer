// Raylib
#include "raylib.h"

#include "entities.h"
#include "levelload.h"
#include "config.h"

#include "loguru.hpp"

#include "box2d/box2d.h"

int main(int argc, char* argv[])
{
    // loguru::add_file("console.log", loguru::Truncate, loguru::Verbosity_MAX);

    LOG_F(INFO, "Started as %s", argv[0]);

    // now find the bin directory by assuming that the executable is it...
    const char *binpath = GetDirectoryPath(argv[0]); // Raylib wins again!
    binpath += 2; //! HACKHACKHACK: Remove the ./ from the path
    LOG_F(INFO, "Assuming bin to be %s", binpath);
    const char *respath = GetPrevDirectoryPath(binpath);
    LOG_F(INFO, "Resources are PROBABLY at %s", respath);


    // Try swapping to the respath
    if (!ChangeDirectory(respath))
    {
        LOG_F(FATAL, "Could not change to resources directory! (%s)", respath);
    }

    loguru::add_file("console.log", loguru::Truncate, loguru::Verbosity_MAX);

    LOG_F(INFO, "Loading config...");
    configStruct config = loadConfig("config.json");

    // SetConfigFlags(FLAG_MSAA_4X_HINT);
    // SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(config.screenW, config.screenH, "Platforrmer");

    SetTargetFPS(60);

    // Camera
    Camera2D Camera = Camera2D();

    Camera.target = Vector2({0,0});
    Camera.offset = Vector2({config.screenW/2, config.screenH/2});
    Camera.zoom = 2.0f;

    LOG_F(INFO, "Attempt to load level file");
    
    EntityLevel world = loadLevel("level.json");
    World *entWorld = world.GetWorld();

    EntityPlayer *player = entWorld->NewEntity<EntityPlayer>();
    
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

            EndMode2D();

        EndDrawing();
        
        entWorld->FrameEnd(delta);
    }

    CloseWindow();

    return 0;
}

