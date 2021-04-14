// Entities!

#pragma once

#include "raylib.h"
#include "box2d/box2d.h"

#include <vector>
#include <algorithm>

// TODO: not this
#define SPRITE_HEIGHT 16
#define SPRITE_WIDTH 16

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
		void Render(Vector2 position, float orient=0) {
			DrawTexture(texture, position.x, position.y, WHITE);
		};
		void Render(Vector2 A, Vector2 B, Vector2 C, Vector2 D);
	private:
		Texture2D texture;
};

class EntityBase
{
	public:
		EntityBase();
		~EntityBase()
		{
			physBody = nullptr;
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
		bool isDead;

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
		EntityWorld(float hgrav=0.0f, float vgrav=-9.8f) {
			// Create the box2d world
			b2World world(b2Vec2(hgrav, vgrav));
			physicsworld = &world;
		};
		~EntityWorld()
		{
			delete physicsworld;
		};

		void AddEntity(EntityBase *enttoadd)
		{
			entlist.push_back(enttoadd);
		};

		static bool ShouldRemove(EntityBase *ent)
		{
			return ent->isDead;
		};

		void Update(float delta)
		{
			// First clear out dead entities
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

		};

		// Creates, Adds, and returns a new Entity of type
		template <typename T>
		T *NewEntity()
		{
			// Create it
			T ent = T();

			// Start tracking it
			AddEntity(&ent);

			return &ent;
		};

	protected:
		std::vector<EntityBase*> entlist;
		b2World *physicsworld;

};

class EntityPlayer : public EntityBase
{
	public:
		EntityPlayer();

		void PreThink(float delta);
};