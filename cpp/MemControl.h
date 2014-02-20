#ifndef _MEMCONTROL_H_
#define _MEMCONTROL_H_
#include <iostream>
struct MemControlBlock
{
    std::size_t size_ : 31;
    bool        available_ : 1;
};

// Nothing is private - Chunk is a Plain Old Data structure
// structure defined inside FixedAllocator
// and manipulated only by it
struct Chunk
{
    void Init(std::size_t blockSize, unsigned char blocks);
    void Release();
    void* Allocate(std::size_t blockSize);
    void Deallocate(void* p, std::size_t blockSize);
    unsigned char* pData_;
    unsigned char firstAvailableBlock_, blocksAvailable_;
};
#endif
