#include "b2debugdraw.h"
#include "loguru.hpp"

void RaylibB2Debug::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
	Color color1;
	color1.r = color.r * 255;
	color1.g = color.g * 255;
	color1.b = color.b * 255;
	color1.a = color.a * 255;

	Vector2 *verts = new Vector2[vertexCount];
	for (int i = 0; i<vertexCount; i++)
	{
		verts[i].x = vertices[i].x;
		verts[i].y = vertices[i].y;
	}

	DrawLineStrip(
		verts,
		vertexCount,
		color1
	);
	DrawLine(
		verts[vertexCount-1].x,
		verts[vertexCount-1].y,
		verts[0].x,
		verts[0].y,
		color1
	);
}
void RaylibB2Debug::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
	// TODO:
	DrawPolygon(vertices, vertexCount, color);
}

void RaylibB2Debug::DrawCircle(const b2Vec2& center, float radius, const b2Color& color)
{
	Color color1;
	color1.r = color.r * 255;
	color1.g = color.g * 255;
	color1.b = color.b * 255;
	color1.a = color.a * 255;

	::DrawCircle(
		center.x,
		center.y,
		radius,
		color1
	);
}
void RaylibB2Debug::DrawSolidCircle(const b2Vec2& center, float radius, const b2Vec2& axis, const b2Color& color)
{

}
void RaylibB2Debug::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
{
	Color color1;
	color1.r = color.r * 255;
	color1.g = color.g * 255;
	color1.b = color.b * 255;
	color1.a = color.a * 255;

	DrawLine(
		p1.x,
		p1.y,
		p2.x,
		p2.y,
		color1
	);

}
void RaylibB2Debug::DrawTransform(const b2Transform& xf)
{
	b2Vec2 p1 = xf.p, p2;
    p2 = p1 + 16 * xf.q.GetXAxis();
    DrawSegment(p1, p2, b2Color(1,0,0));

    p2 = p1 + 16 * xf.q.GetYAxis();
    DrawSegment(p1, p2, b2Color(0,1,0));
}
void RaylibB2Debug::DrawPoint(const b2Vec2& p, float size, const b2Color& color)
{
	Color color1;
	color1.r = color.r * 255;
	color1.g = color.g * 255;
	color1.b = color.b * 255;
	color1.a = color.a * 255;

	::DrawCircle(
		p.x,
		p.y,
		size,
		color1
	);
}