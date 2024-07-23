#pragma once

#include "Core/GameObject/Base/GameObjectBase.h"

/* Derived default

class Derived : public GameObjectUI
{
 public:
	Derived();
	virtual ~Derived() override;
};

//게임 오브젝트를 상속받는 클래스의 cpp 파일에 다음 해더와 매크로를 추가해야 월드 json 저장이 가능합니다.
#include <Framework/GameObjectFactory.h>
REGISTER_GAMEOBJECFT(Derived)

*/
class GameObjectUI : public GameObjectBase
{
public:
	GameObjectUI();
	//virtual ~GameObjectUI() override;
};