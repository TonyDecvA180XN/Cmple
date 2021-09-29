#ifndef SHADER_H_INCLUDED
#define SHADER_H_INCLUDED

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include "GL\glm\ext.hpp"
#include "GL\glad.h"
#include "GL\glfw3.h"

class Shader{
public:
    unsigned int ID;

    void init(const char* vertexPath, const char* fragmentPath);

    void use();

    void setBool(const std::string &name,bool value) const;
    void setInt(const std::string &name,int value) const;
    void setFloat(const std::string &name,float value) const;
    void setVec2(const std::string &name, const glm::vec2& value) const;
    void setVec2(const std::string &name,float x,float y) const;
    void setVec3(const std::string &name,const glm::vec3 &value) const;
    void setVec3(const std::string &name,float x,float y,float z) const;
    void setVec4(const std::string &name,const glm::vec4 &value) const;
    void setVec4(const std::string &name,float x,float y,float z,float w) const;
    void setMat2(const std::string &name,const glm::mat2 &mat) const;
    void setMat3(const std::string &name,const glm::mat3 &mat) const;
    void setMat4(const std::string &name,const glm::mat4 &mat) const;
private:
    void checkCompileErrors(unsigned int shader,std::string type);
};

#endif // SHADER_H_INCLUDED
