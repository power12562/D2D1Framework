#pragma once
#include <Core/Component/Collider/Base/ColliderBase.h>

#include <Bounds/Bounds.h>
#include <Vector/Vector2.h>

class BoxCollider2D : public ColliderBase
{
public:
	BoxCollider2D(GameObjectBase& gameObject);
	virtual ~BoxCollider2D() override;

	bool isDrawCollider = false;
	Vector2 ColliderSize{0, 0};

protected:
	//virtual void Start() override;
	virtual void Update() override;
	//virtual void LateUpdate() override;
	virtual void Render() override;
	virtual bool isCollide(ColliderBase* other); //각자 콜라이더에서 구현

	Bounds bounds;
private:

};
