#include "OpenGLCmakeProject.h"

Shader_ptr shader{ nullptr };
GLuint vao[1]{}, vbo[1]{}, uvvbo[1]{};

void prepareData();
void prepareShader();
void render();
void prepareTexture();

int main()
{
    // Initalize the application
    if (!theApp->Initialize(WindowWidth, WindowHeight, WindowTitle))
    {
        return -1;
    }
    // Prepare the data and shader
    prepareTexture();
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
    // uv posiitons 
    GLfloat uv[]{
        1.0f, 1.0f,
        0.0f, 1.0f,
        0.5f, 0.0f,
    };
    // Generate object
    GLCALL(glGenVertexArrays(1, vao));
    GLCALL(glGenBuffers(1, vbo));
    GLCALL(glGenBuffers(1, uvvbo));
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
    // texture coordinates
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, uvvbo[0]));
    GLCALL(glBufferData(GL_ARRAY_BUFFER, sizeof(uv), uv, GL_STATIC_DRAW));
    GLCALL(glVertexAttribPointer(
        2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (void*)(0)
    ));
    // Enable the vertex attribute
    GLCALL(glEnableVertexAttribArray(0));
    GLCALL(glEnableVertexAttribArray(1));
    GLCALL(glEnableVertexAttribArray(2));
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
    shader->setUniform<float>("time", var); // update the uniform
    GLCALL(glBindVertexArray(vao[0]));
    GLCALL(glDrawArrays(GL_TRIANGLES, 0, 3));
    // Unbind the shader program
    shader->end();
    // Unbind the object
    GLCALL(glBindVertexArray(0));
}

void prepareTexture()
{
    // read image
    int imageWidth{}, imageHeight{}, imageChannels{};
    stbi_set_flip_vertically_on_load(true);
    unsigned char* imageData{
        stbi_load(R"IMAGEPATH(assets/textures/pig.jpg)IMAGEPATH",
            &imageWidth, &imageHeight, &imageChannels, STBI_rgb_alpha)
    };
    if (!imageData) {
        std::cerr << "Failed to load texture" << std::endl;
        assert(false);
    }
    // generate texture object
    GLuint textureID{};
    GLCALL(glGenTextures(1, &textureID));
    // activate texture unit
    GLCALL(glActiveTexture(GL_TEXTURE0));
    // bind texture object with texture unit
    GLCALL(glBindTexture(GL_TEXTURE_2D, textureID));
    // pass texture data to the GPU
    GLCALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight,
        0, GL_RGBA, GL_UNSIGNED_BYTE, imageData));

    // set texture wrapping options
    GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
    GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
    // set texture filtering options
    GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));

    // release image data in memory
    stbi_image_free(imageData);
}
