#include "JsonUtility.h"
#include <fstream>
#include <iostream>
#include <string>
#include "Core/Component/Renderer/SpriteAnimationRenderer.h"

namespace JsonUtiliy
{
    void ordered_jsonSaveToFile(const nlohmann::ordered_json& obj, const wchar_t* path)
    {
        std::ofstream ofs(path);
        ofs << obj.dump(2);
        ofs.close();
    }

    std::string ordered_jsonLoadToFile(const wchar_t* path)
    {
        std::ifstream ifs(path, std::ios::in);
        if (!ifs.is_open())
        {
            printf("jsonLoad, File not found %ws", path);
            return std::string("");
        }
        std::string str((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
        ifs.close();
        return str;
    }

    Vector2 JsonGetVector2(const json_abi_v3_11_3::ordered_json& jsonValue)
    {
        std::vector<float> points = jsonValue.get<std::vector<float>>();
        return Vector2{ points[0], points[1] };
    }
};

