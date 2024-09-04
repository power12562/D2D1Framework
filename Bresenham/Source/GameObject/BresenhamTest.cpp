#include "BresenhamTest.h"
#include <Core/Component/Renderer/LineRenderer.h>
#include <Core/Component/Renderer/BoxRenderer.h>

#include <Framework/WinGameApp.h>

using namespace D2D1;
constexpr int step = 25;

BresenhamTest::BresenhamTest()
{
	gridSize = { 800, 800 };
	SpawnGrid();
	bresenham_line(1, 1, 31, 16);					 
	bresenham_line(1, 31, 31, 16);
	DrawLine(1, 1, 31, 16);
	DrawLine(1, 31, 31, 16);
}

BresenhamTest::~BresenhamTest()
{
}

void BresenhamTest::SpawnGrid()
{
	for (size_t i = 1; i * step <= gridSize.cy; i++)
	{
		LineRenderer& gridY = AddComponent<LineRenderer>();
		gridY.Color = ColorF(ColorF::White);
		gridY.Width = 1;
		gridY.StartPosition = Vector2{ step * (float)i, step };
		gridY.EndPosition =   Vector2{ step * (float)i, (float)gridSize.cy };
	}
	for (size_t i = 1; i * step <= gridSize.cx; i++)
	{
		LineRenderer& gridX = AddComponent<LineRenderer>();
		gridX.Color = ColorF(ColorF::White);
		gridX.Width = 1;
		gridX.StartPosition = Vector2{ step, step * (float)i};
		gridX.EndPosition = Vector2{ (float)gridSize.cx, step * (float)i };
	}
}

void BresenhamTest::DrawPixel(float x, float y)
{
	BoxRenderer& pixel = AddComponent<BoxRenderer>();
	pixel.color = ColorF(ColorF::Red);
	pixel.center = Vector2(x * step + step * 0.5f, y * step + step * 0.5f);
	pixel.size = Vector2(step, step);
	pixel.isFill = true;
}

void BresenhamTest::DrawLine(float x0, float y0, float x1, float y1)
{
	LineRenderer& Line = AddComponent<LineRenderer>();
	Line.Color = ColorF(ColorF::Violet);
	Line.Width = 1;
	Line.StartPosition = Vector2{ x0 * step + step * 0.5f, y0 * step + step * 0.5f };
	Line.EndPosition = Vector2{ x1 * step + step * 0.5f, y1 * step + step * 0.5f };
}

void BresenhamTest::bresenham_line(float x0, float y0, float x1, float y1)
{
	float dx = std::abs(x1 - x0);
	float dy = std::abs(y1 - y0);
	float sx = x0 < x1 ? 1 : -1;
	float sy = y0 < y1 ? 1 : -1;
	float errTerm = dx - dy;
	while (true)
	{
		DrawPixel(x0, y0);
		if (x0 == x1 && y0 == y1)
			break;
		float e2 = 2 * errTerm;
		if (e2 > -dy)
		{
			errTerm -= dy;
			x0 += sx;
		}
		if (e2 < dx)
		{
			errTerm += dx;
			y0 += sy;

		}
	}
}


