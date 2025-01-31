#include "OpenGLCmakeProject.h"

inline Shader_ptr theShader{ nullptr };
inline Camera_ptr theCamera{ nullptr };
inline TrackBallControl* theTrackBall{ nullptr };
int xpos{ }, ypos{ };
GLuint vao{}, vbo{};

void MyResize(int width, int height)
{
    std::cout << "Resize: " << width << ", " << height << std::endl;
}
void MyKeyPress(int key, int x, int y, int modifiers)
{
    std::cout << "Key: " << key << std::endl;
    std::cout << "Modifiers: " << modifiers << std::endl;
    std::cout << "Position: " << x << ", " << y << std::endl;
}

void MyMouseClick(int button, int action, int mods)
{
    std::cout << "Button: " << button << std::endl;
    std::cout << "Action: " << action << std::endl;
    std::cout << "Modifiers: " << mods << std::endl;
    theTrackBall->onMouse(button, action, xpos, ypos);
}

void MyMouseScroll(double xoffset, double yoffset)
{
    std::cout << "Scroll: " << xoffset << ", " << yoffset << std::endl;
    theTrackBall->onCursor(xoffset, yoffset);
}

void MyCursorPos(double x, double y)
{
    std::cout << "Position: " << x << ", " << y << std::endl;
}

void prepare()
{
    GLfloat vertices[] = {
        // positions        // colors
        -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
         0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
         0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f
    };
    GLCALL(glGenVertexArrays(1, &vao));
    GLCALL(glGenBuffers(1, &vbo));
    GLCALL(glBindVertexArray(vao));
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, vbo));
    GLCALL(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW));
    GLCALL(glVertexAttribPointer(
        0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0));
    GLCALL(glVertexAttribPointer(
        1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat))));
    GLCALL(glEnableVertexAttribArray(0));
    GLCALL(glEnableVertexAttribArray(1));
    GLCALL(glBindVertexArray(0));

    theShader = std::make_shared<Shader>("assets/shaders/vertex.glsl", "assets/shaders/fragment.glsl");
    theCamera = std::make_unique<PerspectiveCamera>(
        60.0f, (float)WindowWidth / WindowHeight, 0.1f, 100.0f);
    theTrackBall = new TrackBallControl(theCamera.get());
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
}

void render()
{
    GLCALL(glBindVertexArray(vao));
    GLCALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    theShader->begin();
    glm::mat4 transform = glm::mat4(1.0f);
    theShader->setUniform<glm::mat4>("transform", transform);
    theShader->setUniform<glm::mat4>("view", theCamera->getViewMatrix());
    theShader->setUniform<glm::mat4>("projection", theCamera->getProjectionMatrix());
    GLCALL(glDrawArrays(GL_TRIANGLES, 0, 3));
    theShader->end();
    GLCALL(glBindVertexArray(0));
}


int main()
{
    if (!theApp->Initialize(::WindowWidth, ::WindowHeight, ::WindowTitle))
    {
        return -1;
    }

    theApp->SetCallbacks(SignalType::Resize, MyResize);
    theApp->SetCallbacks(SignalType::KeyPress, MyKeyPress);
    theApp->SetCallbacks(SignalType::MouseClick, MyMouseClick);
    theApp->SetCallbacks(SignalType::CursorPos, MyCursorPos);
    theApp->SetCallbacks(SignalType::MouseScroll, MyMouseScroll);
    prepare();

    while (theApp->Update())
    {
        render();
    }
    theApp->Destroy();
    return 0;
}