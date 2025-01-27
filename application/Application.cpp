#include "Application.hpp"

// static instance of Application
Application* Application::s_Instance{ nullptr };
std::mutex Application::s_InstanceMutex{};

Application::Application()
    : m_WindowHandle{ nullptr }
    , m_ResizeCallback{ nullptr }
    , m_KeyPressCallback{ nullptr }
{
}

void Application::framebufferResizeCallback(GLFWwindow* window, int width, int height)
{
    auto self{ static_cast<Application*>(glfwGetWindowUserPointer(window)) };
    if (self->m_ResizeCallback != nullptr)
    {
        self->m_ResizeCallback(width, height);
    }
    self->SetWindowWidth(width);
    self->SetWindowHeight(height);
}

void Application::keyPressedCallback(
    GLFWwindow* window, int key, int scancode, int action, int mods)
{
    auto self{ static_cast<Application*>(glfwGetWindowUserPointer(window)) };
    if (self->m_KeyPressCallback != nullptr)
    {
        self->m_KeyPressCallback(key, scancode, action, mods);
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

void Application::SetWindowWidth(uint32_t width)
{
    this->m_WindowWidth = width;
}

void Application::SetWindowHeight(uint32_t height)
{
    this->m_WindowHeight = height;
}

void Application::SetResizeCallback(ResizeCallback callback)
{
    this->m_ResizeCallback = callback;
}

void Application::SetKeyPressCallback(KeyPressCallback callback)
{
    this->m_KeyPressCallback = callback;
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

    glfwSetFramebufferSizeCallback(this->m_WindowHandle, framebufferResizeCallback);
    glfwSetKeyCallback(this->m_WindowHandle, keyPressedCallback);
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
