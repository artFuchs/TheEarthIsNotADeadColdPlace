#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"


class Player : public GameObject
{
  public:
    Player(std::string model_name, glm::vec3 position, glm::vec3 scale, glm::vec3 rotation = glm::vec3(0.0f,0.0f,0.0f));
    virtual ~Player();
    void Update(float);
    void Turn(bool l, bool r);
    void SetPropulsion(bool p);

  private:
    bool right;
    bool left;
    bool accelerate;
    float topSpeed;
    float speed;
};

#endif // PLAYER_H
