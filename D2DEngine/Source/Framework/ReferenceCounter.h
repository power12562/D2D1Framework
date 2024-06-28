#pragma once

typedef unsigned long ULONG;

class ReferenceCounter
{
private:
	ULONG refCount;

public:
	ReferenceCounter() : refCount(1) { } //���� �ν��Ͻ� ������ refCount�� 1�� ����

	// virtual Ű���� ������� �ı��ڸ� �����Լ��� ����� delete �� ȣ���Ҷ� 
	// �ı��ڸ� ȣ���� �ڽ��� �ı��� -> �θ��� �ı��� ������ ȣ�� �ǵ��� �Ѵ�.
	// �ڽ�Ŭ�������� ������ ���·� ������ �ص� virtual ���¸� �����Ѵ�
	virtual ~ReferenceCounter() { }

	ULONG AddRef();

	ULONG Release();

	ULONG GetRefCount() const;
};