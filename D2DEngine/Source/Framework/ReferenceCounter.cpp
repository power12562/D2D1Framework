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
		// �ı��ڿ� virtual Ű���带 ��������Ƿ� �ڽ�Ŭ������ �ı��ڰ� ȣ��ȴ�. 		
		delete this;
		return 0;
	}
	return refCount;
}

ULONG ReferenceCounter::GetRefCount() const
{
	return refCount;
}
