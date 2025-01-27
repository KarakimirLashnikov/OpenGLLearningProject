#include "OpenGLCmakeProject.h"

Shader_ptr shader{ nullptr };
GLuint vao[1]{}, vbo[1]{};

void prepareData();
void prepareShader();
void render();

int main()
{
    // Initalize the application
    if (!theApp->Initialize(WindowWidth, WindowHeight, WindowTitle))
    {
        return -1;
    }
    // Prepare the data and shader
    prepareData();
    prepareShader();
    // Set the clear color
    GLCALL(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));
    // Start the main loop
    while (theApp->Update())
    {
        render();
    }
    // Destroy the application
    theApp->Destroy();
    return 0;
}

void prepareData()
{
    GLfloat vertices[] = {
        // positions          // colors
         0.5f,  0.5f, 0.0f,   1.0f, .0f, .0f,
        -0.5f,  0.5f, 0.0f,   .0f, 1.0f, .0f,
         0.0f, -0.5f, 0.0f,   .0f, .0f, 1.0f
    };
    // Generate object
    GLCALL(glGenVertexArrays(1, vao));
    GLCALL(glGenBuffers(1, vbo));
    // Bind the object
    GLCALL(glBindVertexArray(vao[0]));
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, vbo[0]));
    // Set the data
    GLCALL(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));
    // Set the vertex attributes
    GLCALL(glVertexAttribPointer(
        0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0
    ));
    GLCALL(glVertexAttribPointer(
        1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat))
    ));
    // Enable the vertex attribute
    GLCALL(glEnableVertexAttribArray(0));
    GLCALL(glEnableVertexAttribArray(1));
    // Unbind the object
    GLCALL(glBindVertexArray(0));
}

void prepareShader()
{
    shader = std::make_shared<Shader>(
        "assets/shaders/vertex.glsl", "assets/shaders/fragment.glsl"
    );
}

void render()
{
    // Clear the screen
    GLCALL(glClear(GL_COLOR_BUFFER_BIT));
    // Use the shader program
    shader->begin();
    // Draw the object
    float var = glfwGetTime();
    shader->setUniform<1, float>("time", var); // update the uniform
    GLCALL(glBindVertexArray(vao[0]));
    GLCALL(glDrawArrays(GL_TRIANGLES, 0, 3));
    // Unbind the shader program
    shader->end();
    // Unbind the object
    GLCALL(glBindVertexArray(0));
}
