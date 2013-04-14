#include "EncodingFileSaver.h"

EncodingFileSaver::EncodingFileSaver(wxFileName OutputFile)
{
    File = OutputFile;
/*
    pFormatCtx = NULL;

    VideoStream* vStream;
    AudioStream* aStream;
    SubtitleStream* sStream;

    if(File.FileExists())
    {
        av_register_all();
        avcodec_register_all();

        if(avformat_open_input(&pFormatCtx, File.GetFullPath().ToUTF8().data(), NULL, NULL) == 0)
        {
            // stream information exists
            if(avformat_find_stream_info(pFormatCtx, NULL) > -1)
            {
                AVCodecContext* pCodecCtx;
                for(unsigned int i=0; i<pFormatCtx->nb_streams; i++)
                {
                    // initialize codec context for each stream (if not done, decoding packets will crash!)

                    avcodec_open2(pCodecCtx, avcodec_find_decoder(pCodecCtx->codec_id), NULL);

                    if(pCodecCtx->codec_type == AVMEDIA_TYPE_VIDEO)
                    {
                        vStream = new VideoStream();
                        vStream->ID = i;
                        vStream->Info = wxEmptyString;
                        vStream->Size = -1;
                        vStream->Duration = pFormatCtx->streams[i]->duration;
                        // pre-allocate video index arrays with the number of packet count (frame count) for efficient insert operations
                        vStream->IndexEntries.Alloc(EstimateFrameCount(i)+100); // add 100 safety frames
                        VideoStreams.Add();
                        vStream = NULL;
                    }
                }
                pCodecCtx = NULL;

                BuildIndex();
            }
        }
    }*/
}

EncodingFileSaver::~EncodingFileSaver()
{
    // close the video file
    if(pFormatCtx != NULL)
    {
        avformat_close_input(&pFormatCtx);
        pFormatCtx = NULL;
    }
}
