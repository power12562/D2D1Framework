#pragma once	 
class ComponentBase;

/** �ݶ��̴� �̺�Ʈ�� ����� ������Ʈ�� �������̽�. �����ڿ� this�� �Ѱܼ� ������Ʈ ������ üũ �մϴ�.*/
class ICollider2DNotify
{
	friend class WorldManager;
	friend class ColliderManager;
public:
	/*this�� �Ѱ� Ÿ���� üũ�ϼ���. */
	template <typename T>
	ICollider2DNotify(T* _this)
	{
		static_assert(std::is_base_of<ComponentBase, T>::value,
			"ICollider2DNotify Ŭ������ ComponentBase�� ��ӹ޴� Ŭ���������� ��� ���� �մϴ�.");
	}
	virtual ~ICollider2DNotify() = default;
protected:
	virtual void OnCollisionEnter2D(GameObjectBase* collision) = 0;
	virtual void OnCollisionStay2D(GameObjectBase* collision) = 0;
	virtual void OnCollisionExit2D(GameObjectBase* collision) = 0;

	virtual void OnTriggerEnter2D(GameObjectBase* collision) = 0;
	virtual void OnTriggerStay2D(GameObjectBase* collision) = 0;
	virtual void OnTriggerExit2D(GameObjectBase* collision) = 0;
};									   


/*
	virtual void OnCollisionEnter2D(GameObjectBase* collision) override {};
	virtual void OnCollisionStay2D(GameObjectBase* collision) override {};
	virtual void OnCollisionExit2D(GameObjectBase* collision) override {};

	virtual void OnTriggerEnter2D(GameObjectBase* collision) override {};
	virtual void OnTriggerStay2D(GameObjectBase* collision) override {};
	virtual void OnTriggerExit2D(GameObjectBase* collision) override {};
*/

