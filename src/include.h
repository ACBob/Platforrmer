// TODO: BETTER NAME
// This should be globally included by all files

#pragma once

#include "box2d/b2_math.h" // b2Vec2
#include "raylib.h" // Vector2

#include <string>
using str = std::string;

// Vector that should act as an intermediary between all the other vectors the global namespaces are infected with
class Vector
{
	public:
		float x, y, z = 0.0f;

		Vector()
		{
			x = y = z = 0.0f;
		}
		Vector(float x=0, float y=0, float z=0)
		{
			this->x = x;
			this->y = y;
			this->z = z;
		}
	// conversion, from
		Vector(Vector2 raylibVec)
		{
			x = raylibVec.x;
			y = raylibVec.y;
		}
		Vector(b2Vec2 box2dVec)
		{
			x = box2dVec.x;
			y = box2dVec.y;
		}
	// conversion, to
		operator Vector2() const
		{
			return Vector2({x,y});
		}
		operator b2Vec2() const
		{
			return b2Vec2(x,y);
		}

	// Operators
	// Math, with other vectors
		Vector operator+(Vector oVec)
		{
			oVec.x += x, oVec.y += y, oVec.z += z;
			return oVec;
		}
		Vector operator-(Vector oVec)
		{
			oVec.x -= x, oVec.y -= y, oVec.z -= z;
			return oVec;
		}
		Vector operator*(Vector oVec)
		{
			oVec.x *= x, oVec.y *= y, oVec.z *= z;
			return oVec;
		}
		Vector operator/(Vector oVec)
		{
			oVec.x /= x, oVec.y /= y, oVec.z /= z;
			return oVec;
		}
	// Math, with ints/floats
		Vector operator+(float i)
		{
			return operator+(Vector(i,i,i));
		}
		Vector operator-(float i)
		{
			return operator-(Vector(i,i,i));
		}
		Vector operator*(float i)
		{
			return operator*(Vector(i,i,i));
		}
		Vector operator/(float i)
		{
			return operator/(Vector(i,i,i));
		}
	// Comparison
		bool operator==(Vector oVec)
		{
			return oVec.x == x && oVec.y == y && oVec.z == z;
		}
		bool operator!=(Vector oVec)
		{
			return !operator==(oVec);
		}
};