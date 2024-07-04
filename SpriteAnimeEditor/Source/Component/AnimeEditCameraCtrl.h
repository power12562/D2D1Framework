#pragma once
#include "Core/Component/Base/ComponentBase.h"

class AnimeEditCameraCtrl : public ComponentBase
{
public:
	AnimeEditCameraCtrl(GameObjectBase& gameObject);
	virtual ~AnimeEditCameraCtrl() override;

protected:
	virtual void Start() override;
	virtual void Update() override;
	virtual void Render() override;

private:
	float moveSpeed;

};

