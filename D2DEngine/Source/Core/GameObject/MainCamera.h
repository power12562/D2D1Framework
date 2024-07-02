#pragma once
#include "Core/GameObject/Base/GameObjectBase.h"
#include "Bounds/Bounds.h"

class MainCamera : public GameObjectBase
{
public:
	MainCamera();
	//virtual ~MainCamera() override;

	void UpdateBounds() override;
};

