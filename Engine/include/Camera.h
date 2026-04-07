#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class CameraClass
{
public:
    glm::vec3 Position = {  0.0f, 0.0f,  3.0f };
    glm::vec3 Front = {  0.0f, 0.0f, -1.0f };
    glm::vec3 Up = {  0.0f, 1.0f,  0.0f };

    float Yaw = -90.0f;
    float Pitch =   0.0f;
    float Speed =   5.0f;
    float Fov =  45.0f;

    glm::mat4 GetView() const
    {
        return glm::lookAt(Position, Position + Front, Up);
    }

    glm::mat4 GetProjection(float aspectRatio) const
    {
        return glm::perspective(glm::radians(Fov), aspectRatio, 0.1f, 1000.0f);
    }

    void UpdateDirection(float dx, float dy)
    {
        Yaw   += dx * 0.1f;
        Pitch  = glm::clamp(Pitch + dy * 0.1f, -89.0f, 89.0f);

        Front = glm::normalize(glm::vec3(
            cos(glm::radians(Yaw)) * cos(glm::radians(Pitch)),
            sin(glm::radians(Pitch)),
            sin(glm::radians(Yaw)) * cos(glm::radians(Pitch))
        ));
    }

    void Move(int key, float deltaTime, bool SceneActive)
    {
        if(!SceneActive)
            return;
            
        glm::vec3 right = glm::normalize(glm::cross(Front, Up));

        if (key == 87) Position += Front * Speed * deltaTime;
        if (key == 83) Position -= Front * Speed * deltaTime;
        if (key == 65) Position -= right * Speed * deltaTime;
        if (key == 68) Position += right * Speed * deltaTime;
    }
};

extern CameraClass Camera;