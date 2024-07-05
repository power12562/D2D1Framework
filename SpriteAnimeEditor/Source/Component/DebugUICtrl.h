#pragma once
#include "Core/Component/Base/ComponentBase.h"
#include <string>
#include <vector>

class DebugUICtrl : public ComponentBase
{
public:
	DebugUICtrl(GameObjectBase& gameObject);
	virtual ~DebugUICtrl() override;
												
	std::vector<std::wstring> Line;

protected:
	virtual void Start() override;
	virtual void Update() override;
	//virtual void LateUpdate() override;
	//virtual void Render() override;

private:
	class TextRenderer* textRenderer = nullptr;
	class LineRenderer* lineRendererX = nullptr;
	class LineRenderer* lineRendererY = nullptr;
};