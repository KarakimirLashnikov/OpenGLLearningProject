#include "OpenGLCmakeProject.h"


int main()
{
    if (!theApp->Initialize(::WindowWidth, ::WindowHeight, ::WindowTitle))
    {
        return -1;
    }
    std::cout << sizeof((void*)MyResize) << std::endl;
    theApp->SetCallbacks(CallbackType::Resize, MyResize);
    theApp->SetCallbacks(CallbackType::KeyPress, MyKeyPress);
    theApp->SetCallbacks(CallbackType::MouseClick, MyMouseClick);
    theApp->SetCallbacks(CallbackType::CursorPos, MyCursorPos);
    theApp->SetCallbacks(CallbackType::MouseScroll, MyMouseScroll);
    prepare();

    while (theApp->Update())
    {
        render();
    }
    cleanup();
    theApp->Destroy();
    return 0;
}