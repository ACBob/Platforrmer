// Entities!

#pragma once

#include "raylib.h"
#include "box2d/box2d.h"

#include "b2debugdraw.h"

#include "material.h"

#include <vector>
#include <algorithm>
#include <map>

#include "loguru.hpp"

#include "include.h" // SHOULD BE IN EVERY FILE!

// TODO: not this
#define SPRITE_HEIGHT 16
#define SPRITE_WIDTH 16

#pragma once

// Arbitrary
#define MAXENTS 1024

namespace entities
{

	enum TileType{
		TL_NULL, // Invalid/Air
		TL_GRND, // Regular Ground
		TL_ICE, // Slippy
	};

	// Visual Base for Entities
	class SpriteBase
	{
		public:
			SpriteBase(str texturefp = "missing.json");
			~SpriteBase() {};

			// Renders the sprite
			void Render(Vector position, float orient=0);
		protected:
			material::BobMaterial mat;
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

			// MUST Be replaced, will allow creation during game.
			virtual str classname()
			{
				return "_";
			};

			void Render();

			// Returns position
			Vector GetPosition();
			float GetRotation();

			// Sets the physBody's position to the b2Vec2
			void SetPosition(Vector pos);
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
			b2Body *physBody = NULL;

		protected:
			SpriteBase sprite;
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
				physicsworld->Step(physStep, 6, 2);

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

			// The phys step
			float physStep = 1/60;

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

			str classname()
			{
				return "player";
			}
	};

	// A tile in the world
	class EntityTile : public EntityBase
	{
		public:
			EntityTile(b2World *world);
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

			str classname()
			{
				return "worldtile";
			}

		protected:
			TileType type;
	};

	void init();

	// Boing boing!
	class EntityBouncyBall : public EntityBase
	{
		public:
			EntityBouncyBall(b2World *world);
			void CreateBody(b2World *world);

			str classname()
			{
				return "phys_ball";
			}
	};
}