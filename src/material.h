// texture loading system

// Texture name to use when you want to decide to use the default texture
#define DECIDE_TEXTURE_NAME "DEFAULT"
// TODO: Generate missing texture from code
//       OR compile it into the program
#define MISSING_TEXTURE_NAME "missing.png"

#include "raylib.h"
#include <vector>

namespace material
{
	// Load texture at fp, relative to the materials/ folder.
	// giveError will choose if it returns the error texture or not.
	Texture loadTexture(const char *fp, bool giveError = true);
}