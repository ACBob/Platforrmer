// Entities!

#include "raylib.h"
#include "entities.h"

SpriteBase::SpriteBase(const char* texturefp)
{
	// TODO: Material system
	texture = LoadTexture(texturefp);
}

void SpriteBase::Render(Vector2 A, Vector2 B, Vector2 C, Vector2 D)
{
	DrawLineV(A, B, RED);
	DrawLineV(B, C, RED);
	DrawLineV(C, D, RED);
	DrawLineV(D, A, RED);
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
		GetPhysicsShapeVertex(physBody, 0),
		GetPhysicsShapeVertex(physBody, 1),
		GetPhysicsShapeVertex(physBody, 2),
		GetPhysicsShapeVertex(physBody, 3)
	);
}

PhysicsBody EntityBase::GetPhysicsBody()
{
	return physBody;
}


EntityPlayer::EntityPlayer(Vector2 position) : EntityBase(position)
{
	// Don't spin
	physBody->freezeOrient = true;
}