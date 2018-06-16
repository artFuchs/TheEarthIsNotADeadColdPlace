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
    void ChangeAngles(float Phi, float Theta);
    virtual void ChangePos(glm::vec3);
    void SetActive(bool);
    virtual glm::vec4 View();
    virtual glm::vec4 Up();
  protected:
    glm::vec3 pos;
    GameObject *anchor;
  private:
    bool active;
    glm::vec3 relative_pos;
    float phi;
    float theta;
};


// Camera Loot-At: rotaciona ao redor de um ponto.
class CameraLookAt : public Camera
{
  public:
    CameraLookAt(float phi, float theta, float distance, glm::vec3 position = glm::vec3(0,0,0), GameObject *attachment = nullptr);
    void Update();
    void ChangePos(glm::vec3); // muda o ponto para o qual a câmera olha;
    glm::vec4 View();
    void SetDist(float dist);
    float GetDist();
    glm::vec4 Up();
  private:
    float dist;
    glm::vec3 look;
};

#endif // CAMERA_H
