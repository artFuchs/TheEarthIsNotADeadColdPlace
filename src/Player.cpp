#include "Player.h"

Player::Player(std::string model_name, glm::vec3 position, glm::vec3 scale, glm::vec3 rotation) : GameObject(model_name, position, scale, rotation)
{
  left = false;
  right = false;
  up = false;
  down = false;
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
  //
  if (left && !right)
  {
    glm::vec3 rot = getRotation();
    rot.y += 0.6*step;
    setRotation(rot);
  }
  else if (right)
  {
    glm::vec3 rot = getRotation();
    rot.y -= 0.6*step;
    setRotation(rot);
  }

  // pitch
  if (up && !down)
  {
    glm::vec3 rot = getRotation();
    rot.x += 0.6*step;
    setRotation(rot);
  }
  else if (down)
  {
    glm::vec3 rot = getRotation();
    rot.x -= 0.6*step;
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
      speed-=0.05*step;
    else
      speed = 0.0f;
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
