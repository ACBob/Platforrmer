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
using namespace entities;

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
std::vector<EntityTile> *EntityLevel::GetTiles()
{
	return &tiles;
}

void EntityLevel::Render( bool debug )
{
	// Render tiles
	for ( auto tile : tiles )
		tile.Render();

	// Render our entity world
	entityWorld.Render( debug );
}

// TODO: THIS IN A MUCH MUCH BETTER WAY
// 0 -> INVALID
std::map<str, int> entids = { { "base", 0 }, { "player", 0 }, { "tile", 0 }, { "phys_ball", 1 } };

EntityLevel loadLevel( str fp )
{
	ChangeDirectory( "levels" );
	EntityLevel level;

	json j;

	std::ifstream f( fp );
	try
	{
		j = json::parse( f, nullptr, true, true );
	}
	catch ( json::parse_error &e )
	{
		LOG_F( ERROR, "Level file %s is malformed! (ERROR %i)", fp.c_str(), e.id );
		LOG_F( ERROR, e.what() );
		ChangeDirectory( ".." );
		return level; // Return blank level
	}
	ChangeDirectory( ".." );

	// Load blocks
	for ( json blockdef : j["blocks"] )
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
		x *= 16;
		y *= 16; // Assume it to be grid-based

		position.Set( x, y );

		// TODO: textureName
		//! This requires the material system!

		// And now the tile type
		// TODO: Should we allow it to be determined from material, if absent?
		// TODO: DETERMINE INSTEAD OF ASSUMING GROUND!
		typeOfTile = TileType::TL_GRND;

		// And now make a tile entity
		EntityTile tile( level.GetPhysWorld() );
		// Create its' body
		tile.CreateBody( level.GetPhysWorld() );

		// Set its' attributes
		tile.SetPosition( position );
		tile.SetType( typeOfTile );
		// TODO: Material

		// Now add it to our tiles
		level.GetTiles()->push_back( tile );
	}

	for ( json entdef : j["entities"] )
	{
		// TODO: THIS IN A MUCH MUCH BETTER WAY
		str entname = entdef["entname"].get<str>();
		EntityBase *ent;

		switch ( entids[entname] )
		{
			case 0:
				LOG_F( ERROR, "Entity of type %s cannot be created with levels.", entname.c_str() );
				continue;
				break;

			case 1: // PHYS_BALL
				ent = level.GetWorld()->NewEntity<EntityBouncyBall>();
				break;

			default:
				LOG_F( ERROR, "Unkown Entity %s.", entname.c_str() );
				continue;
				break;
		}

		Vector pos( 0, 0 );

		// For now all level coordinates are grid based
		pos.x = entdef["pos"][0].get<float>() * 16;
		pos.y = entdef["pos"][1].get<float>() * 16;

		ent->SetPosition( pos );
	}

	return level;
}