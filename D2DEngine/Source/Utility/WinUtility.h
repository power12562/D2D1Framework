#pragma once
#include <string>

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

};