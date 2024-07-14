#include "RectModeCtrl.h"
#include <Framework/D2DRenderer.h>
#include <Framework/InputSystem.h>

#include <Core/Component/Camera.h>
#include <Core/Component/Renderer/SpriteRenderer.h>
#include <Core/Component/Renderer/SpriteAnimationRenderer.h>

RectModeCtrl::RectModeCtrl(GameObjectBase& gameObject) : ComponentBase(gameObject) 
{


}

RectModeCtrl::~RectModeCtrl()
{

}

void RectModeCtrl::Start()
{
	spriteRenderer = &GetComponent<SpriteRenderer>();
}

void RectModeCtrl::Update()
{
	using namespace InputSystem;
	if (Input.IsKeyDown(KeyCode::Num1))
	{
		SetSourceLeftTop();
	}
	if (Input.IsKeyDown(KeyCode::Num2))
	{
		SetSourceRightBottom();
	}
}

void RectModeCtrl::Render()
{ 
	if (spriteAnimation)
	{
		D2D1_SIZE_F currentSize = spriteRenderer->GetImageSize();
		FrameInfo* frame = spriteAnimation->GetCurrentFrame();	
		D2D1_MATRIX_3X2_F tmImage = D2D1::Matrix3x2F::Translation(currentSize.width * -0.5f, currentSize.height * -0.5f);
		D2D1_MATRIX_3X2_F tmSource = D2D1::Matrix3x2F::Translation(frame->source.left, frame->source.top);
		D2DRenderer::DrawRect(tmImage * gameObject.transform.GetCameraMatrix(), { 0,0, currentSize.width, currentSize.height }, D2D1::ColorF(D2D1::ColorF::Green));
		if (frame)
		{
			D2DRenderer::DrawRect(tmImage * tmSource * gameObject.transform.GetCameraMatrix(), { 0,0, frame->source.right - frame->source.left,  frame->source.bottom - frame->source.top }, D2D1::ColorF(D2D1::ColorF::Red));
		}		
	}	
}

void RectModeCtrl::SetSourceLeftTop()
{
	if (FrameInfo* frame = spriteAnimation->GetCurrentFrame())
	{
		const Vector2& camPos = Camera::GetMainCamera()->gameObject.transform.position;
		const D2D1_SIZE_F imageSize = (*spriteAnimation->GetCurrentImage())->GetSize();
		frame->source.left = int(camPos.x + imageSize.width * 0.5f);
		frame->source.top = int(imageSize.height * 0.5f - camPos.y);
	}
}

void RectModeCtrl::SetSourceRightBottom()
{
	if (FrameInfo* frame = spriteAnimation->GetCurrentFrame())
	{
		const Vector2& camPos = Camera::GetMainCamera()->gameObject.transform.position;
		const D2D1_SIZE_F imageSize = (*spriteAnimation->GetCurrentImage())->GetSize();
		frame->source.right = int(camPos.x + imageSize.width * 0.5f);
		frame->source.bottom = int(imageSize.height * 0.5f - camPos.y);
	}
}
