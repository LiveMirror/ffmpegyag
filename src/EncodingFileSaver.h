#ifndef ENCODINGFILESAVER_H
#define ENCODINGFILESAVER_H

#include <wx/file.h>
#include <wx/filename.h>
#include <wx/progdlg.h>

#include "Libav.h"

class EncodingFileSaver
{
    public: EncodingFileSaver(wxFileName OutputFile);
    public: virtual ~EncodingFileSaver();

    private: wxFileName File;
    private: AVFormatContext *pFormatCtx;
};

WX_DEFINE_ARRAY(EncodingFileSaver*, EncodingFileSaverArray);

#endif // ENCODINGFILESAVER_H
