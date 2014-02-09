<<<<<<< HEAD
#include <assert.h>
#include "FixedAllocator.h"

void* FixedAllocator::Allocate()
{
    if (allockChunk_ == 0 || allockChunk_->blocksAvailable_ == 0)
    {
        // No available memory in this chunk
        // Try to find one
        Chunk::iterator i = chunks_.begin();
=======
#include "FixedAllocator.h"
#include <assert.h>
void* FixedAllocator::Allocate()
{
    if (allocChunk_ == 0 || allocChunk_->blocksAvailable_ == 0)
    {
        // No available memory in this Chunk
        // Tyr to fidn one
        Chunks::iterator i = chunks_.begin();
>>>>>>> 2b807ad90ddf1ca0fb7069dd79916b5028e8d0f5
        for(;; ++i)
        {
            if (i == chunks_.end())
            {
                // All filled up - add a new chunk
                chunks_.push_back(Chunk());
                Chunk& newChunk = chunks_.back();
                newChunk.Init(blockSize_, numBlocks_);
<<<<<<< HEAD
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
=======
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
>>>>>>> 2b807ad90ddf1ca0fb7069dd79916b5028e8d0f5
}

