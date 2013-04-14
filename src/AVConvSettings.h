#ifndef AVCONVSETTINGS_H
#define AVCONVSETTINGS_H

#include <wx/arrstr.h>
#include <wx/dir.h>
#include <wx/filename.h>
#include <wx/stdpaths.h>
#include <wx/textfile.h>

class AVConvSettings
{
    // initialize all static members with valid values
    public: static void Init();
    // returns a list of all available ffmpegyag presets (*.fyt) found in the application directory / user directory
    // (prefer application directory templates over user directory templates when same name was found)
    public: static wxArrayString GetPresets();
    // returns a list of parameters for a given preset, the seperator of parameters is '='
    public: static wxArrayString LoadPreset(wxString Preset);
};

#endif // AVCONVSETTINGS_H
