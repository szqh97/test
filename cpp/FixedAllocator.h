#include "Chunk.h"
#include <vector>
class FixedAllocator
{
public:
    void* Allocate();

private:
    std::size_t blockSize_;
    unsigned char numBlocks_;
    typedef std::vector<Chunk> Chunks;
    Chunks chunks_;
    Chunk* allocChunk_;
    Chunk* deallocChunk_;
};
