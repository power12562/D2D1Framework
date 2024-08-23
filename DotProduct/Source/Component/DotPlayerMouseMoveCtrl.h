#pragma once
#include <Core/Component/Base/ComponentBase.h>

class DotPlayerMouseMoveCtrl : public ComponentBase
{
public:
	DotPlayerMouseMoveCtrl(GameObjectBase& gameObject);
	virtual ~DotPlayerMouseMoveCtrl() override;

protected:
	virtual void Start() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	//virtual void Render() override;

	//virtual void SerializedJson(ordered_json& jsonObj) override;
	//virtual void DeSerializedJson(ordered_json& jsonObj) override;

private:
	class TextRenderer* debugTextRenderer = nullptr;
	class Movement* movement = nullptr;

private:
	Vector2 lastClickPosition{};
	Vector2 leftClickDir{};

	float dotProductValue{};
	float rotationAngle{};
	float rotationDir{};
};