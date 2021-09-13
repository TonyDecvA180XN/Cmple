#ifndef MODEL_H_INCLUDED
#define MODEL_H_INCLUDED

#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/glm/ext.hpp>
#include <bits/stdc++.h>
#include "shader.h"

class Model{
private:
    struct Face{
        std::vector <int> v;
        std::vector <int> vt;
        std::vector <int> vn;
    };

    struct Material{
        float Ns;
        float d;
        float illum;
        float Kd[3];
        float Ka[3];
        float Ks[3];
        float Ke[3];
        unsigned int map_Kd;
    };

    struct Mesh{
        std::vector <Face> faces;
        unsigned int material,vao;
    };

    unsigned int LoadTexture(std::string path){
        unsigned int texture;
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
        return texture;
    }

    void initDefaultTexture(){
        glGenTextures(1,&defaultTexture);
        glBindTexture(GL_TEXTURE_2D,defaultTexture);

        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);

        unsigned char data[3]={255,255,255};
        GLenum format=GL_RGB;

        glBindTexture(GL_TEXTURE_2D,defaultTexture);
        glTexImage2D(GL_TEXTURE_2D,0,format,1,1,0,format,GL_UNSIGNED_BYTE,data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    }

    Face processFace(std::string v0,std::string v1,std::string v2){
        Face face;
        face.v.resize(3);
        face.vt.resize(3);
        face.vn.resize(3);

        int firstSlash=-1,secondSlash=-1;
        for(size_t i=0;i<v0.size();i++){
            if(v0[i]=='/'){
                if(firstSlash==-1)
                    firstSlash=i;
                else
                    secondSlash=i;
            }
        }

        face.v[0]=atoi(v0.substr(0,firstSlash).c_str());
        if(firstSlash+1!=secondSlash)
            face.vt[0]=atoi(v0.substr(firstSlash+1,secondSlash-firstSlash-1).c_str());
        else
            face.vt[0]=-1;
        face.vn[0]=atoi(v0.substr(secondSlash+1).c_str());

        firstSlash=-1,secondSlash=-1;
        for(int i=0;i<(int)v1.size();i++){
            if(v1[i]=='/'){
                if(firstSlash==-1)
                    firstSlash=i;
                else
                    secondSlash=i;
            }
        }

        face.v[1]=atoi(v1.substr(0,firstSlash).c_str());
        if(firstSlash+1!=secondSlash)
            face.vt[1]=atoi(v1.substr(firstSlash+1,secondSlash-firstSlash-1).c_str());
        else
            face.vt[1]=-1;
        face.vn[1]=atoi(v1.substr(secondSlash+1).c_str());

        firstSlash=-1,secondSlash=-1;
        for(size_t i=0;i<v2.size();i++){
            if(v2[i]=='/'){
                if(firstSlash==-1)
                    firstSlash=i;
                else
                    secondSlash=i;
            }
        }

        face.v[2]=atoi(v2.substr(0,firstSlash).c_str());
        if(firstSlash+1!=secondSlash)
            face.vt[2]=atoi(v2.substr(firstSlash+1,secondSlash-firstSlash-1).c_str());
        else
            face.vt[2]=-1;
        face.vn[2]=atoi(v2.substr(secondSlash+1).c_str());

        return face;
    }

    void initPaths(std::string path){
        int firstChar=path.size()-1;
        while(firstChar>=0 && path[firstChar]!='/')
            firstChar--;
        if(path[firstChar]=='/'){
            pathFolder=path.substr(0,firstChar+1);
            pathObj=path.substr(firstChar+1);
        }
        else{
            pathFolder="";
            pathObj=path;
        }
        std::ifstream fileObj(pathFolder+pathObj);
        if(fileObj.fail()){
            throw ".obj file not found";
        }
        std::string linebuffer;
        while(getline(fileObj,linebuffer)){
            std::stringstream linestream(linebuffer);
            std::string buffer;
            linestream>>buffer;
            if(buffer[0]=='#') continue;
            if(buffer=="mtllib"){
                if(linebuffer.size()<8){
                    throw ".mtl file name is corrupted";
                }
                pathMtl=linebuffer.substr(7);
                break;
            }
        }
        if(pathMtl.empty())
            throw "Could not find .mtl file name";
        fileObj.close();
    }

