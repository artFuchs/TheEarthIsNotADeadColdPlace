#ifndef ORBITER_H
#define ORBITER_H

#include "GameObject.h"

class Orbiter : public GameObject
{
  public:
    Orbiter(std::string model_name, glm::vec3 position, glm::vec3 axis, GameObject *anchor);
    virtual ~Orbiter();
    void Update(float);
  protected:
  private:
    glm::vec3 axis;
    GameObject *anchor;
};

#endif // ORBITER_H
