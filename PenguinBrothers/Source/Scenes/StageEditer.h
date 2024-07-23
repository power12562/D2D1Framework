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

	//Json���� �ʱ�ȭ�� ����
	std::wstring stagePath;
	std::wstring bgPath;	//��� �̹��� ��� 
	Vector2 playerSpawnPos; //�÷��̾� ���� ��ġ
	GameObjectBase* playerObj;

	int EnemyDino0_SpawnCount; //EnemyDino0 ������Ʈ ��ȯ ����
	std::vector<Vector2> EnemyDino0_SpawnPos; //EnemyDino0 ������Ʈ ��ȯ ��ġ
	std::vector<GameObjectBase*> EnemyDino0Objs; //������ ���͵�

	int GroundBox_SpawnCount; //�ٴ� �ݶ��̴� ����
	std::vector<Vector2> GroundBox_SpawnPos; //��ġ
	std::vector<Vector2> GroundBox_Size; //ũ��
	std::vector<GameObjectBase*> GroundObjs; //������ �ڽ���
	
	void LoadStageToJson();
	void SpawnSceneObjects();

	void PosToSpawnPos();
private:
	bool isEditer;
	void SaveStageToJson();
	void SpawnEditerObj();
};