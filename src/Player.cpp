#include "Player.h"

Player::Player(std::string model_name, glm::vec3 position, glm::vec3 scale, glm::vec3 rotation) : GameObject(model_name, position, scale, rotation)
{
  left = false;
  right = false;
  speed = 0.0f;
  topSpeed = 5.0f;
  accelerate = false;
}

Player::~Player()
{
  //dtor
}

void Player::Update(float step)
{
  if (left && !right)
  {
    glm::vec3 rot = getRotation();
    rot.y += 0.4*step;
    setRotation(rot);
  }
  else if (right)
  {
    glm::vec3 rot = getRotation();
    rot.y -= 0.4*step;
    setRotation(rot);
  }

  if (accelerate)
  {
    if (speed < topSpeed)
      speed+=0.2*step;
  }
  else
  {
    if (speed > 0.0)
      speed-=0.2*step;
    else
      speed = 0.0f;
  }

  glm::vec3 pos = getPos() + Front()*speed;
  setPos(pos);
}

void Player::Turn(bool l, bool r)
{
  left = l;
  right = r;
}

void Player::SetPropulsion(bool p){
  accelerate = p;
}
