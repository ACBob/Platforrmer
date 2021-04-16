#include "material.h"
#include <map>
#include <fstream>

#include "nlohmann/json.hpp"
using json = nlohmann::json;

#include <iostream>
#include <loguru.hpp>

#define GLSL_VERSION            330

namespace material
{
	Texture texMissing;

	// TODO: Why have I done it this way? Why not make our own class?

	// filepaths -> texture
	std::map<const char*, Texture> texs;
	// texture name -> shader to render with
	std::map<const char*, Shader> textoshader;
	// shadername -> shader
	std::map<const char*, Shader> shaders;
	
	bool init()
	{
		LOG_F(INFO, "Initializing Materials");

		texMissing = loadTexture("missing.json", false);

		if (!initShaders())
		{
			LOG_F(FATAL, "Could not initialise shaders!");
			return false;
		}

		return true;
	}

	bool initShaders()
	{
		LOG_F(INFO, "Initializing Shaders");

		if (!ChangeDirectory("shaders"))
		{
			LOG_F(ERROR, "Could not change to shader directory!");
			return false;
		}

		// Attempt to load shaders/shaders.json
		std::ifstream file("shaders.json");
		json j;
		file >> j;

		std::cout << j << std::endl;

		for (json shaderdef : j)
		{
			const char *name; // Name of the shader
			const char *fs; // frag shader
			const char *vs; // vert shader

			Shader shader; // raylib shader object

			// Call me a boomer but we use c strings, not std::string
			// So we need to get the std::string of the FragShader, and then the c_str() of it!
			fs = shaderdef["FS"].get<std::string>().c_str();
			vs = shaderdef["VS"].get<std::string>().c_str(); // Same for the vertex shader

			// AND The name!
			name = shaderdef["name"].get<std::string>().c_str();

			// Now we tell raylib to compile the shader for us
			shader = LoadShader(vs, fs);

			// Now put it in the hash map
			shaders[name] = shader;

			// and do some logging
			LOG_F(INFO, "Loaded shader %s.", name);
		}

		ChangeDirectory("..");

		return true;
	}

	// Load texture at fp, relative to the materials/ folder.
	// giveError will choose if it returns the error texture or not.
	Texture loadTexture(const char *fp, bool giveError)
	{
		ChangeDirectory("materials");
		if (texs.find(fp) != texs.end())
		{
			ChangeDirectory("..");
			return texs[fp];
		}

		if (!FileExists(fp))
		{
			if (giveError)
			{
				ChangeDirectory("..");
				return texMissing;
			}
		}

		const char *ext = GetFileExtension(fp);
		if (strcmp(ext, "json") != 0)
		{
			LOG_F(ERROR, "Attempted to load a non-json file (%s) as texture.", fp);
			ChangeDirectory("..");
			return texMissing;
		}

		std::ifstream file(fp);
		json j;
		file >> j;

		const char *texpath; // "image":
		const char *shadername; // "shader":

		texpath = j["image"].get<std::string>().c_str();
		shadername = j["shader"].get<std::string>().c_str();

		Texture tex = LoadTexture(texpath);
		Shader shader = shaders[shadername];

		textoshader[fp] = shader;

		ChangeDirectory("..");
		return tex;
	}

	Shader getShader(const char *fp)
	{
		return shaders[fp];
	}
}