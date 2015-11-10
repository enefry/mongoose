#include "DataBuffer.h"
#include <string.h>
#include <stdlib.h>
#include <malloc.h>
#include <assert.h>
#include <stdio.h>
#define LogLine()

typedef int boolean;
#define True 1
#define False 0



static boolean DataBufferReallocMemory(DataBuffer*This,unsigned int size)
{
    if( size<= This->_capacity ){
        return True;
    }
    // 使用 relloc 减少复制内存
    void *temp = malloc(size);
    if(temp==NULL){
        return False;
    }
    //    memset(temp,0,size);
    if(This->_data!=NULL){
        memcpy (temp,This->_data+This->_offset,This->_size);
        free(This->_data);
    }
    This->_data = (char*)temp;
    This->_offset = 0;
    This->_capacity = size;
    return True;
}

static boolean DataBufferSizeIncrease(DataBuffer*This,unsigned int size)
{
    if(size == 0){
        size = (This->_capacity + 128) >> 1 ;
    }
    return DataBufferReallocMemory (This, This->_capacity+size);
}

void DataBufferInitial(DataBuffer*This)
{
    This->_data = NULL;
    This->_offset = 0;
    This->_capacity = 0;
    This->_size = 0;
    DataBufferSizeIncrease (This,16);
}

void DataBufferDealloc(DataBuffer*This)
{
    This->_size = 0;
    This->_offset = 0;
    This->_capacity = 0;
    if(NULL!=This->_data){
        free(This->_data);
    }
    This->_data = NULL;
}




//void AEDataBuffer::append(const void* v,int length){
    //计算剩余容量
//    if( _size + length >= _capacity){
//        //内存增长....
//        bool increaseRet =  sizeIncrease ( length - _capacity  + 64 );
//        assert(increaseRet);
//        if(!increaseRet){
//            printf("Exception!!!!!! No more memory: %s %d",__FUNCTION__,__LINE__);
//            // do nothing
//            return;
//        }
//    }
//    if( _size + _offset + length >= _capacity){
//        memmove (_data,_data+_offset,_size);
//        _offset = 0;
//    }
//    memcpy(_data + _offset + _size,v,length);
//    _size+=length;
//}

//const char *AEDataBuffer::ptr() const
//{
//    return _data+_offset;
//}

//void AEDataBuffer::popLength(unsigned int length)
//{
//    if( length >= _size ){
//        _offset = 0;
//        _size =0;
//    }else {
//        _offset+=length;
//        _size -= length;
//    }
//}

//void AEDataBuffer::removeAll()
//{
//    _offset = 0;
//    _size = 0;
//}


unsigned int DataBufferSize(DataBuffer*This){
    return This->_size;
}

unsigned int DataBufferCount(DataBuffer*This){
    return This->_size;
}

unsigned int DataBufferLength(DataBuffer*This){
    return This->_size;
}

const char*  DataBufferPtr(DataBuffer*This){
    return This->_data + This->_offset;
}

void DataBufferpopLength(DataBuffer*This,unsigned int length){
    if( length >= This->_size ){
        This->_offset = 0;
        This->_size =0;
    }else {
        This->_offset+=length;
        This->_size -= length;
    }
}


void DataBufferremoveAll(DataBuffer*This){
    This->_offset = 0;
    This->_size = 0;
}


#define APPEND(v)  DataBufferAppendChars(This,&v,sizeof(v));

void DataBufferAppendChar(DataBuffer*This,char v)
{
    APPEND(v);
}


void DataBufferAppendUChar(DataBuffer*This,unsigned char v)
{
    APPEND(v);
}


void DataBufferAppendShort(DataBuffer*This,short v)
{
    APPEND(v);
}


void DataBufferAppendUShort(DataBuffer*This,unsigned short v)
{
    APPEND(v);
}


void DataBufferAppendInt(DataBuffer*This,int v)
{
    APPEND(v);
}


void DataBufferAppendUInt(DataBuffer*This,unsigned int v)
{
    APPEND(v);
}


void DataBufferAppendLong(DataBuffer*This,long v)
{
    APPEND(v);
}


void DataBufferAppendULong(DataBuffer*This,unsigned long v)
{
    APPEND(v);
}


void DataBufferAppendLongLong(DataBuffer*This,long long v)
{
    APPEND(v);
}


void DataBufferAppendULongLong(DataBuffer*This,unsigned long long v)
{
    APPEND(v);
}


void DataBufferAppendChars(DataBuffer*This,const void *v, int length)
{
    //计算剩余容量
    if( This->_size + length >= This->_capacity){
        //内存增长....
        boolean increaseRet =  DataBufferSizeIncrease (This, length +This->_size - This->_capacity  + 64 );
        assert(increaseRet);
        if(!increaseRet){
            printf("Exception!!!!!! No more memory: %s %d",__FUNCTION__,__LINE__);
            // do nothing
            return;
        }
    }
    if(This-> _size + This->_offset + length >=This-> _capacity){
        memmove (This->_data,This->_data+This->_offset,This->_size);
        This->_offset = 0;
    }
    memcpy(This->_data +This-> _offset + This->_size,v,length);
    This->_size+=length;
}
