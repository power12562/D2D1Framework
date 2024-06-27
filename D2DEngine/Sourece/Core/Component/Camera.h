#pragma once
#include "Core/Component/Base/ComponentBase.h"

class Camera : public ComponentBase
{
public:
	Camera(GameObjectBase& gameObject);
	virtual ~Camera() override;
	
	/** �� ī�޶� �������� ���� �մϴ�.*/
	void SetMain();

	/** ���� ī�޶�*/
	static inline Camera* const mainCamera() { return mainCam; }

	/** ī�޶��� �����*/

protected:
	virtual void Start() override;
	virtual void Update() override;
	virtual void Render() override;

private:
	static Camera* mainCam;
	
};

