#include "Player.h"

Player::Player(std::string model_name, std::string inner_model_name, glm::vec3 position, glm::vec3 scale, glm::vec3 rotation) : GameObject(model_name, position, scale, rotation)
{
  left = false;
  right = false;
  up = false;
  down = false;
  speed = 5.0f;
  ModelName2 = inner_model_name;
  inside = false;
  bouncing = false;
}

Player::~Player()
{
  //dtor
}

void Player::Update(float step)
{
  glm::vec3 rot = getRotation();

  if (bouncing)
  {
    rot.x-=3*step;
    rot.z-=3*step;
    if (rot.x < -2*PI)
    {
      bouncing = false;
      collision_active = true;
      rot.x = 0;
      rot.z = 0;
    }
    setRotation(rot);
    return;
  }


  // roll
  if (left && !right)
  {
    rot.z-=0.8*step;
    if (rot.z < -PI/6)
      rot.z = -PI/6;
  }
  else if (right)
  {
    rot.z+=0.8*step;
    if (rot.z > PI/6)
      rot.z=PI/6;
  }
  else
  {
    if (rot.z>0.06f || rot.z<-0.06f)
    {
      if (rot.z > 0)
        rot.z-=0.8*step;
      else
        rot.z+=0.8*step;
    }
    else
      rot.z = 0.0f;
  }

  // pitch
  if (up && !down)
  {
    rot.x += 0.6*step;
    if (rot.x > PI/6)
      rot.x = PI/6;
  }
  else if (down)
  {
    rot.x -= 0.6*step;
    if (rot.x < -PI/6)
      rot.x = -PI/6;
  }
  else
  {
    if (rot.x>0.06f || rot.x<-0.06f)
    {
      if (rot.x > 0)
        rot.x-=0.8*step;
      else
        rot.x+=0.8*step;
    }
    else
      rot.x = 0.0f;
  }

  setRotation(rot);

  //movement
  glm::vec3 pos = getPos();
  if (rot.z < 0)
    pos.x += step*speed;
  else if (rot.z > 0)
    pos.x -= step*speed;
  if (rot.x < 0)
    pos.y += step*speed;
  else if (rot.x > 0)
    pos.y -= step*speed;
  setPos(pos);

  if (getCollider()!=nullptr)
  {
    getCollider()->setPos(pos);
  }
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

void Player::setObjectID(int spaceship, int cockpit)
{
  objectID = spaceship,
  cockpitID = cockpit;
}

int Player::getObjectID()
{
  if (inside)
    return cockpitID;
  else
    return objectID;
}

void Player::bounce()
{
  bouncing = true;
  collision_active = false;
}
