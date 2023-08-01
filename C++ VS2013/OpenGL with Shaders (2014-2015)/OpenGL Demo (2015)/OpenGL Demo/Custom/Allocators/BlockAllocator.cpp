#include "BlockAllocator.h"
#include <stdexcept>

namespace ctm
{

namespace allocs
{

//Constructor
BlockAllocator::BlockAllocator(char *Pool, uintptr_t PoolSize, void (*Deallocator)(void*), uintptr_t BlockSize, bool OptimizeForMemory):
pool(Pool),
deallocator(Deallocator),
poolsize(PoolSize),
blocksize(BlockSize),
optimizeformemory(OptimizeForMemory)
{
	Clear();
}

//Destructor
BlockAllocator::~BlockAllocator()
{
	if(deallocator != nullptr)
		deallocator(pool);
}

//Allocate
void *BlockAllocator::Allocate(uintptr_t SizeBytes, uintptr_t Alignment)
{	
	//Round allocation size to next full block size
	if(blocksize != 0)
		SizeBytes += SizeBytes % blocksize;

	//Search for FreeBlock
	FreeBlock *iter = freelist;
	FreeBlock *smallestfit = nullptr;
	for(iter; iter != nullptr; iter = iter->next)
	{
		if(optimizeformemory == false)
		{
			if(iter->sizebytes >= SizeBytes + ((uintptr_t)iter + sizeof(UsedBlock)) % Alignment)
				break;
		}
		else
		{
			if(smallestfit == nullptr && iter->sizebytes >= SizeBytes + ((uintptr_t)iter + sizeof(UsedBlock)) % Alignment) //Check that a block has been found
				smallestfit = iter;
			else if(smallestfit != nullptr)
				if(iter->sizebytes < smallestfit->sizebytes && iter->sizebytes >= SizeBytes + ((uintptr_t)iter + sizeof(UsedBlock)) % Alignment) //Check if this block is smaller and still big enough
					smallestfit = iter;
			if(smallestfit != nullptr) //Break if smallest possible block is found
				if(smallestfit->sizebytes == SizeBytes + ((uintptr_t)smallestfit + sizeof(UsedBlock)) % Alignment)
					break;
		}
	}
	if(optimizeformemory == true)
		iter = smallestfit;


	if(iter == nullptr)
	{
		throw std::runtime_error("BlockAllocator - Allocation failed! Out of memory!\n");
	}

	//Search for previous FreeBlock
	FreeBlock *previous = freelist;
	for(previous; previous != nullptr; previous = previous->next)
	{
		if(previous->next == iter)
			break;
	}

	//Remove UsedBlock from freelist
	if(previous != nullptr)
		previous->next = iter->next;
	else
		freelist = iter->next;

	//Switch FreeBlock to UsedBlock
	uintptr_t actualsize = iter->sizebytes;
	uintptr_t misalignment = ((uintptr_t)iter + sizeof(UsedBlock)) % Alignment;
	UsedBlock *block = (UsedBlock*)((uintptr_t)iter + misalignment);
	block->sizebytes = SizeBytes;
	block->misalignment = misalignment;

	//Make new free block
	FreeBlock *newblock;
	if(actualsize - block->sizebytes - block->misalignment >= blocksize + sizeof(FreeBlock))
	{
		newblock = (FreeBlock*)((uintptr_t)block + block->sizebytes + sizeof(UsedBlock));
		newblock->sizebytes = actualsize - sizeof(UsedBlock) - SizeBytes - misalignment;
	
		//Link past UsedBlock
		if(previous != nullptr)
		{
			newblock->next = previous->next;
			previous->next = newblock;
		}
		else
		{
			newblock->next = nullptr;
		}
	
		//Remake freelist if required
		if(freelist != nullptr)
		{
			if(freelist->next == nullptr)
				freelist->next = newblock;
		}
		else
		{
			freelist = newblock;
		}

		//Update memory usage
		memoryused += sizeof(FreeBlock);
	}

	//Profiling
	++allocations;
	memoryused += block->sizebytes + block->misalignment;

	if(memoryused > memorypeak)
		memorypeak = memoryused;

	return (void*)((uintptr_t)block + sizeof(UsedBlock));
}

//Deallocate
void BlockAllocator::Deallocate(void *Pointer)
{
	//Validate pointer
	if(Pointer < pool || Pointer >= pool + poolsize)
		throw std::runtime_error("BlockAllocator - Deallocation failed! Invalid pointer!\n");

	//Convert pointer to UsedBlock
	UsedBlock *usedcurrent = (UsedBlock*)((uintptr_t)Pointer - sizeof(UsedBlock));

	//Convert UsedBlock to FreeBlock
	FreeBlock *freecurrent = (FreeBlock*)((uintptr_t)usedcurrent - usedcurrent->misalignment);
	freecurrent->sizebytes = usedcurrent->sizebytes + usedcurrent->misalignment;

	//Profiling
	memoryused -= freecurrent->sizebytes;

	//Search for previous FreeBlock
	FreeBlock *prev = freelist;
	for(prev; prev != nullptr; prev = prev->next)
	{
		if(prev < freecurrent && prev->next > freecurrent) //Center fit
			break;
		else if(prev > freecurrent) //Just after
			break;
		else if(prev->next == nullptr) //Last possibility
			break;
	}

	//Reset freelist
	if(prev == nullptr)
		if(freelist == nullptr)
		{
			freelist = freecurrent;
			freecurrent->next = nullptr;
		}

	//Link current into freelist
	if(prev != nullptr)
	{
		if(prev < freecurrent) //Previous is before
		{
			freecurrent->next = prev->next;
			prev->next = freecurrent;
		}
		else //Previous is after
		{
			//Find FreeBlock before previous
			FreeBlock *preprev = freelist;
			for(preprev; preprev != nullptr; preprev = preprev->next)
			{
				if(preprev->next == prev)
					break;
			}

			if(preprev != nullptr)
			{
				preprev->next = freecurrent;
				freecurrent->next = prev;
			}
			else
			{
				freelist = freecurrent;
				freecurrent->next = prev;
			}
		}
	}

	//Merge previous with current
	if(prev != nullptr)
	{
		if(((uintptr_t)prev + prev->sizebytes + sizeof(FreeBlock)) == (uintptr_t)freecurrent) //Check adjacency
		{
			prev->sizebytes += freecurrent->sizebytes + sizeof(FreeBlock);
			prev->next = freecurrent->next;
			freecurrent = prev;
			memoryused -= sizeof(FreeBlock);
		}
	}

	//Merge current with next
	if(freecurrent->next != nullptr)
	{
		if(((uintptr_t)freecurrent + freecurrent->sizebytes + sizeof(FreeBlock)) == (uintptr_t)freecurrent->next) //Check adjacency
		{
			freecurrent->sizebytes += freecurrent->next->sizebytes + sizeof(FreeBlock);
			freecurrent->next = freecurrent->next->next;
			memoryused -= sizeof(FreeBlock);
		}
	}
}

//Clear
void BlockAllocator::Clear()
{
	//Setup free list
	freelist = (FreeBlock*)pool;
	freelist->next = nullptr;
	freelist->sizebytes = poolsize - sizeof(FreeBlock);

	memoryused = sizeof(FreeBlock);
	memorypeak = memoryused;
	allocations = 0;
}

//Capacity
uintptr_t BlockAllocator::Capacity()
{
	return poolsize;
}

//Memory Used
uintptr_t BlockAllocator::MemoryUsed()
{
	return memoryused;
}

//Memory Peak
uintptr_t BlockAllocator::MemoryPeak()
{
	return memorypeak;
}

//Allocations
uintptr_t BlockAllocator::Allocations()
{
	return allocations;
}

//Actual
uintptr_t BlockAllocator::Actual()
{
	uintptr_t memfree = 0;
	for(FreeBlock *iter = freelist; iter != nullptr; iter = iter->next)
	{
		memfree += iter->sizebytes;
	}
	return memfree;
}

}}