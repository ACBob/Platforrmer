#include "entities.h"

#include "include.h" // SHOULD BE IN EVERY FILE!

class EntityLevel
{
	public:
		EntityLevel();

		~EntityLevel();

		// Return a pointer to the tile list
		std::vector<entities::EntityTile>* GetTiles();
		std::vector<entities::EntityBase*>* entities; // Pointer to entityWorld's entity vector

		entities::World* GetWorld()
		{
			return &entityWorld;
		}

		b2World *GetPhysWorld()
		{
			return entityWorld.GetPhysWorld();
		}

		void Render(bool debug);

	protected:
		std::vector<entities::EntityTile> tiles;
		entities::World entityWorld;
};

EntityLevel loadLevel(str fp);