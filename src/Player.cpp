#include "Player.h"

Player::Player(std::string model_name, std::string inner_model_name, glm::vec3 position, glm::vec3 scale, glm::vec3 rotation) : GameObject(model_name, position, scale, rotation)
{
  left = false;
  right = false;
  up = false;
  down = false;
  speed = 0.0f;
  topSpeed = 5.0f;
  accelerate = false;
  ModelName2 = inner_model_name;
  inside = false;
}

Player::~Player()
{
  //dtor
}

void Player::Update(float step)
{
  // yaw
  if (left && !right)
  {
    glm::vec3 rot = getRotation();
    rot.z-=0.8*step;
    if (rot.z < -PI/6)
      rot.z = -PI/6;
    setRotation(rot);
  }
  else if (right)
  {
    glm::vec3 rot = getRotation();
      rot.z+=0.8*step;
    if (rot.z > PI/6)
      rot.z=PI/6;
    setRotation(rot);
  }
  else
  {
    glm::vec3 rot = getRotation();
    if (rot.z>0.06f || rot.z<-0.06f)
    {
      if (rot.z > 0)
        rot.z-=0.8*step;
      else
        rot.z+=0.8*step;
    }
    else
      rot.z = 0.0f;
    setRotation(rot);
  }

  // pitch
  if (up && !down)
  {
    glm::vec3 rot = getRotation();
    rot.x += 0.6*step;
    if (rot.x > PI/6)
      rot.x = PI/6;
    setRotation(rot);
  }
  else if (down)
  {
    glm::vec3 rot = getRotation();
    rot.x -= 0.6*step;
    if (rot.x < -PI/6)
      rot.x = -PI/6;
    setRotation(rot);
  }
  else
  {
    glm::vec3 rot = getRotation();
    if (rot.x>0.06f || rot.x<-0.06f)
    {
      if (rot.x > 0)
        rot.x-=0.8*step;
      else
        rot.x+=0.8*step;
    }
    else
      rot.x = 0.0f;
    setRotation(rot);
  }

  if (accelerate)
  {
    speed+=0.2f*step;
    if (speed > topSpeed)
    {
      speed = topSpeed;
    }
  }

  glm::vec3 pos = getPos() + Front()*speed;
  setPos(pos);
}

void Player::SetTurn(bool l, bool r)
{
  left = l;
  right = r;
}

void Player::SetTurnPitch(bool u, bool d)
{
  up = u;
  down = d;
}

void Player::SetPropulsion(bool p){
  accelerate = p;
}

std::string Player::getModel()
{
  if (inside)
    return ModelName2;
  else
    return ModelName;

}

void Player::setView(bool inner)
{
  inside = inner;
}

bool Player::isViewingInside()
{
  return inside;
}
