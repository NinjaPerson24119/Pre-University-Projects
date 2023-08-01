#ifndef HEAPALLOCATOR_H
#define HEAPALLOCATOR_H

#include "../Base/Base.h"
#include "cAllocator.h"

namespace ctm
{

////////////////////////
//Memory block class
class memblock
{
public:
	memblock(): ptr(0), size(0) {}
	UINT32 size; //Size of memory block
	memblock *ptr; //Pointer to next memory block
};
////////////////////////

////////////////////////
//Heap allocator class
class heapallocator : public allocator
{
public:
	//System
		heapallocator(CHAR8 *iHeap, UINT32 iSizeBytes, UINT32 iAlignment, BOOL8 iAutoDestruct, BOOL8 iOptimizeForMemory); //AutoDestruct means that the allocator will delete the memory block provided upon its destruction
		~heapallocator();
	//Memory
		void clear(); //Clears the heap
		void *allocate(UINT32 nSizeBytes); //Allocates a specified amount of memory
		void deallocate(void *pointer); //Deallocates memory
	//Get
		UINT32 get_size() { return size; } //Returns the size of the heap
		UINT32 get_unused() { return size-memused; } //Returns the amount of memory left
		UINT32 get_used() { return memused; } //Returns the amount of memory in use
		UINT32 get_blocks(); //Returns the amount of blocks allocated
private:
	//Inaccessible
		heapallocator(heapallocator &rhs);
		heapallocator &operator=(heapallocator &rhs);
	CHAR8 *heap; //Heap
	memblock *freeblocks; //List of free blocks
	UINT32 size; //Size of heap
	UINT32 memused; //Memory used
	UINT32 alignment; //Heap alignment
	UINT32 blocks; //Blocks allocated
	BOOL8 autodestruct; //Delete data when allocator is destroyed?
	BOOL8 optimizeformemory; //Optimize for memory?
};
////////////////////////

}

#endif