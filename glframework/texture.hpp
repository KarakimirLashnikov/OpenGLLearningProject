#pragma once

#include "core.h"
#include <string_view>

class Texture
{
private:
    GLuint m_objId{};  // opengl texture object
    int m_width{},  // texture width
        m_height{};  // texture height
    GLuint m_unit{};  // texture unit, from 0 to 31 (GL_TEXTURE0 + m_unit)

public:
    Texture(std::string_view path, GLuint uint = 0);
    ~Texture();

    GLuint bind(GLuint texObj);
};