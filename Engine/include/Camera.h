#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "imgui_internal.h"
class CameraClass
{
public:
    glm::vec3 Position = {  0.0f, 0.0f,  3.0f };
    glm::vec3 Front = {  0.0f, 0.0f, -1.0f };
    glm::vec3 Up = {  0.0f, 1.0f,  0.0f };

    float Yaw = -90.0f;
    float Pitch = 0.0f;
    float Speed = 30.0f;
    float Fov = 45.0f;

    glm::mat4 GetView() const
    {
        return glm::lookAt(Position, Position + Front, Up);
    }

    glm::mat4 GetProjection(float aspectRatio) const
    {
        return glm::perspective(glm::radians(Fov), aspectRatio, 0.1f, 1000.0f);
    }

    void UpdateDirection(float dx, float dy)
    {        Yaw   += dx * 0.1f;
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
        glm::vec3 target = Position;

        switch(key)
        {
            case 'W': target -= Up * Speed * deltaTime; break;
            case 'S': target += Up * Speed * deltaTime; break;
            case 'A': target -= right * Speed * deltaTime; break;
            case 'D': target += right * Speed * deltaTime; break;
            default: break;
        }

        Position = ImLerp(Position, target, 15.0f * deltaTime);
    }
};

extern CameraClass Camera;