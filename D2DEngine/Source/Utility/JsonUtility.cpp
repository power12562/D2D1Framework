#include "JsonUtility.h"
#include <fstream>
#include <iostream>
#include <string>
#include <cassert>
#include "Core/Component/Renderer/SpriteAnimationRenderer.h"

namespace JsonUtiliy
{
    void ordered_jsonSaveToFile(const nlohmann::ordered_json& obj, const wchar_t* path)
    {
        std::wstring savePath = path;
        size_t type = savePath.rfind(L".json");
        if (type == std::wstring::npos)
        {
            savePath += L".json";
        }
        std::ofstream ofs(savePath);
        ofs << obj.dump(2);
        ofs.close();
    }

    bool ordered_jsonLoadToFile(const wchar_t* path, ordered_json& output)
    {
        std::ifstream ifs(path, std::ios::in);
        if (!ifs.is_open())
        {
            printf("jsonLoad, File not found %ws", path);
            assert(false);
            return false;
        }
        std::string str((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
        output = ordered_json::parse(str);
        ifs.close();
        return true;
    }
};

