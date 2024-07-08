#pragma once
#include "Core/Scene/WorldBase.h"

#include <string>

class StageBase : public WorldBase	   
{
public:
	StageBase();
	virtual ~StageBase() override;

	std::wstring bgPath;
	Vector2 playerSpawnPos;

};