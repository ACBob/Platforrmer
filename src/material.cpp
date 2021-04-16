#include "material.h"
#include <map>
#include <fstream>

#include "nlohmann/json.hpp"
using json = nlohmann::json;

#include <iostream>
#include <loguru.hpp>

#include "include.h" // SHOULD BE IN EVERY FILE!

#define GLSL_VERSION            330

namespace material
{
	material::BobMaterial matMissing;

	// filepaths -> Material
	std::map<str, BobMaterial> mats;
	// string shadername -> shader
	std::map<str, Shader> shaders;
	
	bool init()
	{
		LOG_F(INFO, "Initializing Materials");

		if (!initShaders())
		{
			LOG_F(FATAL, "Could not initialise shaders!");
			return false;
		}

		matMissing = loadMaterial("missing.json", false);

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
			str name; // Name of the shader
			// NOTE: The following are only ever given to raylib, so we don't need them to be c++ strings
			const char *fs; // frag shader
			const char* vs; // vert shader

			Shader shader; // raylib shader object

			// we need to get the str of the FragShader, and then the c_str() of it,
			// So raylib (a C library) knows what we're doing
			fs = shaderdef["FS"].get<str>().c_str();
			vs = shaderdef["VS"].get<str>().c_str(); // Same for the VertShader

			name = shaderdef["name"].get<str>();

			// Allow forcing use of raylib internal vertex shader
			if (char(vs[0]) == '0')
			{
				// Now we tell raylib to compile the shader for us
				shaders[name] = LoadShader(NULL, fs);
			}
			else
			{
				// Now we tell raylib to compile the shader for us
				shaders[name] = LoadShader(vs, fs);
			}

			// and do some logging
			LOG_F(INFO, "Loaded shader %s with ID %i.", name, shader.id);
		}

		ChangeDirectory("..");

		return true;
	}

	// Load texture at fp, relative to the materials/ folder.
	// giveError will choose if it returns the error texture or not.
	BobMaterial loadMaterial(str fp, bool giveError)
	{
		ChangeDirectory("materials");
		
		// We have it loaded already
		if (mats.find(fp) != mats.end())
		{
			ChangeDirectory("..");
			return mats[fp];
		}

		// const char *ext = GetFileExtension(fp);
		// if (strcmp(ext, "json") != 0)
		// {
		// 	LOG_F(ERROR, "Attempted to load a non-json file (%s) as texture.", fp);
		// 	ChangeDirectory("..");
		// }

		for (auto& t : shaders)
			std::cout << t.first << " " << t.second.id << std::endl;

		LOG_F(INFO, "Loading material %s", fp.c_str());

		std::ifstream file(fp);
		json j;
		file >> j;

		str texpath; // "image":
		str shadername; // "shader":

		texpath = j["image"].get<str>();
		shadername = j["shader"].get<str>();

		if (shaders.find(shadername) == shaders.end())
		{
			LOG_F(ERROR, "Invalid Material; %s", shadername);
			return matMissing;
		}

		Texture tex = LoadTexture(texpath.c_str());
		Shader shader = shaders[shadername];

		LOG_F(INFO, "Material %s", fp.c_str());
		LOG_F(INFO, "Uses shader %s", shadername.c_str());
		LOG_F(INFO, "Of ID %i", shader.id);

		BobMaterial mat;
		mat.tex = tex;
		mat.shader = shader;

		ChangeDirectory("..");
		return mat;
	}
}