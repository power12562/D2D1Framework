#pragma once
#include "../ThirdParty/single_include/nlohmann/json.hpp"

using namespace nlohmann;
class AnimationClip;

namespace SaveFlie
{
   

    /** �ִϸ��̼� Ŭ���� ���޹��� ��ο� �����մϴ�.*/
    void AnimationClipSaveToFile(const AnimationClip& clip, const wchar_t* path);

    /** ���޹��� ordered_json ��ü�� ��ο� �����մϴ�.*/
    void ordered_jsonSaveToFile(const ordered_json& obj, const wchar_t* path);
};

