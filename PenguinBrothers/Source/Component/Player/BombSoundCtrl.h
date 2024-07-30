#pragma once
#include <Core/Component/Base/ComponentBase.h>

class BombSoundCtrl : public ComponentBase
{
	class AudioClip* audioClip;
public:
	BombSoundCtrl(GameObjectBase& gameObject);
	virtual ~BombSoundCtrl() override;

protected:
	virtual void Start() override;
	virtual void Update() override;
	//virtual void LateUpdate() override;
	//virtual void Render() override;

	//virtual void SerializedJson(ordered_json& jsonObj) override;
	//virtual void DeSerializedJson(ordered_json& jsonObj) override;
};