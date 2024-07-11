#pragma once
#include <Vector/Vector2.h>
#include "../ThirdParty/single_include/nlohmann/json.hpp"

using namespace nlohmann;
class AnimationClip;

namespace JsonUtiliy
{
	/** 전달받은 ordered_json 객체를 경로에 저장합니다.*/
	void ordered_jsonSaveToFile(const ordered_json& obj, const wchar_t* path);

	/*
		전달받은 경로에서 json을 문자열로 불러옵니다. 실패시 "" 담아줍니다.
		odered_json으로 파싱해 사용해야 합니다.
	*/
	std::string ordered_jsonLoadToFile(const wchar_t* path);

	/*
		json 객체의 값을 Vector2 값으로 반환합니다.
	*/
	Vector2 JsonGetVector2(const json_abi_v3_11_3::ordered_json& jsonValue);
};

