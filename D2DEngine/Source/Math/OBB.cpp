#include "OBB.h"
#include <Core/Component/Collider/BoxCollider2D.h>

bool OBB::CheckOverlap(const BoxCollider2D& a, const BoxCollider2D& b)
{
	Vector2 D = (b.transform.position + b.Center) - (a.transform.position + a.Center);

    Vector2 a_axis[2] = { a.transform.Right, a.transform.Up };
    Vector2 b_axis[2] = { b.transform.Right, b.transform.Up };

    for (int i = 0; i < 2; ++i) {
        Vector2 axisA = a_axis[i];

        float projection1 = a.ColliderSize.x * 0.5f * std::abs(Vector2::Dot(axisA, a_axis[0])) +
                            a.ColliderSize.y * 0.5f * std::abs(Vector2::Dot(axisA, a_axis[1]));

        float projection2 = b.ColliderSize.x * 0.5f * std::abs(Vector2::Dot(axisA,b_axis[0])) +
                            b.ColliderSize.y * 0.5f * std::abs(Vector2::Dot(axisA,b_axis[1]));

        float distance = std::abs(Vector2::Dot(D, axisA));

        if (distance > projection1 + projection2) {
            return false; // �浹 ����
        }
    }

    for (int i = 0; i < 2; ++i) {
        Vector2 axisB = b_axis[i];

        float projection1 = a.ColliderSize.x * 0.5f * std::abs(Vector2::Dot(axisB, a_axis[0])) +
                            a.ColliderSize.y * 0.5f * std::abs(Vector2::Dot(axisB, a_axis[1]));

        float projection2 = b.ColliderSize.x * 0.5f * std::abs(Vector2::Dot(axisB, b_axis[0])) +
                            b.ColliderSize.y * 0.5f * std::abs(Vector2::Dot(axisB , b_axis[1]));

        float distance = std::abs(Vector2::Dot(D, axisB));

        if (distance > projection1 + projection2) {
            return false; // �浹 ����
        }
    }

    return true; // �浹 �߻�
}

bool OBB::CheckOverlap(const BoxCollider2D& a, const Vector2& point)
{
    // ���� ��ġ�� OBB�� �߽ɿ����� ������� ��ġ�� ��ȯ
    Vector2 relativePos = point - (a.transform.position + a.Center);

    // OBB�� �� ���Ϳ� ���� ���� ���� ��ǥ ���
    Vector2 localPoint(Vector2::Dot(relativePos, a.transform.Right), Vector2::Dot(relativePos, a.transform.Up));

    // ���� ��ǥ�迡���� ��� �˻�
    return (std::abs(localPoint.x) <= a.ColliderSize.x * 0.5f) && (std::abs(localPoint.y) <= a.ColliderSize.y * 0.5f);;
}
