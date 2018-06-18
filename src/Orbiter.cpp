#include "Orbiter.h"

Orbiter::Orbiter(std::string model_name, glm::vec3 position, glm::vec3 axis, GameObject *anchor) : GameObject(model_name, position)
{
  this->axis = axis/norm(glm::vec4(axis,0));
  this->anchor = anchor;
}

Orbiter::~Orbiter()
{
  //dtor
}

void Orbiter::Update(float step)
{
  if (anchor == nullptr) return;
  glm::vec3 aPos = anchor->getPos();

  glm::vec4 pos(getPos(),1); // leva para origem
  pos = Matrix_Translate(aPos.x, aPos.y, aPos.z)
      *Matrix_Rotate(step*0.1,glm::vec4(axis,0))
      *Matrix_Translate(-aPos.x, -aPos.y, -aPos.z)
      *pos;
  setPos(glm::vec3(pos.x, pos.y, pos.z));

  glm::vec3 rot = getRotation();
  rot.y-= step*0.1;
  setRotation(rot);
}
