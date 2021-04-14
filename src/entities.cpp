// Entities!

#include "raylib.h"
#include "entities.h"

#include <cstdio>

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

EntityBase::EntityBase()
{
	physBody = NULL;

	sprite = SpriteBase("test.png");
}

Vector2 EntityBase::GetPosition()
{
	// b2Vec2 pos = physBody->GetPosition();
	return Vector2({0, 0});
}

int EntityBase::GetRotation()
{
	// return physBody->orient;
	return 0;
}

void EntityBase::Render()
{
	sprite.Render(GetPosition());
}

b2Body *EntityBase::GetPhysicsBody()
{
	return physBody;
}


EntityPlayer::EntityPlayer() : EntityBase()
{
	// // Don't spin
	// physBody->freezeOrient = true;
}

void EntityPlayer::PreThink(float delta)
{
	// // Handle input
	// if (IsKeyPressed(KEY_RIGHT))
	// {
	// 	physBody->velocity.x = 1;
	// }
	// else if (IsKeyPressed(KEY_LEFT))
	// {
	// 	physBody->velocity.x = -1;
	// }

	// if (IsKeyReleased(KEY_RIGHT) || IsKeyReleased(KEY_LEFT))
	// {
	// 	physBody->velocity.x = 0;
	// }

	// if (IsKeyPressed(KEY_UP) && physBody->isGrounded)
	// {
	// 	physBody->velocity.y = -32;
	// }
}