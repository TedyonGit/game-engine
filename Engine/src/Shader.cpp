#include <Shader.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/gtc/type_ptr.hpp>

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
    std::string   vertSrc = ReadFile(vertexPath);
    std::string   fragSrc = ReadFile(fragmentPath);
    const char*   vCode   = vertSrc.c_str();
    const char*   fCode   = fragSrc.c_str();

    // Compile vertex
    unsigned int vert = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vert, 1, &vCode, nullptr);
    glCompileShader(vert);
    CheckErrors(vert, "VERTEX");

    // Compile fragment
    unsigned int frag = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(frag, 1, &fCode, nullptr);
    glCompileShader(frag);
    CheckErrors(frag, "FRAGMENT");

    // Link
    ID = glCreateProgram();
    glAttachShader(ID, vert);
    glAttachShader(ID, frag);
    glLinkProgram(ID);
    CheckErrors(ID, "PROGRAM");

    glDeleteShader(vert);
    glDeleteShader(frag);
}

Shader::~Shader()
{
    glDeleteProgram(ID);
}

void Shader::Bind()   const { glUseProgram(ID); }
void Shader::Unbind() const { glUseProgram(0);  }

void Shader::SetInt(const std::string& name, int value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::SetFloat(const std::string& name, float value) const
{
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::SetVec3(const std::string& name, const glm::vec3& v) const
{
    glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, glm::value_ptr(v));
}

void Shader::SetMat4(const std::string& name, const glm::mat4& m) const
{
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(m));
}

std::string Shader::ReadFile(const char* path)
{
    std::ifstream file;
    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        file.open(path);
        std::stringstream ss;
        ss << file.rdbuf();
        return ss.str();
    }
    catch (std::ifstream::failure& e)
    {
        std::cerr << "Shader file not found: " << path << "\n";
        return "";
    }
}

void Shader::CheckErrors(unsigned int id, const std::string& type)
{
    int  success;
    char log[1024];
    if (type != "PROGRAM")
    {
        glGetShaderiv(id, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(id, 1024, nullptr, log);
            std::cerr << "Shader compile error [" << type << "]:\n" << log << "\n";
        }
    }
    else
    {
        glGetProgramiv(id, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(id, 1024, nullptr, log);
            std::cerr << "Shader link error:\n" << log << "\n";
        }
    }
}