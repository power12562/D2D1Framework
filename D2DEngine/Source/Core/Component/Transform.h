#pragma once
#include "Core/Component/Base/ComponentBase.h"

#include "Vector/Vector2.h"

#include <list>
#include <d2d1helper.h>

class D2D1::Matrix3x2F;
class Vector3;
class Transform : public ComponentBase
{
	friend class WorldManager;
	friend class GameObjectBase;
	friend class Camera;

	class TVector2
	{	
		friend class Transform;
		Transform* thisTransform = nullptr;
		Vector2 value;

	public:
		TVector2(int x, int y) { value.x = (float)x; value.y = (float)y; }
		TVector2(float x, float y) { value.x = x; value.y = y; }
		TVector2(double x, double y) { value.x = (float)x; value.y = (float)y; }

		~TVector2() = default;
		TVector2(const TVector2& other);
		TVector2(const Vector2& other);
		
		float GetX() const { return value.x; } const //property
		float GetY() const { return value.y; } const //property
		__declspec(property(get = GetX)) float x;
		__declspec(property(get = GetY)) float y;

		operator Vector2();
		TVector2& operator=(const Vector2& other);
		Vector2 operator*(const float scala) const;
		TVector2& operator*=(const float scala);
		TVector2& operator+=(const Vector2& other);
		TVector2& operator-=(const Vector2& other);
		Vector2 operator+(const Vector2& other);
		Vector2 operator-(const Vector2& other);
		bool operator!=(const Vector2& other);
		bool operator==(const Vector2& other);
		operator Vector3();
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

	Vector2 GetRight() const;
	__declspec(property(get = GetRight)) Vector2 Right;

	Vector2 GetUp() const;
	__declspec(property(get = GetUp)) Vector2 Up;

	inline const D2D1_MATRIX_3X2_F& GetWorldMatrix() const { return WM; }
	inline const D2D1_MATRIX_3X2_F& GetCameraMatrix() const { return CM; }

	inline const D2D1_MATRIX_3X2_F& GetPivotMatrix() const { return PM; } 
	inline const D2D1_MATRIX_3X2_F& GetInvertPivotMatrix() const { return IPM; }

	/** 부모 오브젝트를 설정합니다.*/
	void SetParent(Transform& parent);	
	void SetParent(GameObjectBase& parent);
	/** 부모 오브젝트를 해제합니다. 부모로 둘 대상을 인자로 넘길 수 있습니다.*/
	void SetParent();
	bool IsParent() { return parent; } //부모 여부 확인용
	const Transform& GetParent() const { return *parent; }

	/** X축 반전 시키기*/
	void FlipX(bool isflip);
	void FlipX();
	/** Y축 반전 시키기*/
	void FlipY(bool isflip);
	void FlipY();

	bool IsFlipX() const { return isFlipX; } 
	/** 좌우 반전*/
	__declspec(property(get = IsFlipX, put = FlipX)) bool flipX;
	bool IsFlipY() const { return isFlipY; } 
	/** 상하 반전*/
	__declspec(property(get = IsFlipY, put = FlipY)) bool flipY;

private:
	Transform* parent{};
	std::list<Transform*> childsList;

	/** 매트릭스를 계산 합니다. WorldManager에서 호출합니다.*/
	void UpdateMatrix();

	void UpdateChildTransform();
	void UpdateWorldMatrix();

	/** World Matrix*/
	D2D1_MATRIX_3X2_F WM; 

	/** Invert World Matrix*/
	D2D1_MATRIX_3X2_F IWM;

	/** Camera Matrix*/
	D2D1_MATRIX_3X2_F CM; //카메라

	/** Pivot Matrix*/
	D2D1_MATRIX_3X2_F PM;

	/** Invert Pivot Matrix*/
	D2D1_MATRIX_3X2_F IPM;

	bool isFlipX = false;
	bool isFlipY = false;

	virtual void SerializedJson(ordered_json& jsonObj) override;
	virtual void DeSerializedJson(ordered_json& jsonObj) override;
};



