#pragma once
#include <Core/GameObject/Base/GameObjectBase.h>

class FireEffect : public GameObjectBase
{
public:
	FireEffect();
	virtual ~FireEffect() override;
	class PlayerCtrl* playerCtrl = nullptr;

};
