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
	
	/** �� ī�޶� �������� ���� �մϴ�.*/
	void SetMain();

	/** ���� ī�޶�. ������ nullptr ��ȯ�մϴ�.*/
	static inline Camera* const GetMainCamera() { return mainCam; }

	/** �� ī�޶��� �����*/
	const D2D1_MATRIX_3X2_F& GetInvertMatrix();

protected:
	//virtual void Start() override;
	//virtual void Update() override;
	//virtual void Render() override;

private:
	/** �� ī�޶��� instanceList������ ���*/
	std::list<Camera*>::iterator instanceIter;

	/** ���� ī�޶�*/
	static Camera* mainCam;

	/** ������ ������Ʈ ����Ʈ*/
	static std::list<Camera*> instanceList;

	/** D2D factory ������� ȣ��Ǵ� �޼���*/
	static void ResetCameraPivot();
};

