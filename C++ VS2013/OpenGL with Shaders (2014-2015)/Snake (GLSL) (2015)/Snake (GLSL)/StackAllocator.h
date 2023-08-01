#ifndef CTM_STACKALLOCATOR_H
#define CTM_STACKALLOCATOR_H

#include "Allocator.h"

namespace ctm
{

//////
//Stack Allocator
class StackAllocator : Allocator
{
public:
	//Base
		StackAllocator(char *Stack, uintptr_t StackSize, void (*Deallocator)(void*));
		~StackAllocator();
	//Memory
		void *Allocate(uintptr_t SizeBytes, uintptr_t Alignment = ALLOCATOR_ALIGNMENT);
		void Deallocate(uintptr_t Marker);
		uintptr_t Marker();
		void Clear();
	//Profiling
		uintptr_t Capacity();
		uintptr_t MemoryUsed();
		uintptr_t MemoryPeak();
		uintptr_t Allocations();
private:
	//Inaccessible
		StackAllocator(StackAllocator &Rhs);
		StackAllocator &operator=(StackAllocator &Rhs);
	char *stack;
	void (*deallocator)(void*);
	uintptr_t stacktop;
	uintptr_t stacksize;
	uintptr_t memoryused;
	uintptr_t memorypeak;
	uintptr_t allocations;
};
//////

}

#endif