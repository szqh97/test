#ifndef _CHUNK_H_
#define _CHUNK_H_
#include <iostream>
// Nothing is private - chunk is a Plain Old Data structure
// structure defined inside FixAllocator
// and manipulated only by it
struct Chunk
{

    void Init(std::size_t blockSize, unsigned char blocks);
    void Release();
    void* Allocate(std::size_t blockSize);
    void Deallocate(void* p, std::size_t blockSize);
    unsigned char* pData_;
    unsigned char 
        firstAvailableBlock_,
        blocksAvailable_;
};
#endif


