#pragma once
#include <Core/Component/Base/ComponentBase.h>
#include <Core/GameObject/Base/GameObjectBase.h>

class SoundTest : public ComponentBase
{
public:
	SoundTest(GameObjectBase& gameObject);
	virtual ~SoundTest() override;

protected:
	//virtual void Start() override;
	virtual void Update() override;
	//virtual void LateUpdate() override;
	//virtual void Render() override;

	//virtual void SerializedJson(ordered_json& jsonObj) override;
	//virtual void DeSerializedJson(ordered_json& jsonObj) override;
};