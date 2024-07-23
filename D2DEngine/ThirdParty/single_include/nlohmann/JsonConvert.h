#pragma once
#include <stdexcept>
#include <string>
#pragma warning(disable : 4333)

namespace JsonConvert
{
    std::string wstring_to_utf8(const std::wstring& wstr);
    std::wstring utf8_to_wstring(const std::string& str);
};
