#include "Obstacle.h"

Obstacle::Obstacle(std::string model_name, glm::vec3 position, float speed) : GameObject(model_name, position)
{
  this->speed = speed;
}

Obstacle::Obstacle(std::string model_name, glm::vec3 position, float speed, glm::vec3 scale, glm::vec3 rotation):
          GameObject(model_name, position, scale, rotation)
{
  this->speed = speed;
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
}
