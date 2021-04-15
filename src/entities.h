// Entities!

#pragma once

#include "raylib.h"
#include "box2d/box2d.h"

#include <vector>
#include <algorithm>

#include "loguru.hpp"

// TODO: not this
#define SPRITE_HEIGHT 16
#define SPRITE_WIDTH 16

// Arbitrary
#define MAXENTS 1024

enum {
	TL_NULL, // Invalid/Air
	TL_GRND, // Regular Ground
	TL_ICE, // Slippy
} TileType;



// Visual Base for Entities
class SpriteBase
{
	public:
		SpriteBase(const char* texturefp);
		~SpriteBase() {};

		// Renders the sprite
		void Render(Vector2 position, float orient=0);
	private:
		Texture2D texture;
};

class EntityBase
{
	public:
		EntityBase(b2World *world);
		~EntityBase()
		{
			// delete physBody;
			isDead = true;
		};

		void Render();

		Vector2 GetPosition();
		int GetRotation();

		b2Body *GetPhysicsBody();

		// Called at the start of a frame
		virtual void PreThink(float delta) {};
		// Called after physics, but before rendering
		virtual void Think(float delta) {};
		// Called at the end of a frame
		virtual void PostThink(float delta) {};

		// Set to true to remove.
		// Should test against this when accessing.
		bool isDead = false;

		// Physics Body
		b2Body *physBody;

	protected:
		SpriteBase sprite = NULL;
};

// Holds the list of entities, Box2D world, etc.
// Pretty much just an entity system
class EntityWorld
{
	public: 
		EntityWorld(float hgrav=0.0f, float vgrav=9.8f)
		{
			// Create the box2d world
			physicsworld = new b2World(b2Vec2(hgrav, vgrav));

			entlist.reserve(MAXENTS);
		};
		~EntityWorld()
		{
			entlist.clear();
		};

		EntityBase *AddEntity(EntityBase enttoadd)
		{
			entlist.push_back(enttoadd);

			if (entlist.size() > MAXENTS) {
				LOG_F(FATAL, "Panic! Too many Entities!\n");
			}

			return &entlist.back();
		};

		static bool ShouldRemove(EntityBase ent)
		{
			return ent.isDead;
		};

		void Update(float delta)
		{
			assert(physicsworld != nullptr);
			// First clear out dead entities
			// TODO: this may not actually delete entities? Memory leak??!!
			entlist.erase(
				std::remove_if(
					entlist.begin(),
					entlist.end(),
					ShouldRemove
				),
				entlist.end()
			);

			for (std::vector<EntityBase>::iterator i = entlist.begin(); i != entlist.end(); ++i)
			{
				i->Think(delta);
			}

			// Do physics
			// TODO: get step from framerate
			physicsworld->Step(1.0f/60.0f, 6, 2);

		};

		void Render()
		{
			for (auto ent : entlist)
			{
				ent.Render();
			}
		};

		// Creates, Adds, and returns a new Entity of type
		template <class T>
		T *NewEntity()
		{
			// Create it
			T ent = T(physicsworld);
		
			// Start tracking it
			return (T*)AddEntity(ent);
		};

		b2World *GetPhysWorld()
		{
			return physicsworld;
		}

	protected:
		std::vector<EntityBase> entlist;
		b2World *physicsworld;

};

class EntityPlayer : public EntityBase
{
	public:
		EntityPlayer(b2World *world);

		void PreThink(float delta);
};