#pragma once
#include <mutex>
#include "glframework/core.h"
#include "wrapper/checkError.hpp"
#include <iostream>
#include <cassert>

struct GLFWwindow;

using ResizeCallback = void(*)(int, int);
using KeyPressCallback = void(*)(int, int, int, int);

class Application
{
    Application(const Application& other) = delete;
    Application(Application&& other) = delete;
    Application& operator=(const Application& other) = delete;
    Application& operator=(Application&& other) = delete;

private:
    Application();

    static Application* s_Instance;
    static std::mutex s_InstanceMutex;

    static void framebufferResizeCallback(
        GLFWwindow* window, int width, int height);
    static void keyPressedCallback(
        GLFWwindow* window, int key, int scancode, int action, int mods);

private: // member variables
    uint32_t m_WindowWidth{};
    uint32_t m_WindowHeight{};
    GLFWwindow* m_WindowHandle{};

private: // member functions
    ResizeCallback m_ResizeCallback;
    KeyPressCallback m_KeyPressCallback;

public:
    static Application* GetInstance();

    ~Application();

public: // member functions
    // Get
    uint32_t GetWindowWidth() const;
    uint32_t GetWindowHeight() const;

    // Set
    void SetWindowWidth(uint32_t width);
    void SetWindowHeight(uint32_t height);
    void SetResizeCallback(ResizeCallback callback);
    void SetKeyPressCallback(KeyPressCallback callback);

    // logic
    bool Initialize(uint32_t width, uint32_t height, const char* title);
    bool Update();
    bool Destroy();
};

#define theApp Application::GetInstance()