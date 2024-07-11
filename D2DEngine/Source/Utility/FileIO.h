#pragma once
#include "../ThirdParty/single_include/nlohmann/json.hpp"

using namespace nlohmann;
class AnimationClip;

namespace SaveFlie
{
    /** 애니메이션 클립을 전달받은 경로에 저장합니다.*/
    void AnimationClipSaveToFile(const AnimationClip& clip, const wchar_t* path);

    /** 전달받은 ordered_json 객체를 경로에 저장합니다.*/
    void ordered_jsonSaveToFile(const ordered_json& obj, const wchar_t* path);
};

namespace LoadFile
{
    /** 애니메이션 클립을 전달받은 경로에서 불러옵니다..*/
    //void AnimationClipLoadToFile(AnimationClip& clip, const wchar_t* path);

    /** 전달받은 경로에서 json 문자열로 불러옵니다. 실패시 ""을 담아줍니다. 파싱해서 사용할 수 있습니다.*/
    std::string ordered_jsonLoadToFile(const wchar_t* path);
};

                                                 