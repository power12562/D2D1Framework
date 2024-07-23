#pragma once
#include "Core/Scene/WorldBase.h"
#include <vector>
#include <string>

class StageEditer : public WorldBase
{
	friend class EditerCtrl;
public:
	StageEditer();
	StageEditer(const wchar_t* stagePath, bool isEditer = false);
	virtual ~StageEditer() override;

	//Json으로 초기화할 값들
	std::wstring stagePath;
	std::wstring bgPath;	//배경 이미지 경로 
	Vector2 playerSpawnPos; //플레이어 시작 위치
	GameObjectBase* playerObj;

	int EnemyDino0_SpawnCount; //EnemyDino0 오브젝트 소환 개수
	std::vector<Vector2> EnemyDino0_SpawnPos; //EnemyDino0 오브젝트 소환 위치
	std::vector<GameObjectBase*> EnemyDino0Objs; //생성된 몬스터들

	int GroundBox_SpawnCount; //바닥 콜라이더 개수
	std::vector<Vector2> GroundBox_SpawnPos; //위치
	std::vector<Vector2> GroundBox_Size; //크기
	std::vector<GameObjectBase*> GroundObjs; //생성된 박스들
	
	void LoadStageToJson();
	void SpawnSceneObjects();

	void PosToSpawnPos();
private:
	bool isEditer;
	void SaveStageToJson();
	void SpawnEditerObj();
};