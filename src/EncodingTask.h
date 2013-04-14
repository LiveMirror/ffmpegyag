#ifndef ENCODINGTASK_H
#define ENCODINGTASK_H

#include "EncodingFileLoader.h"
#include "EncodingFileSaver.h"

enum Pass
{
    NoPass, // No-Pass processing (default)
    FirstPass, // Two-Pass first pass
    SecondPass // Two-Pass seconf pass
};

class FileSegment
{
    public: FileSegment(wxFileName FileOut, int64_t StartTime, int64_t EndTime);
    public: virtual ~FileSegment();

    wxFileName OutputFile; // file where the segment will be stored
    public: int64_t TimeFrom; // start time in milli seconds
    public: int64_t TimeTo; // end time in milli seconds
    public: int FilterVideoFadeIn; // fade in time for video in milli seconds
    public: int FilterVideoFadeOut; // fade out time for video in milli seconds
    public: int FilterAudioFadeIn; // fade in time for audio in milli seconds
    public: int FilterAudioFadeOut; // fade out time for audio in milli seconds
};

WX_DEFINE_ARRAY(FileSegment*, FileSegmentArray);

// TODO: refactoring of structure
// OutputFormat, InputSegments, TwoPass, RemoveMetadata, RemoveChapters
// should moved into OutputSegment Structure so it could accessed by
// EncodingTask->OutputSegments[SegmentIndex]->InputFiles[InputFileIndex]->VideoStreams[VideoStreamIndex].EncodingSettings
class EncodingTask
{
    public: EncodingTask();
    public: virtual ~EncodingTask();

    public: EncodingFileLoaderArray InputFiles;
    public: wxFileName OutputFile;
    public: wxString OutputFormat;
    public: FileSegmentArray OutputSegments;
    // if task contains more han one segment, set this option true to concat the segments into a single file
    public: bool OutputSegmentsConcat;
    public: bool TwoPass;
    public: bool RemoveMetadata;
    public: bool RemoveChapters;

    // return the commands for this encoding task (number depending on segments & multipass count)
    public: wxArrayString GetCommands();
    // return the command for use with avconv
    private: wxString GetCommandAVConv(FileSegment* Segment, Pass PassNumber = NoPass);
};

WX_DEFINE_ARRAY(EncodingTask*, EncodingTaskArray);

#endif // ENCODINGTASK_H
