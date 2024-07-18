#pragma once
#include "Core/Component/Collider/BoxCollider2D.h"

/** �̹��� ũ�⿡ ���󰡴� Collider*/
class SpriteCollider2D : public BoxCollider2D
{
public:
	SpriteCollider2D(GameObjectBase& gameObject);
	virtual ~SpriteCollider2D() override;

	virtual void Update() override;
	virtual void Render() override;

private:
	using BoxCollider2D::ColliderSize;
};

