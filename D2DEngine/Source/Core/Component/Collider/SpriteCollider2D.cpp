#include "SpriteCollider2D.h"

#include "Framework/D2DRenderer.h"
#include "Framework/WinGameApp.h"

#include "Core/GameObject/Base/GameObjectBase.h"

#include "Core/Component/Camera.h"		 

SpriteCollider2D::SpriteCollider2D(GameObjectBase& gameObject) : 
	BoxCollider2D(gameObject)
{

}

SpriteCollider2D::~SpriteCollider2D()
{

}

void SpriteCollider2D::Update()
{
	D2D_VECTOR_2F center = gameObject.GetCenter();
	Center.x = center.x;
	Center.y = center.y;
	ColliderSize.x = transform.pivot.x * 2.f * std::abs(transform.scale.x);
	ColliderSize.y = transform.pivot.y * 2.f * std::abs(transform.scale.y);
}

void SpriteCollider2D::Render()
{
	if (isDrawCollider)
	{	
		D2DRenderer::DrawRect(transform.GetCameraMatrix() * D2D1::Matrix3x2F::Translation(Center.x, -Center.y), { -transform.pivot.x, -transform.pivot.y, transform.pivot.x, transform.pivot.y }, D2D1::ColorF(D2D1::ColorF::Green));
	}
}


