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
    public: FileSegment(int64_t StartTime, int64_t EndTime);
    public: virtual ~FileSegment();

    //public: int64_t TimestampTo;
    //public: int64_t TimestampFrom;
    public: int64_t TimeTo; // end time in milli seconds
    public: int64_t TimeFrom; // start time in milli seconds
    //public: wxString TimecodeTo;
    //public: wxString TimecodeFrom;
    //public: wxString TimecodeDuration;
};

WX_DEFINE_ARRAY(FileSegment*, FileSegmentArray);

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
    private: wxString GetCommandAVConv(wxString OutputFileName, wxString StartTime, wxString Duration, Pass PassNumber = NoPass);
};

WX_DEFINE_ARRAY(EncodingTask*, EncodingTaskArray);

#endif // ENCODINGTASK_H
