#pragma once
#include <Core/Component/Collider/Base/ColliderBase.h>

#include <Bounds/Bounds.h>
#include <Vector/Vector2.h>

#include <d2d1.h>

class BoxCollider2D : public ColliderBase
{
public:
	BoxCollider2D(GameObjectBase& gameObject);
	virtual ~BoxCollider2D() override;

	bool isDrawCollider = false;
	//bool DrawFill = false;	
	//float DrawAlpha = 1.0f;
	Vector2 ColliderSize{0, 0};
	
protected:
	//virtual void Start() override;
	virtual void Update() override;
	//virtual void LateUpdate() override;
	virtual void Render() override;
	virtual bool isCollide(ColliderBase* other) override;
	virtual bool isCollide(const Vector2& point) override;

	virtual float GetTop() override { return bounds.leftTop.y; }
	virtual float GetBottom() override { return bounds.rightBottom.y; }
	virtual float GetLeft() override { return bounds.leftTop.x; }
	virtual float GetRight() override { return bounds.rightBottom.x; }

	Bounds bounds;
private:

};
