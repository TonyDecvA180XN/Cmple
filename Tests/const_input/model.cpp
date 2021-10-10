#include "model.h"

void Model::Load(std::string path) {
    try {
        initPaths(path);
        LoadMtl();
        initDefaultTexture();
        LoadObj();
        initVAO();
        loaded = true;
    }
    catch (char const* err) {
        std::cerr << err << std::endl;
    }
}

void Model::Draw(float posX, float posY, float posZ,
    float rotateAngle, float rotateX, float rotateY, float rotateZ,
    float scaleX, float scaleY, float scaleZ,
    Shader shader, glm::mat4 model) {
    if (!loaded) {
        std::cerr << "Model was not successfully initialized" << std::endl;
        return;
    }

    shader.use();
    model = glm::translate(model, glm::vec3(posX, posY, posZ));
    model = glm::rotate(model, rotateAngle, glm::vec3(rotateX, rotateY, rotateZ));
    model = glm::scale(model, glm::vec3(scaleX, scaleY, scaleZ));
    shader.setMat4("model", model);
    for (size_t t = 0; t < meshes.size(); t++) {
        glActiveTexture(GL_TEXTURE0);
        if (materials[meshes[t].material].map_Kd)
            glBindTexture(GL_TEXTURE_2D, materials[meshes[t].material].map_Kd);
        else
            glBindTexture(GL_TEXTURE_2D, defaultTexture);

        shader.setVec3("material.ambient", materials[meshes[t].material].Ka[0],
            materials[meshes[t].material].Ka[1],
            materials[meshes[t].material].Ka[2]);
        shader.setVec3("material.diffuse", materials[meshes[t].material].Kd[0],
            materials[meshes[t].material].Kd[1],
            materials[meshes[t].material].Kd[2]);
        shader.setVec3("material.specular", materials[meshes[t].material].Ks[0],
            materials[meshes[t].material].Ks[1],
            materials[meshes[t].material].Ks[2]);
        shader.setFloat("material.shininess", materials[meshes[t].material].Ns * 0.001f);

        glBindVertexArray(meshes[t].vao);
        glDrawArrays(GL_TRIANGLES, 0, 3 * meshes[t].faces.size());
    }
}

unsigned int Model::LoadTexture(std::string path) {
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
        std::cout << path << std::endl;
        throw "texture file not found";
    }
    return texture;
}

