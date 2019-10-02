#ifndef MEM_POOL_H
#define MEM_POOL_H

#include <stdlib.h>
#include "memManager_t.h"
#include <vector>

class MemPool_t : public MemManager_t
{
public:
    
    virtual ~MemPool_t();
    MemPool_t();

    inline const size_t getPageSize() const;
    inline static void setDefaultPageSize(size_t num);
    inline static size_t getDefaultPageSize();
    bool read(void *target, size_t numOfBytes, size_t position) const;
    bool read(void *target, size_t numOfBytes) const;
    bool write(const void *source, size_t numOfBytes, size_t position);
    bool write(const void *source, size_t numOfBytes);

private:
    size_t pageSize;
    std::vector<MemPage_t> pageVec;

    static size_t defaultPageSize;

    MemPool_t &operator=(const MemPool_t &mp);
    MemPool_t(const MemPool_t &mp);
    inline const int getCurrentPageNumber() const;
    inline const int getPositionInPage() const;
    bool bufferCpy(char* buf1, const char* buf2, size_t numOfBytes, size_t position, size_t upperLimit);
};

const size_t MemPool_t::getPageSize(){ return pageSize;}
const int getCurrentPageNumber() const{ return size \ pageSize;} 
const int getPositionInPage() const{ return size % pageSize;}
static void setDefaultPageSize(size_t num){ MemPool_t::defaultPageSize = num;}
static size_t getDefaultPageSize() { return MemPool_t::defaultPageSize;}

#endif