// Entities!

#include "raylib.h"
#include "raymath.h"
#include "entities.h"

#include "material.h"

#include <cstdio>
#include <math.h>
#include <map>

#include "include.h" // SHOULD BE IN EVERY FILE!

namespace entities
{
	SpriteBase::SpriteBase(str texturefp)
	{
		mat = material::loadMaterial(texturefp);
	}

	void SpriteBase::Render(Vector position, float orient) {

		Vector offsetPos(-mat.tex.width/2, -mat.tex.height/2);
		orient = orient * RAD2DEG;
		offsetPos = Vector2Rotate(offsetPos, orient);

		position = position + offsetPos;

		BeginShaderMode(mat.shader);
			DrawTextureEx(
				mat.tex,
				position,
				orient,
				1.0,
				WHITE
			);
		EndShaderMode();
	}

	EntityBase::EntityBase(b2World *world)
	{
		physBody = NULL;
		sprite = SpriteBase("face.json");
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

	Vector EntityBase::GetPosition()
	{
		return physBody->GetPosition();
	}

	float EntityBase::GetRotation()
	{
		return physBody->GetAngle();
	}

	void EntityBase::SetPosition(Vector position)
	{
		physBody->SetTransform(
			position,
			GetRotation()
		);
	}

	void EntityBase::SetRotation(float orient)
	{
		physBody->SetTransform(
			GetPosition(),
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
	}

	void EntityPlayer::CreateBody(b2World *world)
	{
		b2BodyDef bodyDef;
		bodyDef.type = b2_dynamicBody; // TODO: Would kinematic be better?
		bodyDef.position.Set(0.0f, 0.0);
		// Don't spin
		// bodyDef.fixedRotation = true;
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

	EntityTile::EntityTile(b2World *world) : EntityBase::EntityBase(world)
	{
		sprite = SpriteBase("floor.json");
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

	void init()
	{

	}

	EntityBouncyBall::EntityBouncyBall(b2World *world) : EntityBase::EntityBase(world)
	{
		sprite = SpriteBase("ball.json");
	}

	void EntityBouncyBall::CreateBody(b2World *world)
	{
		b2BodyDef bodyDef;
		bodyDef.type = b2_dynamicBody;
		bodyDef.position.Set(0.0f, 0.0);
		physBody = world->CreateBody(&bodyDef);

		b2CircleShape shape;
		shape.m_radius = 8;

		b2FixtureDef fixtureDef;
		fixtureDef.shape = &shape;
		fixtureDef.density = 1;
		fixtureDef.restitution = 0.9; // Boing boing
		physBody->CreateFixture(&fixtureDef);
	}
}