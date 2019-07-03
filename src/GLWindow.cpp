#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <GLWindow.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height){
 	glViewport(0, 0, width, height);
}

void std_keyboard(GLWindow* window, bool *keys, void *customData, float deltaTime){
    return;
}
void std_mouse(GLWindow* window, int xpos, int ypos, int lastx, int lasty, void *customData, float deltaTime){
    return;
}
void std_mouse_button(GLWindow* window, int button, void *customData, int action){
    return;
}
void std_scroll(GLWindow*, int xoffset, int yoffset, void *customData, float deltaTime){
    return;
}
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

GLWindow::GLWindow():GLWindow("Window", 800,600,3,3){}
GLWindow::GLWindow(std::string window_name):GLWindow(window_name, 800,600,3,3){}
GLWindow::GLWindow(std::string window_name, int width, int height):GLWindow(window_name, width,height,3,3){}
GLWindow::GLWindow(std::string window_name, int width, int height, int max_version, int min_version){
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, min_version);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, max_version);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    #ifdef _APPLE_
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    this->window = glfwCreateWindow(width, height,  window_name.c_str(), NULL, NULL);
    if (window == NULL){
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }
    glfwSetWindowUserPointer(this->window, this);
    glfwSetKeyCallback(this->window, key_callback);
    glfwSetScrollCallback(this->window, scroll_callback);
    glfwSetCursorPosCallback(this->window, mouse_callback);
    glfwSetMouseButtonCallback(this->window, mouse_button_callback);
    glfwSetFramebufferSizeCallback(this->window, framebuffer_size_callback);
    // this->deltaTime = true; // Delta time always on
    this->firstMouse = true;
    this->lastFrame = glfwGetTime();

    this->key_action = std_keyboard;
    this->mouse_action = std_mouse;
    this->scroll_action = std_scroll;

    glViewport(0, 0, this->width, this->height);

}

void GLWindow::setLocalData(void *customData){
    this->customData = customData;
}


void GLWindow::makeWindowCurrent(){
    glfwMakeContextCurrent(this->window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "Failed to initialize GLAD" << std::endl;
    }
}

bool GLWindow::shouldClose(){
    return (bool)glfwWindowShouldClose(this->window);
}

// void GLWindow::setDeltaTime(bool deltaTime){
//     this->deltaTime = deltaTime;
// }

void GLWindow::input(){
    glfwPollEvents();
    if(this->firstMouse){
        this->lastMousePos[0] = this->curMousePos[0];
        this->lastMousePos[1] = this->curMousePos[1];
        this->firstMouse = false;
    }
    this->deltaTime = glfwGetTime() - this->lastFrame;
    this->lastFrame = glfwGetTime();
    this->key_action(this, this->keys, this->customData, this->deltaTime);
    this->mouse_action(this,this->curMousePos[0], this->curMousePos[1], this->lastMousePos[0], this->lastMousePos[1], this->customData,this->deltaTime);
    this->scroll_action(this, this->scrolloffset[0], this->scrolloffset[1], this->customData, this->deltaTime);
}

void GLWindow::setKeyboardInput(void (*keyboard_input)(GLWindow*, bool*, void*,float)){
    this->key_action = keyboard_input;
}
void GLWindow::setMouseInput(void (*mouse_input)(GLWindow*,int,int,int,int,void*,float)){
    this->mouse_action = mouse_input;
}
void GLWindow::setScrollInput(void (*scroll_input)(GLWindow*,int,int,void*,float)){
    this->scroll_action = scroll_input;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode){
    GLWindow* myWindow = static_cast<GLWindow*>(glfwGetWindowUserPointer(window));
    if(action == GLFW_PRESS){
        myWindow->set_keyboard(key, true);
    }else if(action == GLFW_RELEASE){
        myWindow->set_keyboard(key, false);
    }

}
void mouse_callback(GLFWwindow* window, double xpos, double ypos){
    GLWindow* myWindow = static_cast<GLWindow*>(glfwGetWindowUserPointer(window));
    myWindow->set_mouse(xpos, ypos);
}
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset){
    GLWindow* myWindow = static_cast<GLWindow*>(glfwGetWindowUserPointer(window));
    myWindow->set_scroll(xoffset, yoffset);
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods){
    GLWindow* myWindow = static_cast<GLWindow*>(glfwGetWindowUserPointer(window));
    if(action == GLFW_PRESS){
        myWindow->set_mouse_button(button, (1<<7) + mods);
    }else{
        myWindow->set_mouse_button(button, 0);
    }
}

void GLWindow::setShouldClose(bool should_close){
    if(should_close){
        glfwSetWindowShouldClose(this->window, GL_TRUE);
    }else{
        glfwSetWindowShouldClose(this->window, GL_FALSE);
    }
}

int GLWindow::getWindowHeight(){
    return this->height;
}

int GLWindow::getWindowWidth(){
    return this->width;
}

void GLWindow::set_keyboard(int key, bool action){
    this->keys[key] = action;
}
void GLWindow::set_mouse(int xpos, int ypos){
    this->curMousePos[0] = xpos;
    this->curMousePos[1] = ypos;
}
void GLWindow::set_scroll(int xoffset, int yoffset){
    this->scrolloffset[0] = xoffset;
    this->scrolloffset[1] = yoffset;
}

void GLWindow::set_mouse_button(int button, int mods){
    this->mouse_buttons[button] = mods;
}

void GLWindow::swap_buffers(){
    glfwSwapBuffers(this->window);
}

float GLWindow::getDeltaTime(){
    return this->deltaTime;
}

float GLWindow::getTime(){
    return glfwGetTime();
}
