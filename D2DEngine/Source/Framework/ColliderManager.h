#pragma once
#include <list>

class ColliderBase;

class ColliderManager
{
	friend class ColliderBase;
	friend class WinGameApp;

	static std::list<ColliderBase*> instanceList;	//모든 콜라이더 리스트
};