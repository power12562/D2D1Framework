#pragma once
#include <Vector/Vector2.h>
#include "../ThirdParty/single_include/nlohmann/json.hpp"

using namespace nlohmann;
class AnimationClip;

namespace JsonUtiliy
{
	/*json ���� Vector2�� �����ϸ� std::vector<float>�� ����˴ϴ�.*/
	using Vector2 = std::vector<float>;

	/** ���޹��� ordered_json ��ü�� ��ο� �����մϴ�.*/
	void ordered_jsonSaveToFile(const ordered_json& obj, const wchar_t* path);

	/*
		���޹��� ��ο��� json�� �ҷ��ɴϴ�.
		ouput �Ű������� �Ľ��� �ݴϴ�. ���н� �Լ��� false�� �����մϴ�.
	*/
	bool ordered_jsonLoadToFile(const wchar_t* path, ordered_json& output);


};

