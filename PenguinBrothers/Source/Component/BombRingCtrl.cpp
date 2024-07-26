#include "BombRingCtrl.h"
#include <Core/Component/Renderer/SpriteRenderer.h>

#include "Source/Component/Player/PlayerCtrl.h"

BombRingCtrl::BombRingCtrl(GameObjectBase& gameObject)
	: ComponentBase(gameObject)
	, ICollider2DNotify(this)
{
	type = RingType::Orange;
}

BombRingCtrl::~BombRingCtrl()
{

}

void BombRingCtrl::Start()
{
	switch (type)
	{
	case RingType::Orange:
		GetComponent<SpriteRenderer>().LoadImage(L"Resource/Item/orangeRing.png");
		break;
	case RingType::Red:
		GetComponent<SpriteRenderer>().LoadImage(L"Resource/Item/redRing.png");
		break;
	case RingType::Green:
		GetComponent<SpriteRenderer>().LoadImage(L"Resource/Item/greenRing.png");
		break;
	case RingType::SkyBlue:
		GetComponent<SpriteRenderer>().LoadImage(L"Resource/Item/skyblueRing.png");
		break;
	}
}

void BombRingCtrl::Update()
{

}

void BombRingCtrl::SerializedJson(ordered_json& jsonObj)
{
	ordered_json myJson;
	myJson["type"] = type;

	jsonObj["BombRingCtrl"].push_back(myJson);
}

void BombRingCtrl::DeSerializedJson(ordered_json& jsonObj)
{
	for (auto& data : jsonObj["BombRingCtrl"])
	{
		type = data["type"];
	}
}

void BombRingCtrl::OnTriggerEnter2D(ColliderBase* myCollider, ColliderBase* otherCollider)
{
	if (otherCollider->gameObject.tag == L"Player")
	{
		otherCollider->GetComponent<PlayerCtrl>().bombType = static_cast<BombType>(type);
		gameObject.enable = false;
	}

}
