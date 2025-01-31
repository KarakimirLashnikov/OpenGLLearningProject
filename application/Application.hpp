#pragma once
#include <mutex>
#include "glframework/core.h"
#include "wrapper/checkError.hpp"
#include <iostream>
#include <vector>
#include <variant>
#include <functional>
#include <concepts>
#include <cassert>

struct GLFWwindow;

template <typename T, typename... Args>
concept Callable = requires(T t, Args... args) {
    { t(args...) } -> std::same_as<void>;
};

enum SignalType {
    Resize = 0,  // must start from 0, window resize signal
    KeyPress,  // key press signal
    MouseClick,  // mouse button click signal
    CursorPos,  // mouse cursor move signal
    MouseScroll,   // mouse scroll signal
    SignalCount  // must be last 
};
union SignalCallback {
    void (*resizeCallback)(int, int);
    void (*keyPressedCallback)(int, int, int, int);
    void (*mouseClickCallback)(int, int, int);
    void (*cursorPosCallback)(double, double);
    void (*mouseScrollCallback)(double, double);
};

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

    static void registrationCallback(GLFWwindow* window);
    static void framebufferResizeCallback(
        GLFWwindow* window, int width, int height);
    static void keyPressedCallback(
        GLFWwindow* window, int key, int scancode, int action, int mods);
    static void mousClickCallback(
        GLFWwindow* window, int button, int action, int mods);
    static void cursorPosCallback(
        GLFWwindow* window, double xpos, double ypos);
    static void mouseScrollCallback(
        GLFWwindow* window, double xoffset, double yoffset);

    uint32_t m_WindowWidth{};
    uint32_t m_WindowHeight{};
    GLFWwindow* m_WindowHandle{};

    std::vector<SignalCallback> m_Signals;

public:
    static Application* GetInstance();

    ~Application();

public: // member functions
    // Get
    uint32_t GetWindowWidth() const;
    uint32_t GetWindowHeight() const;

    // Set
    void SetCallbacks(SignalType type, void* callback);

    void SetWindowSize(uint32_t width, uint32_t height);

    // logic
    bool Initialize(uint32_t width, uint32_t height, const char* title);
    bool Update();
    bool Destroy();
};

#define theApp Application::GetInstance()
