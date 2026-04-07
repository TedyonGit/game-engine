#pragma once
#include <string>
#include <glad/glad.h>
#include <glm/glm.hpp>

class Shader
{
public:
    unsigned int ID;

    Shader(const char* vertexPath, const char* fragmentPath);
    ~Shader();

    void Bind()   const;
    void Unbind() const;

    void SetInt  (const std::string& name, int value)         const;
    void SetFloat(const std::string& name, float value)       const;
    void SetVec3 (const std::string& name, const glm::vec3& v) const;
    void SetMat4 (const std::string& name, const glm::mat4& m) const;

private:
    std::string ReadFile(const char* path);
    void CheckErrors(unsigned int id, const std::string& type);
};