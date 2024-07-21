#pragma once
#undef min
#undef max

#include <iostream>
#include <algorithm>
#include <type_traits>

namespace Mathf
{
	constexpr float PI = 3.14159265f;
	constexpr float Deg2Rad = 0.01745329f;
	constexpr float Rad2Deg = 57.29578f;

	float Lerp(float startfloat, float endfloat, float t); //���� ����
	
	/* ���޹��� �迭�� ���� ���� ���� ã���ϴ�.*/
	template<typename T, std::size_t N>
	T FindMin(const T(&arr)[N])
	{
		return *std::min_element(arr, arr + N);
	};

	/* ���޹��� �迭�� ���� ���� ���� ã���ϴ�.*/
	template<typename T, std::size_t N>
	T FindMax(const T(&arr)[N])
	{
		return *std::max_element(arr, arr + N);
	};

	template<typename T>
	T FindMin(T value) 
	{
		return value;
	};
	/** ���޹��� ���ڵ��� ���� ���� ���� ã���ϴ�.*/
	template<typename T, typename... Args>
	T FindMin(T first, Args... args)
	{
		return std::min(first, FindMin(args...));
	};

	template<typename T>
	T FindMax(T value)
	{
		return value;
	};
	/** ���޹��� ���ڵ��� ���� ���� ���� ã���ϴ�.*/
	template<typename T, typename... Args>
	T FindMax(T first, Args... args)
	{
		return std::max(first, FindMax(args...));
	};
}