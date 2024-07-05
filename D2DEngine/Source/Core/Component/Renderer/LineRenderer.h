#pragma once
#include "Core/Component/Base/ComponentBase.h"
#include "Vector/Vector2.h"

#include <d2d1.h>


class LineRenderer : public ComponentBase
{
public:
	LineRenderer(GameObjectBase& gameObject);
	virtual ~LineRenderer() override;

	Vector2 StartPosition{ 0,0 }; //* �ڽ��� ��ġ ���� ���� ��ǥ
	Vector2 EndPosition{ 0,0 };	  //* �ڽ��� ��ġ ���� ���� ��ǥ

	D2D1_COLOR_F Color = D2D1::ColorF(D2D1::ColorF::Black); //* ����
	float Width = 0.5f; //* ����
protected:
	//virtual void Start() override;
	//virtual void Update() override;
	//virtual void LateUpdate() override;
	virtual void Render() override;

private:
	


};