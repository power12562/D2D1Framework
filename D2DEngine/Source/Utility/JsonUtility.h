#pragma once
#include <Vector/Vector2.h>
#include "../ThirdParty/single_include/nlohmann/json.hpp"

using namespace nlohmann;
class AnimationClip;

namespace JsonUtiliy
{
	/** ���޹��� ordered_json ��ü�� ��ο� �����մϴ�.*/
	void ordered_jsonSaveToFile(const ordered_json& obj, const wchar_t* path);

	/*
		���޹��� ��ο��� json�� �ҷ��ɴϴ�.
		ouput �Ű������� �Ľ��� �ݴϴ�. ���н� �Լ��� false�� �����մϴ�.
	*/
	bool ordered_jsonLoadToFile(const wchar_t* path, ordered_json& output);

	/*
		json ��ü�� ���� Vector2 ������ ��ȯ�մϴ�.
	*/
	Vector2 JsonGetVector2(const json_abi_v3_11_3::ordered_json& jsonValue);
};

