#pragma once

#include "wrapper/checkError.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <string_view>
#include <concepts>
#include <cassert>
#include <type_traits>

// concept : Supported uniform variable type
template <typename T>
concept UniformVariableType = (
    std::same_as<T, float> ||
    std::same_as<T, int> ||
    std::same_as<T, bool> ||
    std::same_as<T, glm::mat4> ||
    std::same_as<T, glm::vec3>
    );

class Shader
{
    Shader(const Shader& other) = delete;
    Shader(Shader&& other) = delete;
    Shader& operator=(Shader&& other) = delete;
    Shader& operator=(const Shader& other) = delete;
private:
    GLuint m_program{};

private:
    template <size_t N, typename T, typename... Args>
    void setUniform_impl(const std::string_view name, Args... args) const;
    template <typename T, typename... Args>
    void setUniform_impl(const std::string_view name, Args&&... args) const;
public:
    Shader(const char* vertexPath, const char* fragmentPath);
    ~Shader() noexcept;

    void begin() const; // begin use this shader
    void end() const; // end use this shader

    /*
    * @template param N: uniform variable number
    * @template param T: uniform variable type
    * @template param Args: uniform variable arguments
    * @param name: uniform variable name
    * @param args: uniform variable arguments
    */
    template <typename T, typename... Args>
    void setUniform(const std::string_view name, Args... args) const;
};

// never call this function
template<size_t N, typename T, typename ...Args>
inline void Shader::setUniform_impl(
    const std::string_view name, Args...args) const
{
    std::cerr << "Should not be here!\n";
    assert(false);
}

template<typename T, typename ...Args>
inline void Shader::setUniform_impl(const std::string_view name, Args && ...args) const
{
    std::cerr << "Should not be here!\n";
    assert(false);
}

// entry point for setUniform function
template <typename T, typename... Args>
void Shader::setUniform(
    const std::string_view name, Args... args) const
{
    constexpr size_t N = sizeof...(Args);
    assert(N > 0 && N <= 4);
    static_assert(
        UniformVariableType<T>,
        "Unsupported uniform variable type"
        );
    if constexpr (std::is_trivially_copyable_v<T>) {
        setUniform_impl<N, T>(name, args...);
    }
    else {
        setUniform_impl<N, T>(name, std::move<T>(args)...);
    }
}

template <>
inline void Shader::setUniform_impl<1, float>(
    const std::string_view name, float value) const
{
    GLint location{ glGetUniformLocation(this->m_program, name.data()) };
    GLCALL(glUniform1f(location, value));
}

template <>
inline void Shader::setUniform_impl<2, float>(
    const std::string_view name, float v1, float v2) const
{
    GLint location{ glGetUniformLocation(this->m_program, name.data()) };
    GLCALL(glUniform2f(location, v1, v2));
}

template <>
inline void Shader::setUniform_impl<3, float>(
    const std::string_view name, float v1, float v2, float v3) const
{
    GLint location{ glGetUniformLocation(this->m_program, name.data()) };
    GLCALL(glUniform3f(location, v1, v2, v3));
}

template <>
inline void Shader::setUniform_impl<4, float>(
    const std::string_view name, float v1, float v2, float v3, float v4
) const
{
    GLint location{ glGetUniformLocation(this->m_program, name.data()) };
    GLCALL(glUniform4f(location, v1, v2, v3, v4));
}


template <>
inline void Shader::setUniform_impl<1, int>(
    const std::string_view name, int value) const
{
    GLint location{ glGetUniformLocation(this->m_program, name.data()) };
    GLCALL(glUniform1i(location, value));
}

template <>
inline void Shader::setUniform_impl<2, int>(
    const std::string_view name, int v1, int v2) const
{
    GLint location{ glGetUniformLocation(this->m_program, name.data()) };
    GLCALL(glUniform2i(location, v1, v2));
}

template <>
inline void Shader::setUniform_impl<3, int>(
    const std::string_view name, int v1, int v2, int v3) const
{
    GLint location{ glGetUniformLocation(this->m_program, name.data()) };
    GLCALL(glUniform3i(location, v1, v2, v3));
}

template <>
inline void Shader::setUniform_impl<4, int>(
    const std::string_view name, int v1, int v2, int v3, int v4
) const
{
    GLint location{ glGetUniformLocation(this->m_program, name.data()) };
    GLCALL(glUniform4i(location, v1, v2, v3, v4));
}

template <>
inline void Shader::setUniform_impl<1, bool>(
    const std::string_view name, bool value) const
{
    GLint location{ glGetUniformLocation(this->m_program, name.data()) };
    GLCALL(glUniform1i(location, value));
}

template <>
inline void Shader::setUniform_impl<2, bool>(
    const std::string_view name, bool v1, bool v2) const
{
    GLint location{ glGetUniformLocation(this->m_program, name.data()) };
    GLCALL(glUniform2i(location, v1, v2));
}

template <>
inline void Shader::setUniform_impl<3, bool>(
    const std::string_view name, bool v1, bool v2, bool v3) const
{
    GLint location{ glGetUniformLocation(this->m_program, name.data()) };
    GLCALL(glUniform3i(location, v1, v2, v3));
}

template <>
inline void Shader::setUniform_impl<4, bool>(
    const std::string_view name, bool v1, bool v2, bool v3, bool v4
) const
{
    GLint location{ glGetUniformLocation(this->m_program, name.data()) };
    GLCALL(glUniform4i(location, v1, v2, v3, v4));
}

template <>
inline void Shader::setUniform_impl<1, glm::mat4>(
    const std::string_view name, glm::mat4 value) const
{
    GLint location{ glGetUniformLocation(this->m_program, name.data()) };
    // glm and opengl use column-major order
    GLCALL(glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value)));
}

template <>
inline void Shader::setUniform_impl<1, glm::vec3>(
    const std::string_view name, glm::vec3 value) const
{
    GLint location{ glGetUniformLocation(this->m_program, name.data()) };
    GLCALL(glUniform3fv(location, 1, glm::value_ptr(value)));
}