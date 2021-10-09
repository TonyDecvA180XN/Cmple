#ifndef FONT_H_INCLUDED
#define FONT_H_INCLUDED

#include <string>
#include "shader.h"
#include "stb_image.h"

class Font {
public:
    void Load(std::string path);

    void DrawText(std::string text, float posX, float posY,
        float rotateAngle, float scaleX, float sizeY,
        float colorRed, float colorGreen, float colorBlue,
        Shader shader, glm::mat4 model);

private:
    struct Char {
        int x, y;
        int width, height;
        int xoffset, yoffset;
        int xadvance;
        int page;
        int chnl;
    };

    void LoadFnt(std::string path);

    unsigned int LoadTexture(std::string path);
    void InitVAO();

    std::string ParseVariable(std::string str);
    unsigned int ParseInteger(std::string str);
    std::string ParsePath(std::string str);

    static const int NumberOfChars = 128;
    static const int NumberOfPages = 16;

    bool loaded = false;
    std::string pathFolder;
    unsigned int imageWidth, imageHeight, fontSize;
    Char charData[NumberOfChars];
    unsigned int charVAO[NumberOfChars];
    unsigned int pageTexture[NumberOfPages];
};

#endif // FONT_H_INCLUDED
