#ifndef _MESH_H_
#define _MESH_H_

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <vector>
#include <FreeImage.h>

class Mesh{
public:
    Mesh(std::vector<float> &vertices, std::vector<unsigned int> &indices);
    void draw(unsigned int);
    // void setVertices(std::vector<float> &vertices); // Input should be 3 float to vertex pos, 3 for normal, and 2 for tex coord
    // void setIndices(std::vector<float> &indices);
    void setAmbientColor(glm::vec3);
    void setAmbientColor(std::string shaderName, glm::vec3);
    void setAmbientColorName(std::string shaderName);
    void setDiffuseColor(glm::vec3);
    void setDiffuseColor(std::string shaderName, glm::vec3);
    void setDiffuseColorName(std::string shaderName);
    void setSpecularColor(glm::vec3);
    void setSpecularColor(std::string shaderName, glm::vec3);
    void setSpecularColorName(std::string shaderName);
    void setSpecularExponent(float);
    void setSpecularExponent(std::string shaderName, float);
    void setSpecularExponentName(std::string shaderName);
    void setOpticalDensity(float);
    void setOpticalDensity(std::string shaderName, float);
    void setOpticalDensityName(std::string shaderName);
    void setDissolve(float);
    void setDissolve(std::string shaderName, float);
    void setDissolveName(std::string shaderName);
    void setIllumination(float);
    void setIllumination(std::string shaderName, float);
    void setIlluminationName(std::string shaderName);

    void loadAmbientTexture(std::string);
    void loadDiffuseTexture(std::string);
    void loadSpecularTexture(std::string);
    void loadAlphaTexture(std::string);
    void loadBumpMap(std::string);
    std::vector<float> vertices;
    std::vector<unsigned int> indices;
private:
    glm::vec3 Ka;
    glm::vec3 Kd;
    glm::vec3 Ks;
    float Ns;
    float Ni;
    float d;
    int illum;

    std::string ambientColorName;
    std::string diffuseColorName;
    std::string specularColorName;
    std::string specularExponentName;
    std::string opticalDensityName;
    std::string dissolve;
    std::string illumination;

    GLuint VBO;
    GLuint EBO;
    GLuint VAO;

    GLuint ambientTexture;
    GLuint diffuseTexture;
    GLuint specularTexture;
    GLuint alphaTexture;
    GLuint bumpTexture;

};

#endif
