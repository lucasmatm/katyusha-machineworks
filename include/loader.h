#ifndef _LOADER_H_
#define _LOADER_H_

#include <glad/glad.h>
#include <OBJ_Loader.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string.h>
#include <Mesh.h>
#include <SCL.h>

class loader{
public:
    loader(std::string obj);
    void draw(unsigned int shader);
    void setAmbientColorName(std::string Ka); // Sets name of this value in the shader
    void setDiffuseColorName(std::string Kd); // Sets name of this value in the shader
    void setSpecularColorName(std::string Ks); // Sets name of this value in the shader
    void setSpecularExponentName(std::string Ns); // Sets name of this value in the shader
    void setOpticalDensityName(std::string Ni); // Sets name of this value in the shader
    void setDissolveName(std::string d); // Sets name of this value in the shader
    void setIllumination(std::string illum); // Sets name of this value in the shader

private:
    std::string Ka;
    std::string Kd;
    std::string Ks;
    std::string Ns;
    std::string Ni;
    std::string d;
    std::string illum;
    objl::Loader object;
    std::vector<Mesh> meshes;
};

#endif
