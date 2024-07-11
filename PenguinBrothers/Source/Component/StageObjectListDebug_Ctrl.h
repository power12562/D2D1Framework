#pragma once
#include <Core/Component/Base/ComponentBase.h>

class StageObjectListDebug_Ctrl : public ComponentBase
{
public:
	StageObjectListDebug_Ctrl(GameObjectBase& gameObject);
	virtual ~StageObjectListDebug_Ctrl() override;


protected:
	virtual void Start();
	virtual void Update();

private:
	class TextRenderer* textrenderer;
};