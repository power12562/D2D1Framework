#include "Rigidbody2D.h"
#include <Framework/ColliderManager.h>
#include <Framework/TimeSystem.h>
#include <Utility/Debug.h>

#include <Math/Mathf.h>

using namespace TimeSystem;

Rigidbody2D::Rigidbody2D(GameObjectBase& gameObject)
	: ComponentBase(gameObject) ,
    ICollider2DNotify(this)
{
    currIsGravity = false;
    Velocity = Vector2();
    Gravity = Vector2{ 0.f, -2000.f };
    Drag = 700.f;
}

Rigidbody2D::~Rigidbody2D()
{
	                           
}

void Rigidbody2D::AddForce(const Vector2& _force)
{
    force += _force;
}

void Rigidbody2D::Start()
{
    currIsGravity = false;
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
        currIsGravity = true;
    }
    //gameObject.transform.rotation += angularVelocity * Time.DeltaTime;
}                          

void Rigidbody2D::AddGravity()
{
    if (enabled && useGravity && !isKinematic && currIsGravity)
    {
        force += Gravity * Time.GetDeltatime();
    }
}

void Rigidbody2D::OnCollisionEnter2D(ColliderBase* myCollider, ColliderBase* otherCollider)
{
    if (!enabled || isKinematic)
        return;

    disRL = abs(myCollider->GetRight() - otherCollider->GetLeft());
    disLR = abs(myCollider->GetLeft() - otherCollider->GetRight());
    disTB = abs(myCollider->GetTop() - otherCollider->GetBottom());
    disBT = abs(myCollider->GetBottom() - otherCollider->GetTop());

    float min = Mathf::FindMinValue(disRL, disLR, disTB, disBT);
    if (min == disBT)
    {
        transform.position = Vector2(transform.position.x, otherCollider->GetTop() + (myCollider->GetTop() - myCollider->GetBottom()) * 0.5f - myCollider->Center.y);
        currIsGravity = false;  
    }
    else if (min == disTB)
    {
        Velocity = Vector2(Velocity.x, 0);
        transform.position = Vector2(transform.position.x, otherCollider->GetBottom() - (myCollider->GetTop() - myCollider->GetBottom()) * 0.5f + myCollider->Center.y);
    }
    else if (min == disRL)
    {
        transform.position = Vector2(otherCollider->GetLeft() - (myCollider->GetRight() - myCollider->GetLeft()) * 0.5f + myCollider->Center.x, transform.position.y);
     
    }
    else if (min == disLR)
    {
        transform.position = Vector2(otherCollider->GetRight() + (myCollider->GetRight() - myCollider->GetLeft()) * 0.5f - myCollider->Center.x, transform.position.y) ;     
    }
}

void Rigidbody2D::OnCollisionStay2D(ColliderBase* myCollider, ColliderBase* otherCollider)
{
    if (!enabled || isKinematic)
        return;

    disRL = abs(myCollider->GetRight() - otherCollider->GetLeft());
    disLR = abs(myCollider->GetLeft() - otherCollider->GetRight());
    disTB = abs(myCollider->GetTop() - otherCollider->GetBottom());
    disBT = abs(myCollider->GetBottom() - otherCollider->GetTop());

    float min = Mathf::FindMinValue(disRL, disLR, disTB, disBT);
    if (min == disBT)
    {
        currIsGravity = false;     
        if (Velocity.y <= 0)
        {
            Velocity.y = 0;
            transform.position = Vector2(transform.position.x, otherCollider->GetTop() + (myCollider->GetTop() - myCollider->GetBottom()) * 0.5f - myCollider->Center.y);
        } 
        if (Velocity.x != 0)
        {
            float deltaDrag = Drag * Time.GetDeltatime();
            Velocity.x += ((Velocity.x > 0) ? -1 : 1) * deltaDrag;
            if (abs(Velocity.x) <= deltaDrag)
            {
                Velocity.x = 0;
            }
        }
    }
    else if (min == disTB)
    {
        
    }
    else if (min == disRL)
    {               
        if (Velocity.x >= 0)
        {
            transform.position = Vector2(otherCollider->GetLeft() - (myCollider->GetRight() - myCollider->GetLeft()) * 0.5f + myCollider->Center.x, transform.position.y);
        }
    }
    else if (min == disLR)
    {
        if (Velocity.x <= 0)
        {
            transform.position = Vector2(otherCollider->GetRight() + (myCollider->GetRight() - myCollider->GetLeft()) * 0.5f - myCollider->Center.x, transform.position.y);
        }   
    }

}

void Rigidbody2D::OnCollisionExit2D(ColliderBase* myCollider, ColliderBase* otherCollider)
{
    

}
