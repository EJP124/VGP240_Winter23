#pragma once

#include <XEngine.h>
#include "Vertex.h"

enum class FillMode
{
	Solid,
	Wireframe
};

enum class ShadeMode
{
	Flat,
	Gouraud,
	Phong
};

class Rasterizer
{
public:
	static Rasterizer* Get();

public:
	void SetColor(X::Color color);
	void SetFillMode(FillMode fillmode);
	void SetShadeMode(ShadeMode shadeMode);
	ShadeMode GetShadeMode();

	void DrawPoint(int x, int y);

	void DrawPoint(const Vertex& vertex);
	void DrawLine(const Vertex& a, const Vertex& b);
	void DrawTriangle(Vertex a, Vertex b, Vertex c);

private:
	void DrawFilledTriangle(const Vertex& v0, const Vertex& v1, const Vertex& v2);

	X::Color mColor = X::Colors::White;
	FillMode mFillMode = FillMode::Solid;
	ShadeMode mShadeMode = ShadeMode::Gouraud;
};