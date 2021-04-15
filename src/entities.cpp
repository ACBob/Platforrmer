// Entities!

#include "raylib.h"
#include "entities.h"

#include <cstdio>

SpriteBase::SpriteBase(const char* texturefp)
{
	// TODO: Material system
	texture = LoadTexture(texturefp);
}

void SpriteBase::Render(Vector2 position, float orient) {
	DrawTextureEx(texture, position, orient, 1, WHITE);
	DrawCircle(position.x, position.y, 10, RED);
}

EntityBase::EntityBase(b2World *world)
{
	physBody = NULL;
	sprite = SpriteBase("test.png");
}

void EntityBase::CreateBody(b2World *world)
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(0.0f, 0.0);
	physBody = world->CreateBody(&bodyDef);

	b2PolygonShape shape;
	shape.SetAsBox(1,1);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	fixtureDef.density = 1;
	physBody->CreateFixture(&fixtureDef);
}

Vector2 EntityBase::GetPosition()
{
	// assert(physBody);
	b2Vec2 pos = physBody->GetPosition();
	return Vector2({pos.x, pos.y});
}

int EntityBase::GetRotation()
{
	return physBody->GetAngle();
}

void EntityBase::Render()
{
	sprite.Render(GetPosition(), GetRotation());
}

b2Body *EntityBase::GetPhysicsBody()
{
	return physBody;
}


EntityPlayer::EntityPlayer(b2World *world) : EntityBase(world)
{
	// // Don't spin
	// physBody->freezeOrient = true;
}

void EntityPlayer::PreThink(float delta)
{
	// Handle input
	if (IsKeyPressed(KEY_RIGHT))
	{
		physBody->SetLinearVelocity(
			b2Vec2(
				32.0f,
				physBody->GetLinearVelocity().y
			)
		);
	}
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

void EntityTile::CreateBody(b2World *world)
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(0.0f, 0.0);
	physBody = world->CreateBody(&bodyDef);

	b2PolygonShape shape;
	shape.SetAsBox(1,1);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	fixtureDef.density = 1;
	physBody->CreateFixture(&fixtureDef);
}