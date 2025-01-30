#include "OpenGLCmakeProject.h"

Shader_ptr shader{ nullptr };
Texture_ptr texture{ nullptr };
glm::mat4 t{ 1.0f };
GLuint vao[1]{}, vbo[1]{}, ebo[1]{}, uvvbo[1]{};

void prepareData();
void prepareShader();
void render();
void prepareTexture();
void doTransformations(float);

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
    shader.reset();
    texture.reset();
    // Destroy the application
    theApp->Destroy();
    return 0;
}

void prepareData()
{
    //GLfloat vertices[] = {
    //    // positions          // colors
    //     0.5f,  0.5f, 0.0f,   1.0f, .0f, .0f,
    //    -0.5f,  0.5f, 0.0f,   .0f, 1.0f, .0f,
    //     0.0f, -0.5f, 0.0f,   .0f, .0f, 1.0f
    //};
    //// uv posiitons 
    //GLfloat uv[]{
    //    1.0f, 1.0f,
    //    0.0f, 1.0f,
    //    0.5f, 0.0f,
    //};
    //// Generate object
    //GLCALL(glGenVertexArrays(1, vao));
    //GLCALL(glGenBuffers(1, vbo));
    //GLCALL(glGenBuffers(1, uvvbo));
    //// Bind the object
    //GLCALL(glBindVertexArray(vao[0]));
    //GLCALL(glBindBuffer(GL_ARRAY_BUFFER, vbo[0]));
    //// Set the data
    //GLCALL(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));
    //// Set the vertex attributes
    //GLCALL(glVertexAttribPointer(
    //    0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0
    //));
    //GLCALL(glVertexAttribPointer(
    //    1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat))
    //));
    //// texture coordinates
    //GLCALL(glBindBuffer(GL_ARRAY_BUFFER, uvvbo[0]));
    //GLCALL(glBufferData(GL_ARRAY_BUFFER, sizeof(uv), uv, GL_STATIC_DRAW));
    //GLCALL(glVertexAttribPointer(
    //    2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (void*)(0)
    //));
    //// Enable the vertex attribute
    //GLCALL(glEnableVertexAttribArray(0));
    //GLCALL(glEnableVertexAttribArray(1));
    //GLCALL(glEnableVertexAttribArray(2));
    //// Unbind the object
    //GLCALL(glBindVertexArray(0));

    GLfloat vertecies[]{
        // positions           // colors
        -0.5f, -0.5f, 0.0f,    1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.0f,     0.0f, 1.0f, 0.0f,
        -0.5f, 0.5f, 0.0f,     0.0f, 0.0f, 1.0f,
        0.5f, 0.5f, 0.0f,      0.5f, 0.5f, 0.5f
    };

    GLuint indices[]{
        0, 1, 2,
        2, 1, 3
    };

    GLCALL(glGenVertexArrays(1, vao));
    GLCALL(glGenBuffers(1, vbo));
    GLCALL(glGenBuffers(1, ebo));
    GLCALL(glGenBuffers(1, uvvbo));

    GLCALL(glBindVertexArray(vao[0]));
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, vbo[0]));
    GLCALL(glBufferData(GL_ARRAY_BUFFER, sizeof(vertecies), vertecies, GL_STATIC_DRAW));
    GLCALL(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0));
    GLCALL(glVertexAttribPointer(
        1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat))));
    GLCALL(glEnableVertexAttribArray(0));
    GLCALL(glEnableVertexAttribArray(1));
    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[0]));
    GLCALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW));
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
    doTransformations(var);
    shader->setUniform<glm::mat4>("transform", ::t);
    GLCALL(glBindVertexArray(vao[0]));
    GLCALL(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
    // Unbind the shader program
    shader->end();
    // Unbind the object
    GLCALL(glBindVertexArray(0));
}

void prepareTexture()
{
    texture = std::make_shared<Texture>(
        "assets/textures/girl.jpg"
    );
}

void doTransformations(float dt)
{
    float speed = 0.05f;
    ::t = glm::translate(::t, glm::vec3(0.001f, 0.0f, 0.0f));
    ::t = glm::rotate(::t, glm::radians(speed), glm::vec3(0.0f, 0.0f, 1.0f));
}
