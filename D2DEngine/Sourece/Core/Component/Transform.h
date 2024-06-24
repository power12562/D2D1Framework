#pragma once
#include "Core/Component/Base/ComponentBase.h"
#include "Vector/Vector2.h"
#include <list>
#include <d2d1helper.h>

class D2D1::Matrix3x2F;

class Transform : public ComponentBase
{
	friend class GameObjectBase;
	friend class SpriteRenderer;

	class TVector2
	{	
		friend class Transform;
		Transform* thisTransform = nullptr;
		Vector2 value;
	public:
		TVector2(int x, int y) { value.x = (float)x; value.y = (float)y; }
		TVector2(float x, float y) { value.x = x; value.y = y; }
		TVector2(double x, double y) { value.x = (double)x; value.y = (double)y; }

		~TVector2() = default;
		TVector2(const TVector2& other);
		TVector2(const Vector2& other);
		
		operator Vector2();
		Vector2 operator-(const Vector2& other);
		Vector2 operator+(const Vector2& other);

		TVector2& operator=(const Vector2& other);
		TVector2& operator+=(const Vector2& other);
		TVector2& operator-=(const Vector2& other);
	private: 
		void InitTVector2(Transform* thisTransform);
		TVector2& SetTVector(const Vector2& other);		
	};
	class TFloat
	{
		friend class Transform;
	protected:
		Transform* thisTransform = nullptr;
	public:
		virtual ~TFloat() = default;
		void InitTFloat(Transform* thisTransform);
		TFloat(const float& rotation);
		operator float() const;

		virtual float& operator=(const float& rotation);
		virtual float& operator+=(const float& rotation);
		virtual float& operator-=(const float& rotation);
	private:
		void SetAngle(const float& rotation);
		float angle = 0;
	};

public:
	Transform(GameObjectBase& gameObject);
	~Transform();

	TVector2 position{ 0,0 };
	TFloat rotation = 0;
	TVector2 scale{ 1,1 };
	TVector2 pivot{ 0,0 };

	TVector2 localPosition{ 0,0 };
	TFloat localRotation = 0;
	TVector2 localScale{ 1,1 };

	D2D1::Matrix3x2F& GetWorldMatrix() { return worldMatrix; }

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

	D2D1::Matrix3x2F worldMatrix;
	void UpdateWorldMatrix();

	D2D1::Matrix3x2F mScale, mPosition, mRotation, mPivot, mInvertPivot;
};



