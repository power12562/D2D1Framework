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
	bool DrawFill = false;	
	float DrawAlpha = 1.0f;
	Vector2 ColliderSize{0, 0};

protected:
	//virtual void Start() override;
	virtual void Update() override;
	//virtual void LateUpdate() override;
	virtual void Render() override;
	virtual bool isCollide(ColliderBase* other) override;
	virtual bool isCollide(const Vector2& point) override;

	Bounds bounds;
private:

};
