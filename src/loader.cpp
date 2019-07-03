#include <loader.h>
#include <FreeImage.h>


loader::loader(std::string obj){
    try{
        this->object.LoadFile(obj);
    }catch(std::exception e){
        throw(e.what());
    }
    for (size_t i = 0; i < object.LoadedMeshes.size(); i++) {

        Mesh curMesh;
        std::vector<float> vertices;
        std::vector<float> indices;
        for (size_t j = 0; j < object.LoadedMeshes[i].Vertices.size(); j++) {
            vertices.push_back(object.LoadedMeshes[i].Vertices[j].Position.X);
            vertices.push_back(object.LoadedMeshes[i].Vertices[j].Position.Y);
            vertices.push_back(object.LoadedMeshes[i].Vertices[j].Position.Z);

            vertices.push_back(object.LoadedMeshes[i].Vertices[j].Normal.X);
            vertices.push_back(object.LoadedMeshes[i].Vertices[j].Normal.Y);
            vertices.push_back(object.LoadedMeshes[i].Vertices[j].Normal.Z);

            vertices.push_back(object.LoadedMeshes[i].Vertices[j].TextureCoordinate.X);
            vertices.push_back(object.LoadedMeshes[i].Vertices[j].TextureCoordinate.Y);
        }
        for (size_t j = 0; j < object.LoadedMeshes[i].Indices.size(); j++){
            indices.push_back(object.LoadedMeshes[i].Indices[j]);
        }
        curMesh.setVertices(vertices);
        curMesh.setIndices(indices);
        curMesh.setAmbientColor(glm::vec3(object.LoadedMeshes[i].MeshMaterial.Ka.X, object.LoadedMeshes[i].MeshMaterial.Ka.Y, object.LoadedMeshes[i].MeshMaterial.Ka.Z));
        curMesh.setDiffuseColor(glm::vec3(object.LoadedMeshes[i].MeshMaterial.Kd.X, object.LoadedMeshes[i].MeshMaterial.Kd.Y, object.LoadedMeshes[i].MeshMaterial.Kd.Z));
        curMesh.setSpecularColor(glm::vec3(object.LoadedMeshes[i].MeshMaterial.Ks.X, object.LoadedMeshes[i].MeshMaterial.Ks.Y, object.LoadedMeshes[i].MeshMaterial.Ks.Z));
        curMesh.setSpecularExponent(object.LoadedMeshes[i].MeshMaterial.Ns);
        curMesh.setOpticalDensity(object.LoadedMeshes[i].MeshMaterial.Ni);
        curMesh.setDissolve(object.LoadedMeshes[i].MeshMaterial.d);
        curMesh.setIllumination(object.LoadedMeshes[i].MeshMaterial.illum);
        if(!object.LoadedMeshes[i].MeshMaterial.map_Ka.empty())
            curMesh.loadAmbientTexture(object.LoadedMeshes[i].MeshMaterial.map_Ka);
        if(!object.LoadedMeshes[i].MeshMaterial.map_Kd.empty())
            curMesh.loadDiffuseTexture(object.LoadedMeshes[i].MeshMaterial.map_Kd);
        if(!object.LoadedMeshes[i].MeshMaterial.map_Ks.empty())
            curMesh.loadSpecularTexture(object.LoadedMeshes[i].MeshMaterial.map_Ks);
        if(!object.LoadedMeshes[i].MeshMaterial.map_d.empty())
            curMesh.loadAlphaTexture(object.LoadedMeshes[i].MeshMaterial.map_d);
        if(!object.LoadedMeshes[i].MeshMaterial.map_bump.empty())
            curMesh.loadBumpMap(object.LoadedMeshes[i].MeshMaterial.map_bump);

        this->meshes.push_back(curMesh);

    }

}

void loader::draw(unsigned int shader){
    for (size_t i = 0; i < meshes.size(); i++) {
        meshes[i].draw(shader);
    }
}


void loader::setAmbientColorName(std::string Ka){
    this->Ka = Ka;
    for (size_t i = 0; i < this->meshes.size(); i++) {
        this->meshes[i].setAmbientColorName(Ka);
    }
}
void loader::setDiffuseColorName(std::string Kd){
    this->Kd = Kd;
    for (size_t i = 0; i < this->meshes.size(); i++) {
        this->meshes[i].setDiffuseColorName(Kd);
    }
}
void loader::setSpecularColorName(std::string Ks){
    this->Ks = Ks;
    for (size_t i = 0; i < this->meshes.size(); i++) {
        this->meshes[i].setSpecularColorName(Ks);
    }
}
void loader::setSpecularExponentName(std::string Ns){
    this->Ns = Ns;
    for (size_t i = 0; i < this->meshes.size(); i++) {
        this->meshes[i].setSpecularExponentName(Ns);
    }
}
void loader::setOpticalDensityName(std::string Ni){
    this->Ni = Ni;
    for (size_t i = 0; i < this->meshes.size(); i++) {
        this->meshes[i].setOpticalDensityName(Ni);
    }
}
void loader::setDissolveName(std::string d){
    this->d = d;
    for (size_t i = 0; i < this->meshes.size(); i++) {
        this->meshes[i].setDissolveName(d);
    }
}
void loader::setIllumination(std::string illum){
    this->illum = illum;
    for (size_t i = 0; i < this->meshes.size(); i++) {
        this->meshes[i].setIlluminationName(illum);
    }
}
