#pragma once
#include <string>
#include <iostream>
#include <fstream>

class AnimationClip;

namespace SaveFlie
{
    /** �ִϸ��̼� Ŭ���� ���޹��� ��ο� �����մϴ�.*/
    void AnimationClipSaveToFile(const AnimationClip& clip, const wchar_t* path);

};