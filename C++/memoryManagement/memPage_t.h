#ifndef MEM_PAGE_H
#define MEM_PAGE_H

#include "memManager_t.h"
#include <stdlib.h>

using namespace std;

class MemPage_t : public MemManager_t{
    public:
        virtual ~MemPage_t();
        MemPage_t();
        MemPage_t(size_t size);
        inline bool isFull() const;
        inline const size_t getCapacity() const;
        bool read (void* target, size_t numOfBytes, size_t position) const;
        bool read (void* target, size_t numOfBytes) const;
        bool write (const void* source, size_t numOfBytes, size_t position);
        bool write (const void* source, size_t numOfBytes);
        


    private:
        char* byteStream;
        size_t capacity;

        static size_t defaultCapacity;
        MemPage_t(const MemPage_t& mp){}
        MemPage_t& operator= (const MemPage_t& mp);
        bool bufferCpy(char* buf1, const char* buf2, size_t numOfBytes, size_t position, size_t upperLimit);

};

const size_t MemPage_t::getCapacity() const{ return capacity;}

bool MemPage_t::isFull() const{ return getSize()==capacity;}

#endif