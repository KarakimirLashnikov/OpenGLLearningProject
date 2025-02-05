#pragma once
#include "glframework/core.h"
#include "wrapper/checkError.hpp"
#include <unordered_map>
#include <variant>
#include <functional>
#include <concepts>
#include <cassert>

struct GLFWwindow;

enum class CallbackType {
    Resize = 0,  // must start from 0, window resize signal
    KeyPress = 1,  // key press signal
    MouseClick = 2,  // mouse button click signal
    CursorPos = 3,  // mouse cursor move signal
    MouseScroll = 4,   // mouse scroll signal
    SignalCount = 5 // must be last 
};
//using FunType = std::variant<
//    std::function<void(int, int)>,
//    std::function<void(int, int, int)>,
//    std::function<void(int, int, int, int)>,
//    std::function<void(double, double)>
//>;

using FunType = std::variant<
    void(*)(),
    void(*)(int, int),
    void(*)(int, int, int),
    void(*)(int, int, int, int),
    void(*)(double, double)
>;
template <typename... Args>
using F = std::function<void(Args...)>;

class Application
{
public:
    static Application* GetInstance();
    ~Application();

    // Get
    uint32_t GetWindowWidth() const;
    uint32_t GetWindowHeight() const;

    // Set
    template <typename... Args>
    static void SetCallbacks(CallbackType type, void(*func)(Args...));

    // logic
    bool Initialize(uint32_t width, uint32_t height, const char* title);
    bool Update();
    bool Destroy();

private:
    Application(const Application& other) = delete;
    Application(Application&& other) = delete;
    Application& operator=(const Application& other) = delete;
    Application& operator=(Application&& other) = delete;

    class Visitor {
    public:
        std::unordered_map<int, FunType> m_fun_map;

        template <typename... Args>
        void operator()(int id, Args... args) {
            auto f = m_fun_map[id];
            if (std::holds_alternative<void(*)(Args...)>(f)) {
                std::get<void(*)(Args...)>(f)(args...);
            }
        }
        template <typename... Args>
        void set_fun(int id, void(*f)(Args...)) {
            m_fun_map[id] = f;
        }
        FunType& operator[](int id) {
            return m_fun_map[id];
        }
        FunType& operator[](const CallbackType& type) {
            return m_fun_map[static_cast<int>(type)];
        }

        Visitor() = default;
        ~Visitor() = default;
    private:
        Visitor(const Visitor&) = delete;
        Visitor(Visitor&&) = delete;
        Visitor& operator=(Visitor&&) = delete;
        Visitor& operator=(const Visitor&) = delete;
    };

private:
    Application();

    static Application* s_Instance;

    static void registrationCallback(GLFWwindow* window);

    static Visitor s_CallbackVisitor;

    template <typename... Args>
    static void CALLBACK_FUNCTION(CallbackType type, Args... args)
    {
        int index{ static_cast<int>(type) };
        Application::s_CallbackVisitor(index, args...);
    }

    GLFWwindow* m_WindowHandle{};
};

#define theApp Application::GetInstance()

template<typename ...Args>
inline void Application::SetCallbacks(CallbackType type, void(*func)(Args...))
{
    int index{ static_cast<int>(type) };
    assert(index < static_cast<int>(CallbackType::SignalCount) && index >= 0);
    Application::s_CallbackVisitor.set_fun(index, func);
}
