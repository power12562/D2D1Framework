#pragma once
#include <Core/GameObject/Base/GameObjectBase.h>

class EnemyDino0Attack : public GameObjectBase
{
public:
	EnemyDino0Attack();
	virtual ~EnemyDino0Attack() override;

	class EnemyDino0* myOwner;
};