    void LoadMtl(){
        std::ifstream fileMtl(pathFolder+pathMtl);
        if(fileMtl.fail()){
            throw ".mtl file not found";
        }
        bool firstMaterial=true;
        Material bufferMaterial;
        std::string bufferMaterialName;
        bufferMaterial.map_Kd=0;
        std::string linebuffer;
        while(getline(fileMtl,linebuffer)){
            std::stringstream linestream(linebuffer);
            std::string buffer;
            linestream>>buffer;
            if(buffer[0]=='#') continue;
            else if(buffer=="newmtl"){
                if(!firstMaterial){
                    material_name[bufferMaterialName]=materials.size();
                    materials.push_back(bufferMaterial);
                    bufferMaterial.map_Kd=0;
                }
                if(linebuffer.size()<8)
                    throw "newmtl name is corrupted";
                bufferMaterialName=linebuffer.substr(7);
                firstMaterial=false;
            }
            else if(buffer=="Ns"){
                if(!(linestream>>bufferMaterial.Ns))
                    throw "Not enough arguments for flag Ns";
            }
            else if(buffer=="d"){
                if(!(linestream>>bufferMaterial.d))
                    throw "Not enough arguments for flag d";
            }
            else if(buffer=="illum"){
                if(!(linestream>>bufferMaterial.illum))
                    throw "Not enough arguments for flag illum";
            }
            else if(buffer=="Kd"){
                for(int i=0;i<3;i++){
                    if(!(linestream>>bufferMaterial.Kd[i]))
                        throw "Not enough arguments for flag Kd";
                }
            }
            else if(buffer=="Ka"){
                for(int i=0;i<3;i++){
                    if(!(linestream>>bufferMaterial.Ka[i]))
                        throw "Not enough arguments for flag Ka";
                }
            }
            else if(buffer=="Ks"){
                for(int i=0;i<3;i++){
                    if(!(linestream>>bufferMaterial.Ks[i]))
                        throw "Not enough arguments for flag Ks";
                }
            }
            else if(buffer=="Ke"){
                for(int i=0;i<3;i++){
                    if(!(linestream>>bufferMaterial.Ke[i]))
                        throw "Not enough arguments for flag Ke";
                }
            }
            else if(buffer=="map_Kd"){
                if(linebuffer.size()<8)
                    throw "map_Kd file name is corrupted";
                std::string pathTex=linebuffer.substr(7);
                bufferMaterial.map_Kd=LoadTexture(pathFolder+pathTex);
            }
            else if(!buffer.empty()){
                throw ("Unknown flag is read: "+buffer).c_str();
            }
        }
        material_name[bufferMaterialName]=materials.size();
        materials.push_back(bufferMaterial);

        fileMtl.close();
    }

    void LoadObj(){
        std::ifstream fileObj(pathFolder+pathObj);
        if(fileObj.fail()){
            throw ".obj file not found";
        }
        bool firstMaterial=true;
        std::string bufMaterial;
        Mesh bufMesh;
        std::string linebuffer;

        while(getline(fileObj,linebuffer)){
            std::stringstream linestream(linebuffer);
            std::string buffer;
            linestream>>buffer;
            if(buffer[0]=='#') continue;
            else if(buffer=="s") continue;
            else if(buffer=="o") continue;
            else if(buffer=="g") continue;
            else if(buffer=="mtllib") continue;
            else if(buffer=="v"){
                std::vector <float> v(3);
                for(int i=0;i<3;i++){
                    if(!(linestream>>v[i]))
                        throw "Not enough arguments for flag v";
                }
                vertices.push_back(v);
            }
            else if(buffer=="vt"){
                std::vector <float> vt(2);
                for(int i=0;i<2;i++){
                    if(!(linestream>>vt[i]))
                        throw "Not enough arguments for flag vt";
                }
                vt[1]=1.0f-vt[1];
                verticesTexture.push_back(vt);
            }
            else if(buffer=="vn"){
                std::vector <float> vn(3);
                for(int i=0;i<3;i++){
                    if(!(linestream>>vn[i]))
                        throw "Not enough arguments for flag vn";
                }
                verticesNormal.push_back(vn);
            }
            else if(buffer=="f"){
                std::vector <std::string> vf;
                std::string buffer2;
                while(linestream>>buffer2){
                    vf.push_back(buffer2);
                }
                if(vf.size()<3)
                    throw "Not enough arguments for flag f";
                for(size_t i=1;i<vf.size()-1;i++){
                    bufMesh.faces.push_back(processFace(vf[0],vf[i],vf[i+1]));
                }
            }
            else if(buffer=="usemtl"){
                if(!firstMaterial){
                    meshes.push_back(bufMesh);
                    bufMesh.faces.clear();
                }
                if(linebuffer.size()<8)
                    throw "usemtl name is corrupted";
                bufMaterial=linebuffer.substr(7);
                bufMesh.material=material_name[bufMaterial];
                firstMaterial=false;
            }
            else if(!buffer.empty()){
                throw ("Unknown flag is read: "+buffer).c_str();
            }
        }
        meshes.push_back(bufMesh);

        fileObj.close();
    }

