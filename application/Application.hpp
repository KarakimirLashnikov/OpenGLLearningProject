#pragma once
#include <mutex>
#include "glframework/core.h"
#include "wrapper/checkError.hpp"
#include <unordered_map>
#include <variant>
#include <concepts>
#include <cassert>

struct GLFWwindow;

template <typename T, typename... Args>
concept Callable = requires(T t, Args... args) {
    { t(args...) } -> std::same_as<void>;
};

enum CallbackType {
    Resize = 0,  // must start from 0, window resize signal
    KeyPress = 1,  // key press signal
    MouseClick = 2,  // mouse button click signal
    CursorPos = 3,  // mouse cursor move signal
    MouseScroll = 4,   // mouse scroll signal
    SignalCount = 5 // must be last 
};
union CallbackFunction {
    // must have same variable name with CallbackType, because of #define
    void (*Resize)(int, int);
    void (*KeyPress)(int, int, int, int);
    void (*MouseClick)(int, int, int);
    void (*CursorPos)(double, double);
    void (*MouseScroll)(double, double);
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

    static std::unordered_map<std::size_t, CallbackFunction> s_CallbackMap;

    uint32_t m_WindowWidth{};
    uint32_t m_WindowHeight{};
    GLFWwindow* m_WindowHandle{};

public:
    static Application* GetInstance();

    ~Application();

public: // member functions
    // Get
    uint32_t GetWindowWidth() const;
    uint32_t GetWindowHeight() const;

    // Set
    void SetCallbacks(CallbackType type, void* func);

    void SetWindowSize(uint32_t width, uint32_t height);

    // logic
    bool Initialize(uint32_t width, uint32_t height, const char* title);
    bool Update();
    bool Destroy();
};

#define theApp Application::GetInstance()


