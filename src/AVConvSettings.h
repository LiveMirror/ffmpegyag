#ifndef AVCONVSETTINGS_H
#define AVCONVSETTINGS_H

#include <wx/arrstr.h>
#include <wx/hashmap.h>
#include <wx/dir.h>
#include <wx/file.h>
#include <wx/filename.h>
#include <wx/stdpaths.h>

class AVConvSettings
{
    // returns a list of all available ffmpegyag templates found in the application directory / user directory
    // (prefer application directory templates over user directory templates when same name was found)
    public: static wxArrayString GetTemplates();
    // returns a list of parameters for a given template sperator
    public: static wxArrayString LoadTemplate(wxString TemplateFile);
};

#endif // AVCONVSETTINGS_H
