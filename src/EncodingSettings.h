#ifndef ENCODINGSETTINGS_H
#define ENCODINGSETTINGS_H

#include <wx/string.h>

class VideoSettings
{
    public: VideoSettings();
    public: virtual ~VideoSettings();

    public: wxString Codec;
    public: wxString Bitrate;
    public: wxString FrameRate;
    public: wxString FrameSize;
    public: wxString AspectRatio;
    public: bool Deinterlace;
    public: wxString MacroblockDecision;
    public: wxString MacroblockComparsion;
    public: wxString MotionEstimationComparsion;
    public: wxString PreMotionEstimationComparsion;
    public: wxString SubMotionEstimationComparsion;
    public: bool Trellis;
    public: wxString MinQuantization;
    public: wxString MaxQuantization;
    public: bool QPEL;
    public: bool GMC;
    // indices: [0,1,2,3,4] -> [DoCrop, Width, Height, PosX, PosY]
    // DoCrop 0 -> No Cropping
    // DoCrop 1 -> Crop
    public: int Crop[5];
};

class AudioSettings
{
    public: AudioSettings();
    public: virtual ~AudioSettings();

    public: wxString Codec;
    public: wxString Bitrate;
    public: wxString Frequency;
    public: wxString Channels;
};

class SubtitleSettings
{
    public: SubtitleSettings();
    public: virtual ~SubtitleSettings();

    public: wxString Codec;
};

#endif // ENCODINGSETTINGS_H
