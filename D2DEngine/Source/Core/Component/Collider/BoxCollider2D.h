#pragma once
#include "Core/Component/Collider/Base/ColliderBase.h"

#include "Bounds/Bounds.h"

#include <d2d1.h>

class BoxCollider2D : public ColliderBase
{
public:
	BoxCollider2D(GameObjectBase& gameObject);
	virtual ~BoxCollider2D() override;

	/** Collider ���� �׸���*/
	bool isDrawCollider = false;

protected:
	virtual void Start() override;
	//virtual void Update() override;
	virtual void Render() override;

	bool isCollide(ColliderBase* other) override;

private:
	Bounds* bounds;

};

