#pragma once

#include "wrapper/checkError.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <string_view>
#include <concepts>
#include <cassert>

// concept : Supported uniform variable number
template <size_t N>
concept UniformVariableNumber = (
    N == 1 || N == 2 || N == 3 || N == 4
    );

// concept : Supported uniform variable type
template <typename T>
concept UniformVariableType = (
    std::same_as<T, float> ||
    std::same_as<T, int> ||
    std::same_as<T, bool>
    );

// concept : every element type should be the same
template <typename T, typename... Args>
concept SameType = (... && std::same_as<T, Args>);

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
public:
    Shader(const char* vertexPath, const char* fragmentPath);
    ~Shader() noexcept;

    void begin() const; // begin use this shader
    void end() const; // end use this shader

    // set uniform variable
    template <size_t N, typename T, typename... Args>
    void setUniform(const std::string_view name, Args... args) const;
};

// never call this function
template<size_t N, typename T, typename ...Args>
inline void Shader::setUniform_impl(
    const std::string_view name, Args ...args) const
{
    std::cerr << "Should not be here!\n";
    assert(false);
}

// entry point for setUniform function
template <size_t N, typename T, typename... Args>
void Shader::setUniform(
    const std::string_view name, Args... args) const
{
    static_assert(
        UniformVariableNumber<N>,
        "Unsupported uniform variable number"
        );
    static_assert(
        UniformVariableType<T>,
        "Unsupported uniform variable type"
        );
    static_assert(
        SameType<T, Args...>,
        "All arguments must be of the same type"
        );

    setUniform_impl<N, T, Args...>(name, args...);
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