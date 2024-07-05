#pragma once
#include "Core/Component/Base/ComponentBase.h"
#include "Vector/Vector2.h"

#include <d2d1.h>


class LineRenderer : public ComponentBase
{
public:
	LineRenderer(GameObjectBase& gameObject);
	virtual ~LineRenderer() override;

	Vector2 StartPosition{ 0,0 }; //* 자신의 위치 기준 시작 좌표
	Vector2 EndPosition{ 0,0 };	  //* 자신의 위치 기준 종료 좌표

	D2D1_COLOR_F Color = D2D1::ColorF(D2D1::ColorF::Black); //* 색상
	float Width = 0.5f; //* 굵기
protected:
	//virtual void Start() override;
	//virtual void Update() override;
	//virtual void LateUpdate() override;
	virtual void Render() override;

private:
	


};