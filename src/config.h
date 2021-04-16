#pragma once

#include "nlohmann/json.hpp"
#include <fstream>

#include "include.h" // SHOULD BE IN EVERY FILE!

using json = nlohmann::json;

struct configStruct {
	int screenW;
	int screenH;

	bool debugMode;

	int frameRate;
};

configStruct loadConfig(str fp)
{
	configStruct conf;

	json confjson;

	std::ifstream f(fp);
	confjson << f;
	
	conf.screenW = confjson["screenSize"][0].get<int>();
	conf.screenH = confjson["screenSize"][1].get<int>();

	conf.debugMode = confjson["enableDebug"].get<bool>();

	conf.frameRate = confjson["frameRate"].get<int>();

	return conf;
}