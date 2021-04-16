#pragma once

#include "nlohmann/json.hpp"
#include <fstream>

using json = nlohmann::json;

struct configStruct {
	int screenW;
	int screenH;

	bool debugMode;
};

configStruct loadConfig(const char *fp)
{
	configStruct conf;

	json confjson;

	std::ifstream f(fp);
	confjson << f;
	
	conf.screenW = confjson["screenSize"][0].get<int>();
	conf.screenH = confjson["screenSize"][1].get<int>();

	conf.debugMode = confjson["enableDebug"].get<bool>();

	return conf;
}