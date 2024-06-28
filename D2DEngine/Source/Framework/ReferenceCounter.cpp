#include "ReferenceCounter.h"

ULONG ReferenceCounter::AddRef()
{
	refCount++;
	return refCount;
}

ULONG ReferenceCounter::Release()
{
	refCount--;
	if (refCount == 0) {
		// 파괴자에 virtual 키워드를 사용했으므로 자식클래스의 파괴자가 호출된다. 		
		delete this;
		return 0;
	}
	return refCount;
}

ULONG ReferenceCounter::GetRefCount() const
{
	return refCount;
}
