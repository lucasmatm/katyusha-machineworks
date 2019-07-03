#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
 #include <SCL.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string.h>
#include <Mesh.h>
// #include <loader.h>

#define degreesToRadians(x) x*(3.141592f/180.0f)

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

typedef struct {
    bool keys[1024];
    GLfloat x, lastx, y, lasty;
}input_info;


int main(int argc, char const *argv[]) {

    int width = 800, height = 600;
    input_info input;

    if (argc < 2){
        std::cout << "ERROR::NO OBJECT TO LOAD::USE:" << argv[0] << " OBJ.obj" << std::endl;
        return -1;
    }

    ////========================================================================================================================////
    ////**************************************************INICIALIZACAO DO OPENGL***********************************************////
    ////========================================================================================================================////

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow *window = glfwCreateWindow(width, height,  "Window", NULL, NULL);


    if(window == GL_FALSE){
        std::cout<<"ERROR::GLFW WINDOW::CREATION ERROR"<<std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);


	// Inicializando glad
	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// Cria viewport
	glViewport(0, 0, width, height);
    glEnable(GL_DEPTH_TEST);

    glfwSetWindowUserPointer(window, &input);
    glfwSetKeyCallback(window, key_callback);

    ////========================================================================================================================////
    ////***************************************************SHADER FILES SETUP***************************************************////
    ////========================================================================================================================////

    SCL ourShader("shaders/objectShader.vert", "shaders/objectShader.frag"); // Communism
    ourShader.use();





    ////========================================================================================================================////
    ////*******************************************************LOAD OBJ*********************************************************////
    ////========================================================================================================================////


    objl::Loader object.LoadFile(obj);

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


    ////==============================================================================////
    ////*********************************GAME LOOP************************************////
    ////==============================================================================////


    while(!glfwWindowShouldClose(window)){

        // Poll events
        glfwPollEvents();


        // Clear Screen
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ////==============================================================================////
        ////*********************************RENDERING************************************////
        ////==============================================================================////

        // ourLoader.draw(ourShader.ID());

        ////==============================================================================////
        ////********************************SWAP BUFFERS**********************************////
        ////==============================================================================////

        glfwSwapBuffers(window);

    }


    return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode){
    if(key == GLFW_KEY_ESCAPE){
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}
