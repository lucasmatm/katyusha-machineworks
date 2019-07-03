#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <GLFW/glfw3.h>
#include <string>
// #include <glfwKeys.h>

class GLWindow {

public:
    GLWindow();
    GLWindow(std::string);
    GLWindow(std::string, int width,int height);
    GLWindow(std::string, int width,int height, int min_version, int max_version);
    void setLocalData(void *customData);
    void makeWindowCurrent();
    bool shouldClose();
    void input();
    void setKeyboardInput(void (*keyboard_input)(GLWindow*, bool*,void*,float));
    void setMouseInput(void (*mouse_input)(GLWindow*,int current_x,int current_y,int last_x,int last_y,void*,float deltaTime));
    void setScrollInput(void (*scroll_input)(GLWindow*,int,int,void*,float));
    void setShouldClose(bool);
    int getWindowWidth();
    int getWindowHeight();
    void set_keyboard(int key, bool press);
    void set_mouse(int xpos, int ypos);
    void set_scroll(int xoffset, int yoffset);
    void set_mouse_button(int button, int mods);
    void swap_buffers();
    float getDeltaTime();
    float getTime();
private:
    GLint width;
    GLint height;
    bool fullscreen;
    std::string window_name;
    GLFWwindow* window;
    // bool deltaTime;
    bool keys[1024];
    int lastMousePos[2];
    int curMousePos[2];
    int scrolloffset[2];
    unsigned char mouse_buttons[8];
    float deltaTime, lastFrame;
    void* customData;
    bool firstMouse;
    // void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
    // void mouse_callback(GLFWwindow* window, double xpos, double ypos);
    // void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
    void (*key_action)(GLWindow *window, bool *keys, void *customData, float deltaTime);
    void (*mouse_action)(GLWindow *window, int xpos, int ypos, int lastx, int lasty, void *customData, float deltaTime);
    void (*scroll_action)(GLWindow *window, int xoffset, int yoffset, void *customData, float deltaTime);
    void (*mbutton_action)(GLWindow *window, int button, int action, void *customData, int mod);

protected:

};


#endif
