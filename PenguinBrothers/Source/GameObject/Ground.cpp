#include "Ground.h"

#include <Core/Component/Collider/BoxCollider2D.h>

Ground::Ground()
{
	tag = L"Ground";
	OderLayer = 3;
	AddComponent<BoxCollider2D>().ColliderSize = Vector2{100.f, 100.f};
	GetComponent<BoxCollider2D>().DrawFill = true;
	GetComponent<BoxCollider2D>().DrawAlpha = 0.25f;
}

Ground::~Ground()
{
}
