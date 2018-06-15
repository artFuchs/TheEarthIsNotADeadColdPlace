#include "Camera.h"

Camera::Camera(float Phi, float Theta, glm::vec3 position, GameObject *attachment)
{
  //ctor
  phi = Phi;
  theta = Theta;
  anchor = attachment;
  relative_pos = position;
  pos = position;
  if (anchor != nullptr)
    pos += anchor->getPos();
  active = false;
}

Camera::~Camera()
{
  //dtor
}

void Camera::Update()
{
  // a câmera é fixa em um ponto.
  // mas se ela estiver ancorada em um objeto, deve ser transformada junto
  if (anchor != nullptr)
  {
    glm::vec4 thisPos = glm::vec4(relative_pos.x,relative_pos.y,relative_pos.z,1.0f);
    glm::vec3 AnchorPos = anchor->getPos();
    glm::vec3 Angles = anchor->getRotation();
    glm::vec4 position = Matrix_Translate(AnchorPos.x, AnchorPos.y, AnchorPos.z)
                       * Matrix_Rotate_Z(Angles.z)
                       * Matrix_Rotate_Y(Angles.y)
                       * Matrix_Rotate_X(Angles.x)
                       * thisPos;
    pos = glm::vec3(position.x,position.y,position.z);
  }
}

float Camera::GetPhi() { return phi; }
float Camera::GetTheta() { return theta; }
glm::vec3 Camera::GetPos() { return pos; }
bool Camera::IsActive() { return active; }

void Camera::ChangeAngles(float Phi, float Theta)
{
  phi = Phi;
  theta = Theta;
}

void Camera::ChangePos(glm::vec3 position)
{
  relative_pos = position;
  pos = position;
  if (anchor != nullptr)
    pos += anchor->getPos();
}

void Camera::SetActive(bool v)
{
  active = v;
}

glm::vec4 Camera::View()
{
  float y = sin(phi);
  float z = cos(phi)*cos(theta);
  float x = cos(phi)*sin(theta);

  glm::vec4 view(-x,-y,-z,0.0f);

  return view;
}

glm::vec4 Camera::Up()
{
  return glm::vec4(0.0f,1.0f,0.0f,0.0f);
}



CameraLookAt::CameraLookAt(float phi,float theta, float distance, glm::vec3 position, GameObject *attachment)
              : Camera (phi,theta,position,attachment)
{
  dist =  distance;
}

