#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"


class Player : public GameObject
{
  public:
    Player(std::string model_name, std::string inner_model_name, glm::vec3 position, glm::vec3 scale, glm::vec3 rotation = glm::vec3(0.0f,0.0f,0.0f));
    virtual ~Player();
    void Update(float);
    void SetTurn(bool l, bool r);
    void SetTurnPitch(bool u, bool d);
    void SetPropulsion(bool p);
    std::string getModel();
    void setView(bool);
    bool isViewingInside();
    void setObjectID(int,int);
    int getObjectID();
    void bounce();
  private:
    bool right, left;
    bool up, down;
    bool accelerate;
    bool inside;
    bool bouncing;
    float speed;
    std::string ModelName2;
    int cockpitID;

};

#endif // PLAYER_H
