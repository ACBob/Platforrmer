// Entities!

#pragma once

#include "raylib.h"
#include "box2d/box2d.h"

#include "b2debugdraw.h"

#include <vector>
#include <algorithm>

#include "loguru.hpp"

// TODO: not this
#define SPRITE_HEIGHT 16
#define SPRITE_WIDTH 16

// Arbitrary
#define MAXENTS 1024

enum TileType{
	TL_NULL, // Invalid/Air
	TL_GRND, // Regular Ground
	TL_ICE, // Slippy
};



// Visual Base for Entities
class SpriteBase
{
	public:
		SpriteBase(const char* texturefp);
		~SpriteBase() {};

		// Renders the sprite
		void Render(Vector2 position, float orient=0);
	protected:
		Texture2D texture; // Texture to render with
		Shader shader; // Shader to render with, given by material system
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

		// Returns position as a RAYLIB Vector2
		Vector2 GetPosition();
		// Returns position as a B2D b2Vec2
		b2Vec2 GetVecPosition();
		float GetRotation();

		// Sets the physBody's position to the b2Vec2
		void SetPosition(b2Vec2 pos);
		// Sets the rotation to orient radians
		void SetRotation(float orient);

		b2Body *GetPhysicsBody();
		virtual void CreateBody(b2World *world);

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
class World
{
	public: 
		World(float hgrav=0.0f, float vgrav=9.8f)
		{
			// Create the box2d world
			physicsworld = new b2World(b2Vec2(hgrav, vgrav));
			physicsworld->SetDebugDraw(&debugDraw);
			
			// Draw everything!
			debugDraw.SetFlags(
				b2Draw::e_shapeBit | b2Draw::e_aabbBit | b2Draw::e_centerOfMassBit | b2Draw::e_jointBit | b2Draw::e_pairBit
			);
		};
		~World()
		{
			entlist.clear();
		};

		EntityBase *AddEntity(EntityBase *enttoadd)
		{
			entlist.push_back(enttoadd);

			if (entlist.size() > MAXENTS) {
				LOG_F(FATAL, "Panic! Too many Entities!\n");
			}

			return entlist.back();
		};

		static bool ShouldRemove(EntityBase *ent)
		{
			return ent->isDead;
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

			for (auto ent : entlist)
			{
				ent->Think(delta);
			}

			// Do physics
			// TODO: get step from framerate
			physicsworld->Step(1.0f/60.0f, 6, 2);

		};

		// Pre think
		void FrameStart(float delta)
		{
			for (auto ent : entlist)
			{
				ent->PreThink(delta);
			}
		}

		// Post Think
		void FrameEnd(float delta)
		{
			for (auto ent : entlist)
			{
				ent->PostThink(delta);
			}
		}

		void Render(bool debug = false)
		{
			for (auto ent : entlist)
			{
				ent->Render();
			}

			if (debug)
				physicsworld->DebugDraw();
		};

		// Creates, Adds, and returns a new Entity of type
		template <class T>
		T *NewEntity()
		{
			// Create it
			static T ent = T(physicsworld);
			// Make it get a body
			ent.CreateBody(physicsworld);
		
			// Start tracking it
			return (T*)AddEntity(&ent);
		};

		b2World *GetPhysWorld()
		{
			return physicsworld;
		}

		std::vector<EntityBase*>* GetEntityVector()
		{
			return &entlist;
		}

	protected:
		std::vector<EntityBase*> entlist;
		b2World *physicsworld;
		RaylibB2Debug debugDraw;

};

// The player
class EntityPlayer : public EntityBase
{
	public:
		EntityPlayer(b2World *world);
		void CreateBody(b2World *world);

		void PreThink(float delta);
};

// A tile in the world
class EntityTile : public EntityBase
{
	public:
		EntityTile(b2World *world) : EntityBase(world) {};
		~EntityTile() {};

		void CreateBody(b2World *world);

		void SetType(TileType typeToUse)
		{
			type = typeToUse;
		}
		TileType GetType()
		{
			return type;
		}

	protected:
		TileType type;
};