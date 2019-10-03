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
        inline size_t getCapacity() const;
        inline static size_t getDefualtCapacity();
        inline static void setDefaultCapacity(size_t cap);
        virtual size_t read (void* target, size_t numOfBytes, size_t position);
        virtual size_t read (void* target, size_t numOfBytes);
        virtual size_t write (const void* source, size_t numOfBytes, size_t position);
        virtual size_t write (const void* source, size_t numOfBytes);
        


    private:
        char* byteStream;
        size_t capacity;

        static size_t defaultCapacity;
        
        MemPage_t(const MemPage_t& mp){}
        MemPage_t& operator= (const MemPage_t& mp);
};

size_t MemPage_t::getCapacity() const { return capacity;}
inline  size_t MemPage_t::getDefualtCapacity() { return defaultCapacity;}
inline  void MemPage_t::setDefaultCapacity(size_t cap) { defaultCapacity = cap;}
bool MemPage_t::isFull() const { return getSize()==capacity;}

#endif