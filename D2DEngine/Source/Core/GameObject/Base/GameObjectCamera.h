#pragma once
#include "GameObjectBase.h"

class GameObjectCamera : public GameObjectBase
{
public:
	GameObjectCamera();
	//virtual ~MainCamera() override;

	virtual void UpdateBounds() override;
};