#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <string>

// Headers das bibliotecas OpenGL
//#include <glad/glad.h>   // Criação de contexto OpenGL 3.3

// Headers da biblioteca GLM: criação de matrizes e vetores.
#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "utils.h"
#include "matrices.h"


// Definimos uma estrutura que armazenará dados necessários para renderizar
// cada objeto da cena virtual.
struct SceneObject
{
    std::string  name;        // Nome do objeto
    void*        first_index; // Índice do primeiro vértice dentro do vetor indices[] definido em BuildTrianglesAndAddToVirtualScene()
    int          num_indices; // Número de índices do objeto dentro do vetor indices[] definido em BuildTrianglesAndAddToVirtualScene()
    GLenum       rendering_mode; // Modo de rasterização (GL_TRIANGLES, GL_TRIANGLE_STRIP, etc.)
    GLuint       vertex_array_object_id; // ID do VAO onde estão armazenados os atributos do modelo
    glm::vec3    bbox_min; // Axis-Aligned Bounding Box do objeto
    glm::vec3    bbox_max;
};

#define SPHERIC 0
#define PLANARXY 1
#define TEXCOORDS 2

#define PI 3.141592f

class GameObject
{
  public:
    //main functions
    GameObject(std::string model_name, glm::vec3 position);
    GameObject(std::string model_name, glm::vec3 position, glm::vec3 scale, glm::vec3 rotation = glm::vec3(0.0f,0.0f,0.0f));
    virtual void Update(float);
    virtual ~GameObject();
    // gets
    virtual std::string getModel();
    bool isActive();
    glm::vec3 getPos();
    glm::vec3 getScale();
    glm::vec3 getRotation();
    // sets
    void setActive(bool);
    void setPos(glm::vec3);
    void setScale(glm::vec3);
    void setRotation(glm::vec3);
    void setTextureMode(int);
    void setObjectID(int);
    // direction Properties
    glm::vec3 Front();
    glm::vec3 Right();
    glm::vec3 Up();
    int getTextureMode();
    virtual int getObjectID();
  protected:
    bool active;
    std::string ModelName;
    int objectID;
  private:
    int textureMode;
    glm::vec3 pos;
    glm::vec3 scale;
    glm::vec3 rotation;
};

#endif // GAMEOBJECT_H
