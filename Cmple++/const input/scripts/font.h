#ifndef FONT_H_INCLUDED
#define FONT_H_INCLUDED

struct Character{
    unsigned int TextureID;
    glm::ivec2   Size;
    glm::ivec2   Bearing;
    unsigned int Advance;
};

map <GLchar,Character> Characters;
unsigned int FontVAO,FontVBO;

int initFont(){
    FT_Library ft;

    if(FT_Init_FreeType(&ft)){
        cout<<"ERROR::FREETYPE: Could not init FreeType Library"<<endl;
        return -1;
    }

    string font_name = "fonts/arial.ttf";
    if(font_name.empty()){
        cout<<"ERROR::FREETYPE: Failed to load font_name"<<endl;
        return -1;
    }

    FT_Face face;
    if(FT_New_Face(ft,font_name.c_str(),0,&face)){
        cout<<"ERROR::FREETYPE: Failed to load font"<<endl;
        return -1;
    }
    else{
        FT_Set_Pixel_Sizes(face,0,48);
        glPixelStorei(GL_UNPACK_ALIGNMENT,1);
        for(unsigned int c=0;c<256;c++){
            if(FT_Load_Char(face,c,FT_LOAD_RENDER)){
                cout<<"ERROR::FREETYTPE: Failed to load Glyph"<<endl;
                continue;
            }

            unsigned int texture;
            glGenTextures(1,&texture);
            glBindTexture(GL_TEXTURE_2D,texture);
            glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RED,
                face->glyph->bitmap.width,
                face->glyph->bitmap.rows,
                0,
                GL_RED,
                GL_UNSIGNED_BYTE,
                face->glyph->bitmap.buffer
            );

            glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

            Character character={
                texture,
                glm::ivec2(face->glyph->bitmap.width,face->glyph->bitmap.rows),
                glm::ivec2(face->glyph->bitmap_left,face->glyph->bitmap_top),
                static_cast<unsigned int>(face->glyph->advance.x)
            };
            Characters.insert(pair<char,Character>(c,character));
        }
        glBindTexture(GL_TEXTURE_2D,0);
    }

    FT_Done_Face(face);
    FT_Done_FreeType(ft);

    glGenVertexArrays(1,&FontVAO);
    glGenBuffers(1,&FontVBO);
    glBindVertexArray(FontVAO);
    glBindBuffer(GL_ARRAY_BUFFER,FontVBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(float)*6*4,NULL,GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,4,GL_FLOAT,GL_FALSE,4*sizeof(float),0);
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindVertexArray(0);

    return 0;
}

void RenderText(string text,float x,float y,float scale,glm::vec3 color,Shader shader){
    shader.use();
    glUniform3f(glGetUniformLocation(shader.ID,"textColor"),color.x,color.y,color.z);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(FontVAO);

    for(char c : text){
        Character ch=Characters[c];

        float xpos=x+ch.Bearing.x*scale;
        float ypos=y+(ch.Size.y-ch.Bearing.y)*scale;
        float w=ch.Size.x*scale;
        float h=ch.Size.y*scale;

        float vertices[6][4]={
            {xpos,    ypos - h,   0.0f,0.0f},
            {xpos,    ypos,       0.0f,1.0f},
            {xpos + w,ypos,       1.0f,1.0f},

            {xpos,    ypos - h,   0.0f,0.0f},
            {xpos + w,ypos,       1.0f,1.0f},
            {xpos + w,ypos - h,   1.0f,0.0f}
        };

        glBindTexture(GL_TEXTURE_2D,ch.TextureID);
        glBindBuffer(GL_ARRAY_BUFFER,FontVBO);
        glBufferSubData(GL_ARRAY_BUFFER,0,sizeof(vertices),vertices);
        glBindBuffer(GL_ARRAY_BUFFER,0);
        glDrawArrays(GL_TRIANGLES,0,6);

        x+=(ch.Advance>>6)*scale;
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D,0);
}

#endif // FONT_H_INCLUDED
