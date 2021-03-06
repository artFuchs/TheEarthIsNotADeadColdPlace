#include "Obstacle.h"

Obstacle::Obstacle(std::string model_name, glm::vec3 position) : GameObject(model_name, position)
{
  speed = 0;
  setTextureMode(SPHERIC);
}

Obstacle::Obstacle(std::string model_name, glm::vec3 position, glm::vec3 scale, glm::vec3 rotation):
          GameObject(model_name, position, scale, rotation)
{
  speed = 0;
  setTextureMode(SPHERIC);
  setCollider(new SphereCollider(position,scale.x));
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
  rot.y += 0.01f;
  setRotation(rot);

}

void Obstacle::setSpeed(float s)
{
  speed = s;
}


// CowObstacle

CowObstacle::CowObstacle(std::string model_name, glm::vec3 position, bool right, float ceil, float floor) : Obstacle(model_name, position)
{
  speed = 0;
  this->right = right;
  this->ceil = ceil;
  this->floor = floor;
  if (right)
  {
    glm::vec3 rot = getRotation();
    rot.y = PI;
    setRotation(rot);
  }
  setTextureMode(PLANARXY);
  setCollider(new SphereCollider(getPos(), 1));
}

CowObstacle::~CowObstacle()
{
  //dtor
}

void CowObstacle::Update(float step)
{
  glm::vec3 foward(0.0f, 0.0f, -1.0f);

  foward = speed*foward;

  if (right)
    foward.x = -5;
  else
    foward.x = 5;

  if (up)
    foward.y = 5;
  else
    foward.y = -5;

  glm::vec3 pos = getPos();
  pos += step*foward;
  setPos(pos);

  if (pos.x < -7)
  {
    right = false;
    glm::vec3 rot = getRotation();
    rot.y = 0;
    setRotation(rot);
  }else if (pos.x > 7)
  {
    right = true;
    glm::vec3 rot = getRotation();
    rot.y = PI;
    setRotation(rot);
  }

  if (pos.y >= ceil)
    up = false;

  if (pos.y <= floor)
    up = true;

  if (getCollider()!=nullptr)
    getCollider()->setPos(pos);
}



