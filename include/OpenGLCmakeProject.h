// OpenGLCmakeProject.h: 标准系统包含文件的包含文件
// 或项目特定的包含文件。

#pragma once

// TODO: 在此处引用程序需要的其他标头。
#include "glframework/core.h"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "SOIL2/stb_image.h"
#include "application/Application.hpp"
#include "glframework/Shader.hpp"

// cpp library
#include <memory>
using Shader_ptr = std::shared_ptr<Shader>;

// const variable
constexpr int WindowWidth{ 1280 };
constexpr int WindowHeight{ 720 };
constexpr const char* WindowTitle{ "OpenGLCmakeProject" };