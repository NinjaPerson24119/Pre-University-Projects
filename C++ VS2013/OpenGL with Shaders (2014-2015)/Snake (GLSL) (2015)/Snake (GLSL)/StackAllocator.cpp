#include "StackAllocator.h"
#include <stdexcept>

namespace ctm
{

//Constructor
StackAllocator::StackAllocator(char *Stack, uintptr_t StackSize, void (*Deallocator)(void*)):
stack(Stack),
deallocator(Deallocator),
stacktop(0),
stacksize(StackSize),
memoryused(0),
memorypeak(0),
allocations(0)
{}

//Destructor
StackAllocator::~StackAllocator()
{
	if(deallocator != nullptr)
		deallocator(stack);
}

//Allocate
void *StackAllocator::Allocate(uintptr_t SizeBytes, uintptr_t Alignment)
{
	//Store aligned address
	stacktop += (uintptr_t)&stack[stacktop] % Alignment;
	void *address = (void*)&stack[stacktop];
		
	//Check memory
	if(stacksize - stacktop < SizeBytes)
		throw std::runtime_error("StackAllocator - Allocation failed! Out of memory!\n");
		
	//Update stack top
	stacktop += SizeBytes;

	//Profiling
	++allocations;
	memoryused += SizeBytes;

	if(memoryused > memorypeak)
		memorypeak = memoryused;

	return address;
}

//Deallocate
void StackAllocator::Deallocate(uintptr_t Marker)
{
	stacktop = Marker;
	memoryused = Marker;
}

//Marker
uintptr_t StackAllocator::Marker()
{
	return stacktop;
}

//Clear
void StackAllocator::Clear()
{
	stacktop = 0;
	memoryused = 0;
	memorypeak = 0;
	allocations = 0;
}

//Capacity
uintptr_t StackAllocator::Capacity()
{
	return stacksize;
}

//Memory Used
uintptr_t StackAllocator::MemoryUsed()
{
	return memoryused;
}

//Memory Peak
uintptr_t StackAllocator::MemoryPeak()
{
	return memorypeak;
}

//Allocations
uintptr_t StackAllocator::Allocations()
{
	return allocations;
}

}