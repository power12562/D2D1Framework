#pragma once
#include <string>
#include <iostream>
#include <fstream>

class AnimationClip;

namespace SaveFlie
{
    /** 애니메이션 클립을 전달받은 경로에 저장합니다.*/
    void AnimationClipSaveToFile(const AnimationClip& clip, const wchar_t* path);

};