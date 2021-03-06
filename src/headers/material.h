// texture loading system

// Texture name to use when you want to decide to use the default texture
#define DECIDE_TEXTURE_NAME "DEFAULT"
// TODO: Generate missing texture from code
//       OR compile it into the program
#define MISSING_TEXTURE_NAME "missing.png"

#include "raylib.h"
#include <vector>

#include "include.h" // SHOULD BE IN EVERY FILE!

#pragma once

namespace material
{
	struct BobMaterial
	{
		Texture tex;
		Shader shader;
	};

	// Initialise the system
	bool init();
	// ONLY TO BE CALLED BY INIT()
	bool initShaders();

	Shader getShader( str name );

	// Load texture at fp, relative to the materials/ folder.
	// giveError will choose if it returns the error texture or not.
	BobMaterial loadMaterial( str fp, bool giveError = true );
} // namespace material