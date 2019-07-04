#include <Mesh.h>
#include <iostream>

Mesh::Mesh(std::vector<float> &vtx, std::vector<unsigned int> &idx){
    this->ambientColorName = std::string("ambientColor");
    this->diffuseColorName = std::string("diffuseColor");
    this->specularColorName = std::string("specularColor");
    this->specularExponentName = std::string("specularExponent");
    this->opticalDensityName = std::string("opticalDensity");
    this->dissolve = std::string("dissolve");
    this->illumination = std::string("illumination");

    ambientTexture = 0;
    diffuseTexture = 0;
    specularTexture = 0;
    alphaTexture = 0;
    bumpTexture = 0;

    glGenVertexArrays(1, &(this->VAO));
    glGenBuffers(1, &(this->VBO));
	glGenBuffers(1, &(this->EBO));

    this->vertices = vtx;
    this->indices = idx;

    glBindVertexArray(this->VAO);
        // Setup vertex data
        glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float)*(this->vertices).size(), this->vertices.data(), GL_STATIC_DRAW);

        // Setup index data
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float)*(this->indices).size(), this->indices.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
        glEnableVertexAttribArray(1);

        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
        glEnableVertexAttribArray(2);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

}


void Mesh::draw(unsigned int shader){

    glUniform3f(glGetUniformLocation(shader, this->ambientColorName.c_str()), this->Ka.x, this->Ka.y, this->Ka.z);
    glUniform3f(glGetUniformLocation(shader, this->diffuseColorName.c_str()), this->Kd.x, this->Kd.y, this->Kd.z);
    glUniform3f(glGetUniformLocation(shader, this->specularColorName.c_str()), this->Ks.x, this->Ks.y, this->Ks.z);
    glUniform1f(glGetUniformLocation(shader, this->specularExponentName.c_str()), this->Ns);
    glUniform1f(glGetUniformLocation(shader, this->opticalDensityName.c_str()), this->Ni);
    glUniform1f(glGetUniformLocation(shader, this->dissolve.c_str()), this->d);
    glUniform1i(glGetUniformLocation(shader, this->illumination.c_str()), this->illum);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, 0);
    if (ambientTexture){
        glBindTexture(GL_TEXTURE_2D, this->ambientTexture);
    }
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, 0);
    if (diffuseTexture){
        glBindTexture(GL_TEXTURE_2D, this->diffuseTexture);
    }
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, 0);
    if (specularTexture){
        glBindTexture(GL_TEXTURE_2D, this->specularTexture);
    }
    glActiveTexture(GL_TEXTURE3);
    glBindTexture(GL_TEXTURE_2D, 0);
    if (alphaTexture){
        glBindTexture(GL_TEXTURE_2D, this->alphaTexture);
    }
    glActiveTexture(GL_TEXTURE4);
    glBindTexture(GL_TEXTURE_2D, 0);
    if (bumpTexture){
        glBindTexture(GL_TEXTURE_2D, this->bumpTexture);
    }

    glBindVertexArray(this->VAO);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
	glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, 0);


}


// void Mesh::setVertices(std::vector<float> &vertices){
//     this->vertices = vertices;
//     glBindVertexArray(this->VAO);
//         // Setup vertex data
//         glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
//         glBufferData(GL_ARRAY_BUFFER, sizeof(float)*(this->vertices).size(), this->vertices.data(), GL_STATIC_DRAW);
//
//         glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
//         glEnableVertexAttribArray(0);
//
//         glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
//         glEnableVertexAttribArray(1);
//
//         glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
//         glEnableVertexAttribArray(2);
//
//         glBindBuffer(GL_ARRAY_BUFFER, 0);
//         glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
//
//     glBindVertexArray(0);
//
// }
// void Mesh::setIndices(std::vector<float> &indices){
//     this->indices = indices;
//     glBindVertexArray(this->VAO);
//
//         // Setup index data
//         glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
//         glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float)*(this->indices).size(), this->indices.data(), GL_STATIC_DRAW);
//
//         glBindBuffer(GL_ARRAY_BUFFER, 0);
//         glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
//
//     glBindVertexArray(0);
//
// }
void Mesh::setAmbientColor(glm::vec3 Ka){
    this->Ka = Ka;
}
void Mesh::setAmbientColor(std::string shaderName, glm::vec3){
    this->ambientColorName = shaderName;
    this->Ka = Ka;
}
void Mesh::setAmbientColorName(std::string shaderName){
    this->ambientColorName = shaderName;
}
void Mesh::setDiffuseColor(glm::vec3 Kd){
    this->Kd = Kd;
}
void Mesh::setDiffuseColor(std::string shaderName, glm::vec3 Kd){
    this->diffuseColorName = shaderName;
    this->Kd = Kd;
}
void Mesh::setDiffuseColorName(std::string shaderName){
    this->diffuseColorName = shaderName;
}
void Mesh::setSpecularColor(glm::vec3 Ks){
    this->Ks = Ks;
}
void Mesh::setSpecularColor(std::string shaderName, glm::vec3 Ks){
    this->specularColorName = shaderName;
    this->Ks = Ks;
}
void Mesh::setSpecularColorName(std::string shaderName){
    this->specularColorName = shaderName;
}
void Mesh::setSpecularExponent(float Ns){
    this->Ns = Ns;
}
void Mesh::setSpecularExponent(std::string shaderName, float Ns){
    this->specularExponentName = shaderName;
    this->Ns = Ns;
}
void Mesh::setSpecularExponentName(std::string shaderName){
    this->specularExponentName = shaderName;
}
void Mesh::setOpticalDensity(float Ni){
    this->Ni = Ni;
}
void Mesh::setOpticalDensity(std::string shaderName, float Ni){
    this->opticalDensityName = shaderName;
    this->Ni = Ni;
}
void Mesh::setOpticalDensityName(std::string shaderName){
    this->opticalDensityName = shaderName;
}
void Mesh::setDissolve(float d){
    this->d = d;
}
void Mesh::setDissolve(std::string shaderName, float d){
    this->dissolve = shaderName;
    this->d = d;
}
void Mesh::setDissolveName(std::string shaderName){
    this->dissolve = shaderName;
}
void Mesh::setIllumination(float illum){
    this->illum = illum;
}
void Mesh::setIllumination(std::string shaderName, float illum){
    this->illumination = shaderName;
    this->illum = illum;
}
void Mesh::setIlluminationName(std::string shaderName){
    this->illumination = shaderName;
}

