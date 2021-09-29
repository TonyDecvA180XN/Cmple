#include "sprite.h"

void Sprite::LoadTexture(std::string path){
    glGenTextures(1,&texture);
    glBindTexture(GL_TEXTURE_2D,texture);

    int width,height,nrComponents;
    unsigned char *data=stbi_load(path.c_str(),&width,&height,&nrComponents,0);
    if(data){
        GLenum format=0;
        if(nrComponents==1)
            format=GL_RED;
        else if(nrComponents==3)
            format=GL_RGB;
        else if(nrComponents==4)
            format=GL_RGBA;

        glBindTexture(GL_TEXTURE_2D,texture);
        glTexImage2D(GL_TEXTURE_2D,0,format,width,height,0,format,GL_UNSIGNED_BYTE,data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

        stbi_image_free(data);
    }
    else{
        throw "texture file not found";
    }
}

void Sprite::InitVAO(){
    unsigned int VBO;
    float vertices[] = {
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,

        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f
    };

    glGenVertexArrays(1, &quadVAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(quadVAO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Sprite::Load(std::string path){
    loaded=false;
    try{
        LoadTexture(path);
        InitVAO();
        loaded=true;
    }
    catch(char const *err){
        std::cerr<<err<<std::endl;
    }
}

void Sprite::Draw(float posX, float posY, float angleRotate,
          float xScale, float yScale,
          float colorRed, float colorGreen, float colorBlue,
          Shader shader, glm::mat4 model){
    shader.use();
    model = glm::translate(model, glm::vec3(posX, posY, 0.0f));
    model = glm::translate(model, glm::vec3(0.5f * origin_x, 0.5f * origin_y, 0.0f));
    model = glm::rotate(model, glm::radians(angleRotate), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::translate(model, glm::vec3(-0.5f * origin_x, -0.5f * origin_y, 0.0f));
    model = glm::scale(model, glm::vec3(xScale, yScale, 1.0f));

    shader.setMat4("model", model);

    shader.setVec3("spriteColor", glm::vec3(colorRed, colorGreen, colorBlue));

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,texture);

    glBindVertexArray(quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}
