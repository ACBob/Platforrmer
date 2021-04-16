#include "material.h"

namespace material
{
	Texture texMissing;
	
	bool init()
	{
		texMissing = loadTexture("missing.png", false);
		return true;
	}

	// Load texture at fp, relative to the materials/ folder.
	// giveError will choose if it returns the error texture or not.
	Texture loadTexture(const char *fp, bool giveError)
	{
		if (!FileExists(fp))
		{
			if (giveError)
				return texMissing;
		}

		return LoadTexture(fp);
	}
}