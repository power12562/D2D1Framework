#pragma once
#include <string>
#include <Windows.h>

namespace WinUtility
{
    /* 
      윈도우 창을 열어 경로를 선택해 가져옵니다. 
      매개변수는 필터로 지정할 확장자 입니다.
    */
    std::wstring GetOpenFilePath(const wchar_t* fileType = L"*");
 
    /*
      윈도우 창을 열어 경로를 선택해 가져옵니다.
      매개변수는 필터로 지정할 확장자 입니다.
    */
    std::wstring GetSaveAsFilePath(const wchar_t* fileType = L"*");

    /*
      메시지 박스를 열어 확인을 묻는 메시지 박스를 띄웁니다.
      사용자가 확인 누르면 true를 반환하고, 취소를 누르면 false를 반환합니다.
      * title : 메시지 박스의 제목
      * text : 알림창에 들어갈 안내문
    */
    bool ShowConfirmationDialog(const wchar_t* title, const wchar_t* text);

    /*
    * 사용할려면 프로젝트에 D2DEngine.rc 파일을 추가 해야 합니다.
      int를 입력받는 창을 띄웁니다.
      잘못된 값을 입력하면 -1을 반환합니다.
      * title : 박스의 제목
      * text : 설명
    */
    int GetIntFromUser(HWND hWnd, LPCWSTR title, LPCWSTR text);
};