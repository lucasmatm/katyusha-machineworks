#ifndef Camera_H
#define Camera_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stdlib.h>
#include <iostream>

/**  @author Alqotel, 16 de Abril 2016,
  *  @class ACC(Alqotel's Camera Class)
  *  Class for camera control
  */

class Camera
{
    public:
        Camera(glm::vec3 CameraPos, glm::vec3 CameraFront, glm::vec3 CameraUp);
        void setCameraSpeed(GLfloat CameraSpeed);
        void setMouseSpeed(GLfloat MouseSpeed);
        void setApectRatio(GLfloat ApectRatio);
        void setFieldOfView(GLfloat fielOfView);
        void moveCameraDirection(GLfloat xOffSet, GLfloat yOffSet);
        void moveCamera(GLfloat xAxis, GLfloat yAxis, GLfloat zAxis);
        void setPitchLimit(GLfloat PitchLimit);
        void setCameraPosition(GLfloat xAxis, GLfloat yAxis, GLfloat zAxis);
        void setDeltaTime(bool DeltaTimeEnable);
        void zoomInput(GLfloat yAxis);
        void setZoomLimit(GLfloat MinZoom, GLfloat MaxZoom);
        GLfloat getFieldOfView();
        GLfloat getApectRatio();
        glm::mat4 getCameraMatrix();
        glm::mat4 getLookAtZero();
        glm::mat4 getPerspective();
        void setPerspective(GLfloat FOV, GLfloat ASPECT, GLfloat zNear, GLfloat zFar);
        void setPerspective(GLfloat zNear, GLfloat zFar);
        glm::vec3 cameraPos, cameraFront, cameraUp;

    protected:
    private:
        void processData();
        GLfloat fov = 45.0f;
        GLfloat cameraSpeed = 0.5f, xMovement, yMovement, zMovement;
        GLfloat mouseSensitivity = 0.1f;
        GLfloat aspectRatio;
        glm::mat4 view, projection;
        GLfloat xoffset, yoffset;
        GLfloat pitchLimit = 89.0f, pitch, yaw;
        GLfloat deltaTime, currentFrame, lastFrame;
        GLfloat maxZoom = 45.0f, minZoom = 1.0f;
        bool DELTA_TIME;
};

#endif // Camera_H
