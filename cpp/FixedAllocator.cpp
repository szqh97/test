#include "FixedAllocator.h"
#include <assert.h>
void* FixedAllocator::Allocate()
{
    if (allocChunk_ == 0 || allocChunk_->blocksAvailable_ == 0)
    {
        // No available memory in this Chunk
        // Tyr to fidn one
        Chunks::iterator i = chunks_.begin();
        for(;; ++i)
        {
            if (i == chunks_.end())
            {
                // All filled up - add a new chunk
                chunks_.push_back(Chunk());
                Chunk& newChunk = chunks_.back();
                newChunk.Init(blockSize_, numBlocks_);
                allocChunk_ = &newChunk;
                deallocChunk_ = &chunks_.front();
                break;
            }

            if (i->blocksAvailable_ > 0)
            {
                // Found a chunk
                allocChunk_ = &*i;
                break;
            }
        }
    }
    assert(allocChunk_ != 0);
    assert(allocChunk_->blocksAvailable_ > 0);
    return (allocChunk_->Allocate(blockSize_));
}

