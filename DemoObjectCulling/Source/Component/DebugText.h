#pragma once
#include "Core/Component/Base/ComponentBase.h"

class DebugText : public ComponentBase
{
public:
	DebugText(GameObjectBase& gameObject);
	virtual ~DebugText() override;

protected:
	virtual void Start() override;
	virtual void Update() override;
	//virtual void LateUpdate() override;
	//virtual void Render() override;

private:
	class TextRenderer* textRenderer;
	wchar_t debugText[200];
};