#include "GameObject.h"

GameObject::GameObject(std::string model_name, glm::vec3 position){
  ModelName = model_name;
  pos = position;
  scale = glm::vec3(1.0,1.0,1.0);
  rotation = glm::vec3(0.0,0.0,0.0);
}

GameObject::GameObject(std::string model_name, glm::vec3 position, glm::vec3 scale, glm::vec3 rotation){
  ModelName = model_name;
  pos = position;
  this->scale = scale;
  this->rotation = rotation;
}

GameObject::~GameObject()
{
  //dtor
}

void GameObject::Update(float step){}

std::string GameObject::getModel(){
  return ModelName;
}

bool GameObject::isActive(){  return active; }

glm::vec3 GameObject::getPos(){  return pos; }

glm::vec3 GameObject::getScale(){  return scale; }

glm::vec3 GameObject::getRotation(){  return rotation; }

void GameObject::setActive(bool value){  active = value; }

void GameObject::setPos(glm::vec3 position){  pos = position; }

void GameObject::setScale(glm::vec3 scale){  this->scale = scale; }

void GameObject::setRotation(glm::vec3 rotation){  this->rotation = rotation; }

glm::vec3 GameObject::Front(){
  glm::vec4 vecfront = glm::vec4(0.0,0.0,1.0,0);
  glm::mat4 rot = Matrix_Rotate_Z(rotation.z)
                * Matrix_Rotate_Y(rotation.y)
                * Matrix_Rotate_X(rotation.x);
  vecfront = rot * vecfront;
  norm(vecfront);
  return glm::vec3(vecfront.x,vecfront.y,vecfront.z);
}

glm::vec3 GameObject::Right(){
  glm::vec4 vecright = glm::vec4(-1.0,0.0,0.0,0);
  glm::mat4 rot = Matrix_Rotate_Z(rotation.z)
                * Matrix_Rotate_Y(rotation.y)
                * Matrix_Rotate_X(rotation.x);
  vecright = rot * vecright;
  norm(vecright);
  return glm::vec3(vecright.x,vecright.y,vecright.z);
}

glm::vec3 GameObject::Up(){
  glm::vec4 vecup = glm::vec4(0.0,1.0,0.0,0);
  glm::mat4 rot = Matrix_Rotate_Z(rotation.z)
                * Matrix_Rotate_Y(rotation.y)
                * Matrix_Rotate_X(rotation.x);
  vecup = rot * vecup;
  norm(vecup);
  return glm::vec3(vecup.x,vecup.y,vecup.z);
}




