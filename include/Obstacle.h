#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "GameObject.h"

class Obstacle : public GameObject
{
  public:
    Obstacle(std::string model_name, glm::vec3 position);
    Obstacle(std::string model_name, glm::vec3 position, glm::vec3 scale, glm::vec3 rotation = glm::vec3(0.0f,0.0f,0.0f));
    virtual ~Obstacle();
    virtual void Update(float);
    void setSpeed(float);
  protected:
    float speed;
};

class CowObstacle : public Obstacle
{
  public:
    CowObstacle(std::string model_name, glm::vec3 position, bool right, float ceil, float floor);
    virtual ~CowObstacle();
    void Update(float);
  private:
    bool right;
    bool up;
    float ceil;
    float floor;
};

#endif // OBSTACLE_H
