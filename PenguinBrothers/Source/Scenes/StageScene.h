#pragma once
#include <Source/Scenes/StageEditer.h>

#include <vector>
#include <string>

class StageScene : public StageEditer
{
public:
	StageScene();
	virtual ~StageScene() override;

	//Json���� �ʱ�ȭ�� ����

	std::wstring bgPath;	//��� �̹��� ��� 
	Vector2 playerSpawnPos; //�÷��̾� ���� ��ġ
	unsigned int EnemyDino0_SpawnCount; //EnemyDino0 ������Ʈ ��ȯ ����
	std::vector<Vector2> EnemyDino0_SpawnPos; //EnemyDino0 ������Ʈ ��ȯ ��ġ
};