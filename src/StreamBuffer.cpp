#include "StreamBuffer.h"

StreamBuffer::StreamBuffer()
{
    Type = FIFO;
    Size = 32;
}

StreamBuffer::StreamBuffer(BufferType QueueType, size_t QueueSize)
{
    Type = QueueType;
    Size = QueueSize;
}

StreamBuffer::~StreamBuffer()
{
    if(!IsEmpty())
    {
        // memory leak: buffer not pulled empty
        // we cannot delete type void*
        //WX_CLEAR_ARRAY(Queue);
        Queue.Clear();
    }
}

bool StreamBuffer::IsEmpty()
{
    if(Queue.GetCount() > 0)
    {
        return false;
    }
    return true;
}

bool StreamBuffer::IsFull()
{
    if(Queue.GetCount() < Size)
    {
        return false;
    }
    return true;
}

void StreamBuffer::Push(void* Data)
{
    if(!IsFull())
    {
        if(Type == FIFO)
        {
            Queue.Add(Data);
        }
    }
    // buffer overflow
}

void* StreamBuffer::Pull()
{
    void* Data = NULL;
    if(!IsEmpty())
    {
        if(Type == FIFO)
        {
            Data = Queue[0];
            Queue[0] = NULL;
            Queue.RemoveAt(0);
        }
    }
    // buffer underrun
    return Data;
}