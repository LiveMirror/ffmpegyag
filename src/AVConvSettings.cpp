#include "AVConvSettings.h"

void AVConvSettings::Init()
{
    if(!wxDir::Exists(wxStandardPaths::Get().GetUserDataDir()))
    {
        wxMkdir(wxStandardPaths::Get().GetUserDataDir());
    }
}

wxArrayString AVConvSettings::GetPresets()
{
    wxArrayString PresetFiles;
    wxDir::GetAllFiles(wxStandardPaths::Get().GetExecutablePath().BeforeLast(wxFileName::GetPathSeparator()), &PresetFiles, wxT("*.fyt"));
    wxDir::GetAllFiles(wxStandardPaths::Get().GetUserDataDir(), &PresetFiles, wxT("*.fyt"));
    for(size_t f=0; f<PresetFiles.GetCount(); f++)
    {
        PresetFiles[f] = PresetFiles[f].BeforeLast('.').AfterLast(wxFileName::GetPathSeparator());
    }
    PresetFiles.Sort();
    return PresetFiles;
}

wxArrayString AVConvSettings::LoadPreset(wxString Preset)
{
    wxArrayString PresetSettings;
    wxArrayString PresetFiles;
    // presets in executable directory has higher priority (when same name) then in home directory, so load them first
    wxDir::GetAllFiles(wxStandardPaths::Get().GetExecutablePath().BeforeLast(wxFileName::GetPathSeparator()), &PresetFiles, Preset + wxT(".fyt"));
    wxDir::GetAllFiles(wxStandardPaths::Get().GetUserDataDir(), &PresetFiles, Preset + wxT(".fyt"));
    if(PresetFiles.GetCount() > 0)
    {
        wxTextFile PresetFile;
        PresetFile.Open(PresetFiles[0]);
        PresetSettings.Add(PresetFile.GetFirstLine());
        while(!PresetFile.Eof())
        {
            PresetSettings.Add(PresetFile.GetNextLine());
        }
        PresetFile.Close();
    }
    else
    {
        // preset not found
    }
    return PresetSettings;
}
