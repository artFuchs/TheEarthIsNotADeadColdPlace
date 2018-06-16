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
  {
    glm::vec4 thisPos = glm::vec4(relative_pos.x,relative_pos.y,relative_pos.z,1.0f);
    glm::vec3 AnchorPos = anchor->getPos();
    glm::vec3 Angles = anchor->getRotation();
    glm::vec4 new_position = Matrix_Translate(AnchorPos.x, AnchorPos.y, AnchorPos.z)
                       * Matrix_Rotate_Z(Angles.z)
                       * Matrix_Rotate_Y(Angles.y)
                       * Matrix_Rotate_X(Angles.x)
                       * thisPos;
    pos = glm::vec3(new_position.x,new_position.y,new_position.z);
  }
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

  glm::vec4 view(x,-y,z,0.0f);

  // se a camera estiver ancorada em um objeto, o vetor view deve ser rotacionado.
  if (anchor!=nullptr)
  {
    glm::vec3 Angles = anchor->getRotation();
    view = Matrix_Rotate_Z(Angles.z)
         * Matrix_Rotate_Y(Angles.y)
         * Matrix_Rotate_X(Angles.x)
         * view;
  }
  return view;
}

glm::vec4 Camera::Up()
{
  glm::vec4 up(0.0f,1.0f,0.0f,0.0f);
  // se a camera estiver ancorada em um objeto, o vetor view deve ser rotacionado.
  if (anchor!=nullptr)
  {
    glm::vec3 Angles = anchor->getRotation();
    up = Matrix_Rotate_Z(Angles.z)
         * Matrix_Rotate_Y(Angles.y)
         * Matrix_Rotate_X(Angles.x)
         * up;
  }
  return up;
}




CameraLookAt::CameraLookAt(float phi,float theta, float distance, glm::vec3 position, GameObject *attachment)
              : Camera (phi,theta,position,attachment)
{
  dist =  distance;
}

void CameraLookAt::Update()
{


  float phi = GetPhi();
  float theta = GetTheta();
  float y = dist*sin(phi);
  float z = dist*cos(phi)*cos(theta);
  float x = dist*cos(phi)*sin(theta);

  pos = glm::vec3(x,y,z);

  if (anchor!=nullptr)
  {
    look = anchor->getPos();
    glm::vec3 rot = anchor->getRotation();

    glm::mat4 t = Matrix_Identity();
    t = Matrix_Rotate_Z(rot.z)
      * Matrix_Rotate_Y(rot.y)
      * Matrix_Rotate_X(rot.x);

    glm::vec4 pos4 = t * glm::vec4(pos.x, pos.y, pos.z, 1.0f);
    pos = glm::vec3(-pos4.x, pos4.y, pos.z);
  }

  pos += look;
}

void CameraLookAt::ChangePos(glm::vec3 position)
{
  // se a camera estiver ancorada em um objeto, essa função não deve fazer nada
  if (anchor!=nullptr)
    return;
  look = position; // camera passa a olhar para position
}


glm::vec4 CameraLookAt::View()
{
  glm::vec4 camPos(pos.x, pos.y, pos.z, 1);
  glm::vec4 lookAt(look.x, look.y, look.z, 1);
  return lookAt - camPos;
}

void CameraLookAt::SetDist(float dist){
  const float verysmallnumber = std::numeric_limits<float>::epsilon();
  if (dist < verysmallnumber)
    dist = verysmallnumber;
  this->dist = dist;
}
float CameraLookAt::GetDist(){ return dist; }

glm::vec4 CameraLookAt::Up()
{
  return glm::vec4(0,1,0,0);
}


