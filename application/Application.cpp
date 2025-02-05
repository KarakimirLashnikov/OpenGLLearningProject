#include "Application.hpp"
#include <type_traits>

// static instance of Application
Application* Application::s_Instance{ nullptr };
Application::Visitor Application::s_CallbackVisitor{};

Application::Application()
    : m_WindowHandle{ nullptr }
{
}

void Application::registrationCallback(GLFWwindow* window)
{
    auto framebufferResizeCallback{
        [](GLFWwindow* window, int width, int height)->void {
        Application::CALLBACK_FUNCTION(CallbackType::Resize, width, height); }
    };
    auto keyPressedCallback{
        [](GLFWwindow* window, int key, int scancode, int action, int mods)->void {
        Application::CALLBACK_FUNCTION(CallbackType::KeyPress, key, scancode, action, mods); }
    };
    auto mousClickCallback{ [](GLFWwindow* window, int button, int action, int mods)->void {
        Application::CALLBACK_FUNCTION(CallbackType::MouseClick, button, action, mods); }
    };
    auto cursorPosCallback{ [](GLFWwindow* window, double xpos, double ypos)->void {
        Application::CALLBACK_FUNCTION(CallbackType::CursorPos, xpos, ypos); }
    };
    auto mouseScrollCallback{ [](GLFWwindow* window, double xoffset, double yoffset)->void {
        Application::CALLBACK_FUNCTION(CallbackType::MouseScroll, xoffset, yoffset); }
    };
    glfwSetFramebufferSizeCallback(window, framebufferResizeCallback);
    glfwSetKeyCallback(window, keyPressedCallback);
    glfwSetMouseButtonCallback(window, mousClickCallback);
    glfwSetCursorPosCallback(window, cursorPosCallback);
    glfwSetScrollCallback(window, mouseScrollCallback);
}

Application* Application::GetInstance()
{
    if (s_Instance == nullptr)
    {
        s_Instance = new Application();
    }
    return s_Instance;
}

Application::~Application()
{
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

    this->m_WindowHandle = glfwCreateWindow(width, height, title, nullptr, nullptr);
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
    if (s_Instance != nullptr)
        delete s_Instance;
    s_Instance = nullptr;
    glfwTerminate();
    return true;
}
