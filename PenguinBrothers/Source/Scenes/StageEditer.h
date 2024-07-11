#pragma once
#include "Core/Scene/WorldBase.h"
#include <vector>
#include <string>

class StageEditer : public WorldBase
{
public:
	StageEditer();
	virtual ~StageEditer() override;

	//Json���� �ʱ�ȭ�� ����

	std::wstring bgPath;	//��� �̹��� ��� 
	Vector2 playerSpawnPos; //�÷��̾� ���� ��ġ
	unsigned int EnemyDino0_SpawnCount; //EnemyDino0 ������Ʈ ��ȯ ����
	std::vector<Vector2> EnemyDino0_SpawnPos; //EnemyDino0 ������Ʈ ��ȯ ��ġ

	

private:
	static std::wstring stagePath;

	void LoadStageToJson();
	void SaveStageToJson();

};