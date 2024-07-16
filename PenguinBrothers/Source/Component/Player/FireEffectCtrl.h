#pragma once
#include <Core/Component/Base/ComponentBase.h>
#include <Core/Component/Collider/Interface/ICollider2DNotify.h>

class FireEffectCtrl : public ComponentBase	, public ICollider2DNotify
{
public:
	FireEffectCtrl(GameObjectBase& gameObject);
	virtual ~FireEffectCtrl() override;

protected:
	virtual void Start() override;
	virtual void Update() override;
	//virtual void LateUpdate() override;
	//virtual void Render() override;

private:
	class SpriteAnimationRenderer* animationRenderer = nullptr;

	virtual void OnCollisionEnter2D(GameObjectBase* collision) override;
	virtual void OnCollisionStay2D(GameObjectBase* collision) override;
	virtual void OnCollisionExit2D(GameObjectBase* collision) override;

	virtual void OnTriggerEnter2D(GameObjectBase* collision) override {};
	virtual void OnTriggerStay2D(GameObjectBase* collision) override {};
	virtual void OnTriggerExit2D(GameObjectBase* collision) override {};
};



