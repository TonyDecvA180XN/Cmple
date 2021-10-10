#include "font.h"

void Font::Load(std::string path) {
    try {
        LoadFnt(path);
        InitVAO();
        loaded = true;
    }
    catch (char const* err) {
        std::cerr << err << std::endl;
    }
}

void Font::DrawText(std::string text, float posX, float posY,
    float rotateAngle, float scaleX, float sizeY,
    float colorRed, float colorGreen, float colorBlue,
    Shader shader, glm::mat4 model) {
    if (!loaded) {
        std::cerr << "Font was not successfully initialized" << std::endl;
        return;
    }

    shader.use();
    model = glm::translate(model, glm::vec3(posX, posY, 0.0f));
    model = glm::rotate(model, glm::radians(rotateAngle), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::scale(model, glm::vec3(sizeY * scaleX / fontSize, sizeY / fontSize, 1.0f));

    shader.setMat4("model", model);
    shader.setVec3("textColor", glm::vec3(colorRed, colorGreen, colorBlue));

    glActiveTexture(GL_TEXTURE0);
    for (char c : text) {
        int index = (int)c;
        int page = charData[index].page;
        int width = charData[index].width;
        int height = charData[index].height;
        int xoffset = charData[index].xoffset;
        int yoffset = charData[index].yoffset;
        int xadvance = charData[index].xadvance;

        glBindTexture(GL_TEXTURE_2D, pageTexture[page]);

        glm::mat4 model2 = model;
        model2 = glm::translate(model2, glm::vec3(xoffset, yoffset, 1.0f));
        model2 = glm::scale(model2, glm::vec3(width, height, 1.0f));
        shader.setMat4("model", model2);

        model = glm::translate(model, glm::vec3(xadvance, 0.0f, 0.0f));


        glBindVertexArray(charVAO[index]);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);
    }

}

void Font::LoadFnt(std::string path) {
    int firstChar = (int)path.size() - 1;
    while (firstChar >= 0 && (path[firstChar] != '/' && path[firstChar] != '\\'))
        firstChar--;
    if (path[firstChar] == '/' || path[firstChar] == '\\') {
        pathFolder = path.substr(0, firstChar + 1);
    }
    else {
        pathFolder = "";
    }

    std::ifstream file(path);
    if (!file.is_open()) {
        throw ".fnt file not found";
    }
    std::string linebuffer;
    while (getline(file, linebuffer)) {
        std::stringstream linestream(linebuffer);
        std::string buffer;
        linestream >> buffer;
        if (buffer == "info") {
            while (linestream >> buffer) {
                if (ParseVariable(buffer) == "size") {
                    fontSize = ParseInteger(buffer);
                }
            }
        }
        if (buffer == "common") {
            while (linestream >> buffer) {
                if (ParseVariable(buffer) == "scaleW") {
                    imageWidth = ParseInteger(buffer);
                }
                if (ParseVariable(buffer) == "scaleH") {
                    imageHeight = ParseInteger(buffer);
                }
            }
        }
        else if (buffer == "page") {
            int index;
            std::string path_page;
            while (linestream >> buffer) {
                if (ParseVariable(buffer) == "id") {
                    index = ParseInteger(buffer);
                }
                if (ParseVariable(buffer) == "file") {
                    path_page = ParsePath(buffer);
                }
            }
            pageTexture[index] = LoadTexture(pathFolder + path_page);
        }
        else if (buffer == "char") {
            int index;
            Char ch;
            while (linestream >> buffer) {
                if (ParseVariable(buffer) == "id") {
                    index = ParseInteger(buffer);
                }
                if (ParseVariable(buffer) == "x") {
                    ch.x = ParseInteger(buffer);
                }
                if (ParseVariable(buffer) == "y") {
                    ch.y = ParseInteger(buffer);
                }
                if (ParseVariable(buffer) == "width") {
                    ch.width = ParseInteger(buffer);
                }
                if (ParseVariable(buffer) == "height") {
                    ch.height = ParseInteger(buffer);
                }
                if (ParseVariable(buffer) == "xoffset") {
                    ch.xoffset = ParseInteger(buffer);
                }
                if (ParseVariable(buffer) == "yoffset") {
                    ch.yoffset = ParseInteger(buffer);
                }
                if (ParseVariable(buffer) == "xadvance") {
                    ch.xadvance = ParseInteger(buffer);
                }
                if (ParseVariable(buffer) == "page") {
                    ch.page = ParseInteger(buffer);
                }
                if (ParseVariable(buffer) == "chnl") {
                    ch.chnl = ParseInteger(buffer);
                }
            }
            charData[index] = ch;
        }
    }
    file.close();
}

unsigned int Font::LoadTexture(std::string path) {
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    int width, height, nrComponents;
    unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrComponents, 0);
    if (data) {
        GLenum format = 0;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else {
        throw "texture file not found";
    }
    return texture;
}

void Font::InitVAO() {
    for (unsigned int i = 0; i < NumberOfChars; i++) {
        float x = charData[i].x * 1.0f;
        float y = charData[i].y * 1.0f;
        float width = charData[i].width * 1.0f;
        float height = charData[i].height * 1.0f;
        unsigned int VBO;
        float vertices[] = {
            0.0f, 1.0f, x / imageWidth, (y + height) / imageHeight,
            1.0f, 0.0f, (x + width) / imageWidth, y / imageHeight,
            0.0f, 0.0f, x / imageWidth, y / imageHeight,

            0.0f, 1.0f, x / imageWidth, (y + height) / imageHeight,
            1.0f, 1.0f, (x + width) / imageWidth, (y + height) / imageHeight,
            1.0f, 0.0f, (x + width) / imageWidth, y / imageHeight
        };

        glGenVertexArrays(1, &charVAO[i]);
        glGenBuffers(1, &VBO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glBindVertexArray(charVAO[i]);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
}

std::string Font::ParseVariable(std::string str) {
    for (size_t i = 0; i < str.size(); i++) {
        if (str[i] == '=') {
            return str.substr(0, i);
        }
    }
    return str;
}

unsigned int Font::ParseInteger(std::string str) {
    if (!(str.back() >= '0' && str.back() <= '9'))
        return 0;
    for (int i = (int)str.size() - 1; i >= 0; i--) {
        if (!(str[i] >= '0' && str[i] <= '9')) {
            return atoi(str.substr(i + 1).c_str());
        }
    }
    return atoi(str.c_str());
}

std::string Font::ParsePath(std::string str) {
    int first = -1, second = -1;
    for (size_t i = 0; i < str.size(); i++) {
        if (str[i] == '\"') {
            if (first == -1) {
                first = i;
            }
            else if (second == -1) {
                second = i;
            }
            else {
                throw ".fnt file is corrupted";
            }
        }
    }

    if (first == -1 || second == -1) {
        throw ".fnt file is corrupted";
    }

    return str.substr(first + 1, second - first - 1);
}
