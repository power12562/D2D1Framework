#pragma once
#include "Core/Component/Base/ComponentBase.h"

class CameraMove : public ComponentBase
{
public:
	CameraMove(GameObjectBase& gameObject);
	virtual ~CameraMove() override;

protected:
	virtual void Start();
	virtual void Update();
	//virtual void Render();

private:
	float moveSpeed;

};