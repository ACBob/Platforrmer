// Entities!

#include "raylib.h"
#include "entities.h"

#include "material.h"

#include <cstdio>
#include <math.h>

SpriteBase::SpriteBase(const char* texturefp)
{
	// TODO: Material system
	texture = material::loadTexture(texturefp);
}

void SpriteBase::Render(Vector2 position, float orient) {

	position.x = position.x - (texture.width / 2);
	position.y = position.y - (texture.height / 2);

	orient = orient * RAD2DEG;

	DrawTextureEx(texture, position, orient, 1, WHITE);
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
	shape.SetAsBox(8,8);

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
b2Vec2 EntityBase::GetVecPosition()
{
	return physBody->GetPosition();
}

float EntityBase::GetRotation()
{
	return physBody->GetAngle();
}

void EntityBase::SetPosition(b2Vec2 position)
{
	physBody->SetTransform(
		position,
		GetRotation()
	);
}

void EntityBase::SetRotation(float orient)
{
	physBody->SetTransform(
		GetVecPosition(),
		orient
	);
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
	// Don't spin
	// physBody->SetFixedRotation(true);
}

void EntityPlayer::CreateBody(b2World *world)
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody; // TODO: Would kinematic be better?
	bodyDef.position.Set(0.0f, 0.0);
	// Don't spin
	bodyDef.fixedRotation = true;
	physBody = world->CreateBody(&bodyDef);

	b2PolygonShape shape;
	shape.SetAsBox(8,8);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	fixtureDef.density = 1;
	fixtureDef.restitution = 0;
	physBody->CreateFixture(&fixtureDef);
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
	else if (IsKeyPressed(KEY_LEFT))
	{
		physBody->SetLinearVelocity(
			b2Vec2(
				-32.0f,
				physBody->GetLinearVelocity().y
			)
		);
	}

	if (IsKeyReleased(KEY_RIGHT) || IsKeyReleased(KEY_LEFT))
	{
		physBody->SetLinearVelocity(
			b2Vec2(
				0,
				physBody->GetLinearVelocity().y
			)
		);
	}

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
	shape.SetAsBox(8,8);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	fixtureDef.density = 1;
	physBody->CreateFixture(&fixtureDef);
}