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

	//Json���� �ʱ�ȭ�� ����
	static std::wstring stagePath;
	std::wstring bgPath;	//��� �̹��� ��� 
	Vector2 playerSpawnPos; //�÷��̾� ���� ��ġ
	unsigned int EnemyDino0_SpawnCount; //EnemyDino0 ������Ʈ ��ȯ ����
	std::vector<Vector2> EnemyDino0_SpawnPos; //EnemyDino0 ������Ʈ ��ȯ ��ġ

	void LoadStageToJson();
	void SpawnSceneObjects();
private:
	void SaveStageToJson();
	void SpawnEditerObj();
};