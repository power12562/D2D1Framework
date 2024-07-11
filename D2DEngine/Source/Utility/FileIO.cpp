#include "FileIO.h"
#include <fstream>
#include <iostream>
#include <iosfwd>
#include <string>
#include "Core/Component/Renderer/SpriteAnimationRenderer.h"

void SaveFlie::AnimationClipSaveToFile(const AnimationClip& clip, const wchar_t* path)
{
    std::ofstream outFile(path, std::ios::app); // append mode
    if (outFile.is_open()) 
    {
        for (int i = 0; i < clip.frames.size(); i++)
        {
            outFile << clip.frames[i].source.left << "," << clip.frames[i].source.top << ","
                << clip.frames[i].source.right << "," << clip.frames[i].source.bottom << ","
                << clip.frames[i].center.x << "," << clip.frames[i].center.y << ","
                << clip.frames[i].frameIntervalTime << "\n";
        }     
        outFile.close();
    }
    else 
    {
        std::cerr << "Unable to open file";
    }
}

void SaveFlie::ordered_jsonSaveToFile(const nlohmann::ordered_json& obj, const wchar_t* path)
{
    std::ofstream ofs(path);
    ofs << obj.dump(2);
    ofs.close();
}

