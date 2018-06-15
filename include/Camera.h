#ifndef CAMERA_H
#define CAMERA_H

#include "GameObject.h"

// Uma camera fixada em um ponto, que pode ser relativo a um objeto
class Camera
{
  public:
    Camera(float phi,float theta, glm::vec3 position = glm::vec3(0,0,0), GameObject *attachment = nullptr);
    virtual ~Camera();
    virtual void Update();
    float GetPhi();
    float GetTheta();
    glm::vec3 GetPos();
    bool IsActive();
    virtual void ChangeAngles(float Phi, float Theta);
    virtual void ChangePos(glm::vec3);
    void SetActive(bool);
    virtual glm::vec4 View();
    virtual glm::vec4 Up();
  private:
    bool active;
    GameObject *anchor;
    float phi;
    float theta;
    glm::vec3 pos;
    glm::vec3 relative_pos;
};

class CameraLookAt : public Camera
{
  public:
    CameraLookAt(float phi, float theta, float distance, glm::vec3 position = glm::vec3(0,0,0), GameObject *attachment = nullptr);

  private:
    float dist;
};

#endif // CAMERA_H
