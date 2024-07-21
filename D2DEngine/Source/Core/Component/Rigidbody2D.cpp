#include "Rigidbody2D.h"
#include <Framework/ColliderManager.h>
#include <Framework/TimeSystem.h>

using namespace TimeSystem;

Rigidbody2D::Rigidbody2D(GameObjectBase& gameObject)
	: ComponentBase(gameObject) ,
    ICollider2DNotify(this)
{
    Velocity = Vector2();
    Gravity = Vector2{ 0.f, -2000.f };
    currIsGravity = true;
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
        force += Gravity * Time.GetDeltatime();
    }
}

void Rigidbody2D::OnCollisionEnter2D(GameObjectBase* collision)
{
    currIsGravity = false;
    Velocity = Vector2(0, 0);
}

void Rigidbody2D::OnCollisionExit2D(GameObjectBase* collision)
{
    currIsGravity = true;

}

void Rigidbody2D::OnCollisionStay2D(GameObjectBase* collision)
{
   

}