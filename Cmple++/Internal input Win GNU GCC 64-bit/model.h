#ifndef MODEL_H_INCLUDED
#define MODEL_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "GL\glm\ext.hpp"
#include "GL\glad.h"
#include "GL\glfw3.h"
#include "stb_image.h"
#include "shader.h"

class Model {
public:
    void Load(std::string path);

    void Draw(float posX, float posY, float posZ,
        float rotateAngle, float rotateX, float rotateY, float rotateZ,
        float scaleX, float scaleY, float scaleZ,
        Shader shader, glm::mat4 model);

private:
    struct Face {
        std::vector <int> v;
        std::vector <int> vt;
        std::vector <int> vn;
    };

    struct Material {
        float Ns;
        float Ni;
        float d;
        float illum;
        float Kd[3];
        float Ka[3];
        float Ks[3];
        float Ke[3];
        unsigned int map_Kd;
        unsigned int map_Ka;
        unsigned int map_Disp;
        unsigned int map_d;
    };

    struct Mesh {
        std::vector <Face> faces;
        unsigned int material, vao;
    };

    bool loaded = false;
    unsigned int defaultTexture;
    std::string pathFolder;
    std::string pathObj;
    std::string pathMtl;
    std::vector < std::vector <float> > vertices;
    std::vector < std::vector <float> > verticesTexture;
    std::vector < std::vector <float> > verticesNormal;
    std::vector <Mesh> meshes;
    std::vector <Material> materials;
    std::map <std::string, int> material_name;

    unsigned int LoadTexture(std::string path);
    void initDefaultTexture();
    Face processFace(std::string v0, std::string v1, std::string v2);
    void initPaths(std::string path);
    void LoadMtl();
    void LoadObj();
    void initVAO();
};

#endif // MODEL_H_INCLUDED
