#include "SpriteCollider2D.h"

#include "Framework/D2DRenderer.h"
#include "Framework/WinGameApp.h"

#include "Core/GameObject/Base/GameObjectBase.h"

#include "Core/Component/Camera.h"		 

SpriteCollider2D::SpriteCollider2D(GameObjectBase& gameObject) : 
	BoxCollider2D(gameObject)
{

}

SpriteCollider2D::~SpriteCollider2D()
{

}

void SpriteCollider2D::Update()
{
	bounds = gameObject.cullingBounds;
}

void SpriteCollider2D::Render()
{
	if (isDrawCollider)
	{
		const SIZE& screenSize = WinGameApp::GetClientSize();

		Vector2 worldScale = gameObject.transform.scale;
		worldScale.x = abs(worldScale.x);
		worldScale.y = abs(worldScale.y);
		const D2D1_MATRIX_3X2_F& objMatrix = gameObject.transform.GetWorldMatrix();
		const Vector2& objScale = Vector2::GetScaleFromMatrix(objMatrix);
		const D2D1_MATRIX_3X2_F& drawMatrix =
			(
				D2D1::Matrix3x2F::Scale(objScale.x, objScale.y) *
				D2D1::Matrix3x2F::Translation(bounds.center.x, screenSize.cy - bounds.center.y) *
				Camera::GetMainCamera()->GetInvertMatrix()
				); //ȸ�� ��Ʈ������ ������ ���� ��Ʈ���� * ī�޶� ����� ��Ʈ���� (ī�޶� ���� ��ǥ��)
		D2D1_RECT_F drawRect = {
			-gameObject.transform.pivot.x, -gameObject.transform.pivot.y,
			gameObject.transform.pivot.x, gameObject.transform.pivot.y
		};
		D2DRenderer::DrawRect(drawMatrix, drawRect, D2D1::ColorF(D2D1::ColorF::Green), DrawFill, DrawAlpha);
	}
}


