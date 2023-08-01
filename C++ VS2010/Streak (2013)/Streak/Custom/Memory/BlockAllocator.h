#ifndef CTM_BLOCKALLOCATOR_H
#define CTM_BLOCKALLOCATOR_H

#include <stdint.h>

namespace ctm
{

//////
//Block Allocator
class BlockAllocator
{
public:
	//Support
		enum Optimization { MEMORY, SPEED }; 
	//Base
		BlockAllocator(char *Heap, uintptr_t HeapSize, void (*Deallocator)(void*), Optimization Choice = SPEED);
		~BlockAllocator();
	//Memory
		void Clear();
		void *Allocate(uintptr_t Size, uintptr_t Alignment = 4);
		void Deallocate(void *Target);
	//Configuration
		void Optimize(Optimization Choice) { optimization = Choice; }
		Optimization CurrentOptimization() { return optimization; }
	//Profiling
		uintptr_t Allocations() { return allocations; }
		uintptr_t MemoryUsage() { return memoryusage; }
		uintptr_t MemoryUsagePeak() { return memoryusagepeak; }
		uintptr_t Capacity() { return heapsize; }
	//Release
		void Release();
private:
	//Support
		//////
		//Block
		class Block
		{
		public:
			Block *next;
			uintptr_t size; //Size of the USABLE MEMORY portion of the block
			uintptr_t alignment;
		};
		//////
	//Internal
		void ResetLists();
	//Inaccessible
		BlockAllocator(BlockAllocator &Rhs);
		BlockAllocator &operator=(BlockAllocator &Rhs);
	//Data
		char *heap;
		void (*deallocator)(void*);
		uintptr_t heapsize;
		Block *freelist;
		uintptr_t allocations;
		uintptr_t memoryusage;
		uintptr_t memoryusagepeak;
		Optimization optimization;
};
//////

}

#endif