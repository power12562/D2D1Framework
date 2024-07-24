#include "Ground.h"

#include <Core/Component/Collider/BoxCollider2D.h>
#include <Core/Component/Renderer/BoxRenderer.h>

#include <Framework/GameObjectFactory.h>
REGISTER_GAMEOBJECFT(Ground)

Ground::Ground()
{
	tag = L"Ground";
	OderLayer = 3;
	BoxCollider2D& coll = AddComponent<BoxCollider2D>();
	coll.ColliderSize = Vector2{ 100.f, 100.f };
	coll.isDrawCollider = true;

	BoxRenderer& boxDraw = AddComponent<BoxRenderer>();
	boxDraw.isFill = true;
	boxDraw.color = D2D1::ColorF(D2D1::ColorF::Green);
	boxDraw.alpha = 0.35f;
}

Ground::~Ground()
{
}
