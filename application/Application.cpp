#include "Application.hpp"

// static instance of Application
Application* Application::s_Instance{ nullptr };
std::mutex Application::s_InstanceMutex{};
using std::size_t;

Application::Application()
    : m_WindowHandle{ nullptr }
    , m_Signals{ static_cast<size_t>(SignalType::SignalCount) }
{
    for (size_t i = 0; i < m_Signals.size(); ++i) {
        m_Signals[i].resizeCallback = nullptr;
        m_Signals[i].keyPressedCallback = nullptr;
    }
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
    auto resizeCallback = self->m_Signals[SignalType::Resize].resizeCallback;
    if (resizeCallback != nullptr)
    {
        resizeCallback(width, height);
    }
    self->SetWindowSize(width, height);
}

void Application::keyPressedCallback(
    GLFWwindow* window, int key, int scancode, int action, int mods)
{
    auto self{ static_cast<Application*>(glfwGetWindowUserPointer(window)) };
    auto keyCallback = self->m_Signals[SignalType::KeyPress].keyPressedCallback;
    if (keyCallback != nullptr)
    {
        keyCallback(key, scancode, action, mods);
    }
}

void Application::mousClickCallback(GLFWwindow* window, int button, int action, int mods)
{
    auto self{ static_cast<Application*>(glfwGetWindowUserPointer(window)) };
    auto mouseCallback = self->m_Signals[SignalType::MouseClick].mouseClickCallback;
    if (mouseCallback != nullptr)
    {
        mouseCallback(button, action, mods);
    }
}

void Application::cursorPosCallback(GLFWwindow* window, double xpos, double ypos)
{
    auto self{ static_cast<Application*>(glfwGetWindowUserPointer(window)) };
    auto cursorPosCallback = self->m_Signals[SignalType::CursorPos].cursorPosCallback;
    if (cursorPosCallback != nullptr)
    {
        cursorPosCallback(xpos, ypos);
    }
}

void Application::mouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
    auto self{ static_cast<Application*>(glfwGetWindowUserPointer(window)) };
    auto mouseScrollCallback = self->m_Signals[SignalType::MouseScroll].mouseScrollCallback;
    if (mouseScrollCallback != nullptr)
    {
        mouseScrollCallback(xoffset, yoffset);
    }
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

void Application::SetWindowSize(uint32_t width, uint32_t height)
{
    this->m_WindowWidth = width;
    this->m_WindowHeight = height;
}

bool Application::Initialize(uint32_t width, uint32_t height, const char* title)
{
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
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
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(this->m_WindowHandle);

    // load OpenGL functions
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD" << std::endl;
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


void Application::SetCallbacks(SignalType type, void* callback)
{
    assert(type < SignalCount);
    switch (type) {
    case Resize:
        m_Signals[type].resizeCallback = reinterpret_cast<void (*)(int, int)>(callback);
        break;
    case KeyPress:
        m_Signals[type].keyPressedCallback = reinterpret_cast<void (*)(int, int, int, int)>(callback);
        break;
    case MouseClick:
        m_Signals[type].mouseClickCallback = reinterpret_cast<void (*)(int, int, int)>(callback);
        break;
    case CursorPos:
        m_Signals[type].cursorPosCallback = reinterpret_cast<void (*)(double, double)>(callback);
        break;
    case MouseScroll:
        m_Signals[type].mouseScrollCallback = reinterpret_cast<void (*)(double, double)>(callback);
        break;
    default:
        assert(false);
        break;
    }
}
