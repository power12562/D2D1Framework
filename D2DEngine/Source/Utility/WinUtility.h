#pragma once
#include <string>

namespace WinUtility
{
    /* 
      윈도우 창을 열어 경로를 선택해 가져옵니다. 
      매개변수는 필터로 지정할 확장자 입니다.
    */
    std::wstring GetFilePath(const wchar_t* fileType = L"*");
 

};