#include "GameObject.h"

GameObject::GameObject(std::string model_name, glm::vec3 position){
  ModelName = model_name;
  pos = pos;
  scale = glm::vec3(1.0,1.0,1.0);
  rotation = glm::vec3(0.0,0.0,0.0);
}

GameObject::GameObject(std::string model_name, glm::vec3 position, glm::vec3 scale, glm::vec3 rotation)
{
  ModelName = model_name;
  pos = pos;
  this->scale = scale;
  this->rotation = rotation;
}

GameObject::~GameObject()
{
  //dtor
}

std::string GameObject::getModel()
{
  return ModelName;
}

glm::vec3 GameObject::getPos()
{
  return pos;
}

glm::vec3 GameObject::getScale()
{
  return scale;
}

glm::vec3 GameObject::getRotation()
{
  return rotation;
}

void GameObject::setPos(glm::vec3 position)
{
  pos = position;
}

void GameObject::setScale(glm::vec3 scale)
{
  this->scale = scale;
}

void GameObject::setRotation(glm::vec3 rotation)
{
  this->rotation = rotation;
}






