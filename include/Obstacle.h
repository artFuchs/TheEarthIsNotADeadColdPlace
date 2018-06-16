#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "GameObject.h"

class Obstacle : public GameObject
{
  public:
    Obstacle(std::string model_name, glm::vec3 position, float speed);
    Obstacle(std::string model_name, glm::vec3 position, float speed, glm::vec3 scale, glm::vec3 rotation = glm::vec3(0.0f,0.0f,0.0f));
    virtual ~Obstacle();
    void Update(float);
  protected:

  private:
    float speed;
};

#endif // OBSTACLE_H
