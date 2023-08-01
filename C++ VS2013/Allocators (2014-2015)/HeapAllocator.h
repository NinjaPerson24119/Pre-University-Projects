#ifndef CTM_HEAPALLOCATOR_H
#define CTM_HEAPALLOCATOR_H

#include "Allocator.h"
#include <stdexcept>

namespace ctm
{

////////////////////////
//Heap Allocator
class HeapAllocator : Allocator
{
public:
	//Base
		HeapAllocator(char *Heap, void (*Deallocator)(void *), uintptr_t SizeBytes, bool OptimizeForMemory);
		~HeapAllocator();
	//Memory
		template<class Type = void> Type *Allocate(uintptr_t SizeBytes, uintptr_t Alignment = ALLOCATOR_ALIGNMENT);
		void Deallocate(void *Pointer);
		void Clear();
	//Profiling
		uintptr_t Capacity();
		uintptr_t MemoryUsed();
		uintptr_t MemoryPeak();
		uintptr_t Allocations();
private:
	//Inaccessible
		HeapAllocator(HeapAllocator &rhs);
		HeapAllocator &operator=(HeapAllocator &rhs);
	//Memory Block
	class memblock
	{
	public:
		memblock(): ptr(0), size(0) {}
		uintptr_t size; //Size of memory block
		memblock *ptr; //Pointer to next memory block
	};
	char *heap; //Heap
	memblock *freeblocks;
	void (*deallocator)(void *);
	uintptr_t heapsize;
	uintptr_t memoryused;
	uintptr_t memorypeak; 
	uintptr_t allocations;
	bool optimizeformemory;
};
////////////////////////

}

#endif