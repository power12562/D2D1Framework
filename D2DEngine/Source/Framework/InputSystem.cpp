#include "Framework/InputSystem.h"
#include "Framework/WinGameApp.h"

#include "Core/GameObject/Base/GameObjectBase.h"

#include "Core/Component/Camera.h"

namespace InputSystem
{
    Inputsystem Input;

    Vector2 MouseState::GetWorldPos() const
    {
        const SIZE& clientSize = WinGameApp::GetClientSize();
        Camera* mainCam = Camera::GetMainCamera();
        if (mainCam)
        {
            const Vector2& camScale = mainCam->gameObject.transform.scale;
            Vector2 mousePos{ x * camScale.x, y * camScale.y };
            D2D1_MATRIX_3X2_F worldMatrix = mainCam->GetMatrix();
            return Vector2(worldMatrix.dx + mousePos.x, -(worldMatrix.dy + mousePos.y - clientSize.cy)); //??? y축 맞추는 코드 아직 이해 못함...
        } 
        return Vector2(0, 0);
    }
}
using namespace InputSystem;

Inputsystem::Inputsystem()
{
    //키보드 입력 초기화
    for (int i = 0; i < 256; i++)
    {
        isKeyDown[i] = false;
        isKeyUp[i] = false;
        isKey[i] = false;
    }

    //마우스 입력 초기화
    mouseState.x = 0;
    mouseState.y = 0;
}

bool Inputsystem::IsKeyDown(KeyCode _key) const
{
    int key = (int)_key;

    return isKeyDown[key];
}

bool Inputsystem::IsKeyUp(KeyCode _key) const
{
    int key = (int)_key;

    return isKeyUp[key];
}

bool Inputsystem::IsKey(KeyCode _key) const
{
    int key = (int)_key;

    return isKey[key];
}

bool Inputsystem::IsAnyKey()
{
    return isAnyKey;
}

bool Inputsystem::IsAnyKeyDown()
{
    return isAnyKeyDown;
}

bool Inputsystem::IsAnyKeyUp()
{
    return isAnyKeyUp;
}

const MouseState& Inputsystem::GetMouseState()
{
    return mouseState;
}


//private:
void Inputsystem::SetKeyDown(KeyCode _key)
{
    int key = (int)_key;

    isKeyDown[key] = true;
    isKey[key] = true;
    isAnyKeyDown = true;
    isAnyKey = true;
}

void Inputsystem::SetKeyUp(KeyCode _key)
{
    int key = (int)_key;

    isKeyUp[key] = true;
    isKey[key] = false;
    isAnyKeyUp = true;
}

void Inputsystem::ResetInput()
{
    isAnyKey = false;

    for (int i = 0; i < 256; i++)
    {
        isKeyDown[i] = false;
        isKeyUp[i] = false;
        isAnyKey = isAnyKey || isKey[i];
    }

    mouseState.isLeftClickUp = false;
    mouseState.isLeftClickDown = false;

    mouseState.isRightClickUp = false;
    mouseState.isRightClickDown = false;

    mouseState.isMiddleClickUp = false;
    mouseState.isMiddleClickDown = false;

    isAnyKeyDown = false;
    isAnyKeyUp = false;
}

void Inputsystem::UpdateMouse()
{
    POINT pt;
    GetCursorPos(&pt);
    ScreenToClient(WinGameApp::GetHwnd(), &pt);

    mouseState.x = pt.x;
    mouseState.y = pt.y;

    if (!mouseState.isLeftClick && (GetAsyncKeyState(VK_LBUTTON) & 0x8000) != 0)
    {
        isAnyKeyDown = true;
        mouseState.isLeftClickDown = true;
        mouseState.isLeftClick = true;
    }
    else if (mouseState.isLeftClick && (GetAsyncKeyState(VK_LBUTTON) & 0x8000) == 0)
    {
        mouseState.isLeftClickUp = true;
        mouseState.isLeftClick = false;
        isAnyKeyUp = true;
    }

    if (!mouseState.isRightClick && (GetAsyncKeyState(VK_RBUTTON) & 0x8000) != 0)
    {
        isAnyKeyDown = true;
        mouseState.isRightClickDown = true;
        mouseState.isRightClick = true;
    }
    else if (mouseState.isRightClick && (GetAsyncKeyState(VK_RBUTTON) & 0x8000) == 0)
    {
        mouseState.isRightClickUp = true;
        mouseState.isRightClick = false;
        isAnyKeyUp = true;
    }

    if (!mouseState.isMiddleClick && (GetAsyncKeyState(VK_MBUTTON) & 0x8000) != 0)
    {
        mouseState.isMiddleClickDown = true;
        mouseState.isMiddleClick = true;
    }
    else if (mouseState.isMiddleClick && (GetAsyncKeyState(VK_MBUTTON) & 0x8000) == 0)
    {
        mouseState.isMiddleClickUp = true;
        mouseState.isMiddleClick = false;
    }
}

