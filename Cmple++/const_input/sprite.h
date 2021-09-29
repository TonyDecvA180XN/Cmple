#ifndef SPRITE_H_INCLUDED
#define SPRITE_H_INCLUDED

#include <iostream>
#include <string>
#include "GL\glm\ext.hpp"
#include "stb_image.h"
#include "shader.h"

class Sprite{
public:
    void Load(std::string path);

    void Draw(float posX, float posY, float angleRotate,
              float xScale, float yScale,
              float colorRed, float colorGreen, float colorBlue,
              Shader shader, glm::mat4 model);

private:
    bool loaded=false;
    int origin_x = 0.0;
    int origin_y = 0.0;
    unsigned int quadVAO;
    unsigned int texture;

    void LoadTexture(std::string path);

    void InitVAO();
};

#endif // SPRITE_H_INCLUDED
