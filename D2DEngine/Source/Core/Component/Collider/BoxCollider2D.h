#pragma once
#include "Core/Component/Base/ComponentBase.h"

#include "Bounds/Bounds.h"

#include <d2d1.h>

class BoxCollider2D : public ComponentBase
{
public:
	BoxCollider2D(GameObjectBase& gameObject);
	virtual ~BoxCollider2D() override;

	/** Collider 영역 그릴지*/
	bool isDrawCollider = false;

protected:
	virtual void Start() override;
	//virtual void Update() override;
	virtual void Render() override;

private:
	Bounds* bounds;
	D2D1_MATRIX_3X2_F trMatrix;

};

