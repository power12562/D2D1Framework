#include "BoxCollider2D.h"

#include "Framework/D2DRenderer.h"
#include "Framework/WinGameApp.h"

#include "Core/GameObject/Base/GameObjectBase.h"

#include "Core/Component/Camera.h"

BoxCollider2D::BoxCollider2D(GameObjectBase& gameObject) : ComponentBase(gameObject)
{
	bounds = nullptr;	
	trMatrix = D2D1::Matrix3x2F::Identity();
}

BoxCollider2D::~BoxCollider2D()
{

}

void BoxCollider2D::Start()
{
	bounds = &gameObject.GetBounds();
}


void BoxCollider2D::Render()
{
	if (isDrawCollider)
	{
		const SIZE& screenSize = WinGameApp::GetClientSize();

		Vector2 worldScale = gameObject.transform.scale;
		const D2D1_MATRIX_3X2_F& objMatrix = gameObject.transform.GetWorldMatrix();
		const Vector2& objScale = Vector2::GetScaleFromMatrix(objMatrix);
		const D2D1_MATRIX_3X2_F& drawMatrix =
			(		
				D2D1::Matrix3x2F::Scale(objScale.x, objScale.y) * 		
				D2D1::Matrix3x2F::Translation(bounds->center.x, screenSize.cy - bounds->center.y)*
				Camera::GetMainCamera()->GetInvertMatrix()
				); //ȸ�� ��Ʈ������ ������ ���� ��Ʈ���� * ī�޶� ����� ��Ʈ���� (ī�޶� ���� ��ǥ��)
		const D2D1_RECT_F& drawRect = { -bounds->extents.x / worldScale.x , -bounds->extents.y / worldScale.y, bounds->extents.x / worldScale.x, bounds->extents.y / worldScale.y }; //�ڽ��� ������ ����(�� ��Ʈ������ �̹� ���Ե�)
		D2DRenderer::DrawRect(drawMatrix, drawRect, D2D1::ColorF(D2D1::ColorF::Green));
	}
}
