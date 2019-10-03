#ifndef MEM_POOL_H
#define MEM_POOL_H

#include <stdlib.h>
#include "memManager_t.h"
#include "memPage_t.h"
#include <vector>

class MemPool_t : public MemManager_t
{
public:
    
    virtual ~MemPool_t();
    MemPool_t();

    inline  size_t getPageSize() const;
    inline static void setDefaultPageSize(size_t num);
    inline static size_t getDefaultPageSize();
    virtual size_t read(void *target, size_t numOfBytes, size_t position);
    virtual size_t read(void *target, size_t numOfBytes);
    virtual size_t write(const void *source, size_t numOfBytes, size_t position);
    virtual size_t write(const void *source, size_t numOfBytes);

private:
    size_t pageSize;
    std::vector<MemPage_t*> pageVec;

    MemPool_t &operator=(const MemPool_t &mp);
    MemPool_t(const MemPool_t &mp);
    inline  int getCurrentPageNumber() const;
    inline  int getPositionInPage() const;

};

inline size_t MemPool_t::getPageSize() const { return pageSize;}
inline int MemPool_t::getCurrentPageNumber() const { return getPosition() / pageSize;} 
inline int MemPool_t::getPositionInPage() const { return getPosition() % pageSize;}
inline  void MemPool_t::setDefaultPageSize(size_t num) { MemPage_t::setDefaultCapacity(num);}
inline  size_t MemPool_t::getDefaultPageSize() { return MemPage_t::getDefualtCapacity();}

#endif