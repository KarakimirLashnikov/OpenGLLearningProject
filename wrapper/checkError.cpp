#include "checkError.hpp"
#include <string>
#include <iostream>
#include <cassert>

// check for errors in OpenGL calls
void checkError()
{
    GLenum errorCode{ glGetError() };
    if (errorCode != GL_NO_ERROR)
    {
        std::string error{};
        switch (errorCode)
        {
        case GL_INVALID_ENUM:
            error = "GL_INVALID_ENUM";
            break;
        case GL_INVALID_VALUE:
            error = "GL_INVALID_VALUE";
            break;
        case GL_INVALID_OPERATION:
            error = "GL_INVALID_OPERATION";
            break;
        case GL_STACK_OVERFLOW:
            error = "GL_STACK_OVERFLOW";
            break;
        case GL_STACK_UNDERFLOW:
            error = "GL_STACK_UNDERFLOW";
            break;
        case GL_OUT_OF_MEMORY:
            error = "GL_OUT_OF_MEMORY";
            break;
        case GL_INVALID_FRAMEBUFFER_OPERATION:
            error = "GL_INVALID_FRAMEBUFFER_OPERATION";
            break;
        default:
            error = "Unknown Error";
            break;
        }
        std::cerr << "Error: " << error << std::endl;
        assert(false);
    }
}

void shaderCheckError(GLuint shader, CHECK_ERROR_TYPE type)
{
    // check for errors in the shader compilation
    auto checkCompileError{ [](GLuint shader) -> void {
        GLint success{};
        GLchar infoLog[::MAX_LOG_SIZE];
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, ::MAX_LOG_SIZE, nullptr, infoLog);
            std::cerr << "Error: Shader Compilation failed\n" << infoLog << std::endl;
            assert(false);
        }
        }
    };
    // check for errors in the program linking
    auto checkLinkError{ [](GLuint program) -> void {
        GLint success{};
        GLchar infoLog[::MAX_LOG_SIZE];
        glGetProgramiv(program, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(program, ::MAX_LOG_SIZE, nullptr, infoLog);
            std::cerr << "Error: Program Linking failed\n" << infoLog << std::endl;
            assert(false);
        }
        }
    };

    // entry point, choose check type
    switch (type)
    {
    case CHECK_ERROR_TYPE::COMPILE_ERROR:
        checkCompileError(shader);
        break;
    case CHECK_ERROR_TYPE::LINK_ERROR:
        checkLinkError(shader);
        break;
    default: // should never happen
        std::cerr << "Error: Invalid check type" << std::endl;
        assert(false);
    }
}
