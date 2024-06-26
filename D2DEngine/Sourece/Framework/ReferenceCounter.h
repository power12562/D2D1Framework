#pragma once

typedef unsigned long ULONG;

class ReferenceCounter
{
private:
	ULONG refCount;

public:
	ReferenceCounter() : refCount(1) { } //최초 인스턴스 생성시 refCount는 1로 시작

	// virtual 키워드 사용으로 파괴자를 가상함수로 만들어 delete 를 호출할때 
	// 파괴자를 호출이 자식의 파괴자 -> 부모의 파괴자 순으로 호출 되도록 한다.
	// 자식클래스에서 제거한 상태로 재정의 해도 virtual 상태를 유지한다
	virtual ~ReferenceCounter() { }

	ULONG AddRef();

	ULONG Release();

	ULONG GetRefCount() const;
};