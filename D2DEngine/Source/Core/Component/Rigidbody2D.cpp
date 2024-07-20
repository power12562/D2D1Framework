#include "Rigidbody2D.h"
#include <Framework/ColliderManager.h>
#include <Framework/TimeSystem.h>

using namespace TimeSystem;

Rigidbody2D::Rigidbody2D(GameObjectBase& gameObject)
	: ComponentBase(gameObject) 
{
    Velocity = Vector2();
    Gravity = Vector2{ 0.f, -300.f };
    currGravity = Vector2();
    currIsGravity = false;
}

Rigidbody2D::~Rigidbody2D()
{
	                           
}

void Rigidbody2D::AddForce(const Vector2& _force)
{
    force += _force;
}

void Rigidbody2D::Update()
{
    if (!isKinematic) 
    {
        AddGravity();
        acceleration = force / mass;
        Velocity += acceleration;
        gameObject.transform.position += Velocity * Time.GetDeltatime();
        force = Vector2(0, 0); 
    }
    //gameObject.transform.rotation += angularVelocity * Time.DeltaTime;
}

void Rigidbody2D::AddGravity()
{
    if (useGravity && !isKinematic && currIsGravity)
    {
        currGravity += Gravity * Time.GetDeltatime();
        force += Gravity * Time.GetDeltatime();
    }
    else
    {
        force -= currGravity;
        currGravity = Vector2();
    }
    currIsGravity = true;
}



