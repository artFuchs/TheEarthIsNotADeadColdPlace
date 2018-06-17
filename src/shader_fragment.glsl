#version 330 core

// Atributos de fragmentos recebidos como entrada ("in") pelo Fragment Shader.
// Neste exemplo, este atributo foi gerado pelo rasterizador como a
// interpolação da cor de cada vértice, definidas em "shader_vertex.glsl" e
// "main.cpp".
in vec4 position_world;
in vec4 normal;

// Posição do vértice atual no sistema de coordenadas local do modelo.
in vec4 position_model;

// Coordenadas de textura obtidas do arquivo OBJ (se existirem!)
in vec2 texcoords;

// Matrizes computadas no código C++ e enviadas para a GPU
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

// Identificador que define qual objeto está sendo desenhado no momento
#define SPHERIC 0
#define PLANARXY  1
#define TEXCOORDS  2
uniform int texture_mode;

#define SPACESHIP 0
#define COCKPIT 1
#define EARTH 2
#define EVIL 3
#define SKY 4
#define COW 5
#define MOON 6
uniform int object_id;

// Parâmetros da axis-aligned bounding box (AABB) do modelo
uniform vec4 bbox_min;
uniform vec4 bbox_max;

// Variáveis para acesso das imagens de textura
uniform sampler2D TextureSpaceShip; // textura da nave do jogador
uniform sampler2D TextureCockpit; // textura da cockpit da nave do jogador
uniform sampler2D TextureEarth; // textura da terra de dia
uniform sampler2D TextureEvil;
uniform sampler2D TextureSky;
uniform sampler2D TextureCow;
uniform sampler2D TextureMoon;
uniform sampler2D TextureSpaceShipSpec;

// O valor de saída ("out") de um Fragment Shader é a cor final do fragmento.
out vec3 color;

// Constantes
#define M_PI   3.14159265358979323846
#define M_PI_2 1.57079632679489661923

void main()
{
    // Obtemos a posição da câmera utilizando a inversa da matriz que define o
    // sistema de coordenadas da câmera.
    vec4 origin = vec4(0.0, 0.0, 0.0, 1.0);
    vec4 camera_position = inverse(view) * origin;

    // O fragmento atual é coberto por um ponto que percente à superfície de um
    // dos objetos virtuais da cena. Este ponto, p, possui uma posição no
    // sistema de coordenadas global (World coordinates). Esta posição é obtida
    // através da interpolação, feita pelo rasterizador, da posição de cada
    // vértice.
    vec4 p = position_world;

    // Normal do fragmento atual, interpolada pelo rasterizador a partir das
    // normais de cada vértice.
    vec4 n = normalize(normal);

    // Vetor que define o sentido da fonte de luz em relação ao ponto atual.
    vec4 l = normalize(vec4(1.0,1.0,0.0,0.0));

    // Vetor que define o sentido da câmera em relação ao ponto atual.
    vec4 v = normalize(camera_position - p);
    // Vetor que define o sentido da reflexão especular ideal.
    vec4 r = -l + 2 * n * dot(n,l); // PREENCHA AQUI o vetor de reflexão especular ideal

    // Coordenadas de textura U e V
    float U = 0.0;
    float V = 0.0;

    if ( texture_mode == SPHERIC )
    {
        vec4 bbox_center = (bbox_min + bbox_max) / 2.0;
        vec4 pvector = position_model - bbox_center;

        float ro = length(pvector);
        float theta = atan(position_model.x,position_model.z);
        float phi = asin(position_model.y/ro);

        U = (theta + M_PI)/(2*M_PI);
        V = (phi + M_PI_2)/M_PI;
    }
    else if ( texture_mode == PLANARXY )
    {
        float minx = bbox_min.x;
        float maxx = bbox_max.x;

        float miny = bbox_min.y;
        float maxy = bbox_max.y;

        float minz = bbox_min.z;
        float maxz = bbox_max.z;

        U = (position_model.x-minx)/(maxx - minx);
        V = (position_model.y-miny)/(maxy - miny);
    }
    else if ( texture_mode == TEXCOORDS )
    {
        // Coordenadas de textura do plano, obtidas do arquivo OBJ.
        U = texcoords.x;
        V = texcoords.y;
    }

    // Obtemos a refletância difusa a partir da leitura das imagens
    vec3 KdShip = texture(TextureSpaceShip, vec2(U,V)).rgb;
    vec3 KdCabin = texture(TextureCockpit, vec2(U,V)).rgb;
    vec3 KdEarth = texture(TextureEarth, vec2(U,V)).rgb;
    vec3 KdEvil = texture(TextureEvil, vec2(U,V)).rgb;
    vec3 KdSky= texture(TextureSky, vec2(U,V)).rgb;
    vec3 KdCow = texture(TextureCow, vec2(U,V)).rgb;
    vec3 KdMoon = texture(TextureMoon, vec2(U,V)).rgb;

    // Equação de Iluminação difusa
    vec3 I = vec3(1.0,1.0,1.0);
    vec3 lambert = I* max(0,dot(n,l));
    vec3 ambient = vec3(0.09, 0.62, 0.75) * vec3(0.02,0.02,0.02);
    vec3 Ks;
    float q = 20.0; // Expoente especular para o modelo de iluminação de Phong
    vec3 phong =  I * pow(max(0, dot(r,v)), q);


    if (object_id == SPACESHIP)
    {
        Ks = texture(TextureSpaceShipSpec, vec2(U,V)).rgb;
        color = KdShip*lambert + ambient + Ks*phong;
        //color = ambient + KdShip * (lambert + 0.01);
    }
    else if (object_id == COCKPIT)
    {
        color = KdCabin;
    }
    else if (object_id == EARTH)
    {
        color =  KdEarth*(lambert + 0.01) + 0.5f*KdEvil;
    }
    else if (object_id == SKY)
    {
        color = KdSky;
    }
    else if (object_id == COW)
    {
        color = ambient + KdCow * (lambert + 0.01);
    }
    else if (object_id == MOON)
    {
        color = ambient + KdMoon * (lambert + 0.01);
    }
    else
    {
        color = vec3(0.6,0.6,0.6)*(lambert + 0.01);
    }



    // Cor final com correção gamma, considerando monitor sRGB.
    // Veja https://en.wikipedia.org/w/index.php?title=Gamma_correction&oldid=751281772#Windows.2C_Mac.2C_sRGB_and_TV.2Fvideo_standard_gammas
    color = pow(color, vec3(1.0,1.0,1.0)/2.2);
}
