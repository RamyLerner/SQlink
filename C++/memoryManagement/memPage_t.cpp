#include "memManager_t.h" 
#include "memPage_t.h"
#include <stdlib.h>
#include <cstring>
#include <algorithm>
#include <string>

size_t MemPage_t::defaultCapacity = 6;

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

size_t MemPage_t::read (void* target, size_t numOfBytes, size_t pos) { 
    if (pos > getSize())
        throw std::string("Invalid position");
    numOfBytes = min(numOfBytes, getSize() - pos);
    std::memcpy(target, byteStream + pos, numOfBytes);
    setPosition(pos + numOfBytes);
    return numOfBytes; 
}
        
size_t MemPage_t::read (void* target, size_t numOfBytes) {
    return read(target, numOfBytes, getPosition());
}


size_t MemPage_t::write (const void* source, size_t numOfBytes, size_t pos){ 
    if (pos > getSize())
        throw std::string("Invalid position");
    numOfBytes = min(numOfBytes, capacity - pos);
    std::memcpy(byteStream + pos, source, numOfBytes);
    setPosition(pos + numOfBytes);
    if (getPosition() > getSize())
        setSiz  e(getPosition());
    return numOfBytes; 
}

size_t MemPage_t::write (const void* source, size_t numOfBytes){ 
    return write(source, numOfBytes, getPosition());
}