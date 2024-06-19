#pragma once
#include "Core/Component/Base/ComponentBase.h"
#include "Vector/Vector2.h"
#include <list>

class Transform : public ComponentBase
{
	friend class GameObjectBase;

	class TVector2 : public Vector2
	{
	protected:
		Transform* pTransform = nullptr;
	public:
		virtual ~TVector2() override = default;
		void InitTVector2(Transform* thisTransform);
		TVector2(float x = 0, float y = 0) : Vector2(x, y) {}
		TVector2(double x, double y) : Vector2(x, y) {}
		TVector2(int x, int y) : Vector2(x, y) {}

		TVector2(const Vector2& other);
		virtual Vector2& operator=(const Vector2& other) override;
		virtual Vector2& operator+=(const Vector2& other) override;
		virtual Vector2& operator-=(const Vector2& other) override;
	};
	class TFloat
	{
	protected:
		Transform* pTransform = nullptr;
	public:
		float angle = 0;
		virtual ~TFloat() = default;
		void InitTFloat(Transform* thisTransform);
		TFloat(const float& rotation);
		operator float() const;
		virtual float& operator=(const float rotation);
		virtual float& operator+=(const float rotation);
		virtual float& operator-=(const float rotation);
	};

public:
	Transform(GameObjectBase& gameObject);
	~Transform();

	TVector2 position{ 0,0 };
	TFloat rotation = 0;
	TVector2 scale{ 1,1 };

	TVector2 localPosition{ 0,0 };
	TFloat localRotation = 0;
	TVector2 localScale{ 1,1 };

	/** 부모 오브젝트를 설정합니다. nullptr을 넘기면 헤제됩니다.*/
	void SetParent(Transform& parent);	
	void SetParent(void* ptr);
	Transform& GetParent() { return *parent; }

protected:
	virtual void Update() override;
	virtual void Render() override;

private:
	Transform* parent{};
	std::list<Transform*> childsList;
	void UpdateChildTransform(Transform& parent);

	bool isTranslation = true;

	/** 최상위 부모의 isTranslation 변수를 true로 변경 해줍니다.*/
	static void SetParentIsTranslation(Transform& transform);
};



