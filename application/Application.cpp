#include "Application.hpp"
#include <type_traits>

// static instance of Application
Application* Application::s_Instance{ nullptr };
std::unordered_map<std::size_t, CallbackFunction> Application::s_CallbackMap{};
std::mutex Application::s_InstanceMutex{};
using std::size_t;

#define CALLBACK_FUNCTION(type, ...) std::size_t index{ static_cast<std::size_t>(type)} ; if (Application::s_CallbackMap.find(index) != Application::s_CallbackMap.end()) {CallbackFunction __callback_func_##type{ Application::s_CallbackMap[index] }; __callback_func_##type.##type(__VA_ARGS__); }

Application::Application()
    : m_WindowHandle{ nullptr }
{
}

void Application::registrationCallback(GLFWwindow* window)
{
    glfwSetFramebufferSizeCallback(window, framebufferResizeCallback);
    glfwSetKeyCallback(window, keyPressedCallback);
    glfwSetMouseButtonCallback(window, mousClickCallback);
    glfwSetCursorPosCallback(window, cursorPosCallback);
    glfwSetScrollCallback(window, mouseScrollCallback);
}

void Application::framebufferResizeCallback(GLFWwindow* window, int width, int height)
{
    auto self{ static_cast<Application*>(glfwGetWindowUserPointer(window)) };
    CALLBACK_FUNCTION(Resize, width, height);
    self->SetWindowSize(width, height);
}

void Application::keyPressedCallback(
    GLFWwindow* window, int key, int scancode, int action, int mods)
{
    CALLBACK_FUNCTION(KeyPress, key, scancode, action, mods);
}

void Application::mousClickCallback(GLFWwindow* window, int button, int action, int mods)
{
    CALLBACK_FUNCTION(MouseClick, button, action, mods);
}

void Application::cursorPosCallback(GLFWwindow* window, double xpos, double ypos)
{
    CALLBACK_FUNCTION(CursorPos, xpos, ypos);
}

void Application::mouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
    CALLBACK_FUNCTION(MouseScroll, xoffset, yoffset);
}

Application* Application::GetInstance()
{
    std::lock_guard<std::mutex> lock(s_InstanceMutex);
    if (s_Instance == nullptr)
    {
        s_Instance = new Application();
    }
    return s_Instance;
}

Application::~Application()
{
}

uint32_t Application::GetWindowWidth() const
{
    return this->m_WindowWidth;
}

uint32_t Application::GetWindowHeight() const
{
    return this->m_WindowHeight;
}

#define SET_CALLBACK_FUNC(type, index, func) s_CallbackMap[index].##type = func

void Application::SetCallbacks(CallbackType type, void* func)
{
    std::size_t index{ static_cast<std::size_t>(type) };
    switch (type) {
    case CallbackType::Resize:
        SET_CALLBACK_FUNC(Resize, index, reinterpret_cast<void(*)(int, int)>(func));
        break;
    case CallbackType::KeyPress:
        SET_CALLBACK_FUNC(KeyPress, index, reinterpret_cast<void(*)(int, int, int, int)>(func));
        break;
    case CallbackType::MouseClick:
        SET_CALLBACK_FUNC(MouseClick, index, reinterpret_cast<void(*)(int, int, int)>(func));
        break;
    case CallbackType::CursorPos:
        SET_CALLBACK_FUNC(CursorPos, index, reinterpret_cast<void(*)(double, double)>(func));
        break;
    case CallbackType::MouseScroll:
        SET_CALLBACK_FUNC(MouseScroll, index, reinterpret_cast<void(*)(double, double)>(func));
        break;
    default:
        // invalid callback type
        assert(false);
        break;
    }
}

void Application::SetWindowSize(uint32_t width, uint32_t height)
{
    this->m_WindowWidth = width;
    this->m_WindowHeight = height;
}

bool Application::Initialize(uint32_t width, uint32_t height, const char* title)
{
    if (!glfwInit())
    {
        // glfw failed to initialize
        assert(false);
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    // use OpenGL core profile
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    this->m_WindowWidth = width;
    this->m_WindowHeight = height;
    this->m_WindowHandle = glfwCreateWindow(
        this->m_WindowWidth, this->m_WindowHeight, title, nullptr, nullptr);
    if (this->m_WindowHandle == nullptr)
    {
        // glfw window creation failed
        assert(false);
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(this->m_WindowHandle);

    // load OpenGL functions
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        // glad failed to load OpenGL functions
        assert(false);
        glfwTerminate();
        return false;
    }

    registrationCallback(this->m_WindowHandle);
    glfwSetWindowUserPointer(this->m_WindowHandle, this);

    return true;
}

bool Application::Update()
{
    if (glfwWindowShouldClose(this->m_WindowHandle)) {
        return false;
    }
    glfwPollEvents();
    glfwSwapBuffers(this->m_WindowHandle);
    return true;
}

bool Application::Destroy()
{
    std::lock_guard<std::mutex> lock(s_InstanceMutex);
    if (s_Instance != nullptr)
        delete s_Instance;
    s_Instance = nullptr;
    glfwTerminate();
    return true;
}
