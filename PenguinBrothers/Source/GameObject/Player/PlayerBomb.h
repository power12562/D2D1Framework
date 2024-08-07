#pragma once
#include "Core/GameObject/Base/GameObjectBase.h"

class PlayerBomb : public GameObjectBase
{
public:
	PlayerBomb();
	virtual ~PlayerBomb() override;
	static int GetObjectCount() { return objectCount; }
	class PlayerCtrl *playerCtrl = nullptr;

private:
	static int objectCount;
};