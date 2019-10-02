#ifndef MEM_MANAGER_H
#define MEM_MANAGER_H

#include <stdlib.h>

class MemManager_t
{
public:
    MemManager_t();
    inline const size_t getPosition() const;
    inline int setPosition(size_t position);
    inline const size_t getSize() const;
    inline const bool isEmpty() const;
    virtual bool read(void *target, size_t numOfBytes, size_t position) const { return 0; }
    virtual bool read(void *target, size_t numOfBytes) const { return 0; }
    virtual bool write(const void *source, size_t numOfBytes, size_t position) { return 0; }
    virtual bool write(const void *source, size_t numOfBytes) { return 0; }

protected:
    virtual ~MemManager_t() {}

private:
    MemManager_t(const MemManager_t &mm) {}
    MemManager_t &operator=(const MemManager_t mm) {}
    size_t size;
    size_t position;
};

const size_t MemManager_t::getPosition() const { return position; }
int MemManager_t::setPosition(size_t position)
{
    if (position < size){
        position = position;
        return 1;
    }
    return 0;
}
const size_t MemManager_t::getSize() const { return size; }
const bool MemManager_t::isEmpty() const { return !size; }
#endif