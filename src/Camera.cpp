#include "Camera.h"

float getNorma(glm::vec3 vec){
    return sqrt(pow(vec.x, 2) + pow(vec.y, 2) + pow(vec.z, 2));
}

Camera::Camera(glm::vec3 CameraPos, glm::vec3 CameraFront, glm::vec3 CameraUp){
    this->cameraUp = CameraUp;
    this->cameraPos = CameraPos;
    this->cameraFront = CameraFront;
    this->view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
    this->fov = 45.0f;
    this->cameraSpeed = 0.5f;
    this->mouseSensitivity = 0.1f;
    this->pitchLimit = 89.0f;
    this->maxZoom = 45.0f;
    this->minZoom = 1.0f;
    this->xoffset = 0;
    this->yoffset = 0;
    float aux = glm::dot(glm::vec3(0.0, CameraFront.y, CameraFront.z), glm::vec3(0.0,0.0, 1.0))/(getNorma(glm::vec3(0.0, CameraFront.y, CameraFront.z)) * getNorma(glm::vec3(0.0,0.0,1.0)));
    this->pitch = acos(aux);
    aux = glm::dot(glm::vec3(CameraFront.x, 0.0, CameraFront.z), glm::vec3(0.0,0.0, 1.0))/(getNorma(glm::vec3(CameraFront.x, 0.0, CameraFront.z)) * getNorma(glm::vec3(0.0,0.0,1.0)));
    this->yaw = acos(aux);
    DELTA_TIME = true;
}

void Camera::setCameraSpeed(GLfloat CameraSpeed){
    cameraSpeed = CameraSpeed;
}

void Camera::setMouseSpeed(GLfloat MouseSpeed){
    mouseSensitivity = MouseSpeed;
}

void Camera::setApectRatio(GLfloat AspectRatio){
    aspectRatio = AspectRatio;
}

void Camera::setFieldOfView(GLfloat fieldOfView){
    fov = fieldOfView;
}

void Camera::moveCameraDirection(GLfloat xOffSet, GLfloat yOffSet){

    xoffset = xOffSet;
    yoffset = yOffSet;
}

void Camera::moveCamera(GLfloat xAxis, GLfloat yAxis, GLfloat zAxis){
    xMovement = xAxis;
    yMovement = yAxis;
    zMovement = zAxis;
}

void Camera::setPitchLimit(GLfloat PitchLimit){
    pitchLimit = PitchLimit;
}

void Camera::setCameraPosition(GLfloat xAxis, GLfloat yAxis, GLfloat zAxis){
    cameraPos = glm::vec3(xAxis, yAxis, zAxis);
}

void Camera::setDeltaTime(bool DeltaTimeEnable){
    DELTA_TIME = DeltaTimeEnable;
}

void Camera::zoomInput(GLfloat yAxis){
    fov -= yAxis;
    if(fov < minZoom){
        fov = minZoom;
    }
    if(fov > maxZoom){
        fov = maxZoom;
    }
}

void Camera::setZoomLimit(GLfloat MinZoom, GLfloat MaxZoom){
    if(MaxZoom <= 180.0f){
        maxZoom = MaxZoom;
    }
    if(MinZoom >= 1.0f){
        minZoom = MinZoom;
    }
}

GLfloat Camera::getFieldOfView(){
    return glm::radians(fov);
}

GLfloat Camera::getApectRatio(){
    return aspectRatio;
}

glm::mat4 Camera::getCameraMatrix(){
    this->processData();
    view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
    return view;
}

glm::mat4 Camera::getLookAtZero(){
    return glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
}

glm::mat4 Camera::getPerspective(){
    return projection;
}

void Camera::processData(){

////**************MOUSE MOVEMENT********************////

////*****DELTA TIME******////
    if(DELTA_TIME){
        currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        deltaTime *= 10.0f;
    }else{
        deltaTime = 1.0f;
    }
////****END DELTA TIME***////

    pitch += yoffset * mouseSensitivity;
    yaw   += xoffset * mouseSensitivity;
    xoffset = 0.0f;
    yoffset = 0.0f;
    if(pitch > 89.0f){
        pitch = 89.0f;
    }
    if(pitch < -89.0f){
        pitch = -89.0f;
    }
    glm::vec3 front;
    front.x = cos(glm::radians(pitch)) * sin(glm::radians(yaw)) * deltaTime;
    front.y = sin(glm::radians(pitch)) * deltaTime;
    front.z = cos(glm::radians(pitch)) * cos(glm::radians(yaw)) * deltaTime;
    cameraFront = glm::normalize(front);
////***************END MOUSE MOVEMENT**************////

////***************CAMERA MOVEMENT*****************////
    cameraPos += cameraFront * zMovement * cameraSpeed * deltaTime;
    cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed *xMovement * deltaTime;
////*************END CAMERA MOVEMENT***************////

}

void Camera::setPerspective(GLfloat FOV, GLfloat ASPECT, GLfloat zNear, GLfloat zFar){
    if(!FOV){
        FOV = fov;
    }
    if(!ASPECT){
        ASPECT = aspectRatio;
    }
    projection = glm::perspective(glm::radians(FOV), ASPECT, zNear, zFar);
}

void Camera::setPerspective(GLfloat zNear, GLfloat zFar){
    projection = glm::perspective(glm::radians(fov), aspectRatio, zNear, zFar);
}


//glm::mat4 Camera::getCamera(GLfloat deltaTime){
//    return view;
//}
