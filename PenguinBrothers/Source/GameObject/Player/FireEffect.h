#pragma once
#include <Core/GameObject/Base/GameObjectBase.h>

enum class BombType;

class FireEffect : public GameObjectBase
{
public:
	FireEffect();
	virtual ~FireEffect() override;
	BombType bombType;

};
