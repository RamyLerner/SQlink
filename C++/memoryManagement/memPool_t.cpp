#include "memManager_t.h"
#include "memPool_t.h"
#include "memPage_t.h"
#include <stdlib.h>
#include <vector>
#include <string>
#include <algorithm>


MemPool_t::MemPool_t()
{
    MemPage_t *firstPage = new MemPage_t(getDefaultPageSize());
    pageVec.push_back(firstPage);
    pageSize = getDefaultPageSize();
}

MemPool_t::~MemPool_t()
{
    size_t i;
    for (i = 0; i < pageVec.size(); i++)
        delete pageVec[i];
}

size_t MemPool_t::read(void *target, size_t numOfBytes, size_t pos)
{
    char *targetStr = (char *)target;
    MemPage_t* pagePt;
    size_t leftInPage, result, pageNum;
    size_t leftToRead = numOfBytes;

    setPosition(pos);
    pageNum = getCurrentPageNumber();
    pagePt = pageVec[pageNum];
    pagePt->setPosition(getPositionInPage());
    leftInPage = min(pageSize - getPositionInPage(), leftToRead);
    while (leftToRead > 0 && pageNum < pageVec.size())
    {
        result = pagePt->read(targetStr, min(leftInPage, leftToRead));
        setPosition(getPosition() + result);
        targetStr += result;
        leftToRead -= result;
        pageNum++;
        if (leftToRead > 0 && pageNum < pageVec.size())
        {    
            pagePt = pageVec[pageNum];
            pagePt->setPosition(0);
            leftInPage = (pageNum == pageVec.size() - 1) ? getSize()%pageSize  : pageSize;
        }
    }
    return numOfBytes - leftToRead;
}

size_t MemPool_t::read(void *target, size_t numOfBytes)
{
    return read(target, numOfBytes, getPosition());
}

size_t MemPool_t::write(const void *source, size_t numOfBytes, size_t pos)
{
    char *sourceStr = (char *)source;
    MemPage_t* pagePt;
    size_t leftInPage, result, pageNum;
    size_t leftToWrite = numOfBytes;

    setPosition(pos);
    pageNum = getCurrentPageNumber();
    pagePt = pageVec[pageNum];
    pagePt->setPosition(getPositionInPage());
    leftInPage = min(pageSize - getPositionInPage(), leftToWrite);
    while (leftToWrite > 0)
    {
        result = pagePt->write(sourceStr, min(leftInPage, leftToWrite));
        setPosition(getPosition() + result);
        sourceStr += result;
        leftToWrite -= result;
        pageNum++;
        if (leftToWrite > 0)
        {    
            if (pageNum == pageVec.size())
                pageVec.push_back(new MemPage_t(pageSize));
            pagePt = pageVec[pageNum];
            pagePt->setPosition(0);
            leftInPage = pageSize;
        }
    }
    if (getPosition() > getSize())
        setSize(getPosition());
    return numOfBytes;
}

size_t MemPool_t::write(const void *source, size_t numOfBytes)
{
    return write(source, numOfBytes, getPosition());
}