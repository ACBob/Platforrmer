// Raylib
#include "raylib.h"

#include "entities.h"
#include "levelload.h"
#include "config.h"
#include "material.h"

#include "loguru.hpp"

#include "box2d/box2d.h"

#include "include.h" // SHOULD BE IN EVERY FILE!

int main( int argc, char *argv[] )
{
	// loguru::add_file("console.log", loguru::Truncate, loguru::Verbosity_MAX);

	LOG_F( INFO, "Started as %s", argv[0] );

	// now find the bin directory by assuming that the executable is it...
	str binpath = GetDirectoryPath( argv[0] ); // Raylib wins again!
	LOG_F( INFO, "Assuming bin to be %s", binpath.c_str() );
	str respath = GetPrevDirectoryPath( binpath.c_str() );
	LOG_F( INFO, "Resources are PROBABLY at %s", respath.c_str() );

	// Try swapping to the respath
	if ( !ChangeDirectory( respath.c_str() ) )
	{
		LOG_F( FATAL, "Could not change to resources directory! (%s)", respath.c_str() );
	}

	LOG_F( INFO, "Loading config..." );
	configStruct config = loadConfig( "config.json" );

	loguru::Verbosity VERB = loguru::Verbosity_WARNING;

	if ( config.debugMode )
	{
		LOG_F( INFO, "Started in debug mode!" );
		VERB = loguru::Verbosity_MAX;
	}

	loguru::add_file( "console.log", loguru::Truncate, VERB );

	// SetConfigFlags(FLAG_MSAA_4X_HINT);
	// SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow( config.screenW, config.screenH, "Platforrmer" );
	SetTargetFPS( config.frameRate );
	BeginDrawing();
	ClearBackground( BLACK );
	DrawText( "Loading....", config.screenW / 2, config.screenH / 2, 24, RED );
	EndDrawing();

	// Init Entities
	entities::init();

	// Init material system
	material::init();

	Shader skyShader = material::getShader( "sky" );

	// Camera
	Camera2D Camera = Camera2D();

	Camera.target = Vector( 0, 0 );
	Camera.offset = Vector( config.screenW / 2, config.screenH / 2 );
	Camera.zoom = 2.0f;

	LOG_F( INFO, "Loading debug level..." );

	EntityLevel world = loadLevel( "devland.json" );
	entities::World *entWorld = world.GetWorld();

	entWorld->physStep = 1.0f / config.frameRate;

	entities::EntityPlayer *player = entWorld->NewEntity<entities::EntityPlayer>();

	// Main game loop
	while ( !WindowShouldClose() )
	{
		if ( IsKeyPressed( KEY_G ) )
			config.debugMode = !config.debugMode;

		float delta = GetFrameTime();
		entWorld->FrameStart( delta );

		entWorld->Update( delta );
		Camera.target = player->GetPosition();

		BeginDrawing();
		{
			ClearBackground( RED );

			// Draw Sky
			BeginShaderMode( skyShader );
			DrawRectangle( 0, 0, config.screenW, config.screenH, WHITE );
			EndShaderMode();

			BeginMode2D( Camera );
			{
				world.Render( config.debugMode );
			}
			EndMode2D();

			DrawFPS( 0, 0 );
		}
		EndDrawing();

		entWorld->FrameEnd( delta );
	}

	CloseWindow();

	return 0;
}
