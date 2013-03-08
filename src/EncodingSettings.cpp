#include "EncodingSettings.h"

VideoSettings::VideoSettings()
{
    Codec = wxEmptyString;
    Bitrate = wxEmptyString;
    FrameRate = wxEmptyString;
    FrameSize = wxEmptyString;
    AspectRatio = wxEmptyString;
    Deinterlace = false;
    MacroblockDecision = wxT("rd");
    MacroblockComparsion = wxT("rd");
    MotionEstimationComparsion = wxT("rd");
    PreMotionEstimationComparsion = wxT("rd");
    SubMotionEstimationComparsion = wxT("rd");
    Trellis = true;
    MinQuantization = wxT("1");
    MaxQuantization = wxT("31");
    QPEL = false;
    GMC = false;
    Crop[0] = 0;
    Crop[1] = 0;
    Crop[2] = 0;
    Crop[3] = 0;
    Crop[4] = 0;
}

VideoSettings::~VideoSettings()
{
    //wxDELETEA(Crop);
}

AudioSettings::AudioSettings()
{
    Codec = wxEmptyString;
    Bitrate = wxEmptyString;
    Frequency = wxEmptyString;
    Channels = wxEmptyString;
}

AudioSettings::~AudioSettings()
{
    //
}

SubtitleSettings::SubtitleSettings()
{
    Codec = wxEmptyString;
}

SubtitleSettings::~SubtitleSettings()
{
    //
}
