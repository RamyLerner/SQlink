#ifndef MEM_MANAGER_H
#define MEM_MANAGER_H

#include <stdlib.h>
#include <string>

class MemManager_t
{
public:
    virtual ~MemManager_t();
    MemManager_t();
    
    inline  size_t getPosition() const;
    inline void setPosition(size_t position);
    inline  size_t getSize() const;
    inline  bool isEmpty() const;
    virtual size_t read(void *target, size_t numOfBytes, size_t position)  = 0;
    virtual size_t read(void *target, size_t numOfBytes)  = 0;
    virtual size_t write(const void *source, size_t numOfBytes, size_t position) = 0;
    virtual size_t write(const void *source, size_t numOfBytes) = 0;

protected:   
    inline void setSize(size_t s);

private:
    MemManager_t(const MemManager_t &mm);
    MemManager_t &operator=(const MemManager_t& mm);

    size_t size;
    size_t position;
};

inline size_t MemManager_t::getPosition() const { return position; }
inline void MemManager_t::setPosition(size_t pos)
{
    if (pos <= size){
        position = pos;  
    }
    else
    {
        throw std::string("Invalid position!");
    }  
}
inline size_t MemManager_t::getSize() const { return size; }
inline void MemManager_t::setSize(size_t s) { size = s;}
inline bool MemManager_t::isEmpty() const { return !size; }
#endif