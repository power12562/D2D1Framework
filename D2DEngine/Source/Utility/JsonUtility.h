#pragma once
#include <Vector/Vector2.h>
#include "../ThirdParty/single_include/nlohmann/json.hpp"

using namespace nlohmann;
class AnimationClip;

namespace JsonUtiliy
{
	/*json 으로 Vector2를 저장하면 std::vector<float>로 저장됩니다.*/
	using Vector2 = std::vector<float>;

	/** 전달받은 ordered_json 객체를 경로에 저장합니다.*/
	void ordered_jsonSaveToFile(const ordered_json& obj, const wchar_t* path);

	/*
		전달받은 경로에서 json을 불러옵니다.
		ouput 매개변수에 파싱해 줍니다. 실패시 함수는 false를 리턴합니다.
	*/
	bool ordered_jsonLoadToFile(const wchar_t* path, ordered_json& output);


};

