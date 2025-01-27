#pragma once

#include "wrapper/checkError.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

class Shader
{
    Shader(const Shader& other) = delete;
    Shader(Shader&& other) = delete;
    Shader& operator=(Shader&& other) = delete;
    Shader& operator=(const Shader& other) = delete;
private:
    GLuint m_program{};
public:
    Shader(const char* vertexPath, const char* fragmentPath);
    ~Shader() noexcept;

    void begin() const; // begin use this shader
    void end() const; // end use this shader
};