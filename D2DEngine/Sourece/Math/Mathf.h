#pragma once

namespace Mathf
{
	constexpr float PI = 3.14159265f;
	constexpr float Deg2Rad = 0.01745329f;
	constexpr float Rad2Deg = 57.29578f;

	float Lerp(float startfloat, float endfloat, float t); //선형 보간
}