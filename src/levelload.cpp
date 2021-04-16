// Handles level loading via JSON
// TODO: Maybe support more serialisation methods?

#include "nlohmann/json.hpp"
#include "entities.h"

#include "levelload.h"

#include <fstream>
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>

#include "include.h" // SHOULD BE IN EVERY FILE!

using json = nlohmann::json;

// *TECHNICALLY* an entity
// But not really

EntityLevel::EntityLevel()
{
	entities = entityWorld.GetEntityVector();
}

EntityLevel::~EntityLevel()
{
	tiles.clear();
}

// Return a pointer to the tile list
std::vector<EntityTile>* EntityLevel::GetTiles()
{
	return &tiles;
}

void EntityLevel::Render(bool debug)
{
	// Render tiles
	for (auto tile: tiles)
		tile.Render();

	// Render our entity world
	entityWorld.Render(debug);
}

EntityLevel loadLevel(str fp)
{
	EntityLevel level;

	std::ifstream file(fp);
	json j;
	file >> j;

	// Load blocks
	for (json blockdef : j["blocks"])
	{
		b2Vec2 position;
		str texture;
		TileType typeOfTile;

		// Tiles are defined as such:
		/*
			{
				"pos": [x,y],
				"tex": "textureName",
				"type": tileType
			}
		*/
		// Where x,y can be floats,
		// textureName is a texturename accepted by the material system (TODO)
		// tileType is an enum value name

		// Handle position first

		float x;
		float y;

		x = blockdef["pos"][0].get<float>();
		y = blockdef["pos"][1].get<float>();
		x *= 16; y *= 16; // Assume it to be grid-based

		position.Set(x, y);

		// TODO: textureName
		//! This requires the material system!

		// And now the tile type
		// TODO: Should we allow it to be determined from material, if absent?
		// TODO: DETERMINE INSTEAD OF ASSUMING GROUND!
		typeOfTile = TileType::TL_GRND;
		

		// And now make a tile entity
		EntityTile tile(level.GetPhysWorld());
		// Create its' body
		tile.CreateBody(level.GetPhysWorld());

		// Set its' attributes
		tile.SetPosition(position);
		tile.SetType(typeOfTile);
		// TODO: Material

		// Now add it to our tiles
		level.GetTiles()->push_back(tile);

	}

	return level;
}