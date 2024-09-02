#include "BresenhamTest.h"
#include <Core/Component/Renderer/LineRenderer.h>
#include <Core/Component/Renderer/BoxRenderer.h>

#include <Framework/WinGameApp.h>

using namespace D2D1;
constexpr int step = 20;

BresenhamTest::BresenhamTest()
{
	gridSize = { 800, 800 };
	stepPos = gridSize.cx / (step - 1);
	SpawnGrid();
	bresenham_line(0, 0, 19, 10);
	bresenham_line(0, 19, 19, 10);
}

BresenhamTest::~BresenhamTest()
{
}

void BresenhamTest::SpawnGrid()
{
	for (size_t i = 0; i < step; i++)
	{
		LineRenderer& gridY = AddComponent<LineRenderer>();
		gridY.Color = ColorF(ColorF::White);
		gridY.Width = 2;
		gridY.StartPosition = Vector2{ gridSize.cx * i / float(step - 1), (float)gridSize.cy };
		gridY.EndPosition = Vector2{ gridSize.cx * i / float(step - 1), (float)0 };
	}
	for (size_t i = 0; i < step; i++)
	{
		LineRenderer& gridX = AddComponent<LineRenderer>();
		gridX.Color = ColorF(ColorF::White);
		gridX.Width = 2;
		gridX.StartPosition = Vector2{ (float)gridSize.cx, gridSize.cy * i / float(step - 1) };
		gridX.EndPosition = Vector2{ (float)0,gridSize.cy * i / float(step - 1) };
	}
}

void BresenhamTest::DrawPixel(float x, float y)
{
	BoxRenderer& pixel = AddComponent<BoxRenderer>();
	pixel.color = ColorF(ColorF::Red);
	pixel.center = Vector2(x * stepPos, y * stepPos);
	pixel.size = Vector2(step, step);
	pixel.isFill = true;
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


