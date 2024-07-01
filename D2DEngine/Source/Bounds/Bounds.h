#pragma once
#include "Vector/Vector2.h"
#include <Windows.h>

struct Bounds
{
	/** 중심 위치*/
	Vector2 center;

	/** 사이즈*/
	Vector2 size;

	/** 사이즈 절반*/
	Vector2 extents;

	/** 왼쪽 위*/
	Vector2 leftTop;

	/** 오른쪽 아래*/
	Vector2 rightBottom;
};