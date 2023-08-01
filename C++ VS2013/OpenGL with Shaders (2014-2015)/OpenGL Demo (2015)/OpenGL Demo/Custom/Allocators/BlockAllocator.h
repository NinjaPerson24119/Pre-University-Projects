#ifndef CTM_BLOCKALLOCATOR_H
#define CTM_BLOCKALLOCATOR_H

#include "Allocator.h"
#include "CtnCompAllocator.h"

namespace ctm
{

namespace allocs
{

//////
//Block Allocator
class BlockAllocator : Allocator, CtnCompAllocator
{
	//Free Block
	class FreeBlock
	{
	public:
		uintptr_t sizebytes;
		FreeBlock *next;
	};
	//Used Block
	class UsedBlock
	{
	public:
		uintptr_t sizebytes;
		uintptr_t misalignment;
	};
public:
	//Base
		BlockAllocator(char *Pool, uintptr_t PoolSize, void (*Deallocator)(void*), uintptr_t BlockSize = 0, bool OptimizeForMemory = false);
		~BlockAllocator();
	//Memory
		void *Allocate(uintptr_t SizeBytes, uintptr_t Alignment = ALLOCATOR_ALIGNMENT);
		void Deallocate(void *Pointer);
		void Clear();
	//Profiling
		uintptr_t Capacity();
		uintptr_t MemoryUsed();
		uintptr_t MemoryPeak();
		uintptr_t Allocations();
		uintptr_t Actual();
private:
	//Inaccessible
		BlockAllocator(BlockAllocator &Rhs);
		BlockAllocator &operator=(BlockAllocator &Rhs);
	char *pool;
	FreeBlock *freelist;
	void (*deallocator)(void*);
	uintptr_t poolsize;
	uintptr_t blocksize;
	uintptr_t memoryused;
	uintptr_t memorypeak;
	uintptr_t allocations;
	bool optimizeformemory;
};
//////

}}

#endif