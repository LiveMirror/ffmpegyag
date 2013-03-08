#include "EncodingMediaStreams.h"

IndexEntry::IndexEntry(int64_t PacketTimestamp, int64_t PacketPosition, bool PacketKeyframe)
{
    Timestamp = PacketTimestamp;
    Position = PacketPosition;
    Keyframe = PacketKeyframe;
}

IndexEntry::~IndexEntry()
{
    //
}

MediaStream::MediaStream()
{
    ID = 0;
    Enabled = true;
}

MediaStream::MediaStream(unsigned int StreamID, bool EnableStream)
{
    ID = StreamID;
    Enabled = EnableStream;
}

MediaStream::~MediaStream()
{
    //
}

VideoStream::VideoStream(unsigned int StreamID, bool EnableStream)
{
    ID = StreamID;
    Enabled = EnableStream;
}

VideoStream::~VideoStream()
{
    WX_CLEAR_ARRAY(IndexEntries);
}

AudioStream::AudioStream(unsigned int StreamID, bool EnableStream)
{
    ID = StreamID;
    Enabled = EnableStream;
}

AudioStream::~AudioStream()
{
    //
}

SubtitleStream::SubtitleStream(unsigned int StreamID, bool EnableStream)
{
    ID = StreamID;
    Enabled = EnableStream;
}

SubtitleStream::~SubtitleStream()
{
    //
}
