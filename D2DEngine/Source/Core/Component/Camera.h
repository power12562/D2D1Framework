#pragma once
#include "Core/Component/Base/ComponentBase.h"
#include <d2d1.h>
#include <list>

class Camera : public ComponentBase
{
	friend LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
public:
	Camera(GameObjectBase& gameObject);
	virtual ~Camera() override;
	
	/** 이 카메라를 메인으로 설정 합니다.*/
	void SetMain();

	/** 메인 카메라. 없으면 nullptr 반환합니다.*/
	static inline Camera* const GetMainCamera() { return mainCam; }

	/** 이 카메라의 역행렬*/
	const D2D1_MATRIX_3X2_F& GetInvertMatrix();

protected:
	//virtual void Start() override;
	//virtual void Update() override;
	//virtual void Render() override;

private:
	/** 이 카메라의 instanceList에서의 노드*/
	std::list<Camera*>::iterator instanceIter;

	/** 메인 카메라*/
	static Camera* mainCam;

	/** 생성된 컴포넌트 리스트*/
	static std::list<Camera*> instanceList;

	/** D2D factory 재생성시 호출되는 메서드*/
	static void ResetCameraPivot();
};

