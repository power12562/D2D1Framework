#pragma once
#include <Core/GameObject/Base/GameObjectBase.h>

class BresenhamTest : public GameObjectBase
{
public:
	BresenhamTest();
	virtual ~BresenhamTest() override;			

private:
	SIZE gridSize{};

private:
	void SpawnGrid();
	void DrawPixel(float x, float y);
	void DrawLine(float x0, float y0, float x1, float y1);
	void bresenham_line(float x0, float y0, float x1, float y1);
};