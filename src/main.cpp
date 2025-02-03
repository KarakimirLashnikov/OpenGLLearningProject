#include "OpenGLCmakeProject.h"

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
    cleanup();
    theApp->Destroy();
    return 0;
}