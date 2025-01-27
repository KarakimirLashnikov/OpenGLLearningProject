#pragma once
#include "glframework/core.h"

#ifdef DEBUG
#define GLCALL(func) func; checkError()
#define SHADERCHECK(shader, type) shaderCheckError(shader, type)
#else
#define GLCALL(func) func
#define SHADERCHECK(shader, type) ;
#endif

enum class CHECK_ERROR_TYPE {
    COMPILE_ERROR, // shader compile error
    LINK_ERROR // shader link error
};


constexpr int MAX_LOG_SIZE = 1024;
void checkError();
void shaderCheckError(GLuint shader, CHECK_ERROR_TYPE type);