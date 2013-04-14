#include "app.h"
#include "../src/AVConvGUIMain.h"
#include <wx/image.h>

IMPLEMENT_APP(AVConvGUIApp);

bool AVConvGUIApp::OnInit()
{
    wxInitAllImageHandlers();
    AVConvSettings::Init();
    Libav::Init();
    AVConvGUIFrame* Frame = new AVConvGUIFrame(0);
    Frame->Show();
    SetTopWindow(Frame);

    return true;
}
