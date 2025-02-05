#include "OpenGLCmakeProject.h"

int main()
{
    if (!theApp->Initialize(::WindowWidth, ::WindowHeight, ::WindowTitle))
    {
        return -1;
    }

    RigisterCallbacks();
    Prepare();

    while (theApp->Update())
    {
        Render();
    }
    Cleanup();
    theApp->Destroy();
    return 0;
}