#include "EncodingTask.h"

FileSegment::FileSegment(int64_t StartTime, int64_t EndTime)
{
    //TimestampTo = 0;
    //TimestampFrom = 0;
    TimeTo = EndTime;
    TimeFrom = StartTime;
    //TimecodeTo = wxEmptyString;
    //TimecodeFrom = wxEmptyString;
    //TimecodeDuration = wxEmptyString;
}

FileSegment::~FileSegment()
{
    //
}

EncodingTask::EncodingTask()
{
    OutputSegmentsConcat = false;
    TwoPass = false;
    RemoveMetadata = true;
    RemoveChapters = true;
}

EncodingTask::~EncodingTask()
{
    WX_CLEAR_ARRAY(InputFiles);
    WX_CLEAR_ARRAY(OutputSegments);
}

wxArrayString EncodingTask::GetCommands()
{
    wxArrayString Commands;

    if(OutputFile.Mkdir(0755, wxPATH_MKDIR_FULL))
    {
        wxString SegmentFile;
        wxString SegmentStart;
        wxString SegmentDuration;

        size_t SegmentCount = OutputSegments.GetCount();

        for(size_t i=0; i<wxMax(1, SegmentCount); i++)
        {
            SegmentFile = OutputFile.GetPathWithSep() + OutputFile.GetName();
            if(SegmentCount > 1)
            {
                // append segment number
                SegmentFile.Append(wxString::Format(wxT(".part%02d"), (int)(i+1)));
            }
            if(OutputFormat.StartsWith(wxT("image2")))
            {
                // append image number placeholder
                SegmentFile.Append(wxT(".%06d"));
            }
            SegmentFile.Append(wxT(".") + OutputFile.GetExt());

            //SegmentFiles.Add(SegmentFile);

            SegmentStart = wxEmptyString;
            SegmentDuration = wxEmptyString;

            if(SegmentCount > 0)
            {
                if(OutputSegments[i]->TimeFrom != OutputSegments[i]->TimeTo)
                {
                    SegmentStart = Libav::MilliToString(OutputSegments[i]->TimeFrom);
                }
                if(OutputSegments[i]->TimeFrom < OutputSegments[i]->TimeTo)
                {
                    SegmentDuration = Libav::MilliToString(OutputSegments[i]->TimeTo - OutputSegments[i]->TimeFrom);
                }
            }

            if(TwoPass)
            {
                Commands.Add(GetCommandAVConv(SegmentFile, SegmentStart, SegmentDuration, FirstPass));
                Commands.Add(GetCommandAVConv(SegmentFile, SegmentStart, SegmentDuration, SecondPass));
            }
            else
            {
                Commands.Add(GetCommandAVConv(SegmentFile, SegmentStart, SegmentDuration/*, NoPass*/));
            }
        }
    }

    // TODO: merge files
/*
        if(FileSegmentConcat && SegmentCount > 1 && !FileFormat.StartsWith(wxT("image2")))
        {
            // FIXME: concat currently not possible with ffmpeg / avconv

            // only join if not format.startswith("image2") because a sequence of image can't be joined to another sequence of images

            // input format: FileFormat
            // input files: SegmentFiles;
            // output format: FileFormat
            // output file: FileOut.GetFullPath()
        }
    }
*/
    return Commands;
}

