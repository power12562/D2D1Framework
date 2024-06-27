#pragma once
#include "Core/Component/Base/ComponentBase.h"

class Camera : public ComponentBase
{
public:
	Camera(GameObjectBase& gameObject);
	virtual ~Camera() override;
	
	/** 이 카메라를 메인으로 설정 합니다.*/
	void SetMain();

	/** 메인 카메라*/
	static inline Camera* const mainCamera() { return mainCam; }

	/** 카메라의 역행렬*/

protected:
	virtual void Start() override;
	virtual void Update() override;
	virtual void Render() override;

private:
	static Camera* mainCam;
	
};

