#pragma once
#include "Core/Scene/WorldBase.h"
#include <vector>
#include <string>

class StageEditer : public WorldBase
{
	friend class EditerCtrl;
public:
	StageEditer(bool editer = true);
	virtual ~StageEditer() override;

	//Json으로 초기화할 값들
	static std::wstring stagePath;
	std::wstring bgPath;	//배경 이미지 경로 
	Vector2 playerSpawnPos; //플레이어 시작 위치
	unsigned int EnemyDino0_SpawnCount; //EnemyDino0 오브젝트 소환 개수
	std::vector<Vector2> EnemyDino0_SpawnPos; //EnemyDino0 오브젝트 소환 위치

	void LoadStageToJson();
	void SpawnSceneObjects();
private:
	void SaveStageToJson();
	void SpawnEditerObj();
};