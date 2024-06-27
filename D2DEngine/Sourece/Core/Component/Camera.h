#pragma once
#include "Core/Component/Base/ComponentBase.h"

class Camera : public ComponentBase
{
public:
	Camera(GameObjectBase& gameObject);
	virtual ~Camera() override;

protected:
	virtual void Start();
	virtual void Update();
	virtual void Render();

private:



};

