#ifndef CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED

#include "GL\glm\ext.hpp"
#include "GL\glad.h"
#include "GL\glfw3.h"

enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.7f;
const float ZOOM = 45.0f;

class Camera {
public:
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;

    float Yaw;
    float Pitch;

    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;

    Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch);
    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);

    void SetPositionByAngles(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);
    void SetPositionByLookAt(float posX, float posY, float posZ, float targetX, float targetY, float targetZ);

    glm::mat4 GetViewMatrix();

    void ProcessKeyboard(Camera_Movement direction, float deltaTime);
    void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch);
    void ProcessMouseScroll(float yoffset);

private:
    void updateCameraVectors();
};

#endif // CAMERA_H_INCLUDED
