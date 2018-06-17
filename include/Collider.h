#ifndef COLLIDER_H
#define COLLIDER_H

#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>
#include <glm/vec3.hpp>
#include <math.h>
#include <glm/gtc/type_ptr.hpp>

// Collider interface
class Collider
{
  public:
    Collider(glm::vec3 position);
    virtual ~Collider();
    virtual bool Collide(Collider);
    glm::vec3 getPos();
    void setPos(glm::vec3);
  private:
    glm::vec3 pos;
};

class SphereCollider : public Collider
{
  public:
    SphereCollider(glm::vec3 position, float r);
    virtual ~SphereCollider();
    bool Collide(SphereCollider other);
    float getRadius();
  private:
    float radius;
};


#endif // COLLIDER_H
