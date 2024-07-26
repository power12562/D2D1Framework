#pragma once
#include <Vector/Vector2.h>

#include <string>
#include <Windows.h>

namespace WinUtility
{
    /* 
      ������ â�� ���� ��θ� ������ �����ɴϴ�. 
      �Ű������� ���ͷ� ������ Ȯ���� �Դϴ�.
    */
    std::wstring GetOpenFilePath(const wchar_t* fileType = L"*");
 
    /*
      ������ â�� ���� ��θ� ������ �����ɴϴ�.
      �Ű������� ���ͷ� ������ Ȯ���� �Դϴ�.
    */
    std::wstring GetSaveAsFilePath(const wchar_t* fileType = L"*");

    /*
      �޽��� �ڽ��� ���� Ȯ���� ���� �޽��� �ڽ��� ���ϴ�.
      ����ڰ� Ȯ�� ������ true�� ��ȯ�ϰ�, ��Ҹ� ������ false�� ��ȯ�մϴ�.
      * title : �޽��� �ڽ��� ����
      * text : �˸�â�� �� �ȳ���
    */
    bool ShowConfirmationDialog(const wchar_t* title, const wchar_t* text);

    /*
    * ����ҷ��� ������Ʈ�� D2DEngine.rc ������ �߰� �ؾ� �մϴ�.
      int�� �Է¹޴� â�� ���ϴ�.
      �߸��� ���� �Է��ϸ� -1�� ��ȯ�մϴ�.
      * title : �ڽ��� ����
      * text : ����
    */
    int GetIntFromUser(LPCWSTR title, LPCWSTR text);

    /*
    * ����ҷ��� ������Ʈ�� D2DEngine.rc ������ �߰� �ؾ� �մϴ�.
      Vector2�� �Է¹޴� â�� ���ϴ�.
      �߸��� ���� �Է��ϸ� {0,0}�� ��ȯ�մϴ�.
      * title : �ڽ��� ����
    */
    Vector2 GetVector2FromUser(HWND hWnd, LPCWSTR title);
};