#include <assert.h>
#include "FixedAllocator.h"

void* FixedAllocator::Allocate()
{
    if (allockChunk_ == 0 || allockChunk_->blocksAvailable_ == 0)
    {
        // No available memory in this chunk
        // Try to find one
        Chunk::iterator i = chunks_.begin();
        for(;; ++i)
        {
            if (i == chunks_.end())
            {
                // All filled up - add a new chunk
                chunks_.push_back(Chunk());
                Chunk& newChunk = chunks_.back();
                newChunk.Init(blockSize_, numBlocks_);
                allockChunk_ = &newChunk;
                deallocChunk_ = &chunks_.front();
                break;
            }
            if (i->blocksAvailable_ > 0)
            {
                // Found a chunk
                allockChunk_ = &*i;
                break;
            }

        }
    }
    assert(allockChunk_ != 0);
    assert(allockChunk_->blocksAvailable_ >0);
    return allockChunk_->Allocate(blockSize_);
}

