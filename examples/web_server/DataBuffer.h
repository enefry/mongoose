#ifndef AEDATABUFFER_H
#define AEDATABUFFER_H

//#include <string>
typedef struct DATABUFFER{
    // 输入数据
    unsigned int _capacity ;
    char* _data ;
    unsigned int _offset ;
    unsigned int _size ;
}DataBuffer;

void DataBufferInitial(DataBuffer*);
void DataBufferDealloc(DataBuffer*);
unsigned int DataBufferSize(DataBuffer*);
unsigned int DataBufferCount(DataBuffer*);
unsigned int DataBufferLength(DataBuffer*);
const char *DataBufferPtr(DataBuffer*);
void DataBufferpopLength(DataBuffer*,unsigned int);
void DataBufferremoveAll(DataBuffer*);

void DataBufferAppendChar(DataBuffer*,char v);
void DataBufferAppendUChar(DataBuffer*,unsigned char v);
void DataBufferAppendShort(DataBuffer*,short v);
void DataBufferAppendUShort(DataBuffer*,unsigned short v);
void DataBufferAppendInt(DataBuffer*,int v);
void DataBufferAppendUInt(DataBuffer*,unsigned int v);
void DataBufferAppendLong(DataBuffer*,long v);
void DataBufferAppendULong(DataBuffer*,unsigned long v);
void DataBufferAppendLongLong(DataBuffer*,long long v);
void DataBufferAppendULongLong(DataBuffer*,unsigned long long v);
void DataBufferAppendChars(DataBuffer*,const void* v,int length);

#endif // AEDATABUFFER_H
