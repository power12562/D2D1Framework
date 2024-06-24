#pragma once
#include "Core/Scene/SceneBase.h"

class SceneManager
{
public:
	template<typename T> static void LoadScene();
	
	static void Start();
	static void Update();
	static void Render();
private:
	SceneManager();
	~SceneManager();
	static class SceneBase* currentScene;
};

template<typename T> inline void SceneManager::LoadScene()
{
	// T�� SceneBase�κ��� ��ӹ޴��� Ȯ��
	static_assert(std::is_base_of<SceneBase, T>::value, "Is not Scene");

	if (currentScene)
	{
		delete currentScene;		
	}
	currentScene = new T;
	Start();
}
