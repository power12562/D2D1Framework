#include "Rigidbody2D.h"
#include <Framework/TimeSystem.h>

std::list<Rigidbody2D*> Rigidbody2D::rigidbodyList;

Rigidbody2D::Rigidbody2D(GameObjectBase& gameObject)
	: ComponentBase(gameObject) 
{
	rigidbodyList.push_back(this);
	myIter = std::prev(rigidbodyList.end());
}

Rigidbody2D::~Rigidbody2D()
{
	rigidbodyList.erase(myIter);                            
}

void Rigidbody2D::AddForce(const Vector2& _force)
{
    force += _force;
}

void Rigidbody2D::Update()
{
    using namespace TimeSystem;
    if (!isKinematic) 
    {
        if (useGravity) 
        {
            force += Gravity;
        }
        acceleration = force / mass;
        Velocity += acceleration;
        gameObject.transform.position += Velocity * Time.GetDeltatime();

        force = Vector2(0, 0); 
    }
    //gameObject.transform.rotation += angularVelocity * Time.DeltaTime;
}



