#include "shader.hpp"

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
    // vertex shader, fragment shader
    std::string vertexCode{}, fragmentCode{};
    // read shader code from file
    std::ifstream vShaderFile{}, fShaderFile{};
    // if oepn file failed, throw exception
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try
    {
        // open files
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        // read files
        std::stringstream vShaderStream{},
            fShaderStream{};
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        // close files
        vShaderFile.close();
        fShaderFile.close();
        // convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (std::ifstream::failure& e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ\n";
        std::cout << e.what() << std::endl;
    }

    // create shader program
    const char* vShaderSource{ vertexCode.c_str() },
        * fShaderSource{ fragmentCode.c_str() };
    GLuint vertexShaderHandle{ glCreateShader(GL_VERTEX_SHADER) },
        fragmentShaderHandle{ glCreateShader(GL_FRAGMENT_SHADER) };
    // input shaders source to shaders
    GLCALL(glShaderSource(vertexShaderHandle, 1, &vShaderSource, nullptr));
    GLCALL(glShaderSource(fragmentShaderHandle, 1, &fShaderSource, nullptr));
    // compile shaders
    GLCALL(glCompileShader(vertexShaderHandle));
    GLCALL(glCompileShader(fragmentShaderHandle));
    // check for errors in shaders
    auto TYPE{ CHECK_ERROR_TYPE::COMPILE_ERROR };
    SHADERCHECK(vertexShaderHandle, TYPE);
    SHADERCHECK(fragmentShaderHandle, TYPE);
    // create shader program
    this->m_program = glCreateProgram();
    // attach shaders to program
    GLCALL(glAttachShader(this->m_program, vertexShaderHandle));
    GLCALL(glAttachShader(this->m_program, fragmentShaderHandle));
    // link program
    GLCALL(glLinkProgram(this->m_program));
    // check program for errors
    TYPE = CHECK_ERROR_TYPE::LINK_ERROR;
    SHADERCHECK(this->m_program, TYPE);
    // delete shaders
    GLCALL(glDeleteShader(vertexShaderHandle));
    GLCALL(glDeleteShader(fragmentShaderHandle));
}

Shader::~Shader() noexcept
{
}

void Shader::begin() const
{
    GLCALL(glUseProgram(m_program));
}

void Shader::end() const
{
    GLCALL(glUseProgram(0));
}
