#include "Obstacle.h"

Obstacle::Obstacle(std::string model_name, glm::vec3 position) : GameObject(model_name, position)
{
  speed = 0;
}

Obstacle::Obstacle(std::string model_name, glm::vec3 position, glm::vec3 scale, glm::vec3 rotation):
          GameObject(model_name, position, scale, rotation)
{
  speed = 0;
}

Obstacle::~Obstacle()
{
  //dtor
}

void Obstacle::Update(float step)
{
  glm::vec3 foward(0.0f, 0.0f, -1.0f);
  glm::vec3 pos = getPos();
  pos += speed*step*foward;
  setPos(pos);

  if (getCollider()!=nullptr)
    getCollider()->setPos(pos);

  glm::vec3 rot= getRotation();
  rot.y += 0.1f;
  setRotation(rot);
}

void Obstacle::setSpeed(float s)
{
  speed = s;
}
