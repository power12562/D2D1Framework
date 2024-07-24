#pragma once
#include <Core/Component/Base/ComponentBase.h>
#include <d2d1helper.h>

class BoxRenderer : public ComponentBase
{
public:
	BoxRenderer(GameObjectBase& gameObject) : ComponentBase(gameObject) {}
	virtual ~BoxRenderer() override;

	Vector2 center{}; //�׸� ��ġ (������Ʈ ���� ���� ��ǥ)
	Vector2 size{}; //�ڽ� ũ�� (�ʺ�, ����)
	D2D1::ColorF color = D2D1::ColorF(D2D1::ColorF::Black);	//�׸� ����
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