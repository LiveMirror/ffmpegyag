#include "VideoFrameGOP.h"

VideoFrameGOP::VideoFrameGOP()
{
    ID = -1;
}

VideoFrameGOP::VideoFrameGOP(int Uid)
{
    ID = Uid;
}

VideoFrameGOP::~VideoFrameGOP()
{
    Flush();
}

size_t VideoFrameGOP::GetCount()
{
    return VideoFrames.GetCount();
}

void VideoFrameGOP::Flush()
{
    WX_CLEAR_ARRAY(VideoFrames);
    //VideoFrames.Clear();
    ID = -1;
}

int VideoFrameGOP::GetID()
{
    return ID;
}

void VideoFrameGOP::SetID(int uid)
{
    ID = uid;
}

int64_t VideoFrameGOP::GetFirstTimestamp()
{
    size_t Count = VideoFrames.GetCount();

    if(Count > 0)
    {
        return VideoFrames[0]->Timestamp;
    }

    return int64_t(-1);
}

int64_t VideoFrameGOP::GetLastTimestamp()
{
    size_t Count = VideoFrames.GetCount();

    if(Count > 0)
    {
        return VideoFrames[Count-1]->Timestamp;
    }

    return int64_t(-1);
}

bool VideoFrameGOP::ContainsTimestamp(int64_t Timestamp)
{
    if(Timestamp >= GetFirstTimestamp() && Timestamp <= GetLastTimestamp())
    {
        return true;
    }
    return false;
}

void VideoFrameGOP::AddVideoFrame(VideoFrame *Frame)
{
    // only add frame if it's timestamp > gop's last timestamp
    if(Frame->Timestamp > GetLastTimestamp())
    {
        VideoFrames.Add(Frame);
    }
    else
    {
        wxDELETE(Frame);
    }
}

VideoFrame* VideoFrameGOP::GetVideoFrame(int64_t Timestamp)
{
    size_t Count = VideoFrames.GetCount();

    if(Count > 0)
    {
        if(Timestamp == VideoFrames[0]->Timestamp)
        {
            return VideoFrames[0];
        }

        if(Timestamp == VideoFrames[Count-1]->Timestamp)
        {
            return VideoFrames[Count-1];
        }

        // search backwards, the last added frame is probably those that is requested
        for(long i=Count-2; i>=0; i--)
        {
            if(Timestamp >= VideoFrames[i]->Timestamp && VideoFrames[i+1]->Timestamp >= Timestamp)
            {
                if(Timestamp-VideoFrames[i]->Timestamp < VideoFrames[i+1]->Timestamp-Timestamp)
                {
                    return VideoFrames[i];
                }
                else
                {
                    return VideoFrames[i+1];
                }
            }
        }
    }

    // no corresponding frame found in gop...
    return NULL;
}
