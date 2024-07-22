#include "Ground.h"

#include <Core/Component/Collider/BoxCollider2D.h>
#include <Core/Component/Renderer/BoxRenderer.h>

Ground::Ground()
{
	tag = L"Ground";
	OderLayer = 3;
	AddComponent<BoxCollider2D>().ColliderSize = Vector2{100.f, 100.f};
#ifdef _DEBUG
	BoxRenderer& boxDraw = AddComponent<BoxRenderer>();
	boxDraw.isFill = true;
	boxDraw.color = D2D1::ColorF(D2D1::ColorF::Green);
	boxDraw.alpha = 0.35f;
#endif // _DEBUG
}

Ground::~Ground()
{
}
