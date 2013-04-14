#ifndef ENCODINGTASK_H
#define ENCODINGTASK_H

#include "EncodingFileLoader.h"
#include "EncodingFileSaver.h"

// Impact on GUI higher than expected... Branch dropped
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
    public: EncodingFileLoaderArray InputFiles;
    public: wxFileName OutputFile;
    public: wxString OutputFormat;
    public: bool TwoPass;
    public: bool RemoveMetadata;
    public: bool RemoveChapters;
    public: wxArrayString GetCommands();
    private: wxString GetCommand(Pass PassNumber = NoPass);
};

WX_DEFINE_ARRAY(FileSegment*, FileSegmentArray);

class EncodingTask
{
    public: EncodingTask();
    public: virtual ~EncodingTask();

    // all output segments encoded by this task
    public: FileSegmentArray OutputFileSegments;
    // if task contains more han one segment, set this option true to concat the segments into a single file
    public: bool OutputSegmentsConcat;
    // base output filename for all segments (segment filenames will be generated in GetCommands())
    public: wxFileName BaseOutputFile;
    // return the commands for this encoding task (number depending on segments & multipass count)
    public: wxArrayString GetCommands();
};

WX_DEFINE_ARRAY(EncodingTask*, EncodingTaskArray);

#endif // ENCODINGTASK_H