wxString EncodingTask::GetCommandAVConv(wxString OutputFileName, wxString StartTime, wxString Duration, Pass PassNumber)
{
	wxString Seperator = wxFileName::GetPathSeparator();

    #ifdef __LINUX__
	// primary choice
	wxString Command = wxT("ffmpeg-x264-10bit");
	if(!wxFile::Exists(wxT("/usr/bin/") + Command) && !wxFile::Exists(wxT("/sbin/") + Command) && !wxFile::Exists(wxT("/bin/") + Command))
    {
		// secondary choice
		Command = wxT("avconv-x264-10bit");
		if(!wxFile::Exists(wxT("/usr/bin/") + Command) && !wxFile::Exists(wxT("/sbin/") + Command) && !wxFile::Exists(wxT("/bin/") + Command))
		{
			// third choice
			Command = wxT("ffmpeg");	
			if(!wxFile::Exists(wxT("/usr/bin/") + Command) && !wxFile::Exists(wxT("/sbin/") + Command) && !wxFile::Exists(wxT("/bin/") + Command))
			{
				// fallback choice
				Command = wxT("avconv");	
			}
		}
	}
    #endif
    #ifdef __WINDOWS__
    wxString CommandDirectory = wxStandardPaths::Get().GetExecutablePath().BeforeLast(Seperator));
	// primary choice
	wxString Command = CommandDirectory + Seperator + wxT("ffmpeg-x264-10bit.exe");
	if(!wxFile::Exists(Command))
	{
		// secondary choice
		Command = CommandDirectory + Seperator + wxT("avconv-x264-10bit.exe");
		if(!wxFile::Exists(Command))
		{
			// third choice
			Command = CommandDirectory + Seperator + wxT("ffmpeg.exe");
			if(!wxFile::Exists(Command))
			{
				// fallback choice
				Command = CommandDirectory + Seperator + wxT("avconv.exe");
			}
		}

	}
    #endif

    AVMediaFlags SupportedMediaFlags = Libav::FormatMediaMap[OutputFormat]; // AVMEDIA_FLAG_VIDEO

    // input options
    //{
        //...
    //}

    // input file(s) / format
    //{
        for(size_t f=0; f<InputFiles.GetCount(); f++)
        {
            Command.Append(wxT(" -i \"") + InputFiles[f]->File.GetFullPath() + wxT("\""));
        }

        Command.Append(wxT(" -strict experimental"));

        if(!OutputFormat.IsEmpty())
        {
            Command.Append(wxT(" -f ") + OutputFormat);
        }
    //}

    // stream/data mapping
    //{
        // metadata stream selection (mapping)
        if(RemoveMetadata)
        {
            // NOTE: metatags will affect stream info -> remove language from metadata -> also remove language from track info

            // -1 switch is not wrking in latest version of ffmpeg/avconv
            //Command.Append(wxT(" -map_metadata -1"));

            // currently best solution is to map all input metadata (global + streams) to an invalid output stream (999)
            /*
            for(size_t f=0; f<InputFiles.GetCount(); f++)
            {
                Command.Append(wxString::Format(wxT(" -map_metadata:s:999 %lu:g"), (unsigned long)f));
                Command.Append(wxString::Format(wxT(" -map_metadata:s:999 %lu:s"), (unsigned long)f));
            }
            */

            // -map_metadata[:target] [sourcefile:sorcestream:...]
            // map metadata from all streams to global metadata
            // -map_metadata:g 0:s

            // removing metadata from matroska by remuxing with mkvmerge
            /*
            {
                // remove metadata, attachements, chapters,... using mkvmerge
                // mkvmerge -o "/home/ronny/Desktop/bakemonogatari-clean.mkv" --no-buttons --no-global-tags --no-track-tags --no-chapters --no-attachments "/home/ronny/Desktop/bakemonogatari.mkv"
            }
            */
        }

        // chapter stream selection (mapping)
        if(RemoveChapters)
        {
            Command.Append(wxT(" -map_chapters -1"));
        }

        // video stream selection (-map InputFileIndex:StreamIndex)
        if(SupportedMediaFlags & AVMEDIA_FLAG_VIDEO || SupportedMediaFlags & AVMEDIA_FLAG_IMG2SEQUENCE)
        {
            for(size_t f=0; f<InputFiles.GetCount(); f++)
            {
                for(size_t v=0; v<InputFiles[f]->VideoStreams.GetCount(); v++)
                {
                    if(InputFiles[f]->VideoStreams[v]->Enabled)
                    {
                        Command.Append(wxString::Format(wxT(" -map %lu:%u"), (unsigned long)f, InputFiles[f]->VideoStreams[v]->ID));
                    }
                }
            }
        }

        // audio stream selection (-map InputFileIndex:StreamIndex)
        if(SupportedMediaFlags & AVMEDIA_FLAG_AUDIO && PassNumber != FirstPass)
        {
            for(size_t f=0; f<InputFiles.GetCount(); f++)
            {
                for(size_t a=0; a<InputFiles[f]->AudioStreams.GetCount(); a++)
                {
                    if(InputFiles[f]->AudioStreams[a]->Enabled)
                    {
                        Command.Append(wxString::Format(wxT(" -map %lu:%u"), (unsigned long)f, InputFiles[f]->AudioStreams[a]->ID));
                    }
                }
            }
        }

        // subtitle stream selection (-map InputFileIndex:StreamIndex)
        if(SupportedMediaFlags & AVMEDIA_FLAG_SUBTITLE && PassNumber != FirstPass)
        {
            for(size_t f=0; f<InputFiles.GetCount(); f++)
            {
                for(size_t s=0; s<InputFiles[f]->SubtitleStreams.GetCount(); s++)
                {
                    if(InputFiles[f]->SubtitleStreams[s]->Enabled)
                    {
                        Command.Append(wxString::Format(wxT(" -map %lu:%u"), (unsigned long)f, InputFiles[f]->SubtitleStreams[s]->ID));
                    }
                }
            }
        }
    //}

    // subtitle encoding
    //{
        if(SupportedMediaFlags & AVMEDIA_FLAG_SUBTITLE && PassNumber != FirstPass)
        {
            int sub_count = 0;
            for(size_t f=0; f<InputFiles.GetCount(); f++)
            {
                for(size_t s=0; s<InputFiles[f]->SubtitleStreams.GetCount(); s++)
                {
                    if(InputFiles[f]->SubtitleStreams[s]->Enabled)
                    {
                        if(!InputFiles[f]->SubtitleStreams[s]->EncodingSettings.Codec.IsEmpty())
                        {
                            Command.Append(wxString::Format(wxT(" -c:s:%i ") + InputFiles[f]->SubtitleStreams[s]->EncodingSettings.Codec, sub_count));
                        }
                        if(!InputFiles[f]->SubtitleStreams[s]->EncodingSettings.Codec.IsSameAs(wxT("copy")))
                        {
                            // more encoding options for subtitles

                            // subtitle filters
                            //{
                                //
                            //}
                        }
                        sub_count++;
                    }
                }
            }
            if(sub_count == 0)
            {
                Command.Append(wxT(" -sn"));
            }
        }
        else
        {
            Command.Append(wxT(" -sn"));
        }
    //}

    // audio processing
    //{
        if(SupportedMediaFlags & AVMEDIA_FLAG_AUDIO && PassNumber != FirstPass)
        {
            int aud_count = 0;
            for(size_t f=0; f<InputFiles.GetCount(); f++)
            {
                for(size_t a=0; a<InputFiles[f]->AudioStreams.GetCount(); a++)
                {
                    if(InputFiles[f]->AudioStreams[a]->Enabled)
                    {
                        if(!InputFiles[f]->AudioStreams[a]->EncodingSettings.Codec.IsEmpty())
                        {
                            Command.Append(wxString::Format(wxT(" -c:a:%i ") + InputFiles[f]->AudioStreams[a]->EncodingSettings.Codec, aud_count));
                        }
                        if(!InputFiles[f]->AudioStreams[a]->EncodingSettings.Codec.IsSameAs(wxT("copy")))
                        {
                            if(!InputFiles[f]->AudioStreams[a]->EncodingSettings.Bitrate.IsEmpty())
                            {
                                Command.Append(wxString::Format(wxT(" -b:a:%i ") + InputFiles[f]->AudioStreams[a]->EncodingSettings.Bitrate, aud_count));
                            }
                            if(!InputFiles[f]->AudioStreams[a]->EncodingSettings.Frequency.IsEmpty())
                            {
                                Command.Append(wxString::Format(wxT(" -ar:a:%i ") + InputFiles[f]->AudioStreams[a]->EncodingSettings.Frequency, aud_count));
                            }
                            if(!InputFiles[f]->AudioStreams[a]->EncodingSettings.Channels.IsEmpty())
                            {
                                Command.Append(wxString::Format(wxT(" -ac:a:%i ") + InputFiles[f]->AudioStreams[a]->EncodingSettings.Channels, aud_count));
                            }
                            // audio filters
                            //{
                                //
                            //}
                        }
                        aud_count++;
                    }
                }
            }
            if(aud_count == 0)
            {
                Command.Append(wxT(" -an"));
            }
        }
        else
        {
            Command.Append(wxT(" -an"));
        }
    //}

    // video processing
    //{
        if(SupportedMediaFlags & AVMEDIA_FLAG_VIDEO)
        {
            int vid_count = 0;
            for(size_t f=0; f<InputFiles.GetCount(); f++)
            {
                for(size_t v=0; v<InputFiles[f]->VideoStreams.GetCount(); v++)
                {
                    if(InputFiles[f]->VideoStreams[v]->Enabled)
                    {
                        if(!InputFiles[f]->VideoStreams[v]->EncodingSettings.Codec.IsEmpty())
                        {
                            Command.Append(wxString::Format(wxT(" -c:v:%i ") + InputFiles[f]->VideoStreams[v]->EncodingSettings.Codec, vid_count));
                        }
                        if(!InputFiles[f]->VideoStreams[v]->EncodingSettings.Codec.IsSameAs(wxT("copy")))
                        {
                            if(!InputFiles[f]->VideoStreams[v]->EncodingSettings.Bitrate.IsEmpty())
                            {
								if(InputFiles[f]->VideoStreams[v]->EncodingSettings.Bitrate.StartsWith(wxT("-crf")))
								{
									Command.Append(wxString::Format(wxT(" ") + InputFiles[f]->VideoStreams[v]->EncodingSettings.Bitrate));
								}
								else
								{
									Command.Append(wxString::Format(wxT(" -b:v:%i ") + InputFiles[f]->VideoStreams[v]->EncodingSettings.Bitrate, vid_count));
								}
                            }
                            if(!InputFiles[f]->VideoStreams[v]->EncodingSettings.FrameRate.IsEmpty())
                            {
                                Command.Append(wxString::Format(wxT(" -r:v:%i ") + InputFiles[f]->VideoStreams[v]->EncodingSettings.FrameRate, vid_count));
                            }
                            if(!InputFiles[f]->VideoStreams[v]->EncodingSettings.AspectRatio.IsEmpty())
                            {
                                Command.Append(wxString::Format(wxT(" -aspect:v:%i ") + InputFiles[f]->VideoStreams[v]->EncodingSettings.AspectRatio, vid_count));
                            }
                            if(!InputFiles[f]->VideoStreams[v]->EncodingSettings.MacroblockDecision.IsEmpty())
                            {
                                Command.Append(wxString::Format(wxT(" -mbd:v:%i ") + InputFiles[f]->VideoStreams[v]->EncodingSettings.MacroblockDecision, vid_count));
                            }
                            if(!InputFiles[f]->VideoStreams[v]->EncodingSettings.MacroblockComparsion.IsEmpty())
                            {
                                Command.Append(wxString::Format(wxT(" -mbcmp:v:%i ") + InputFiles[f]->VideoStreams[v]->EncodingSettings.MacroblockComparsion, vid_count));
                            }
                            if(!InputFiles[f]->VideoStreams[v]->EncodingSettings.MotionEstimationComparsion.IsEmpty())
                            {
                                Command.Append(wxString::Format(wxT(" -cmp:v:%i ") + InputFiles[f]->VideoStreams[v]->EncodingSettings.MotionEstimationComparsion, vid_count));
                            }
                            if(!InputFiles[f]->VideoStreams[v]->EncodingSettings.PreMotionEstimationComparsion.IsEmpty())
                            {
                                Command.Append(wxString::Format(wxT(" -precmp:v:%i ") + InputFiles[f]->VideoStreams[v]->EncodingSettings.PreMotionEstimationComparsion, vid_count));
                            }
                            if(!InputFiles[f]->VideoStreams[v]->EncodingSettings.SubMotionEstimationComparsion.IsEmpty())
                            {
                                Command.Append(wxString::Format(wxT(" -subcmp:v:%i ") + InputFiles[f]->VideoStreams[v]->EncodingSettings.SubMotionEstimationComparsion, vid_count));
                            }
                            if(!InputFiles[f]->VideoStreams[v]->EncodingSettings.MinQuantization.IsEmpty())
                            {
                                Command.Append(wxString::Format(wxT(" -qmin:v:%i ") + InputFiles[f]->VideoStreams[v]->EncodingSettings.MinQuantization, vid_count));
                            }
                            if(!InputFiles[f]->VideoStreams[v]->EncodingSettings.MaxQuantization.IsEmpty())
                            {
                                Command.Append(wxString::Format(wxT(" -qmax:v:%i ") + InputFiles[f]->VideoStreams[v]->EncodingSettings.MaxQuantization, vid_count));
                            }
                            if(InputFiles[f]->VideoStreams[v]->EncodingSettings.Trellis)
                            {
                                Command.Append(wxString::Format(wxT(" -trellis:v:%i 1"), vid_count));
                            }
                            if(/*InputFiles[f]->VideoStreams[v]->EncodingSettings.Trellis || */InputFiles[f]->VideoStreams[v]->EncodingSettings.GMC || InputFiles[f]->VideoStreams[v]->EncodingSettings.QPEL)
                            {
                                Command.Append(wxString::Format(wxT(" -flags:v:%i "), vid_count));
                                // FIXME: deprecated, use mpegvideo private options instead
                                /*
                                if(InputFiles[f]->VideoStreams[v]->EncodingSettings.Trellis)
                                {
                                    Command.Append(wxT("+cbp"));
                                }
                                */
                                if(InputFiles[f]->VideoStreams[v]->EncodingSettings.GMC)
                                {
                                    Command.Append(wxT("+gmc"));
                                }
                                if(InputFiles[f]->VideoStreams[v]->EncodingSettings.QPEL)
                                {
                                    Command.Append(wxT("+qpel"));
                                }
                            }
                            // video filters
                            //{
                                wxString filters = wxEmptyString;
                                bool append = false;

                                if(InputFiles[f]->VideoStreams[v]->EncodingSettings.Crop[0] > 0)
                                {
                                    if(append)
                                    {
                                        filters.append(wxT(","));
                                    }
                                    filters.append(wxString::Format(wxT("crop=%i:%i:%i:%i"), InputFiles[f]->VideoStreams[v]->EncodingSettings.Crop[1], InputFiles[f]->VideoStreams[v]->EncodingSettings.Crop[2], InputFiles[f]->VideoStreams[v]->EncodingSettings.Crop[3], InputFiles[f]->VideoStreams[v]->EncodingSettings.Crop[4]));
                                    append = true;
                                }
                                if(InputFiles[f]->VideoStreams[v]->EncodingSettings.FrameSize.Contains(wxT("x")))
                                {
                                    if(append)
                                    {
                                        filters.append(wxT(","));
                                    }
                                    filters.append(wxT("scale=") + InputFiles[f]->VideoStreams[v]->EncodingSettings.FrameSize.Before('x') + wxT(":") + InputFiles[f]->VideoStreams[v]->EncodingSettings.FrameSize.After('x'));
                                    append = true;
                                }
                                if(InputFiles[f]->VideoStreams[v]->EncodingSettings.Deinterlace)
                                {
                                    if(append)
                                    {
                                        filters.append(wxT(","));
                                    }
                                    filters.append(wxT("yadif=1"));
                                    append = true;
                                }

                                if(!filters.IsEmpty())
                                {
                                    Command.Append(wxString::Format(wxT(" -filter:v:%i \"") + filters + wxT("\""), vid_count));
                                }
                            //}
                            switch(PassNumber)
                            {
                                case FirstPass:     Command.Append(wxString::Format(wxT(" -pass:v:%i 1"), vid_count));
                                                    break;
                                case SecondPass:    Command.Append(wxString::Format(wxT(" -pass:v:%i 2"), vid_count));
                                                    break;
                                default:            break;
                            }
                        }
                        vid_count++;
                    }
                }
            }
            if(vid_count == 0)
            {
                Command.Append(wxT(" -vn"));
            }
        }
        else
        {
            Command.Append(wxT(" -vn"));
        }
    //}

    // trim
    //{
        if(!StartTime.IsEmpty())
        {
            Command.Append(wxT(" -ss ") + StartTime);
        }

        if(!Duration.IsEmpty())
        {
            Command.Append(wxT(" -t ") + Duration);
        }
    //}

    // output file
    //{
        if(PassNumber == FirstPass)
        {
            #ifdef __LINUX__
            Command.Append(wxT(" -y /dev/null"));
            #endif
            #ifdef __WINDOWS__
            Command.Append(wxT(" -y NUL"));
            #endif
        }
        else
        {
            Command.Append(wxT(" -y \"") + OutputFileName + wxT("\""));
        }
    //}

    return Command;
}
