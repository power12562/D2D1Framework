#pragma once
#include "Core/Component/Base/ComponentBase.h"

class DebugTextCtrl : public ComponentBase
{
public:
	DebugTextCtrl(GameObjectBase& gameObject);
	virtual ~DebugTextCtrl() override;

protected:
	virtual void Start() override;
	virtual void Update() override;
	//virtual void LateUpdate() override;
	//virtual void Render() override;

};