void Model::initDefaultTexture() {
    glGenTextures(1, &defaultTexture);
    glBindTexture(GL_TEXTURE_2D, defaultTexture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    unsigned char data[3] = { 255, 255, 255 };
    GLenum format = GL_RGB;

    glBindTexture(GL_TEXTURE_2D, defaultTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, format, 1, 1, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

Model::Face Model::processFace(std::string v0, std::string v1, std::string v2) {
    Face face;
    face.v.resize(3);
    face.vt.resize(3);
    face.vn.resize(3);

    int firstSlash = -1, secondSlash = -1;
    for (size_t i = 0; i < v0.size(); i++) {
        if (v0[i] == '/') {
            if (firstSlash == -1)
                firstSlash = i;
            else
                secondSlash = i;
        }
    }

    face.v[0] = atoi(v0.substr(0, firstSlash).c_str());
    if (firstSlash + 1 != secondSlash)
        face.vt[0] = atoi(v0.substr(firstSlash + 1, secondSlash - firstSlash - 1).c_str());
    else
        face.vt[0] = -1;
    face.vn[0] = atoi(v0.substr(secondSlash + 1).c_str());

    firstSlash = -1, secondSlash = -1;
    for (int i = 0; i < (int)v1.size(); i++) {
        if (v1[i] == '/') {
            if (firstSlash == -1)
                firstSlash = i;
            else
                secondSlash = i;
        }
    }

    face.v[1] = atoi(v1.substr(0, firstSlash).c_str());
    if (firstSlash + 1 != secondSlash)
        face.vt[1] = atoi(v1.substr(firstSlash + 1, secondSlash - firstSlash - 1).c_str());
    else
        face.vt[1] = -1;
    face.vn[1] = atoi(v1.substr(secondSlash + 1).c_str());

    firstSlash = -1, secondSlash = -1;
    for (size_t i = 0; i < v2.size(); i++) {
        if (v2[i] == '/') {
            if (firstSlash == -1)
                firstSlash = i;
            else
                secondSlash = i;
        }
    }

    face.v[2] = atoi(v2.substr(0, firstSlash).c_str());
    if (firstSlash + 1 != secondSlash)
        face.vt[2] = atoi(v2.substr(firstSlash + 1, secondSlash - firstSlash - 1).c_str());
    else
        face.vt[2] = -1;
    face.vn[2] = atoi(v2.substr(secondSlash + 1).c_str());

    return face;
}

void Model::initPaths(std::string path) {
    int firstChar = (int)path.size() - 1;
    while (firstChar >= 0 && (path[firstChar] != '/' && path[firstChar] != '\\'))
        firstChar--;
    if (path[firstChar] == '/' || path[firstChar] == '\\') {
        pathFolder = path.substr(0, firstChar + 1);
        pathObj = path.substr(firstChar + 1);
    }
    else {
        pathFolder = "";
        pathObj = path;
    }

    std::ifstream fileObj(pathFolder + pathObj);
    if (fileObj.fail()) {
        throw ".obj file not found";
    }
    std::string linebuffer;
    while (getline(fileObj, linebuffer)) {
        std::stringstream linestream(linebuffer);
        std::string buffer;
        linestream >> buffer;
        if (buffer[0] == '#') continue;
        if (buffer == "mtllib") {
            if (linebuffer.size() < 8) {
                throw ".mtl file name is corrupted";
            }
            pathMtl = linebuffer.substr(7);
            break;
        }
    }
    if (pathMtl.empty())
        throw "Could not find .mtl file name";
    fileObj.close();
}

void Model::LoadMtl() {
    std::ifstream fileMtl(pathFolder + pathMtl);
    if (fileMtl.fail()) {
        throw ".mtl file not found";
    }
    bool firstMaterial = true;
    Material bufferMaterial;
    std::string bufferMaterialName;
    bufferMaterial.map_Kd = 0;
    bufferMaterial.map_Ka = 0;
    bufferMaterial.map_Disp = 0;
    bufferMaterial.map_d = 0;
    std::string linebuffer;
    while (getline(fileMtl, linebuffer)) {
        std::stringstream linestream(linebuffer);
        std::string buffer;
        linestream >> buffer;
        if (buffer[0] == '#') continue;
        else if (buffer == "newmtl") {
            if (!firstMaterial) {
                material_name[bufferMaterialName] = materials.size();
                materials.push_back(bufferMaterial);
                bufferMaterial.map_Kd = 0;
                bufferMaterial.map_Ka = 0;
                bufferMaterial.map_Disp = 0;
                bufferMaterial.map_d = 0;
            }
            if (!(linestream >> buffer))
                throw "Not enough arguments for flag newmtl";
            bufferMaterialName = buffer;
            firstMaterial = false;
        }
        else if (buffer == "Ns") {
            if (!(linestream >> bufferMaterial.Ns))
                throw "Not enough arguments for flag Ns";
        }
        else if (buffer == "Ni") {
            if (!(linestream >> bufferMaterial.Ni))
                throw "Not enough arguments for flag Ni";
        }
        else if (buffer == "d") {
            if (!(linestream >> bufferMaterial.d))
                throw "Not enough arguments for flag d";
        }
        else if (buffer == "illum") {
            if (!(linestream >> bufferMaterial.illum))
                throw "Not enough arguments for flag illum";
        }
        else if (buffer == "Kd") {
            for (int i = 0; i < 3; i++) {
                if (!(linestream >> bufferMaterial.Kd[i]))
                    throw "Not enough arguments for flag Kd";
            }
        }
        else if (buffer == "Ka") {
            for (int i = 0; i < 3; i++) {
                if (!(linestream >> bufferMaterial.Ka[i]))
                    throw "Not enough arguments for flag Ka";
            }
        }
        else if (buffer == "Ks") {
            for (int i = 0; i < 3; i++) {
                if (!(linestream >> bufferMaterial.Ks[i]))
                    throw "Not enough arguments for flag Ks";
            }
        }
        else if (buffer == "Ke") {
            for (int i = 0; i < 3; i++) {
                if (!(linestream >> bufferMaterial.Ke[i]))
                    throw "Not enough arguments for flag Ke";
            }
        }
        else if (buffer == "map_Kd") {
            if (!(linestream >> buffer))
                throw "Not enough arguments for flag map_Kd";
            bufferMaterial.map_Kd = LoadTexture(pathFolder + buffer);
        }
        else if (buffer == "map_Ka") {
            if (!(linestream >> buffer))
                throw "Not enough arguments for flag map_Ka";
            bufferMaterial.map_Ka = LoadTexture(pathFolder + buffer);
        }
        else if (buffer == "map_Disp") {
            if (!(linestream >> buffer))
                throw "Not enough arguments for flag map_Disp";
            bufferMaterial.map_Disp = LoadTexture(pathFolder + buffer);
        }
        else if (buffer == "map_d") {
            if (!(linestream >> buffer))
                throw "Not enough arguments for flag map_d";
            bufferMaterial.map_d = LoadTexture(pathFolder + buffer);
        }
        else if (!buffer.empty()) {
            throw ("Unknown flag is read: " + buffer).c_str();
        }
    }
    material_name[bufferMaterialName] = materials.size();
    materials.push_back(bufferMaterial);

    fileMtl.close();
}

void Model::LoadObj() {
    std::ifstream fileObj(pathFolder + pathObj);
    if (fileObj.fail()) {
        throw ".obj file not found";
    }
    bool firstMaterial = true;
    std::string bufMaterial;
    Mesh bufMesh;
    std::string linebuffer;

    while (getline(fileObj, linebuffer)) {
        std::stringstream linestream(linebuffer);
        std::string buffer;
        linestream >> buffer;
        if (buffer[0] == '#') continue;
        else if (buffer == "s") continue;
        else if (buffer == "o") continue;
        else if (buffer == "g") continue;
        else if (buffer == "mtllib") continue;
        else if (buffer == "v") {
            std::vector <float> v(3);
            for (int i = 0; i < 3; i++) {
                if (!(linestream >> v[i]))
                    throw "Not enough arguments for flag v";
            }
            vertices.push_back(v);
        }
        else if (buffer == "vt") {
            std::vector <float> vt(2);
            for (int i = 0; i < 2; i++) {
                if (!(linestream >> vt[i]))
                    throw "Not enough arguments for flag vt";
            }
            vt[1] = 1.0f - vt[1];
            verticesTexture.push_back(vt);
        }
        else if (buffer == "vn") {
            std::vector <float> vn(3);
            for (int i = 0; i < 3; i++) {
                if (!(linestream >> vn[i]))
                    throw "Not enough arguments for flag vn";
            }
            verticesNormal.push_back(vn);
        }
        else if (buffer == "f") {
            std::vector <std::string> vf;
            std::string buffer2;
            while (linestream >> buffer2) {
                vf.push_back(buffer2);
            }
            if (vf.size() < 3)
                throw "Not enough arguments for flag f";
            for (size_t i = 1; i < vf.size() - 1; i++) {
                bufMesh.faces.push_back(processFace(vf[0], vf[i], vf[i + 1]));
            }
        }
        else if (buffer == "usemtl") {
            if (!firstMaterial) {
                meshes.push_back(bufMesh);
                bufMesh.faces.clear();
            }
            if (linebuffer.size() < 8)
                throw "usemtl name is corrupted";
            bufMaterial = linebuffer.substr(7);
            bufMesh.material = material_name[bufMaterial];
            firstMaterial = false;
        }
        else if (!buffer.empty()) {
            throw ("Unknown flag is read: " + buffer).c_str();
        }
    }
    meshes.push_back(bufMesh);

    fileObj.close();
}

void Model::initVAO() {
    for (size_t t = 0; t < meshes.size(); t++) {
        std::vector <float> data;
        for (Face i : meshes[t].faces) {
            for (int j = 0; j < 3; j++) {
                data.push_back(vertices[i.v[j] - 1][0]);
                data.push_back(vertices[i.v[j] - 1][1]);
                data.push_back(vertices[i.v[j] - 1][2]);
                data.push_back(verticesNormal[i.vn[j] - 1][0]);
                data.push_back(verticesNormal[i.vn[j] - 1][1]);
                data.push_back(verticesNormal[i.vn[j] - 1][2]);
                if (i.vt[j] != -1) {
                    data.push_back(verticesTexture[i.vt[j] - 1][0]);
                    data.push_back(verticesTexture[i.vt[j] - 1][1]);
                }
                else {
                    data.push_back(0.0f);
                    data.push_back(0.0f);
                }
            }
        }

        unsigned int VBO;
        glGenVertexArrays(1, &meshes[t].vao);
        glGenBuffers(1, &VBO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), &data[0], GL_STATIC_DRAW);

        glBindVertexArray(meshes[t].vao);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));

        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    }
}
