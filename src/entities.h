// Entities!

#pragma once

#include "raylib.h"
#include "physac.h"


#define NULL 0

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
		EntityBase(Vector2 position);
		~EntityBase() {};

		void Render();

		Vector2 GetPosition();
		int GetRotation();

		PhysicsBody GetPhysicsBody();

		// Called at the start of a frame
		virtual void PreThink(float delta) {};
		// Called after physics, but before rendering
		virtual void Think(float delta) {};
		// Called at the end of a frame
		virtual void PostThink(float delta) {};

	protected:
		SpriteBase sprite = NULL;

		// Physics Body
		PhysicsBody physBody;
};

class EntityPlayer : public EntityBase
{
	public:
		EntityPlayer(Vector2 position);

		void PreThink(float delta);
};