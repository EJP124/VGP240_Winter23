#include "Rasterizer.h"
#include "DepthBuffer.h"
#include "LightManager.h"
#include "TextureCache.h"

//draw a line where abs(m) > 0 and m < 1
void DrawLineLow(const Vertex& left, const Vertex& right)
{
	float dx = right.pos.x - left.pos.x;
	int startX = static_cast<int>(left.pos.x);
	int endX = static_cast<int>(right.pos.x);
	for (int x = startX; x < endX; ++x)
	{
		float t = static_cast<float>(x - startX) / dx;
		if (Rasterizer::Get()->GetShadeMode() == ShadeMode::Phong)
		{
			Rasterizer::Get()->DrawPoint(LerpVertexAndNormal(left, right, t));
		}
		else
		{
			Rasterizer::Get()->DrawPoint(LerpVertex(left, right, t));
		}
	}
}

// draw a line where abs(m) > 1
void DrawLineHeight(const Vertex& bottom, const Vertex& top)
{
	float dy = top.pos.y - bottom.pos.y;
	int startY = static_cast<int>(bottom.pos.y);
	int endY = static_cast<int>(top.pos.y);
	for (int y = startY; y < endY; ++y)
	{
		float t = static_cast<float>(y - startY) / dy;
		if (Rasterizer::Get()->GetShadeMode() == ShadeMode::Phong)
		{
			Rasterizer::Get()->DrawPoint(LerpVertexAndNormal(bottom, top, t));
		}
		else
		{
			Rasterizer::Get()->DrawPoint(LerpVertex(bottom, top, t));
		}
	}
}


Rasterizer* Rasterizer::Get()
{
	static Rasterizer sInstance;
	return &sInstance;
}

void Rasterizer::SetColor(X::Color color)
{
	mColor = color;
}

void Rasterizer::SetFillMode(FillMode fillmode)
{
	mFillMode = fillmode;
}

void Rasterizer::SetShadeMode(ShadeMode shadeMode)
{
	mShadeMode = shadeMode;
}

ShadeMode Rasterizer::GetShadeMode()
{
	return mShadeMode;
}

void Rasterizer::DrawPoint(int x, int y)
{
	X::DrawPixel(x, y, mColor);
}

void Rasterizer::DrawPoint(const Vertex& vertex)
{
	if (DepthBuffer::Get()->CheckDepthBuffer(vertex.pos.x, vertex.pos.y, vertex.pos.z))
	{
		X::Color pixColor = vertex.color;
		if (pixColor.z < 0.0f)
		{
			pixColor = TextureCache::Get()->SampleColor(vertex.color);
		}
		else if (mShadeMode == ShadeMode::Phong)
		{
			pixColor *= LightManager::Get()->ComputeLightColor(vertex.pos, vertex.normal);
		}
		SetColor(pixColor);
		DrawPoint(static_cast<int>(vertex.pos.x), static_cast<int>(vertex.pos.y));
	}
}

void Rasterizer::DrawLine(const Vertex& a, const Vertex& b)
{
	int dx = b.pos.x - a.pos.x;
	int dy = b.pos.y - a.pos.y;
	if (abs(dx) <= 0.01f)
	{
		if (dx <= 0)
		{
			if (a.pos.y < b.pos.y) DrawLineHeight(a, b);
			else DrawLineHeight(b, a);
		}
	}
	else
	{
		float m = dy / dx;
		if (abs(m) < 1)
		{
			if (a.pos.x < b.pos.x) DrawLineLow(a, b);
			else DrawLineLow(b, a);
		}
		else
		{
			if (a.pos.y < b.pos.y) DrawLineHeight(a, b);
			else DrawLineHeight(b, a);
		}
	}
	
}

void Rasterizer::DrawTriangle(Vertex a, Vertex b, Vertex c)
{
	if (mShadeMode == ShadeMode::Flat)
	{
		b.color = a.color;
		c.color = a.color;
	}
	switch (mFillMode)
	{
		case FillMode::Solid:
		{
			std::vector<Vertex> sortedVerticies;
			sortedVerticies.push_back(a);
			sortedVerticies.push_back(b);
			sortedVerticies.push_back(c);
			std::sort(sortedVerticies.begin(), sortedVerticies.end(), [](const Vertex& lhs, const Vertex& rhs) {return lhs.pos.y < rhs.pos.y; });
			DrawFilledTriangle(sortedVerticies[0], sortedVerticies[1], sortedVerticies[2]);
		}
		break;
		case FillMode::Wireframe:
		{
			DrawLine(a, b);
			DrawLine(b, c);
			DrawLine(c, a);
		}
		break;
	}
}

void Rasterizer::DrawFilledTriangle(const Vertex& v0, const Vertex& v1, const Vertex& v2)
{
	float dy = v2.pos.y - v0.pos.y;
	if (MathHelper::CheckEqual(v0.pos.y, v1.pos.y))
	{
		int startY = static_cast<int>(v0.pos.y);
		int endY = static_cast<int>(v2.pos.y);
		for (int y = startY; y <= endY; ++y)
		{
			float t = (y - v0.pos.y) / dy;
			Vertex a = (mShadeMode == ShadeMode::Phong)? LerpVertexAndNormal(v0, v2, t) : LerpVertex(v0, v2, t);
			Vertex b = (mShadeMode == ShadeMode::Phong)? LerpVertexAndNormal(v1, v2, t) : LerpVertex(v1, v2, t);
			DrawLine(a, b);
		}
	}
	else if (MathHelper::CheckEqual(v1.pos.y, v2.pos.y))
	{
		int startY = static_cast<int>(v0.pos.y);
		int endY = static_cast<int>(v2.pos.y);
		for (int y = startY; y <= endY; ++y)
		{
			float t = (y - v0.pos.y) / dy;
			Vertex a = (mShadeMode == ShadeMode::Phong)? LerpVertexAndNormal(v0, v2, t) : LerpVertex(v0, v2, t);
			Vertex b = (mShadeMode == ShadeMode::Phong) ? LerpVertexAndNormal(v0, v1, t) : LerpVertex(v0, v1, t);
			DrawLine(a, b);
		}
	}
	else
	{
		float t = (v1.pos.y - v0.pos.y) / dy;
		Vertex splitVertex = LerpVertex(v0, v2, t);
		//bottom fill
		DrawFilledTriangle(v0, v1, splitVertex);
		//top fill
		DrawFilledTriangle(v1, splitVertex, v2);
	}
}