    void initVAO(){
        for(size_t t=0;t<meshes.size();t++){
            std::vector <float> data;
            for(Face i : meshes[t].faces){
                for(int j=0;j<3;j++){
                    data.push_back(vertices[i.v[j]-1][0]);
                    data.push_back(vertices[i.v[j]-1][1]);
                    data.push_back(vertices[i.v[j]-1][2]);
                    data.push_back(verticesNormal[i.vn[j]-1][0]);
                    data.push_back(verticesNormal[i.vn[j]-1][1]);
                    data.push_back(verticesNormal[i.vn[j]-1][2]);
                    if(i.vt[j]!=-1){
                        data.push_back(verticesTexture[i.vt[j]-1][0]);
                        data.push_back(verticesTexture[i.vt[j]-1][1]);
                    }
                    else{
                        data.push_back(0.0f);
                        data.push_back(0.0f);
                    }
                }
            }

            unsigned int VBO;
            glGenVertexArrays(1,&meshes[t].vao);
            glGenBuffers(1,&VBO);

            glBindBuffer(GL_ARRAY_BUFFER,VBO);
            glBufferData(GL_ARRAY_BUFFER,data.size()*sizeof(float),&data[0],GL_STATIC_DRAW);

            glBindVertexArray(meshes[t].vao);

            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)0);

            glEnableVertexAttribArray(1);
            glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)(3*sizeof(float)));

            glEnableVertexAttribArray(2);
            glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)(6*sizeof(float)));
        }
    }

    bool loaded=false;
    unsigned int defaultTexture;
    std::string pathFolder;
    std::string pathObj;
    std::string pathMtl;
    std::vector < std::vector <float> > vertices;
    std::vector < std::vector <float> > verticesTexture;
    std::vector < std::vector <float> > verticesNormal;
    std::vector <Mesh> meshes;
    std::vector <Material> materials;
    std::map <std::string,int> material_name;

public:
    void Load(std::string path){
        loaded=false;
        try{
            initPaths(path);
            LoadMtl();
            initDefaultTexture();
            LoadObj();
            initVAO();
            loaded=true;
        }
        catch(char const *err){
            std::cerr<<err<<std::endl;
        }
    }

    void Draw(float xPos,float yPos,float zPos,float angleRotate,float xRotate,float yRotate,float zRotate,float xScale,float yScale,float zScale,
              Shader shader,glm::mat4 model){
        if(!loaded){
            std::cerr<<"Model was not successfully initialized"<<std::endl;
            return;
        }

        shader.use();
        model=glm::translate(model,glm::vec3(xPos,yPos,zPos));
        model=glm::rotate(model,angleRotate,glm::vec3(xRotate,yRotate,zRotate));
        model=glm::scale(model,glm::vec3(xScale,yScale,zScale));
        shader.setMat4("model",model);
        for(size_t t=0;t<meshes.size();t++){
            glActiveTexture(GL_TEXTURE0);
            if(materials[meshes[t].material].map_Kd)
                glBindTexture(GL_TEXTURE_2D,materials[meshes[t].material].map_Kd);
            else
                glBindTexture(GL_TEXTURE_2D,defaultTexture);

            shader.setVec3("material.ambient",materials[meshes[t].material].Ka[0],
                                              materials[meshes[t].material].Ka[1],
                                              materials[meshes[t].material].Ka[2]);
            shader.setVec3("material.diffuse",materials[meshes[t].material].Kd[0],
                                              materials[meshes[t].material].Kd[1],
                                              materials[meshes[t].material].Kd[2]);
            shader.setVec3("material.specular",materials[meshes[t].material].Ks[0],
                                               materials[meshes[t].material].Ks[1],
                                               materials[meshes[t].material].Ks[2]);
            shader.setFloat("material.shininess",materials[meshes[t].material].Ns*0.01f);

            glBindVertexArray(meshes[t].vao);
            glDrawArrays(GL_TRIANGLES,0,3*meshes[t].faces.size());
        }
    }
};

#endif // MODEL_H_INCLUDED
