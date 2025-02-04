// OpenGLCmakeProject.h: 标准系统包含文件的包含文件
// 或项目特定的包含文件。

#pragma once

// TODO: 在此处引用程序需要的其他标头。
#include "glframework/core.h"
#include "application/Application.hpp"
#include "glframework/Shader.hpp"
#include "glframework/texture.hpp"
#include "application/camera/PerspectiveCamera.hpp"
#include "application/camera/GameCameraControl.hpp"

#define STB_IMAGE_IMPLEMENTATION
// cpp library
#include <memory>
using Shader_ptr = std::shared_ptr<Shader>;
using Camera_ptr = std::unique_ptr<PerspectiveCamera>;
using Texture_ptr = std::shared_ptr<Texture>;

// const variable
constexpr int WindowWidth{ 1280 };
constexpr int WindowHeight{ 720 };
constexpr const char* WindowTitle{ "OpenGLCmakeProject" };

// function
#include "OpenGLCmakeProject.h"

void MyResize(int width, int height);

void MyKeyPress(int key, int scancode, int action, int modifiers);

void MyMouseClick(int button, int action, int mods);

void MyMouseScroll(double xoffset, double yoffset);

void MyCursorPos(double x, double y);

void prepare();

void render();

void cleanup();