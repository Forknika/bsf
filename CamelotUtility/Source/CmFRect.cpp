#include "CmFRect.h"
#include "CmVector2.h"
#include "CmMatrix4.h"
#include "CmMath.h"

namespace CamelotFramework
{
	const FRect FRect::EMPTY = FRect();

	FRect::FRect()
		:x(0), y(0), width(0), height(0)
	{ }

	FRect::FRect(float _x, float _y, float _width, float _height)
		:x(_x), y(_y), width(_width), height(_height)
	{ }

	bool FRect::contains(const Vector2& point) const
	{
		if(point.x >= x && point.x <= (x + width))
		{
			if(point.y >= y && point.y <= (y + height))
				return true;
		}

		return false;
	}

	bool FRect::overlaps(const FRect& other) const
	{
		float otherRight = other.x + other.width;
		float myRight = x + width;

		float otherBottom = other.y + other.height;
		float myBottom = y + height;

		if(x < otherRight && myRight > other.x &&
			y < otherBottom && myBottom > other.y)
			return true;

		return false;
	}

	void FRect::encapsulate(const FRect& other)
	{
		float myRight = x + width;
		float myBottom = y + height;
		float otherRight = other.x + other.width;
		float otherBottom = other.y + other.height;

		if(other.x < x)
			x = other.x;

		if(other.y < y)
			y = other.y;

		if(otherRight > myRight)
			width = otherRight - x;
		else
			width = myRight - x;

		if(otherBottom > myBottom)
			height = otherBottom - y;
		else
			height = myBottom - y;
	}

	void FRect::clip(const FRect& clipRect)
	{
		float newLeft = std::max(x, clipRect.x);
		float newTop = std::max(y, clipRect.y);

		float newRight = std::min(x + width, clipRect.x + clipRect.width);
		float newBottom = std::min(y + height, clipRect.y + clipRect.height);

		x = newLeft;
		y = newTop;
		width = newRight - newLeft;
		height = newBottom - newTop;
	}

	void FRect::transform(const Matrix4& matrix)
	{
		Vector4 verts[4];
		verts[0] = Vector4(x, y, 0.0f, 1.0f);
		verts[1] = Vector4(x + width, y, 0.0f, 1.0f);
		verts[2] = Vector4(x, y + height, 0.0f, 1.0f);
		verts[3] = Vector4(x + width, y + height, 0.0f, 1.0f);

		for(UINT32 i = 0; i < 4; i++)
			verts[i] = matrix * verts[i];

		float minX = std::numeric_limits<float>::max();
		float maxX = std::numeric_limits<float>::min();
		float minY = std::numeric_limits<float>::max();
		float maxY = std::numeric_limits<float>::min();

		for(UINT32 i = 0; i < 4; i++)
		{
			if(verts[i].x < minX)
				minX = verts[i].x;

			if(verts[i].y < minY)
				minY = verts[i].y;

			if(verts[i].x > maxX)
				maxX = verts[i].x;

			if(verts[i].y > maxY)
				maxY = verts[i].y;
		}

		x = minX;
		y = minY;
		width = maxX - x;
		height = maxY - y;
	}
}