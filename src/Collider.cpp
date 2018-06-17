#include "Collider.h"

float distance(glm::vec3 a, glm::vec3 b)
{
  float x2 = (b.x-a.x)*(b.x-a.x);
  float y2 = (b.y-a.y)*(b.y-a.y);
  float z2 = (b.z-a.z)*(b.z-a.z);
  return sqrt(x2+y2+z2);
}


// Interface Collider

Collider::Collider(glm::vec3 position){ pos = position; }

Collider::~Collider(){ }

glm::vec3 Collider::getPos() { return pos; }

void Collider::setPos(glm::vec3 position) { pos = position; }

bool Collider::Collide(Collider other) { return (other.getPos() == getPos());}


// Sphere Collider

SphereCollider::SphereCollider(glm::vec3 pos, float r) : Collider(pos)
{
  radius = r;
}

SphereCollider::~SphereCollider(){}

float SphereCollider::getRadius() { return radius; }

bool SphereCollider::Collide(SphereCollider other)
{
  float d = distance(getPos(),other.getPos());
  if (d < radius + other.getRadius())
    return true;
}
