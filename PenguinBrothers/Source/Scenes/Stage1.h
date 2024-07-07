#pragma once
#include "Core/Scene/WorldBase.h"

#include <string>

class Stage1 : public WorldBase
{
public:
	Stage1();
	virtual ~Stage1() override;

private:
	std::wstring bgPath;

};