#ifndef CTM_OVERRIDEMEMORY_H
#define CTM_OVERRIDEMEMORY_H

#include <Custom/Memory/BlockAllocator.h>

namespace ctm
{

void SetMemoryAllocator(BlockAllocator *Allocator);
void SetMemoryAlignment(uintptr_t Alignment);

}

#endif