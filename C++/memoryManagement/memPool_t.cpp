#include "memManager_t.h"
#include "memPool_t.h"
#include "memPage_t.h"
#include <stdlib.h>
#include <vector>

size_t MemPool_t::defaultPageSize = 6;

MemPool_t::MemPool_t(){
    MemPage_t firstPage;
    pageVec = new std::vector<MemPage_t>();
    firstPage = new MemPage_t(defaultPageSize);
    pageVec.push_back(firstPage);
    pageSize = defaultPageSize;
}

MemPool_t::~MemPool_t(){
    int i;
    for (i=0; i<pageVec.size(); i++)
        delete pageVec[i];
    delete pageVec;
}

bool MemPool_t::bufferCpy(char* buf1, const char* buf2, size_t numOfBytes, size_t position, size_t upperLimit){
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

bool MemPool_t::read (void* target, size_t numOfBytes, size_t position) const{ 
    char* targetStr = (char*) target;
    MemPage_t page;
    size_t leftInPage;
    size_t leftToRead = numOfBytes;
    if (position > getSize())
        return false;
    setPosition(position);
    page = pageVec[getCurrentPageNumber()];
    leftInPage = pageSize - getPositionInPage();
    while (leftToRead > leftInPage){
        page.read(target, leftInPage, getPositionInPage());
        setPosition(getPosition() + leftInPage);
        if ()
    }

    //return bufferCpy(targetStr, byteStream + position, numOfBytes, position, getSize());
}
        
bool MemPool_t::read (void* target, size_t numOfBytes) const{
    return read(target, numOfBytes, getPosition());
}


bool MemPage_t::write (const void* source, size_t numOfBytes, size_t position){ 
    char* sourceStr = (char*) source;
    return bufferCpy(byteStream + position, sourceStr, numOfBytes, position, capacity);
}

bool MemPage_t::write (const void* source, size_t numOfBytes){ 
    return write(source, numOfBytes, getPosition());
}