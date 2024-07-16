#pragma once
#include "GameObjectBase.h"

/* Derived default

class Derived : public GameObjectCamera
{
 public:
	Derived();
	virtual ~Derived() override;
};

*/
class GameObjectCamera : public GameObjectBase
{
public:
	GameObjectCamera();
	//virtual ~MainCamera() override;

	virtual void UpdateCullingBounds() override;
};