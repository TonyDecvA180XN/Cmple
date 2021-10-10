#ifndef SPRITE_H_INCLUDED
#define SPRITE_H_INCLUDED

#include <iostream>
#include <string>
#include "GL\glm\ext.hpp"
#include "stb_image.h"
#include "shader.h"

class Sprite {
public:
    void Load(std::string path);

    void Draw(float posX, float posY, float rotateAngle,
        float scaleX, float scaleY,
        float colorRed, float colorGreen, float colorBlue,
        Shader shader, glm::mat4 model);

private:
    bool loaded = false;
    unsigned int quadVAO;
    unsigned int texture;

    void LoadTexture(std::string path);

    void InitVAO();
};

#endif // SPRITE_H_INCLUDED
