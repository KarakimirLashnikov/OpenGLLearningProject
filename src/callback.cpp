#include "OpenGLCmakeProject.h"

inline Shader_ptr theShader{ nullptr }, lightShader{ nullptr };
inline Camera_ptr theCamera{ nullptr };
inline Texture_ptr theTexture{ nullptr };
inline GameCameraControl* theCameraController{ nullptr };
inline float xpos{ }, ypos{ };
inline GLuint vao{}, vbo{}, lightVAO{};
inline glm::vec3 lightPos{ 1.2f, 1.0f, 2.0f };

// cube vertex data
GLfloat vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
};


void MyResize(int width, int height)
{
    glViewport(0, 0, width, height);
}
void MyKeyPress(int key, int scancode, int action, int modifiers)
{
    theCameraController->onKey(key, action, modifiers);
}

void MyMouseClick(int button, int action, int mods)
{
    theCameraController->onMouse(button, action, xpos, ypos);
}

void MyMouseScroll(double xoffset, double yoffset)
{
    theCameraController->onScroll(static_cast<float>(xoffset), static_cast<float>(yoffset));
}

void MyCursorPos(double x, double y)
{
    xpos = static_cast<float>(x);
    ypos = static_cast<float>(y);
    theCameraController->onCursor(xpos, ypos);
}

void prepare()
{
    // Generate and bind VAO and VBO
    GLCALL(glGenVertexArrays(1, &vao));
    GLCALL(glGenBuffers(1, &vbo));
    GLCALL(glBindVertexArray(vao));
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, vbo));
    GLCALL(glBufferData(GL_ARRAY_BUFFER, sizeof(::vertices), ::vertices, GL_STATIC_DRAW));
    GLCALL(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0));
    GLCALL(glVertexAttribPointer(
        1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat))));
    GLCALL(glEnableVertexAttribArray(0));
    GLCALL(glEnableVertexAttribArray(1));
    GLCALL(glBindVertexArray(0));

    // light VAO
    GLCALL(glGenVertexArrays(1, &lightVAO));
    GLCALL(glBindVertexArray(lightVAO));
    GLCALL(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0));
    GLCALL(glEnableVertexAttribArray(0));
    GLCALL(glBindVertexArray(0));

    //theTexture = std::make_shared<Texture>("assets/textures/pig.jpg");

    theShader = std::make_shared<Shader>("assets/shaders/vertex.glsl", "assets/shaders/fragment.glsl");
    lightShader = std::make_shared<Shader>("assets/shaders/vertex.glsl", "assets/shaders/light.frag");
    theCamera = std::make_unique<PerspectiveCamera>(
        45.0f, (float)WindowWidth / WindowHeight, 0.0f, 100.0f);
    theCameraController = new GameCameraControl(theCamera.get());
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    // object shader
    theShader->begin();
    theShader->setUniform<glm::mat4>("projection", theCamera->getProjectionMatrix());
    glm::mat4 transform = glm::mat4(1.0f);
    theShader->setUniform<glm::mat4>("transform", transform);
    theShader->setUniform<glm::vec3>("material.ambient", glm::vec3(1.0f, 0.5f, 0.31f));
    theShader->setUniform<glm::vec3>("material.diffuse", glm::vec3(1.0f, 0.5f, 0.31f));
    theShader->setUniform<glm::vec3>("material.specular", glm::vec3(0.5f, 0.5f, 0.5f));
    // light 
    theShader->setUniform<glm::vec3>("light.specular", glm::vec3(1.0f, 1.0f, 1.0f));
    theShader->setUniform<float>("material.shininess", 32.0f);
    theShader->end();

    // light shader
    lightShader->begin();
    transform = glm::translate(glm::mat4(1.0f), lightPos);
    transform = glm::scale(transform, glm::vec3(0.2f));
    lightShader->setUniform<glm::mat4>("transform", transform);
    lightShader->end();
}

void render()
{
    theCameraController->begin();
    GLCALL(glBindVertexArray(vao));
    GLCALL(glEnable(GL_DEPTH_TEST));
    GLCALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

    auto viewMat{ theCamera->getViewMatrix() };
    auto projMat{ theCamera->getProjectionMatrix() };

    // Draw object
    theShader->begin();
    theShader->setUniform<glm::mat4>("view", viewMat);
    theShader->setUniform<glm::mat4>("projection", projMat);
    theShader->setUniform<glm::vec3>("visitorPos", theCamera->getPosition());
    float currentTime = (float)glfwGetTime();
    glm::vec3 lightColor{ std::sin(currentTime * 2.0f), std::sin(currentTime * 0.7f),
        std::sin(currentTime * 1.3f) };
    theShader->setUniform<glm::vec3>("light.position", lightPos);
    theShader->setUniform<glm::vec3>("light.ambient", glm::vec3(0.2f) * lightColor);
    theShader->setUniform<glm::vec3>("light.diffuse", glm::vec3(0.5f) * lightColor);
    GLCALL(glDrawArrays(GL_TRIANGLES, 0, 36));
    theShader->end();
    GLCALL(glBindVertexArray(0));
    // Draw light
    GLCALL(glBindVertexArray(lightVAO));
    lightShader->begin();
    lightShader->setUniform<glm::mat4>("view", viewMat);
    lightShader->setUniform<glm::mat4>("projection", projMat);
    GLCALL(glBindVertexArray(lightVAO));
    GLCALL(glDrawArrays(GL_TRIANGLES, 0, 36));
    lightShader->end();
    GLCALL(glBindVertexArray(0));
}

void cleanup()
{
    delete theCameraController;
    theCamera.reset();
    theShader.reset();
    lightShader.reset();
    theTexture.reset();
    GLCALL(glDeleteVertexArrays(1, &vao));
    GLCALL(glDeleteBuffers(1, &vbo));
    GLCALL(glDeleteVertexArrays(1, &lightVAO));
}