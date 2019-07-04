#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <SCL.h>

// #include <glm/glm.hpp>
// #include <glm/gtc/matrix_transform.hpp>
// #include <glm/gtc/type_ptr.hpp>
#include <string.h>
#include <Mesh.h>
#include <Camera.h>
#include <loader.h>




#define degreesToRadians(x) x*(3.141592f/180.0f)

typedef struct {
    bool keys[1024];
    GLfloat x, lastx, y, lasty;
    bool firstMouse;
}input_info;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void keyAction(Camera *ourCamera, input_info *input);
void mouseAction(Camera *ourCamera, input_info *input);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);



int main(int argc, char const *argv[]) {

    int width = 800, height = 600;
    input_info input;
    for (size_t i = 0; i < 1024; i++) {
        input.keys[i] = false;
    }
    input.firstMouse = false;

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

    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, mouse_callback);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glfwSetWindowUserPointer(window, &input);

    ////========================================================================================================================////
    ////***************************************************SHADER FILES SETUP***************************************************////
    ////========================================================================================================================////

    SCL ourShader("shaders/objectShader.vert", "shaders/objectShader.frag"); // Communism
    ourShader.use();


    ////========================================================================================================================////
    ////*******************************************************LOAD OBJ*********************************************************////
    ////========================================================================================================================////


    loader ourLoader(argv[1]);


    ////========================================================================================================================////
    ////*****************************************************CAMERA SETUP*******************************************************////
    ////========================================================================================================================////


    Camera ourCamera(glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    ourCamera.setApectRatio(((GLfloat)width/(GLfloat)height));
    ourCamera.setPerspective(0.1f, 100.0f);


    ////========================================================================================================================////
    ////*****************************************************CUBE SETUP*********************************************************////
    ////========================================================================================================================////

    GLfloat cubeVertice[] = {
                // Positions          // Normals           // Texture Coords
              -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
               0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
               0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
               0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
              -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
              -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

              -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
               0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
               0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
               0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
              -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
              -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

              -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
              -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
              -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
              -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
              -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
              -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

               0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
               0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
               0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
               0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
               0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
               0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

              -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
               0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
               0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
               0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
              -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
              -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

              -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
               0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
               0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
               0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
              -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
              -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
    };

    GLuint VAO, VBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertice), cubeVertice, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
        glEnableVertexAttribArray(1);

        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
        glEnableVertexAttribArray(2);


    glBindVertexArray(0);


    ////==============================================================================////
    ////*********************************GAME LOOP************************************////
    ////==============================================================================////



    while(!glfwWindowShouldClose(window)){

        // Poll events
        glfwPollEvents();
        keyAction(&ourCamera, &input);
        mouseAction(&ourCamera, &input);

        // Clear Screen
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ////==============================================================================////
        ////*********************************RENDERING************************************////
        ////==============================================================================////

        ourShader.use();
        // glm::mat4 projection = glm::perspective(ourCamera.Zoom, (float)width/(float)height, 0.1f, 100.0f);
        glm::mat4 projection = ourCamera.getPerspective();
        glm::mat4 view = ourCamera.getCameraMatrix();
        glUniformMatrix4fv(glGetUniformLocation(ourShader.ID(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(ourShader.ID(), "view"), 1, GL_FALSE, glm::value_ptr(view));

        // Draw the loaded model
        glm::mat4 model(1.0);
        model = glm::translate(model, glm::vec3(0.0f, -0.5f, 0.0f)); // Translate it down a bit so it's at the center of the scene
        // model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));	// It's a bit too big for our scene, so scale it down
        glUniformMatrix4fv(glGetUniformLocation(ourShader.ID(), "model"), 1, GL_FALSE, glm::value_ptr(model));
        // ourModel.draw(shader);

        ourLoader.draw(ourShader.ID());


        ////==============================================================================////
        ////********************************SWAP BUFFERS**********************************////
        ////==============================================================================////

        glfwSwapBuffers(window);

    }


    return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode){
    input_info* input = static_cast<input_info*>(glfwGetWindowUserPointer(window));

    if(key == GLFW_KEY_ESCAPE){
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
    if(action == GLFW_PRESS){
        input->keys[key] = true;
    }else if(action == GLFW_RELEASE){
        input->keys[key] = false;
    }

}

void mouse_callback(GLFWwindow* window, double xpos, double ypos){
    input_info* input = static_cast<input_info*>(glfwGetWindowUserPointer(window));

    input->lastx = input->x;
    input->lasty = input->y;
    input->x = xpos;
    input->y = ypos;

}

void keyAction(Camera *ourCamera, input_info *input){

    GLfloat xAxis = 0.0f, zAxis = 0.0f;
    if(input->keys[GLFW_KEY_W]){
        zAxis += 1.0f;
    }
    if(input->keys[GLFW_KEY_S]){
        zAxis -= 1.0f;
    }
    if(input->keys[GLFW_KEY_A]){
        xAxis -= 1.0f;
    }
    if(input->keys[GLFW_KEY_D]){
        xAxis += 1.0f;
    }
    ourCamera->moveCamera(xAxis, 0.0f, zAxis);
}

void mouseAction(Camera *ourCamera, input_info *input){
    if(input->firstMouse == true){
        input->lastx = input->x;
        input->lasty = input->y;
        input->firstMouse = false;
    }
    GLfloat xoffset, yoffset;

    xoffset = input->lastx - input->x;
    yoffset = input->lasty - input->y;
    ourCamera->moveCameraDirection(2*xoffset, 2*yoffset);

}