void Mesh::loadAmbientTexture(std::string texture_name){

    glActiveTexture(GL_TEXTURE0);

    glGenTextures(1, &(this->ambientTexture));
    glBindTexture(GL_TEXTURE_2D, this->ambientTexture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    FIBITMAP* bitmap = FreeImage_Load(FreeImage_GetFileType(texture_name.c_str(), 0), texture_name.c_str());

    FIBITMAP *pImage = FreeImage_ConvertTo32Bits(bitmap);
    int imageHeight = FreeImage_GetHeight(pImage);
    int imageWidth = FreeImage_GetWidth(pImage);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, imageWidth, imageHeight, 0, GL_BGRA, GL_UNSIGNED_BYTE, (void*)FreeImage_GetBits(pImage));
    glGenerateMipmap(GL_TEXTURE_2D);
    FreeImage_Unload(bitmap);

    glBindTexture(GL_TEXTURE_2D, 0);

}
void Mesh::loadDiffuseTexture(std::string texture_name){

    glActiveTexture(GL_TEXTURE1);

    glGenTextures(1, &(this->diffuseTexture));
    glBindTexture(GL_TEXTURE_2D, this->diffuseTexture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    FIBITMAP* bitmap = FreeImage_Load(FreeImage_GetFileType(texture_name.c_str(), 0), texture_name.c_str());

    FIBITMAP *pImage = FreeImage_ConvertTo32Bits(bitmap);
    int imageHeight = FreeImage_GetHeight(pImage);
    int imageWidth = FreeImage_GetWidth(pImage);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, imageWidth, imageHeight, 0, GL_BGRA, GL_UNSIGNED_BYTE, (void*)FreeImage_GetBits(pImage));
    glGenerateMipmap(GL_TEXTURE_2D);
    FreeImage_Unload(bitmap);

    glBindTexture(GL_TEXTURE_2D, 0);

}
void Mesh::loadSpecularTexture(std::string texture_name){

        glActiveTexture(GL_TEXTURE2);

        glGenTextures(1, &(this->specularTexture));
        glBindTexture(GL_TEXTURE_2D, this->specularTexture);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        FIBITMAP* bitmap = FreeImage_Load(FreeImage_GetFileType(texture_name.c_str(), 0), texture_name.c_str());

        FIBITMAP *pImage = FreeImage_ConvertTo32Bits(bitmap);
        int imageHeight = FreeImage_GetHeight(pImage);
        int imageWidth = FreeImage_GetWidth(pImage);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, imageWidth, imageHeight, 0, GL_BGRA, GL_UNSIGNED_BYTE, (void*)FreeImage_GetBits(pImage));
        glGenerateMipmap(GL_TEXTURE_2D);
        FreeImage_Unload(bitmap);

        glBindTexture(GL_TEXTURE_2D, 0);

}
void Mesh::loadAlphaTexture(std::string texture_name){

            glActiveTexture(GL_TEXTURE3);

            glGenTextures(1, &(this->alphaTexture));
            glBindTexture(GL_TEXTURE_2D, this->alphaTexture);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

            FIBITMAP* bitmap = FreeImage_Load(FreeImage_GetFileType(texture_name.c_str(), 0), texture_name.c_str());

            FIBITMAP *pImage = FreeImage_ConvertTo32Bits(bitmap);
            int imageHeight = FreeImage_GetHeight(pImage);
            int imageWidth = FreeImage_GetWidth(pImage);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, imageWidth, imageHeight, 0, GL_BGRA, GL_UNSIGNED_BYTE, (void*)FreeImage_GetBits(pImage));
            glGenerateMipmap(GL_TEXTURE_2D);
            FreeImage_Unload(bitmap);

            glBindTexture(GL_TEXTURE_2D, 0);

}
void Mesh::loadBumpMap(std::string texture_name){

                glActiveTexture(GL_TEXTURE4);

                glGenTextures(1, &(this->bumpTexture));
                glBindTexture(GL_TEXTURE_2D, this->bumpTexture);

                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

                FIBITMAP* bitmap = FreeImage_Load(FreeImage_GetFileType(texture_name.c_str(), 0), texture_name.c_str());

                FIBITMAP *pImage = FreeImage_ConvertTo32Bits(bitmap);
                int imageHeight = FreeImage_GetHeight(pImage);
                int imageWidth = FreeImage_GetWidth(pImage);
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, imageWidth, imageHeight, 0, GL_BGRA, GL_UNSIGNED_BYTE, (void*)FreeImage_GetBits(pImage));
                glGenerateMipmap(GL_TEXTURE_2D);
                FreeImage_Unload(bitmap);

                glBindTexture(GL_TEXTURE_2D, 0);

}
