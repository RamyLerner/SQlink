#include "memManager_t.h" 
#include "memPage_t.h"
#include <stdlib.h>

size_t MemPage_t::defaultCapacity = 1024;

MemPage_t::MemPage_t(){
    capacity = defaultCapacity;
    byteStream = new char[capacity];
}

MemPage_t::MemPage_t(size_t capacity){
    capacity = capacity;
    byteStream = new char[capacity];
}

MemPage_t::~MemPage_t(){
    delete[] byteStream;
}

bool MemPage_t::bufferCpy(char* buf1, const char* buf2, size_t numOfBytes, size_t position, size_t upperLimit){
    int offset = 0;
    if (position > getSize())
        return false;

    setPosition(position);
    while (position < upperLimit && offset < numOfBytes){
            buf1[offset] = buf2[offset];
            offset ++;
            position ++;
            setPosition(position);
    }
    return offset==numOfBytes ? 1 : 0;
}

bool MemPage_t::read (void* target, size_t numOfBytes, size_t position) const{ 
    char* targetStr = (char*) target;
    return bufferCpy(targetStr, byteStream + position, numOfBytes, position, getSize());
}
        
bool MemPage_t::read (void* target, size_t numOfBytes) const{
    return read(target, numOfBytes, getPosition());
}


bool MemPage_t::write (const void* source, size_t numOfBytes, size_t position){ 
    char* sourceStr = (char*) source;
    return bufferCpy(byteStream + position, sourceStr, numOfBytes, position, capacity);
}

bool MemPage_t::write (const void* source, size_t numOfBytes){ 
    return write(source, numOfBytes, getPosition());
}