#pragma once
#include "Core/Component/Base/ComponentBase.h"

class BoxCollider2D : public ComponentBase
{
public:
	BoxCollider2D(GameObjectBase& gameObject);
	virtual ~BoxCollider2D() override;

	/** Collider 영역 그릴지*/
	bool isDrawRect = false;

protected:
	virtual void Start() override;
	virtual void Update() override;
	virtual void Render() override;

private:
	

};

