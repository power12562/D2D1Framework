#pragma once
#include <Core/Component/Base/ComponentBase.h>
#include <d2d1helper.h>

class BoxRenderer : public ComponentBase
{
public:
	BoxRenderer(GameObjectBase& gameObject) : ComponentBase(gameObject) {}
	virtual ~BoxRenderer() override;

	Vector2 center{}; //그릴 위치 (오브젝트 기준 로컬 좌표)
	Vector2 size{}; //박스 크기 (너비, 높이)
	D2D1::ColorF color = D2D1::ColorF(D2D1::ColorF::Black);	//그릴 색상
	bool isFill = false;
	float alpha = 1.0f;

protected:
	//virtual void Start() override;
	//virtual void Update() override;
	//virtual void LateUpdate() override;
	virtual void Render() override;

private:
	virtual void SerializedJson(ordered_json& jsonObj) override;
	virtual void DeSerializedJson(ordered_json& jsonObj) override;
};