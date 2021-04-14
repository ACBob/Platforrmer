// Entities!

#include "raylib.h"
#include "entities.h"

SpriteBase::SpriteBase(const char* texturefp)
{
	// TODO: Material system
	texture = LoadTexture(texturefp);
}

EntityBase::EntityBase(Vector2 position)
{
	physBody = CreatePhysicsBodyRectangle(position, SPRITE_WIDTH, SPRITE_HEIGHT, 1);

	sprite = SpriteBase("test.png");
}

Vector2 EntityBase::GetPosition()
{
	return physBody->position;
}

int EntityBase::GetRotation()
{
	return physBody->orient;
}

void EntityBase::Render()
{
	sprite.Render(
		physBody->position
	);
}


EntityPlayer::EntityPlayer(Vector2 position) : EntityBase(position)
{
}