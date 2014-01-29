#include <assert.h>
#include "Chunk.h"

void Chunk::Init(std::size_t blockSize, unsigned char blocks)
{
    pData_ = new unsigned char [blockSize * blocks];
    firstAvailableBlock_ = 0;
    blocksAvailable_ = blocks;
    unsigned char i = 0;
    unsigned char* p = pData_;
    for(; i != blocks; p += blockSize)
    {
        *p = ++i;
    }
}

void* Chunk::Allocate(std::size_t blockSize)
{
    if (!blocksAvailable_) return 0;
    unsigned char* pResult = 
        pData_ + (firstAvailableBlock_ * blockSize);

    //update firstAvailableBlock_ to point to the next block
    firstAvailableBlock_ = *pResult;
    --blocksAvailable_;
    return pResult;
}

void Chunk::Deallocate(void* p, std::size_t blockSize)
{
    assert(p >= pData_);
    unsigned char* toRelease = static_cast<unsigned char*> (p);

    // Alignment check
    assert((toRelease - pData_) % blockSize == 0);
    *toRelease = firstAvailableBlock_;
    firstAvailableBlock_ = static_cast<unsigned char>(
            (toRelease - pData_) / blockSize);

    // Truncation check
    assert(firstAvailableBlock_ == (toRelease - pData_) / blockSize);
    ++blocksAvailable_;
}
void Chunk::Release()
{
    delete []pData_;
    pData_ = NULL;
    blocksAvailable_ = firstAvailableBlock_ = 0;
}
