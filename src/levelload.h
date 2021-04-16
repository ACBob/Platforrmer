#include "entities.h"

#include "include.h" // SHOULD BE IN EVERY FILE!

class EntityLevel
{
	public:
		EntityLevel();

		~EntityLevel();

		// Return a pointer to the tile list
		std::vector<EntityTile*>* GetTiles();
		std::vector<EntityBase*>* entities; // Pointer to entityWorld's entity vector

		World* GetWorld()
		{
			return &entityWorld;
		}

		b2World *GetPhysWorld()
		{
			return entityWorld.GetPhysWorld();
		}

	protected:
		std::vector<EntityTile*> tiles;
		World entityWorld;
};

EntityLevel loadLevel(str fp);